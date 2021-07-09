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
#include <deque>

#include "pugixml.hpp"

#include "interface/ireplacer.hpp"
#include "interface/ilogger.hpp"
#include "exception.hpp"

namespace xrep {

using std::filesystem::file_size;
using std::this_thread::sleep_for;
using std::chrono_literals::operator""ms;

//------------------------------------------------------------------------------
#pragma pack(push, 4)
class FileDataReplacer : public interface::ReplacerInterface {
    using duration_t = std::chrono::duration<long, std::ratio<1, 1000>>;
    using pairs_map = std::unordered_map<std::string, std::string>;
    using counter_ptr = std::shared_ptr<std::atomic<unsigned int>>;
    using fs_path = std::filesystem::path;

private:
    pairs_map pairs;
    counter_ptr stream_counter;
    int max_stream_count;
    duration_t threading_sleep_time;

public:
    FileDataReplacer(const pugi::xml_node& config);
    ~FileDataReplacer() override = default ;

    void replase(std::forward_list<fs_path>& object) const override;

private:
    static std::string get_buffer_from(const fs_path& filePath);

    static void
    write_buffer_to_file(const std::string& buffer, const fs_path& filePath);

    static void replace_in_file(
            const fs_path& file_path,
            const pairs_map& pairs,
            counter_ptr stream_counter);
};
#pragma pack(pop)

}
