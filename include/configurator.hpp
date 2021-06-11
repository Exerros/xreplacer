#pragma once

#include <filesystem>

#include "pugixml.hpp"

#include "interface/iconfigurator.hpp"
#include "exception.hpp"

namespace xrep {
namespace config {

namespace fs = std::filesystem;
using pugi::xml_node;

//------------------------------------------------------------------------------
class XMLConfigurator : interface::ConfiguratorInterface<xml_node> {
private:
    xml_node config_data;

public:
    XMLConfigurator(const fs::path& config_path);
    ~XMLConfigurator() override = default;

    xml_node get_config_for(const std::string& identify) const override;
};

}
}
