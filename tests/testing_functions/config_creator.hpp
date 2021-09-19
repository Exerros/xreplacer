#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>

namespace tests {
/**
 * @brief An auxiliary class for creating configuration files for tests.
 */
class ConfigCreator {
    using fs_path = std::filesystem::path;
    using json = nlohmann::json;
    using pairs_map = std::unordered_map<std::string, std::string>;

private:
    json data {};
    fs_path root_dir {};
    int thread_count {};
    pairs_map pairs {};

public:

    ConfigCreator() = default;
    ~ConfigCreator() = default;

    /**
     * @brief A method to write information to the configuration file.
     * @param config_path The path where the configuration file will be located.
     */
    void write_to_file(const fs_path& config_path) const {
        std::ofstream file(config_path, std::ios::out | std::ios::trunc);

        file << std::setw(4) << data << std::endl;

        file.close();
    }

    /**
     * @brief Method that sets the root directory.
     * @param value Path to the root directory.
     */
    void set_root_dir(const std::string& value) {
        data["parser"]["root_dir"] = value;
        root_dir = value;
    }

    /**
     * @brief A method that sets the number of handler threads.
     * @param value The value of the number of threads.
     */
    void set_thread_count(const int value) {
        data["replaser"]["thread_count"] = value;
        thread_count = value;
    }

    /**
     * @brief A method that adds a pair for replacement.
     * @param v_from The meaning of what will be replaced.
     * @param v_to The value by which the replacement will be made.
     */
    void add_pair(const std::string& v_from, const std::string& v_to) {
        data["replaser"]["pairs"][v_from] = v_to;
        pairs.insert(std::pair(v_from, v_to));
    }

    /**
     * @brief Returns a reference to the value of the root directory.
     * @return Reference to the value of the root directory.
     */
    const fs_path& get_root_dir() const { return root_dir; }

    /**
     * @brief Returns a reference to the value of the number of handler threads.
     * @return Number of worker threads.
     */
    const int& get_thread_count() const { return thread_count; }

    /**
     * @brief Returns the container with replacement pairs.
     * @return Container with replacement pairs.
     */
    const pairs_map& get_pairs() const { return pairs; }
};

} // namespace tests
