#pragma once

#include <string>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <ostream>
#include <filesystem>

#include "pugixml.hpp"

namespace xrep {

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

    virtual pugi:: get_replacer_data() = 0;
    virtual std::string get_parser_data() = 0;
};

//------------------------------------------------------------------------------


}
