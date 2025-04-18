#pragma once
#include <string>
#include "utils/LongInt.h"

std::string getCurrentTimestamp();
std::string buildFilename(const std::string& prefix);
std::vector<lpn::LongInt> readNumbers(const std::string& filename);
