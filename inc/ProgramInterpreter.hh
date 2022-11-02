#pragma once

#include "Scene.hh"
#include "Set4LibInterfaces.hh"

class ProgramInterpreter
{
private:
  Scene _Scn;
  Set4LibInterfaces _LibManager;

public:
  ProgramInterpreter();
  ~ProgramInterpreter();
};

ProgramInterpreter::ProgramInterpreter()
{
}

ProgramInterpreter::~ProgramInterpreter()
{
}
