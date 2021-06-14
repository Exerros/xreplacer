#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>
#include <forward_list>
#include <atomic>
#include <memory>
#include <fstream>

#include "pugixml.hpp"

#include "interface/ireplacer.hpp"
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
using pairs_map = std::unordered_map<string, string>;

//------------------------------------------------------------------------------
#pragma pack(push, 4)
class FileDataReplacer : interface::ReplacerInterface<forward_list<path>> {
private:
    pairs_map pairs;
    shared_ptr<atomic<unsigned long long>> replace_counter;
    shared_ptr<atomic<unsigned int>> stream_counter;
    int max_stream_count;

public:
    FileDataReplacer(const xml_node& config);
    ~FileDataReplacer() override = default ;

    unsigned long long replase(forward_list<path>& object) const override;

private:
    string get_buffer_from(const path& filePath) const;
    void write_buffer_to_file(string& buffer, const path& filePath) const;
    unsigned long long replace_in_file(const path& file_path) const;
};
#pragma pack(pop)

}
}
