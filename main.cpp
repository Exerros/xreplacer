#include <filesystem>
#include <string>
#include <iostream>
#include <chrono>
#include <future>

#include "cmake_variables.hpp"
#include "parser.hpp"

#ifdef BUILD_TESTS
    #include "tests.hpp"
#endif

using namespace epx_test;
namespace fs = std::filesystem;

void fill(const fs::path& p) {
    std::ofstream file(p);
    for(int i = 0; i < 10000; ++i) {
        file << "<first> <second> <third>\n";
    }
    file.close();
}

#ifdef BUILD_TESTS
int main() {
    tests::config_tests();
    tests::replacer_tests();
    tests::parser_tests();
#else
int main(int argc, char** argv) {
    fs::path configPath;
    if(argc > 1) {
        configPath = argv[1];
    } else {
        configPath("config.txt")
    }

    Parser p(configPath, &std::cout);
    p.replace_data();
#endif

    return 0;
}
