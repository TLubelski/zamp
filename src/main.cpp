#include <iostream>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "Preprocessor.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"

using namespace std;

int main(int argc, char **argv)
{
  string cmd = processCmdFile(argv[1]);
  cout << cmd;

  Set4LibInterfaces libman;

  libman["Move"] = new LibInterface("libInterp4Move.so", RTLD_LAZY);
  libman["Pause"] = new LibInterface("libInterp4Pause.so", RTLD_LAZY);
  libman["Rotate"] = new LibInterface("libInterp4Rotate.so", RTLD_LAZY);
  libman["Set"] = new LibInterface("libInterp4Set.so", RTLD_LAZY);

  for (auto &lib : libman)
  {
    cout << lib.second->getCmdName() << endl;
    lib.second->getCmd()->PrintSyntax();
    lib.second->getCmd()->PrintCmd();
  }
}
