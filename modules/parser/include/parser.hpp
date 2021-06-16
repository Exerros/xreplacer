#pragma once

#include <filesystem>
#include <forward_list>

#include "pugixml.hpp"

#include "interface/iparser.hpp"
#include "exception.hpp"

namespace xrep {
namespace parser {

using pugi::xml_node;
using std::forward_list;
using std::filesystem::path;
using fs_iterator = std::filesystem::recursive_directory_iterator;

//------------------------------------------------------------------------------
class FileSystemParser : interface::ParserInterface<forward_list<path>> {
private:
    path root_dir;
    forward_list<path> objects;

public:
    FileSystemParser(const xml_node& config);
    ~FileSystemParser() override = default;

    unsigned int search_objects_to_replase() override;
    forward_list<path>& get_objects_to_replase() override;
    bool has_objects_to_replace() const override;
};

}
}
