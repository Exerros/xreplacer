#pragma once

#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>

/**
 * @brief An auxiliary class for creating configuration files for tests.
 */
class ConfigCreator {
    using fs_path = std::filesystem::path;
    using json = nlohmann::json;

private:
    json data {};

public:
    ConfigCreator() = default;
    ~ConfigCreator() = default;

    /**
     * @brief A method for retrieving a value from the config file that is being
     *        created.
     *
     * @param value_name The name of the field storing the value.
     */
    template<class T>
    T get_value(const std::string& value_name) const {
        return data[value_name];
    }

    /**
     * @brief A method that adds a value to a configuration file.
     *
     * @param value_name The name of the field that will store the value.
     *
     * @param value The value that will be placed in the configuration file.
     */
    template<class T>
    void set_value(const std::string& value_name, const T& value) {

    }

    /**
     * @brief A method to write information to the configuration file.
     *
     * @param config_path The path where the configuration file will be located.
     */
    void write_to_file(const fs_path& config_path) const {

    }
};
