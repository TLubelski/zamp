#pragma once

#include "Scene.hh"
#include "Set4LibInterfaces.hh"
#include "FileParser.hh"
#include "Interp4Command.hh"
#include "SocketClient.hh"
#include <vector>
#include <sstream>
#include <queue>
#include <thread>

using std::cout;
using std::endl;
using std::string;

class ProgramInterpreter
{
private:
  Scene _Scn;
  Set4LibInterfaces _LibMan;
  Configuration _Config;
  SocketClient _Sock;
  std::vector<std::vector<Interp4Command *>> _Cmds;
  std::queue<std::thread> _ThreadQueue;

public:
  ProgramInterpreter() {}
  ~ProgramInterpreter() {}

  void parseConfig()
  {
    cout << "Czytanie xml ..." << endl;
    if (!processConfig("config/config.xml", _Config))
    {
      // cout << "Config parser error!" << endl;
      exit(1);
    }
  }

  void loadLibs()
  {
    for (const string &libName : _Config.getLibs())
      _LibMan.addLib(libName);
  }

  void printLibs()
  {
    cout << "Zaladowane wtyczki: " << endl;
    int i = 1;
    for (auto &lib : _LibMan)
    {
      cout << i++ << ".";
      lib.second->getCmd()->PrintSyntax();
    }
  }

  void prepareScene()
  {
    _Sock.Send("Clear\n");

    for (const CubeConfig &cube : _Config.getCubes())
    {
      auto obj = std::make_shared<MobileObj>();
      obj->SetName(cube.Name.c_str());
      obj->SetPosition_m(cube.Trans_m);
      obj->SetAng_Roll_deg(cube.RotXYZ_deg[0]);
      obj->SetAng_Pitch_deg(cube.RotXYZ_deg[1]);
      obj->SetAng_Yaw_deg(cube.RotXYZ_deg[2]);

      _Scn.AddMobileObj(obj);

      std::stringstream strm;

      strm << "AddObj"
           << " Name=" << cube.Name
           << " Shift=" << cube.Shift
           << " Scale=" << cube.Scale
           << " RotXYZ_deg=" << cube.RotXYZ_deg
           << " Trans_m=" << cube.Trans_m
           << " RGB=" << cube.RGB
           << "\n";

      cout << strm.str();

      _Sock.Send(strm.str().c_str());
    }
  }

  void parseCmds(string cmdFile)
  {
    std::stringstream cmdStream(processCmdFile(cmdFile));
    bool parallel = false;
    std::vector<Interp4Command *> cmds_temp;

    while (!cmdStream.eof())
    {
      string name;
      cmdStream >> name;
      if (name.length() > 1)
      {
        if (name == "Begin_Parallel_Actions")
        {
          parallel = true;
          cmds_temp.clear();
        }
        else if (name == "End_Parallel_Actions")
        {
          parallel = false;
          _Cmds.push_back(cmds_temp);
        }
        else
        {
          if (parallel)
          {
            cmds_temp.push_back(_LibMan[name]->getCmd());
            cmds_temp.back()->ReadParams(cmdStream);
          }
          else
          {
            cmds_temp.clear();
            cmds_temp.push_back(_LibMan[name]->getCmd());
            cmds_temp.back()->ReadParams(cmdStream);
            _Cmds.push_back(cmds_temp);
          }
        }
      }
    }
  }

  void printCmds()
  {
    cout << "Odczytane komendy: " << endl;
    int i = 1;
    for (std::vector<Interp4Command *> &cmds : _Cmds)
    {
      for (Interp4Command *cmd : cmds)
      {
        cout << i++ << ". ";
        cmd->PrintCmd();
      }
    }
  }

  void execCmds()
  {
    for (std::vector<Interp4Command *> &cmds : _Cmds)
    {
      for (Interp4Command *cmd : cmds)
        _ThreadQueue.push(std::thread(&Interp4Command::ExecCmd, cmd, &_Scn, &_Sock));

      while (!_ThreadQueue.empty())
      {
        _ThreadQueue.front().join();
        _ThreadQueue.pop();
      }
    }
  }

  void run(string cmdFile)
  {
    parseConfig();
    loadLibs();
    printLibs();
    parseCmds(cmdFile);
    printCmds();

    _Sock.Open();

    prepareScene();

    execCmds();

    _Sock.Close();
  }
};
