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

class JsonConfigurator final : public interface::ConfiguratorInterface {
    using pairs_map = std::unordered_map<std::string, std::string>;
    using fs_path = std::filesystem::path;
    using json = nlohmann::json;

private:
    json config_data;

public:
    JsonConfigurator(const fs_path& config_path);
    ~JsonConfigurator() override = default;

    /**
     * @brief verify_config
     */
    void verify_config() const override;

    /**
     * @brief get_root_dir
     * @return
     */
    fs_path get_root_dir() const override;

    /**
     * @brief get_stream_count
     * @return
     */
    unsigned int get_thread_count() const override;

    /**
     * @brief get_pairs
     * @return
     */
    pairs_map get_pairs() const override;
};

} // namespace xrep
