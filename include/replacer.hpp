#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <fstream>
#include <cstdint>
#include <string>
#include <regex>
#include <iostream>

namespace epx_test {

    using std::unordered_map;
    using std::ifstream;
    using std::ofstream;
    using std::string;
    using std::regex;
    using std::pair;
    using std::smatch;
    using std::move;
    using std::regex_search;
    using std::regex_replace;
    using std::unordered_set;
    using std::cout;
    using std::flush;

    const string UPPER_REGULAR_STRING = "[^<>]*<{1}([^<>]*)>{1}[^<>]*",
                 LOWER_REGULAR_STRING =
                 "\"{1}([^\"]*)(\"[[:blank:]]*=[[:blank:]]*\"){1}([^\"]*)\"{1}";

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
    private:
        char* get_buf_and_close(const string& filePath) const;
    };

}
