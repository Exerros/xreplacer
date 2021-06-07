#pragma once

#include <string>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <ostream>
#include <filesystem>

#include "functions.hpp"
#include "exception.hpp"

namespace xrep {
    namespace fs = std::filesystem;
    using std::string;
    using std::unordered_map;
    using std::unordered_set;
    using std::regex;
    using std::regex_search;
    using std::smatch;
    using std::ostream;
    using xrep_func::get_buffer_from;
    using xrep_func::create_regex_string;

    const string
    ROOT_REGULAR_STRING = "root:[[:blank:]]*\"{1}(.*)\"{1};",
    STREAMS_REGULAR_STRING = "streams:[[:blank:]]*([[:digit:]]*);",
    REPLACE_REGULAR_STRING = "replace:[[:blank:]]*([^;]*);{1}",
    PAIR_REGULAR_STRING =
                 "\"{1}([^\"]*)(\"[[:blank:]]*=[[:blank:]]*\"){1}([^\"]*)\"{1}",
    DELIMITER(80, '-'),
    FILLER(37, '-'),
    TITLE = FILLER + "PARSER" + FILLER;

    constexpr unsigned long
    ROOT_MATCH_INDEX = 1,
    STREAMS_MATCH_INDEX = 1,
    PAIRS_MATCH_INDEX = 1;

//Данный класс занимается разбором файла конфигурации и в последствии отдает
//полученную информацию классам Replacer и Parser. Также этот класс выводит
//полученную информацию в переданный поток
    class Configurator {
    public:
        //поля описаны как публичные с целью дальнейшего перемещения значений
        //parser data
        unsigned long maxStreamCount;
        fs::path rootDirectory;
        //replacer data
        unordered_map<string, string> pairs;
        ostream* outputStream;

//Все действия данного класса выполняются в конструкторе: и парсинг, и вывод.
        Configurator(const fs::path& filePath, ostream* output);

//Функция для вывода информации
        void show_data() const;
//Функция поиска необходимой информации в буфере.
    private:
        decltype(auto) search(
                const string& regStr,
                const string& buffer,
                const unsigned long index
                ) const;
    };

}
