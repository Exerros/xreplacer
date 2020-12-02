#pragma once

#include <unordered_map>
#include <utility>
#include <fstream>
#include <cstdint>
#include <string>
#include <regex>

namespace epx_test {

    using std::unordered_map;
    using std::ifstream;
    using std::ofstream;
    using std::string;
    using std::regex;
    using std::pair;
    using std::smatch;
    using std::getline;
    using std::regex_search;

    const string upper_regular_string = "[^<>]*<{1}([^<>]*)>{1}[^<>]*",
                 lower_regular_string =
                 "\"{1}([^\"]*)(\"[[:blank:]]*=[[:blank:]]*\"){1}([^\"])*\"{1}";

    class Replacer {
    private:
        unordered_map<string, string> pairs;
    public:
        Replacer(const string& filePath);
        pair<uint32_t, string> operator() (const string& filePath) const;
    };

}
