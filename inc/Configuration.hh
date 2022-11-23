#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <vector>
#include "Vector3D.hh"

using std::string;

struct CubeConfig
{
  string Name;
  Vector3D Shift;
  Vector3D Scale;
  Vector3D RotXYZ_deg;
  Vector3D Trans_m;
  Vector3D RGB;

  CubeConfig()
  {
    Name = "cube";

    for(int i = 0; i<3; i++)
    {
      Shift[i] = 0;
      Scale[i] = 1;
      RotXYZ_deg[i] = 0;
      Trans_m[i] = 0;
      RGB[i] = 128;
    }
  }
};

class Configuration
{
  std::vector<string> libs;
  std::vector<CubeConfig> cubes;
public:

  const std::vector<string>& getLibs() const {return libs; };
  const std::vector<CubeConfig>& getCubes() const {return cubes; };

  std::vector<string>& modLibs() {return libs; }
  std::vector<CubeConfig>& modCubes() { return cubes; } 

};

#endif
