#pragma once

#include <iostream>
#include <fstream>
#include <forward_list>
#include <memory>

#include "pugixml.hpp"

#include "interface/ilogger.hpp"
#include "exception.hpp"

namespace xrep {
namespace logger {

using std::ostream;
using std::string;
using std::forward_list;
using std::ofstream;
using pugi::xml_node;
using pugi::xml_document;
using stream_pointer = std::unique_ptr<ostream, void(*)(ostream*)>;
using streams_list = forward_list<stream_pointer>;

//------------------------------------------------------------------------------
class Logger : interface::LoggerInterface<string> {
private:
    streams_list streams;
    string prefix;
    string postfix;

public:
    Logger(const xml_node& config);
    ~Logger() override = default;

    void log(const string& message) const noexcept override;

private:
    void add_stream(const string& name);
    void add_file(const string& file_path);
};

}
}
