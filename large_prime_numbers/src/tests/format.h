#pragma once
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

std::string getCurrentTimestamp();
std::string buildFilename(const std::string& prefix);
std::vector<boost::multiprecision::cpp_int> readNumbers(const std::string& filename);
