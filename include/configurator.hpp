#pragma once

#include <string>
#include <regex>
#include <iostream>

#include "functions.hpp"
#include "exception.hpp"

namespace epx_test {
    using std::string;
    using std::move;
    using std::regex;
    using std::smatch;
    using std::regex_search;
    using epx_func::get_buffer_from;

    const string ROOT_REGULAR_STRING =
                 "root[[:blank:]]*=[^<>]*<{1}(.*)>{1}",
                 STREAMS_REGULAR_STRING =
                 "streams[[:blank:]]*=[^<>]*<{1}(.*)>{1}";

    struct Configurator {
        int maxStreamCount;
        string rootDirectory;

        Configurator(const string& filePath);
    };

}
