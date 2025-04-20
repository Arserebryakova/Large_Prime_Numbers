#include "format.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>
#include <fstream>
#include <filesystem>

namespace {
std::string getCurrentTimestamp() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    return oss.str();
}
}

namespace test_field {
std::filesystem::path buildFilename(const std::string &prefix) {
    namespace fs = std::filesystem;
    fs::path dir = fs::path("..") / "test_results";
    std::string filename = prefix + "_" + getCurrentTimestamp() + ".csv";
    return dir / filename;

}

std::vector<lpn::LongInt> readNumbers(const std::string &filename) {
    std::ifstream inputFile("../src/tests/static/" + filename + ".txt");
    std::string numberStr;
    std::vector<lpn::LongInt> numbers;
    while (inputFile >> numberStr) {
        numbers.emplace_back(numberStr);
    }
    return numbers;
}
}
