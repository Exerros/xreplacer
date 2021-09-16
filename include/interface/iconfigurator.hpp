#pragma once

#include <string>
#include <filesystem>
#include <unordered_map>

#include "base.hpp"

namespace xrep::interface {

/**
 * @brief The interface of the class responsible for taking the necessary
 *        settings data and passing them to the constructors of the other
 *        classes
 */
class ConfiguratorInterface : Interface {
    using pairs_map = std::unordered_map<std::string, std::string>;
    using fs_path = std::filesystem::path;

public:
    ConfiguratorInterface() = default;
    virtual ~ConfiguratorInterface() = default;

    /**
     * @brief Method for checking the configuration for all required data
     */
    virtual void verify_config() const = 0;

    /**
     * @brief A method that returns the path to the directory with
     *        the files that will be processed by the program.
     *
     * @return the full path to the working directory.
     */
    virtual fs_path get_root_dir() const = 0;

    /**
     * @brief Value indicating the number of file handler threads.
     *
     * @return The number of threads specified by the user in the configuration
     *         file.
     */
    virtual unsigned int get_thread_count() const = 0;

    /**
     * @brief Pairs indicating values for substitutions. In other
     *        words, what to replace.
     *
     * @return Container with pairs of values for replacements.
     */
    virtual pairs_map get_pairs() const = 0;
};

} // namespace xrep::interface
