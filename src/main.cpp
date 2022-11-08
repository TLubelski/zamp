#include <iostream>
#include "ProgramInterpreter.hh"


int main(int argc, char **argv)
{
  ProgramInterpreter interp;
  std::cout << endl;

  interp.loadLibs();
  interp.printLibs();

  std::cout << endl;

  interp.parseConfig();

  std::cout << endl;
  
  interp.parseInput(argv[1]);
  interp.printCommands();

  return 0;
}
