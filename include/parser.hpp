#pragma once

#include <filesystem>
#include <vector>

#include "interface/iparser.hpp"
#include "exception.hpp"
#include "logger.hpp"

namespace xrep {

/**
 * @brief A class that replaces information in files.
 */
class FileSystemParser final : public interface::ParserInterface {
    using fs_iterator = std::filesystem::recursive_directory_iterator;
    using fs_path = std::filesystem::path;

private:
    fs_path root_dir;
    std::vector<fs_path> objects;

public:
    /**
     * @brief A class that searches for files in which information needs to be
     *        replaced.
     *
     * @param conf_root_dir The path to the root directory where files will be
     *        recursively searched.
     */
    FileSystemParser(const fs_path& conf_root_dir);
    ~FileSystemParser() override = default;

    /**
     * @brief A method that starts the file search process.
     */
    void search_objects_to_replase() override;

    /**
     * @brief The method is intended to send the further collected list of
     *        files.
     *
     * @return A list of found files in which the data will be replaced.
     */
    std::vector<fs_path>& get_objects_to_replase() override;

    /**
     * @brief A method to check if the files were found, for further data
     *        replacement.
     *
     * @return True if the file list is not empty.
     */
    bool has_objects_to_replace() const override;
};

} // namespace xrep
