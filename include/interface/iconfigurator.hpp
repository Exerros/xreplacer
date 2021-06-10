#pragma once

#include <string>

#include "interface/base_interface.hpp"
#include "pugixml.hpp"

namespace xrep {
namespace interface {

class ConfiguratorInterface : BaseInterface {
public:
    ConfiguratorInterface() = default;
    virtual ConfiguratorInterface() = default;

    virtual pugi::xml_node get_config(const std::string& node_name) const = 0;
}

}
}
