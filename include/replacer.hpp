#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>
#include <forward_list>
#include <atomic>
#include <memory>
#include <fstream>
#include <regex>
#include <thread>
#include <chrono>

#include "pugixml.hpp"

#include "interface/ireplacer.hpp"
#include "interface/ilogger.hpp"
#include "exception.hpp"

namespace xrep {
namespace replacer {

using pugi::xml_node;
using std::string;
using std::forward_list;
using std::filesystem::path;
using std::filesystem::file_size;
using std::shared_ptr;
using std::atomic;
using std::ifstream;
using std::ofstream;
using std::regex;
using std::this_thread::sleep_for;
using std::chrono_literals::operator""ms;
using pairs_map = std::unordered_map<string, string>;
using duration_t = std::chrono::duration<long, std::ratio<1, 1000>>;
using logger_ptr = shared_ptr<interface::LoggerInterface<string>>;

//------------------------------------------------------------------------------
#pragma pack(push, 4)
class FileDataReplacer : interface::ReplacerInterface<forward_list<path>> {
private:
    pairs_map pairs;
    int max_stream_count;
    duration_t threading_sleep_time;
    logger_ptr logger;

public:
    FileDataReplacer(const xml_node& config);
    ~FileDataReplacer() override = default ;

    void replase(forward_list<path>& object) const override;

private:
    static string get_buffer_from(const path& filePath);
    static void write_buffer_to_file(const string& buffer, const path& filePath);
    static void replace_in_file(
            const path& file_path,
            const pairs_map& pairs,
            shared_ptr<atomic<unsigned int>> stream_counter);
    void set_logger(logger_ptr l);
};
#pragma pack(pop)

}
}
