#pragma once

#include <map>
#include <memory>
#include "LibInterface.hh"

class Set4LibInterfaces : public std::map<std::string, LibInterface *>
{
private:
  /* data */
public:
  Set4LibInterfaces(/* args */);
  ~Set4LibInterfaces();
};

Set4LibInterfaces::Set4LibInterfaces(/* args */)
{
}

Set4LibInterfaces::~Set4LibInterfaces()
{
}
