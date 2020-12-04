#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <ostream>
#include <string>
#include <filesystem>
#include <atomic>
#include <chrono>

#include "replace_notificator.hpp"
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
    using std::atomic;
    using std::chrono::steady_clock;
    using epx_func::get_buffer_from;
    using epx_func::write_buffer_to_file;

    class Replacer {
    private:
        unordered_map<string, string> pairs;
        unordered_set<char> searchSymbols;
        unsigned long maxSearchSize;
        ostream* outputStream;
    public:
        Replacer();
        Replacer(Configurator& config);

        void replace_in (
                const path& filePath,
                atomic<unsigned long>* streamCounter
                ) const;
    };

}
