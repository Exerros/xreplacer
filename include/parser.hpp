#pragma once

#include <filesystem>
#include <vector>

#include "pugixml.hpp"

#include "interface/iparser.hpp"
#include "exception.hpp"
#include "logger.hpp"

namespace xrep {

class FileSystemParser final : public interface::ParserInterface {
    using fs_iterator = std::filesystem::recursive_directory_iterator;
    using fs_path = std::filesystem::path;

private:
    fs_path root_dir;
    std::vector<fs_path> objects;

public:
    FileSystemParser(const pugi::xml_node& config);
    ~FileSystemParser() override = default;

    void search_objects_to_replase() override;
    std::vector<fs_path>& get_objects_to_replase() override;
    bool has_objects_to_replace() const override;
};

}
