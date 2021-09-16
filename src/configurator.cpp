#include "configurator.hpp"

namespace xrep {

JsonConfigurator::JsonConfigurator(const fs_path& config_path)
    :config_data()
{
    LOG(info) << "Reading the configuration";
    try {
        std::ifstream config_file(config_path, std::ios::in);
        config_file >> config_data;
        config_file.close();
    } catch (...) {
        throw exception::configurator::ReadingError();
    }
    LOG(info) << "Reading is successful";

    LOG(info) << "Verifing the config file";
    verify_config();
    LOG(info) << "Verifing is successful";

}

//------------------------------------------------------------------------------
void JsonConfigurator::verify_config() const {
    if   ((config_data.at("parser") == NULL)
       || (config_data.at("replaser") == NULL)
       || (config_data.at("parser").at("root_dir") == NULL)
       || (config_data.at("replaser").at("thread_count") == NULL)
       || (config_data.at("replaser").at("pairs")        == NULL))
    {
        throw exception::configurator::IncorrectConfigFile();
    }
}

//------------------------------------------------------------------------------
std::filesystem::path JsonConfigurator::get_root_dir() const {
    return std::string(config_data["parser"]["root_dir"].get<std::string>());
}

//------------------------------------------------------------------------------
unsigned int JsonConfigurator::get_thread_count() const {
    return config_data["replaser"]["thread_count"].get<unsigned int>();
}

//------------------------------------------------------------------------------
std::unordered_map<std::string, std::string>
JsonConfigurator::get_pairs() const {
    std::unordered_map<std::string, std::string> tmp {};

    for(const auto& item : config_data["replaser"]["pairs"].items()) {
        tmp.insert(std::pair(item.key(), item.value()));
    }

    return tmp;
}

} // namespace xrep
