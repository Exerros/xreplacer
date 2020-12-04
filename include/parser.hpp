#pragma once

#include <filesystem>
#include <future>
#include <string>
#include <vector>
#include <ostream>
#include <algorithm>
#include <atomic>

#include "configurator.hpp"
#include "replacer.hpp"
#include "exception.hpp"

namespace epx_test {
    using std::string;
    using std::vector;
    using std::ostream;
    using std::filesystem::path;
    using std::filesystem::is_directory;
    using fs_iterator = std::filesystem::recursive_directory_iterator;
    namespace fs = std::filesystem;
    using std::atomic;

    class Parser {
    private:
        Replacer replacer;
        vector<path> files;
        unsigned long maxStreamCount;
        ostream* outputStream;
    public:
        Parser(const path& configPath, ostream* output);
        void show_paths() const;
        void replace_data() const;
    private:
    };

}
