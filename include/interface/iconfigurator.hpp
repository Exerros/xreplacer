#pragma once

#include <string>
#include <filesystem>
#include <unordered_map>

#include "base.hpp"

namespace xrep::interface {

/**
 * @brief TODO
 */
class ConfiguratorInterface : Interface {
    using pairs_map = std::unordered_map<std::string, std::string>;
    using fs_path = std::filesystem::path;

public:
    ConfiguratorInterface() = default;
    virtual ~ConfiguratorInterface() = default;

    /**
     * @brief verify_config TODO
     */
    virtual void verify_config() const = 0;

    /**
     * @brief get_root_dir
     * @return TODO
     */
    virtual fs_path get_root_dir() const = 0;

    /**
     * @brief get_stream_count
     * @return TODO
     */
    virtual unsigned int get_thread_count() const = 0;

    /**
     * @brief get_pairs
     * @return TODO
     */
    virtual pairs_map get_pairs() const = 0;
};

} // namespace xrep::interface
