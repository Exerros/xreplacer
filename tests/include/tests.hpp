#pragma once

#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <atomic>
#include <functional>
#include <vector>
#include <thread>
#include <chrono>

#include "parser.hpp"
#include "functions.hpp"
#include "tests_functions.hpp"

namespace tests {
    using std::chrono_literals::operator""ms;
    using std::this_thread::sleep_for;
    using std::unordered_map;
    using std::string;

//Функции запускающие ряды тестов.
    void config_tests();
    void replacer_tests();
    void parser_tests();

//тесты для проверки конфига
    void test_correct_config();
    void test_void_config();
    void test_uncorrect_rootdir();
    void test_uncorrect_streams();
    void test_null_pairs();
    void test_oneline_pairs();
    void test_strange_placed_pairs();
    void test_no_config_file();

//тесты для проверки replacer
    void test_correct_replace();
    void test_nothing_to_replace();
    void test_only_one_of_pairs();
    void test_no_file_to_replace();

//Тесты для парсера
    void test_correct_parse();
    void test_no_files();
    void test_too_much_streams();
    void test_one_stream();
    void test_symbols();

}
