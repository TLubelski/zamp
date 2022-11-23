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
      cout << "Blad!" << endl;
      exit(1);
    }
  }

  void loadLibs()
  {
    for(const string& libName : _Config.getLibs())
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
    for(const CubeConfig& cube : _Config.getCubes())
    {
      std::shared_ptr<MobileObj> obj;
      obj->SetName(cube.Name.c_str());
      obj->SetPosition_m(cube.Trans_m);
      // obj->
    }
  }

  void parseCmds(string cmdFile)
  {
    std::stringstream cmdStream(processCmdFile(cmdFile));

    while (!cmdStream.eof())
    {
      string name;
      cmdStream >> name;
      if (name.length() > 0)
      {
        _Cmds.push_back(_LibMan[name]->getCmd());
        _Cmds.back()->ReadParams(cmdStream);
      }
      if (cmdStream.fail())
      {
        cout << "Blad!" << endl;
        exit(1);
      }
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
  }

  void run(string cmdFile)
  {
    parseConfig();
    loadLibs();

    parseInput(cmdFile);

    sock.Open();
    
    execCmds();
  }
};
