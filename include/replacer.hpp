#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <regex>
#include <thread>
#include <cmath>

#include "interface/ireplacer.hpp"
#include "exception.hpp"
#include "logger.hpp"

namespace xrep {

#pragma pack(push, 4)
/**
 * @brief A class for replacing information in files.
 */
class FileDataReplacer final : public interface::ReplacerInterface {
    using pairs_map = std::unordered_map<std::string, std::string>;
    using fs_path = std::filesystem::path;

private:
    pairs_map pairs;
    unsigned int thread_count;

public:
    /**
     * @brief Designer replaser getting information from the configurator.
     *
     * @param config_pairs Container with pairs to replace the information.
     *
     * @param config_thread_count Number of file handler threads.
     */
    FileDataReplacer(pairs_map config_pairs, int config_thread_count);
    ~FileDataReplacer() override = default ;

    /**
     * @brief A method that starts file processing.
     *
     * @param object Container with a list of files that will be processed by
     *        the application.
     */
    void replace(std::vector<fs_path>& object) const override;

private:
    /**
     * @brief A method that reads information from a file into a buffer.
     *
     * @param The path to the file you want to read.
     *
     * @return The file buffer read by the method.
     */
    static std::string get_buffer_from(const fs_path& filePath);

    /**
     * @brief A method to write the passed buffer to a file.
     *
     * @param The buffer to write.
     *
     * @param The path to the file in which the buffer will be written.
     */
    static void
    write_buffer_to_file(const std::string& buffer, const fs_path& filePath);

    /**
     * @brief A method that replaces the information in the passed file group.
     *
     * @param Container with a group of files to replace the information by one
     *        of the handler threads.
     *
     * @param Pairs of replacements transferred earlier to the replaser class.
     */
    static void replace_in_files(
            const std::vector<fs_path>& files_paths,
            const pairs_map& pairs);

    /**
     * @brief A method that divides the general list of files into groups of
     *        files for handler threads.
     *
     * @param Container of paths to files in which you want to make a
     *        replacement.
     *
     * @return Container with groups of paths prepared for handler threads.
     */
    std::vector<std::vector<fs_path>>
    chop_objects_container(std::vector<fs_path>& container) const;
};
#pragma pack(pop)

} // namespace xrep
