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

//Проверки проверяющие бросок исключения помечены как - (искл)
//Проверки проверяющие корректность поведения, помечены как -  (корр)

//тесты для проверки конфига
    //проверка чтения правильного конфига (корр)
    void test_correct_config();

    //проверка чтения пустого конфига (искл)
    void test_void_config();

    //проверка конфига при неверном указании пути (искл)
    void test_uncorrect_rootdir();

    //проверка с неверным числом потоков (искл)
    void test_uncorrect_streams();

    //проверка с пустым блоком пар (искл)
    void test_null_pairs();

    //проверка с парами записанными в одну строку (корр)
    void test_oneline_pairs();

    //проверка с парами записанными как попало (корр)
    void test_strange_placed_pairs();

    //проверка поведения при отсутствии конфига (искл)
    void test_no_config_file();


//тесты для проверки replacer
    //проверка проведения замены при корректных условиях (корр)
    void test_correct_replace();

    //проверка когда в файле нечего заменять (корр)
    void test_nothing_to_replace();

    //проверка когда в файле встречаются не все искомые пары (корр)
    void test_only_one_of_pairs();

    //проверка случая когда файла для замен нет (искл)
    void test_no_file_to_replace();


//Тесты для парсера
    //проверка корректной работы (корр)
    void test_correct_parse();

    //проверка с корректным конфигом но без файлов по указанному пути (корр)
    void test_no_files();

    //проверка когда потоков больше чем файлов (корр)
    void test_too_much_streams();

    //проверка однопоточного исполнения (корр)
    void test_one_stream();

    //проверка работоспособности строк использующих различные символы (корр)
    void test_symbols();

    //проверка случая когда строка, на которую заменено значение, больше чем
    //строка которая была заменена (корр)
    void test_bigger();

    //Проверка случая когда заменяемая строка больше чем результирующая (корр)
    void test_smaller();

}
