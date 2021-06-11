#pragma once

#include <string>

#include "interface/interface.hpp"

namespace xrep {
namespace interface {

template<class T>
class ConfiguratorInterface : Interface {
public:
    ConfiguratorInterface() = default;
    virtual ~ConfiguratorInterface() = default;

    virtual T get_config_for(const std::string& identify) const = 0;
};

}
}
