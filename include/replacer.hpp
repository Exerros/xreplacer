#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <regex>
#include <thread>

#include "interface/ireplacer.hpp"
#include "exception.hpp"
#include "logger.hpp"

namespace xrep {

#pragma pack(push, 4)
class FileDataReplacer final : public interface::ReplacerInterface {
    using pairs_map = std::unordered_map<std::string, std::string>;
    using fs_path = std::filesystem::path;

private:
    pairs_map pairs;
    unsigned int thread_count;

public:
    FileDataReplacer(pairs_map config_pairs, unsigned int config_thread_count);
    ~FileDataReplacer() override = default ;

    void replase(std::vector<fs_path>& object) const override;

private:
    static std::string get_buffer_from(const fs_path& filePath);

    static void
    write_buffer_to_file(const std::string& buffer, const fs_path& filePath);

    static void replace_in_files(
            const std::vector<fs_path>& files_paths,
            const pairs_map& pairs);

    std::vector<std::vector<fs_path>>
    chop_objects_container(std::vector<fs_path>& container) const;
};
#pragma pack(pop)

} // namespace xrep
