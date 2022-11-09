#pragma once

#include "Scene.hh"
#include "Set4LibInterfaces.hh"
#include "FileParser.hh"
#include "Interp4Command.hh"
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
  std::vector<Interp4Command *> _Cmds;

public:
  ProgramInterpreter() {}
  ~ProgramInterpreter() {}

  void loadLibs()
  {
    _LibMan.addLib("libInterp4Move.so");
    _LibMan.addLib("libInterp4Pause.so");
    _LibMan.addLib("libInterp4Rotate.so");
    _LibMan.addLib("libInterp4Set.so");
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

  void parseConfig()
  {
    cout << "Czytanie xml " << ReadFile("config/config.xml", _Config) << endl;
  }

  void parseInput(string cmdFile)
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
    }
  }

  void printCommands()
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
};
