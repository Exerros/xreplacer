#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <cstdint>
#include <string>
#include <regex>
#include <iostream>

#include "functions.hpp"
#include "exception.hpp"

namespace epx_test {
    using std::unordered_map;
    using std::string;
    using std::regex;
    using std::smatch;
    using std::pair;
    using std::move;
    using std::regex_search;
    using std::regex_replace;
    using std::unordered_set;
    using std::cout;
    using std::flush;
    using epx_func::get_buffer_from;
    using epx_func::write_buffer_to_file;

    const string FIRST_REGULAR_STRING =
                 "replace[[:blank:]]*=[^<>]*<{1}([^<>]*)>{1}",
                 SECOND_REGULAR_STRING =
                 "\"{1}([^\"]*)(\"[[:blank:]]*=[[:blank:]]*\"){1}([^\"]*)\"{1}";

    //Данный класс занимается заменами в файлах переданных ему в виде пути
    //Основные коментарии в .cpp файле
    class Replacer {
    private:
        unordered_map<string, string> pairs;
        size_t maxSearchSize;
        unordered_set<char> searchSymbols;
    public:
        Replacer(const string& filePath);

        pair<uint32_t, string> replace_in (const string& filePath) const;
        pair<uint32_t, string> fast_replace_in (const string& filePath) const;
        void show_pairs() const;
    };

}
