#pragma once

#include <iostream>
#include <fstream>
#include <forward_list>
#include <memory>
#include <chrono>

#include "pugixml.hpp"

#include "interface/ilogger.hpp"
#include "exception.hpp"

namespace xrep::logger {

using std::ostream;
using std::string;
using std::forward_list;
using std::ofstream;
using std::operator""s;
using pugi::xml_node;
using pugi::xml_document;
using files_pointer = std::unique_ptr<ofstream, void(*)(ofstream)>;
using files_list = forward_list<files_pointer>;
using streams_list = forward_list<ostream&>;
using time_point = std::chrono::time_point<std::chrono::system_clock>;

//------------------------------------------------------------------------------
class Logger : interface::LoggerInterface<string> {
private:
    time_point start_time;
    streams_list streams;
    files_list files;
    string start_msg;
    string finish_msg;
    bool show_time;

public:
    Logger(const xml_node& config);
    ~Logger() override;

    void log(const string& message) const noexcept override;

private:
    void add_stream(const string& name);
    void add_file(const string& file_path);
    string get_time_string() const ;
};

}
