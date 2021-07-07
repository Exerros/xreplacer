#include "logger.hpp"

namespace xrep::logger {

//------------------------------------------------------------------------------
Logger::Logger(const pugi::xml_node& config)
        : start_time(std::chrono::system_clock::now())
        , streams()
        , files()
        , start_msg()
        , finish_msg()
        , show_time(false)
{
    if(config.child("start_msg").value()) {
        start_msg = string(config.child("start_msg").value());
    }

    if(config.child("finish_msg").value()) {
	finish_msg = string(config.child("finish_msg").value());
    }
    
    if(config.child("show_time").value() == "true"s) {
        show_time = true;
    }

    try {
        for(const auto& child : config) {
            if(child.name() == pugi::string_t("file")) {
                add_stream(child.value());

            } else if(child.name() == pugi::string_t("stream")) {
                add_file(child.value());
            }
        }
    } catch (...) {
        throw exception::ConfigException();
    }

    for(auto& stream : streams) {
        *stream << finish_msg;
    }

    for(auto& stream : files) {
        *stream << finish_msg;
    }
}

//------------------------------------------------------------------------------
Logger::~Logger() {
    for(auto& stream : streams) {
        *stream << finish_msg;
    }

    for(auto& stream : files) {
        *stream << finish_msg;
    }
}

//------------------------------------------------------------------------------
void Logger::log(const string& message) const noexcept {
    string time{};

    if(show_time == true)
        time = get_time_string();

    for(auto& stream : streams) {
        *stream << time << message;
    }

    for(auto& stream : files) {
        *stream << time << message;
    }
}

//------------------------------------------------------------------------------
void Logger::add_stream(const string& name) {
    if(name == "STDOUT") {
        streams.push_front(std::cout);

    } else if(name == "STDERR") {
        streams.push_front(std::cerr);

    } else if(name == "STDLOG") {
        streams.push_front(std::clog);

    } else throw exception::ConfigException();
}

//------------------------------------------------------------------------------
void Logger::add_file(const string& file_path) {
    try {
        files_pointer file(
                    new ofstream(file_path, std::ios::ate | std::ios::trunc),
                    [](ofstream f){ f.close(); });
        files.push_front(file);
    } catch(...) {
        throw exception::ConfigException();
    }
}
//------------------------------------------------------------------------------
string Logger::get_time_string() const {
    if(show_time == false)
        return string();

    return std::chrono::system_clock::now();
}

}
