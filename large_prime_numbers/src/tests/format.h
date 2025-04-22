#pragma once

#include <filesystem>
#include <string>
#include "utils/LongInt.h"
#include "utils/Status.h"

namespace test_field {
std::filesystem::path buildFilename(const std::string &prefix);

std::vector<lpn::LongInt> readNumbers(const std::string &filename);

std::string statusToString(lpn::Status s);
}
