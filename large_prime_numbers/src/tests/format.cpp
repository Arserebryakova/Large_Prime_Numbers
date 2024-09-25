#include "format.h"
#include <iomanip>
#include <ctime>
#include <sstream>


std::string getCurrentTimestamp() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    return oss.str();
}

std::string buildFilename(const std::string& prefix) {
    return "../test_results/" + prefix + "_" + getCurrentTimestamp() + ".csv";
}

