#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>
#include <forward_list>

#include "pugixml.hpp"

#include "interface/ireplacer.hpp"
#include "exception.hpp"

namespace xrep {
namespace replacer {

namespace fs = std::filesystem;
using pugi::xml_node;
using std::string;
using std::forward_list;
using pairs_map = std::unordered_map<string, string>;

class FileDataReplacer : interface::ReplacerInterface<fs::path> {
private:
    int stream_count = 1;
    pairs_map pairs;

public:
    FileDataReplacer(const xml_node& config);
    ~FileDataReplacer() = default;

    bool replase(forward_list<fs::path>& object) const;

private:
    bool replace_in_file(const fs::path& file_path) const;
};

}
}
