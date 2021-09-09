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

    verify_config();

    LOG(info) << "Reading is successful";
}

//------------------------------------------------------------------------------
void JsonConfigurator::verify_config() const {
    if   ((config_data.find("root_path")    == config_data.end())
       || (config_data.find("stream_count") == config_data.end())
       || (config_data.find("pairs")        == config_data.end()))
    {
        throw exception::configurator::IncorrectConfigFile();
    }
}

//------------------------------------------------------------------------------
std::filesystem::path JsonConfigurator::get_root_dir() const {
    return config_data["parser"]["root_dir"];
}

//------------------------------------------------------------------------------
unsigned int JsonConfigurator::get_thread_count() const {
    return config_data["replaser"]["stream_count"];
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
