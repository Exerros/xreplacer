#pragma once

#include <unordered_map>
#include <cassert>
#include <string>
#include <sstream>

#include "parser.hpp"
#include "tests_functions.hpp"

namespace tests {
    using std::unordered_map;
    using std::string;

//Функции запускающие ряды тестов.
    void config_tests();
    void replaser_tests();
    void parser_tests();

//тесты для проверки конфига
    bool test_correct_config();
    bool test_void_config();
    bool test_uncorrect_rootdir();
    bool test_uncorrect_streams();
    bool test_null_pairs();
    bool test_oneline_pairs();
    bool test_strange_placed_pairs();

//тесты для проверки replacer
    bool test_correct_replace();
    bool test_nothing_to_replace();
    bool test_one_of_pairs();

//Тесты для парсера
    bool test_correct_parse();
    bool test_no_files();
    bool test_too_much_streams();
    bool test_one_stream();

}
