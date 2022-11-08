#pragma once
#include <string>
#include "Configuration.hh"

std::string processCmdFile(std::string filename);

bool ReadFile(const char* sFileName, Configuration &rConfig);