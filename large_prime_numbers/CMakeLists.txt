cmake_minimum_required(VERSION 3.25)
project(lpn)


include(FetchContent)

set(BOOST_INCLUDE_LIBRARIES multiprecision)
set(BOOST_ENABLE_CMAKE ON)

message(STATUS "Downloading and extracting boost library sources. This will take some time...")
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
        Boost
            URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.7z # downloading a zip release speeds up the download
        USES_TERMINAL_DOWNLOAD TRUE
        GIT_PROGRESS TRUE
        DOWNLOAD_NO_EXTRACT FALSE
)
FetchContent_MakeAvailable(Boost)

message(STATUS "Downloading and extracting gtest sources. This will take some time...")
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
        USES_TERMINAL_DOWNLOAD TRUE
        GIT_PROGRESS TRUE
        DOWNLOAD_NO_EXTRACT FALSE
)
FetchContent_MakeAvailable(googletest)

include_directories(src)

# Example executable
add_executable(lpn
        src/main.cpp

        src/trial_division/trial_division.cpp
        src/sieve_of_eratosthenes/sieve_of_eratosthenes.cpp
        src/fermat/fermat.cpp
        src/miller-rabin/miller-rabin.cpp
        src/pollard/pollard.cpp
        src/utils/big_integer_arithmetics.cpp
        src/main.cpp
        src/dixon/dixon.cpp
)
target_link_libraries(lpn PRIVATE Boost::multiprecision)
target_compile_features(lpn PRIVATE cxx_std_20)


# Подрубка тестов
enable_testing()
add_executable(lpn_tests
        src/trial_division/trial_division.cpp
        src/sieve_of_eratosthenes/sieve_of_eratosthenes.cpp
        src/fermat/fermat.cpp
        src/miller-rabin/miller-rabin.cpp
        src/pollard/pollard.cpp
        src/dixon/dixon.cpp

        src/utils/big_integer_arithmetics.cpp

        src/tests/format.cpp
        src/tests/main_tests.cpp
        src/tests/test_time_trial_division.cpp
        src/tests/test_time_dixon.cpp
        src/tests/test_time_miller-rabin.cpp
        src/tests/test_time_pollard.cpp
        src/tests/test_time_sieve.cpp
        src/tests/test_time_fermat.cpp
)
add_test(NAME lpn_tests COMMAND lpn_tests)
target_link_libraries(lpn_tests PRIVATE Boost::multiprecision gtest gtest_main)
target_compile_features(lpn_tests PRIVATE cxx_std_20)
