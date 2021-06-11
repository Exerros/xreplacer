#include "logger.hpp"

namespace xrep {
namespace logger {

Logger::Logger(const pugi::xml_node& config) {
    if(config.child("prefix").value()) {
        prefix = string(config.child("prefix").value());
    }

    if(config.child("postfix").value()) {
        postfix = string(config.child("postfix").value());
    }
    try {
        for(const auto& child : config) {
            if(child.name() == "file") {

            } else if(child.name() == "stream") {

            }
        }
    } catch (...) {
        throw exception::ConfigException();
    }
    streams();

}

void Logger::log(const std::string& message) const noexcept {
    for(const auto& stream : streams) {
        stream << message;
    }
}

}
}
