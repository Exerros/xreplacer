#include "configurator.hpp"

namespace xrep {

XMLConfigurator::XMLConfigurator(const fs_path& config_path) {
    try {
        pugi::xml_document config_file;
        config_file.load_file(config_path.c_str());
        config_data = config_file.root();

    } catch (...) {
        throw ConfigException();
    }
}

//------------------------------------------------------------------------------
pugi::xml_node
XMLConfigurator::get_config_for(const std::string& identifier) const {
    if(!config_data.child(identifier.c_str()).value())
        throw ConfigException();

    return config_data.child(identifier.c_str());
}

}
