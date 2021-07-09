#pragma once

#include <filesystem>
#include <forward_list>

#include "pugixml.hpp"

#include "interface/iparser.hpp"
#include "interface/ilogger.hpp"
#include "exception.hpp"

namespace xrep {

class FileSystemParser : public interface::ParserInterface {
    using fs_iterator = std::filesystem::recursive_directory_iterator;
    using fs_path = std::filesystem::path;

private:
    fs_path root_dir;
    std::forward_list<fs_path> objects;

public:
    FileSystemParser(const pugi::xml_node& config);
    ~FileSystemParser() override = default;

    unsigned int search_objects_to_replase() override;
    std::forward_list<fs_path>& get_objects_to_replase() override;
    bool has_objects_to_replace() const override;
};

}
