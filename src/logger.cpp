#include "logger.hpp"

namespace xrep {
namespace logger {

Logger::Logger(const pugi::xml_node& config)
    :streams()
    { }

void Logger::add_stream(const std::ostream& stream)  {
    streams.push_front(stream);
}

void Logger::log(const std::string& message) const noexcept {
    for(const auto& stream : streams) {
        stream << message;
    }
}

}
}
