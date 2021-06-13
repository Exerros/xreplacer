#pragma once

#include "interface/base.hpp"

namespace xrep {
namespace interface {

template<class ConfigType, class Identifier>
/**
 * @brief The ConfiguratorInterface class is a template configuration class
 *        interface. It is implemented in such a way that it does not depend on
 *        the specific format of the configuration object.
 */
class ConfiguratorInterface : Interface {
public:
    ConfiguratorInterface() = default;
    virtual ~ConfiguratorInterface() = default;

    /**
     * @brief get_config_for A function designed to pass the necessary part of
     *        the config to other classes.
     * @param identifier Identifies the desired config.
     * @return Necessary element of the configure.
     */
    virtual ConfigType get_config_for(const Identifier& identifier) const = 0;
};

}
}
