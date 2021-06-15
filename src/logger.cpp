#include "logger.hpp"

namespace xrep {
namespace logger {

//------------------------------------------------------------------------------
Logger::Logger(const pugi::xml_node& config)
        : streams()
        , prefix("")
        , postfix("")
        , with_timings(false)
{
    try {
        if(config.child("prefix").value()) {
            prefix = string(config.child("prefix").value());
        }

        if(config.child("postfix").value()) {
            postfix = string(config.child("postfix").value());
        }

        if(config.child("timings").value()) {
            with_timings = (
                    config.child("timings").value() == pugi::string_t("true"));
        }

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
}

//------------------------------------------------------------------------------
void Logger::log(const string& message) const noexcept {
    for(auto& stream : streams) {
        if(with_timings) {
            const auto now = sys_clock::to_time_t(sys_clock::now());
            *stream << put_time(localtime(&now), "%H:%M:%S :");
        }
        *stream << prefix << message << postfix << std::endl;
    }
}

//------------------------------------------------------------------------------
void Logger::add_stream(const string& name) {/*
    if(name == "STDOUT") {
        stream_pointer stdout_stream(
                    &std::cout,
                    [](ostream* s){ delete(s); });
        streams.push_front(stdout_stream);
    } else if(name == "STDERR") {
        stream_pointer stderr_stream(
                    &std::cerr,
                    [](ostream* s){ delete(s); });
        streams.push_front(stderr_stream);
    } else if(name == "STDLOG") {
        stream_pointer stdlog_stream(
                    &std::clog,
                    [](ostream* s){ delete(s); });
        streams.push_front(stdlog_stream);
    } else throw exception::ConfigException();*/
}

//------------------------------------------------------------------------------
void Logger::add_file(const string& file_path) {/*
    try {
        stream_pointer file(
                    new ofstream(file_path, std::ios::ate | std::ios::trunc),
                    [](ostream* f){ reinterpret_cast<ofstream*>(f)->close(); });
        streams.push_front(file);
    } catch(...) {
        throw exception::ConfigException();
    }*/
}

}
}
