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
using files_pointer = std::unique_ptr<ostream*, void(*)(ostream*)>;
using files_list = forward_list<files_pointer>;
using streams_list = forward_list<ostream&>;

//------------------------------------------------------------------------------
class Logger : interface::LoggerInterface<string> {
private:
    streams_list streams;
    files_list files;
    string prefix;
    string postfix;
    string start_msg;
    string finish_msg;

public:
    Logger(const xml_node& config);
    ~Logger() override = default;

    void log(const string& message) const noexcept override;
    void set_show_time(const bool& value) noexcept override;

private:
    void add_stream(const string& name);
    void add_file(const string& file_path);
};

}
}
