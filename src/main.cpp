#include <iostream>
#include "ProgramInterpreter.hh"


int main(int argc, char **argv)
{
  ProgramInterpreter interp;
  
  interp.parseConfig();
  interp.loadLibs();
  interp.printLibs();
  interp.prepareScene();
  interp.parseCmds(argv[1]);
  interp.printCmds();
  interp.execCmds();

  return 0;
}
