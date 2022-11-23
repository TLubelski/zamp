#include <iostream>
#include "ProgramInterpreter.hh"


int main(int argc, char **argv)
{
  ProgramInterpreter interp;
  std::cout << endl;
  interp.run(argv[1]);
  return 0;
}
