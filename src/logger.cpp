#include "logger.hpp"

namespace xrep {

LoggerHelper::LoggerHelper(LogLevel level) noexcept {
    auto log_time{system_clock::now()};
    output = sstream();

    auto time = system_clock::to_time_t(log_time);
    output << std::put_time(std::localtime(&time), "%T")
           << std::setw(11) << std::left
           << std::string(" [" + lvl_to_string(level) + "] ");
}

//------------------------------------------------------------------------------
LoggerHelper::~LoggerHelper() noexcept {
    Logger::get_instance().log(output.str());
}

//------------------------------------------------------------------------------
std::string LoggerHelper::lvl_to_string(LogLevel level) const noexcept {
    std::array<const char*, 6> levelStrings {
        "trace", "debug", "info", "warning", "error", "fatal"
    };


    return std::string(levelStrings[static_cast<unsigned int>(level)]);
}

//------------------------------------------------------------------------------
void Logger::log(const std::string& data) const noexcept {
    std::cout << data << std::endl;
}

//------------------------------------------------------------------------------
const Logger& Logger::get_instance() {
    static Logger logger;
    return logger;
}

}
