#pragma once

#include <string>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <ostream>
#include <filesystem>

#include "pugixml.hpp"

#include "exception.hpp"

namespace xrep {
namespace config {

namespace fs = std::filesystem;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::regex;
using std::regex_search;
using std::smatch;
using std::ostream;
//using xrep_func::get_buffer_from;
//using xrep_func::create_regex_string;

//------------------------------------------------------------------------------

class ConfiguratorInterface {
public:
    ConfiguratorInterface() = default;
    virtual ~ConfiguratorInterface() = default;

    virtual pugi::xml_node get_replacer_data() const = 0;
    virtual pugi::xml_node get_parser_data() const = 0;
};

//------------------------------------------------------------------------------

class XMLConfigurator : ConfiguratorInterface {
private:
    pugi::xml_node config_data;

public:
    XMLConfigurator(const fs::path& config_path);
    ~XMLConfigurator() override = default;

    pugi::xml_node get_replacer_data() const override;
    pugi::xml_node get_parser_data() const override;
};

}
}
