#include "tests.hpp"

#define REMOVE_UNUSED(x) (void)x

namespace tests {

    void config_tests() {
        test_correct_config(); //проверка чтения правильного конфига
//        test_void_config(); //проверка чтения пустого конфига
//        test_uncorrect_rootdir(); //проверка конфига при неверном указании пути
//        test_uncorrect_streams(); //проверка с неверным числом потоков
//        test_null_pairs(); //проверка с пустым блоком пар
//        test_oneline_pairs(); //проверка с парами записанными в одну строку
//        test_strange_placed_pairs(); //проверка с парами записанными как попало
    }

    void replaser_tests() {
//        test_correct_replace(); //проверка проведения замены при корректных условиях
//        test_nothing_to_replace(); //проверка когда в файле нечего заменять
//        test_one_of_pairs(); //проверка когда в файле встречаются не все искомые пары
    }

    void parser_tests() {
//        test_correct_parse(); //проверка корректной работы
//        test_no_files(); //проверка с корректным конфигом но отсутствующими файлами по указанному пути
//        test_too_much_streams(); //проверка когда потоков больше чем файлов
//        test_one_stream(); //проверка однопоточного исполнения
    }

//    bool test_correct_config() {
//    }

}
