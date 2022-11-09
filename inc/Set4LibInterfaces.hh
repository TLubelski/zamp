#pragma once

#include <map>
#include <memory>

#include "LibInterface.hh"

class Set4LibInterfaces : public std::map<std::string, std::shared_ptr<LibInterface>>
{
private:
  /* data */
public:
  Set4LibInterfaces(/* args */){}
  ~Set4LibInterfaces(){}

  void addLib(std::string file)
  {
    auto libPtr = std::make_shared<LibInterface>(file.c_str());
    insert(std::pair<std::string, std::shared_ptr<LibInterface> >(libPtr->getCmdName(), libPtr));
  }
};
