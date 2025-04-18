#include "format.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>
#include <fstream>


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

std::vector<lpn::LongInt> readNumbers(const std::string& filename){
    std::ifstream inputFile("../src/tests/static/"+filename+".txt");
    std::string numberStr;
    std::vector<lpn::LongInt> numbers;
    while (inputFile >> numberStr) {
        numbers.emplace_back(numberStr);
    }
    return numbers;
}
