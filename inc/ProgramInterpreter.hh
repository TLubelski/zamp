#pragma once

#include "Scene.hh"
#include "Set4LibInterfaces.hh"
#include "FileParser.hh"
#include "Interp4Command.hh"
#include "SocketClient.hh"
#include <vector>
#include <sstream>

using std::cout;
using std::endl;
using std::string;

class ProgramInterpreter
{
private:
  Scene _Scn;
  Set4LibInterfaces _LibMan;
  Configuration _Config;
  SocketClient sock;
  std::vector<Interp4Command *> _Cmds;

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
    sock.Send("Clear\n");

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
           << " Trans_m=" << cube.Trans_m
           << " RGB=" << cube.RGB
           << "\n";

      cout << strm.str();

      sock.Send(strm.str().c_str());
    }
  }

  void parseCmds(string cmdFile)
  {
    std::stringstream cmdStream(processCmdFile(cmdFile));

    while (!cmdStream.eof())
    {
      string name;
      cmdStream >> name;
      if (name.length() > 1)
      {
        _Cmds.push_back(_LibMan[name]->getCmd());
        _Cmds.back()->ReadParams(cmdStream);
      }
      // if (cmdStream.fail())
      // {
      //   // cout << "Command parse error!" << endl;
      //   // exit(1);
      // }
    }
  }

  void printCmds()
  {
    cout << "Odczytane komendy: " << endl;
    int i = 1;
    for (Interp4Command *cmd : _Cmds)
    {
      cout << i++ << ". ";
      cmd->PrintCmd();
    }
  }

  void execCmds()
  {
    for (Interp4Command *cmd : _Cmds)
    {
    }
  }

  void run(string cmdFile)
  {
    parseConfig();
    loadLibs();
    printLibs();
    parseCmds(cmdFile);
    printCmds();

    sock.Open();

    prepareScene();

    execCmds();

    sock.Close();
  }
};
