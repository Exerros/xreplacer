#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "interface/iconfigurator.hpp"
#include "exception.hpp"
#include "logger.hpp"

namespace xrep {

/**
 * @brief A configurator class that retrieves configuration data from a .json
 *        file.
 */
class JsonConfigurator final : public interface::ConfiguratorInterface {
    using pairs_map = std::unordered_map<std::string, std::string>;
    using fs_path = std::filesystem::path;
    using json = nlohmann::json;

private:
    json config_data;

public:
    /**
     * @brief A class constructor that reads information from a file.
     *
     * @param config_path The path to the configuration file. If the file is not
     *        available, an attempt will be made to find the configuration file
     *        using the standard path (in the same directory).
     */
    JsonConfigurator(const fs_path& config_path);
    ~JsonConfigurator() override = default;

    /**
     * @brief A method that checks if the .json configuration file contains all
     *        required fields.
     */
    void verify_config() const override;

    /**
     * @brief Method passing information from parser/root_dir field.
     *
     * @return The path to the root directory, relative to which the files will
     *         be recursively processed.
     */
    fs_path get_root_dir() const override;

    /**
     * @brief A method that returns information from the replaser/thread_count
     *        field of the configuration file.
     *
     * @return The number of handler threads that will be used in the process of
     *         replasing the information in the files.
     */
    unsigned int get_thread_count() const override;

    /**
     * @brief A method that returns information from the replaser/pairs field of
     *        the .json configuration file.
     *
     * @return Map where the key is the value to be replaced and the value is
     *         what the data will be replaced with.
     */
    pairs_map get_pairs() const override;
};

} // namespace xrep
