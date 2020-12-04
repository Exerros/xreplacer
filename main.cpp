#include <filesystem>
#include <string>
#include <iostream>
#include <chrono>
#include <future>

#include "cmake_variables.hpp"
#include "parser.hpp"
#ifdef DEBUG
//ТЕСТЫ
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

int main() {
#ifdef DEBUG
    std::cout << "DEBUG" << std::endl;
#endif
    fs::path configPath("config.txt");

    std::ofstream config(configPath);
    config << "root: \"dir\";\n";
    config << "streams: 10;\n";
    config << "replace:\n";
    config << "\"<first>\" = \"1\"";
    config << "\"<second>\" = \"2\"";
    config << "\"<third>\" = \"3\"";
    config << ";\n";
    config.close();

    fs::create_directories("dir/a/b");
    path a1("dir/a/a1.txt"); fill(a1);
    path a2("dir/a/a2.txt"); fill(a2);
    path a3("dir/a/a3.txt"); fill(a3);
    path a4("dir/a/a4.txt"); fill(a4);
    path a5("dir/a/a5.txt"); fill(a5);
    path b1("dir/a/b1.txt"); fill(b1);
    path b2("dir/a/b2.txt"); fill(b2);
    path b3("dir/a/b3.txt"); fill(b3);
    path b4("dir/a/b4.txt"); fill(b4);
    path b5("dir/a/b5.txt"); fill(b5);
    path c1("dir/a/c1.txt"); fill(c1);
    path c2("dir/a/c2.txt"); fill(c2);
    path c3("dir/a/c3.txt"); fill(c3);
    path c4("dir/a/c4.txt"); fill(c4);
    path c5("dir/a/c5.txt"); fill(c5);
    path d1("dir/a/b/d1.txt"); fill(d1);
    path d2("dir/a/b/d2.txt"); fill(d2);
    path d3("dir/a/b/d3.txt"); fill(d3);
    path d4("dir/a/b/d4.txt"); fill(d4);
    path d5("dir/a/b/d5.txt"); fill(d5);
    path e1("dir/e1.txt"); fill(e1);
    path e2("dir/e2.txt"); fill(e2);
    path e3("dir/e3.txt"); fill(e3);
    path e4("dir/e4.txt"); fill(e4);
    path e5("dir/e5.txt"); fill(e5);

    Parser p(configPath, &std::cout);
    p.replace_data();

    return 0;
}
