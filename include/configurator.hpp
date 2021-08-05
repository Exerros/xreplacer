#pragma once

#include <string>
#include <filesystem>

#include "pugixml.hpp"

#include "interface/iconfigurator.hpp"
#include "exception.hpp"
#include "logger.hpp"

namespace xrep {

class XMLConfigurator final : public interface::ConfiguratorInterface {
    using fs_path = std::filesystem::path;

private:
    pugi::xml_node config_data;

public:
    XMLConfigurator(const fs_path& config_path);
    ~XMLConfigurator() override = default;

    pugi::xml_node
    get_config_for(const std::string& identifier) const override;
};

}
