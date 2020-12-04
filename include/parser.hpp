#pragma once

#include <filesystem>
#include <future>
#include <string>
#include <vector>
#include <ostream>
#include <algorithm>

#include "configurator.hpp"
#include "replacer.hpp"
#include "exception.hpp"

namespace epx_test {
    using std::string;
    using std::vector;
    using std::ostream;
    using std::filesystem::path;

    using fs_iterator = std::filesystem::recursive_directory_iterator;

    class Parser {
    private:
        Replacer replacer;
        vector<path> files;
        unsigned long maxStreamCount;
    public:
        Parser(const path& configPath, ostream* output);
        void parse() const;
    private:
    };

}
