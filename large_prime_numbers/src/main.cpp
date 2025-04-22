#include <cstdlib>
#include <gtest/gtest.h>
#include "utils/Except.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result;
    try {
        result = RUN_ALL_TESTS();
    } catch (...) {
        except::react();
        result = EXIT_FAILURE;
    }
    return result;
}
