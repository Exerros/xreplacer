#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <ostream>
#include <string>
#include <filesystem>

#include "configurator.hpp"
#include "functions.hpp"
#include "exception.hpp"

namespace epx_test {
    using std::unordered_map;
    using std::unordered_set;
    using std::ostream;
    using std::string;
    using std::pair;
    using std::filesystem::path;
    using epx_func::get_buffer_from;
    using epx_func::write_buffer_to_file;

    constexpr auto
    START_MSG = "Replacement started in file: ",
    FINISH_MSG = "Replacement finished in file: ",
    COUNT_MSG = ". Number of changes is ";

    class Replacer {
    private:
        unordered_map<string, string> pairs;
        unordered_set<char> searchSymbols;
        unsigned long maxSearchSize;
        ostream* outputStream;
    public:
        Replacer();
        Replacer(Configurator& config);

        void replace_in (const path& filePath) const;
        void fast_replace_in (const path& filePath) const;

        void notify_started(const path& filePath) const;
        void notify_finished(
                const path& filePath,
                unsigned long repCount = 0
        ) const;
    };

}
