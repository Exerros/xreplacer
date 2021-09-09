#pragma once

#include <filesystem>
#include <vector>

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
    FileSystemParser(const fs_path& conf_root_dir);
    ~FileSystemParser() override = default;

    /**
     * @brief search_objects_to_replase TODO
     */
    void search_objects_to_replase() override;

    /**
     * @brief get_objects_to_replase
     * @return TODO
     */
    std::vector<fs_path>& get_objects_to_replase() override;

    /**
     * @brief has_objects_to_replace
     * @return TODO
     */
    bool has_objects_to_replace() const override;
};

} // namespace xrep
