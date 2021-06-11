#include "logger.hpp"

namespace xrep {
namespace logger {

Logger::Logger(const pugi::xml_node& config)
    : streams()
    , prefix()
    , postfix()
    { }

void Logger::set_prefix(const std::string& message) const noexcept {

}

void Logger::set_postfix(const std::string& message) const noexcept {

}

void Logger::log(const std::string& message) const noexcept {
    for(const auto& stream : streams) {
        stream << message;
    }
}

}
}
