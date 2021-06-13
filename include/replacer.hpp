#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>
#include <forward_list>
#include <atomic>
#include <memory>

#include "pugixml.hpp"

#include "interface/ireplacer.hpp"
#include "exception.hpp"

namespace xrep {
namespace replacer {

using pugi::xml_node;
using std::string;
using std::forward_list;
using std::filesystem::path;
using std::shared_ptr;
using std::atomic;
using pairs_map = std::unordered_map<string, string>;

//------------------------------------------------------------------------------
class FileDataReplacer : interface::ReplacerInterface<forward_list<path>> {
private:
    int stream_count = 1;
    pairs_map pairs;
    shared_ptr<atomic<unsigned long long>> replace_counter;
    shared_ptr<atomic<unsigned int>> stream_counter;

public:
    FileDataReplacer(const xml_node& config);
    ~FileDataReplacer() = default;

    unsigned long long replase(forward_list<path>& object) const;

private:
    unsigned long long replace_in_file(const path& file_path) const;
};

}
}
