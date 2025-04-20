#pragma once

#include <filesystem>
#include <string>
#include "utils/LongInt.h"

namespace test_field {
std::filesystem::path buildFilename(const std::string &prefix);

std::vector<lpn::LongInt> readNumbers(const std::string &filename);
}
