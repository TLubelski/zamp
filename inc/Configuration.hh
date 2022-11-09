#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <map>
#include "Vector3D.hh"

using std::string;

class Configuration
{
  struct Cube
  {
    Vector3D Shift;
    Vector3D Scale;
    Vector3D RotXYZ_deg;
    Vector3D Trans_m;
  };

public:
  std::vector<string> libs;

  void parseLib(string libName)
  {
    libs.push_back(libName);
  }

  std::map<string, Cube> cubes;
  
  void parseCube(string cubeName, string sScale, string sRGB)
  {
    
  }

};

#endif
