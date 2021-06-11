#pragma once

#include <iostream>
#include <fstream>
#include <forward_list>

#include "interface/ilogger.hpp"
#include "exception.hpp"

#include "pugixml.hpp"

namespace xrep {
namespace logger {

using std::ostream;
using std::string;
using std::forward_list;
using pugi::xml_node;
using pugi::xml_document;

//------------------------------------------------------------------------------
class Logger : interface::LoggerInterface {
private:
    forward_list<ostream&> streams;
    string prefix;
    string postfix;

public:
    Logger(const xml_node& config);
    ~Logger() override = default;

    void log(const string& message) const noexcept override;
};

}
}
