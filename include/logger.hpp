#pragma once

#include <iostream>
#include <fstream>
#include <forward_list>
#include <memory>
#include <chrono>
#include <sstream>
#include <iomanip>

#include "pugixml.hpp"

#include "interface/ilogger.hpp"
#include "exception.hpp"

namespace xrep {

class Logger : public interface::LoggerInterface {
    using files_pointer = std::unique_ptr<std::ofstream, void(*)(std::ofstream)>;
    using system_clock = std::chrono::system_clock;
    using time_point = std::chrono::time_point<system_clock>;
    using files_list = std::forward_list<files_pointer>;
    using streams_list = std::forward_list<std::ostream&>;

private:
    time_point start_time;
    streams_list streams;
    files_list files;
    std::string start_msg;
    std::string finish_msg;
    bool show_time;

public:
    Logger(const pugi::xml_node& config);
    ~Logger() override;

    void log(const std::string& message) const noexcept override;

private:
    void add_stream(const std::string& name);
    void add_file(const std::string& file_path);
};

}
