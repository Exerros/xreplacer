#include "parser.hpp"

#include <filesystem>
#include <string>
#include <iostream>
#include <chrono>

using namespace epx_test;
namespace fs = std::filesystem;

void fill(const fs::path& p) {
    std::ofstream file(p);
    for(int i = 0; i < 10000; ++i) {
        file << "<first> <second> <third> \n";
    }
    file.close();
}

int main() {
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
    path a("dir/a/a.txt"); fill(a);
    path b("dir/a/b.txt"); fill(b);
    path c("dir/a/c.txt"); fill(c);
    path d("dir/a/b/d.txt"); fill(d);
    path e("dir/e.txt"); fill(e);

    Parser p(configPath, &std::cout);
    p.replace_data();

    return 0;
}
