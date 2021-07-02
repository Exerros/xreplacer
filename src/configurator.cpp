#include "configurator.hpp"

namespace xrep {
namespace config {

//------------------------------------------------------------------------------
XMLConfigurator::XMLConfigurator(const fs::path& config_path) {
    try {
        pugi::xml_document config_file;
        config_file.load_file(config_path.c_str());
        config_data = config_file.root();

    } catch (...) {
        throw exception::ConfigException();
    }
}

//------------------------------------------------------------------------------
xml_node XMLConfigurator::get_config_for(const std::string& identify) const {
    if(!config_data.child(identify.c_str()).value())
        throw exception::ConfigException();

    return config_data.child(identify.c_str());
}

}
}
