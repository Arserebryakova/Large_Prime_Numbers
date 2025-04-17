#include <iostream>
#include <dixon/dixon.h>
#include <chrono>

namespace bmp = boost::multiprecision;

namespace  {
double Time() {
    static auto const gtb = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<double> >(
            std::chrono::high_resolution_clock::now() - gtb).count();
}
}

int main() {
    std::optional a = lpn::Dixon::findFactor(123456);
    std::cout << a->convert_to<int32_t>();
    return 0;
} // TODO: поправить мейн
