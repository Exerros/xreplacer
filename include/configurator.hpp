#pragma once

#include <string>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <ostream>
#include <filesystem>

#include "functions.hpp"
#include "exception.hpp"

namespace epx_test {
    using std::string;
    using std::unordered_map;
    using std::unordered_set;
    using std::regex;
    using std::regex_search;
    using std::smatch;
    using std::ostream;
    using std::filesystem::path;
    using epx_func::get_buffer_from;

    const string
    ROOT_REGULAR_STRING = "root[[:blank:]]*=[^\"]*\"{1}(.*)\"{1}",
    STREAMS_REGULAR_STRING = "streams[[:blank:]]*=[^\"]*\"{1}(.*)\"{1}",
    REPLACE_REGULAR_STRING = "replace[[:blank:]]*=[^<>]*<{1}([^<>]*)>{1}",
    PAIR_REGULAR_STRING =
                 "\"{1}([^\"]*)(\"[[:blank:]]*=[[:blank:]]*\"){1}([^\"]*)\"{1}",
    DELIMITER(80, '-'),
    FILLER(34, '-');

    constexpr unsigned long
    ROOT_MATCH_INDEX = 1,
    STREAMS_MATCH_INDEX = 1,
    PAIRS_MATCH_INDEX = 1;

    class Configurator {
    public:
        //parser data
        unsigned long maxStreamCount;
        path rootDirectory;
        //replacer data
        unordered_map<string, string> pairs;
        unordered_set<char> searchSymbols;
        unsigned long maxSearchSize;
        ostream* outputStream;

        Configurator(const path& filePath, ostream* output);

        void show_data() const;
    private:
        decltype(auto) search(
                const string& regStr,
                const string& buffer,
                const unsigned long index
        ) const;
    };

}
