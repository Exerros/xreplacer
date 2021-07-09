#include "logger.hpp"

namespace xrep {

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
        start_msg = std::string(config.child("start_msg").value());
    }

    if(config.child("finish_msg").value()) {
        finish_msg = std::string(config.child("finish_msg").value());
    }
    
    if(config.child("show_time").value() == std::string("true")) {
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
        throw ConfigException();
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
        *stream << finish_msg << std::endl;
    }

    for(auto& stream : files) {
        *stream << finish_msg << std::endl;
    }
}

//------------------------------------------------------------------------------
void Logger::log(const std::string& message) const noexcept {
    std::ostringstream msg{};

    if(show_time == true) {
        const auto time_now = system_clock::to_time_t(system_clock::now());
        msg << std::put_time(std::localtime(&time_now), "%F %T : ") << message;
    }

    for(auto& stream : streams) {
        *stream << msg.str() << std::flush;
    }

    for(auto& stream : files) {
        *stream << msg.str() << std::flush;
    }
}

//------------------------------------------------------------------------------
void Logger::add_stream(const std::string& name) {
    if(name == "STDOUT") {
        streams.push_front(std::cout);

    } else if(name == "STDERR") {
        streams.push_front(std::cerr);

    } else if(name == "STDLOG") {
        streams.push_front(std::clog);

    } else throw ConfigException();
}

//------------------------------------------------------------------------------
void Logger::add_file(const std::string& file_path) {
    try {
        files_pointer file(
                new std::ofstream(file_path, std::ios::ate | std::ios::trunc),
                [](std::ofstream f){ f.close(); });
        files.push_front(file);

    } catch(...) {
        throw ConfigException();
    }
}
//------------------------------------------------------------------------------

}
