#include "logger.hpp"

namespace xrep {

//------------------------------------------------------------------------------
LoggerHelper::LoggerHelper() noexcept
    : log_time(system_clock::now())
    , output()
    { }

//------------------------------------------------------------------------------
LoggerHelper::~LoggerHelper() noexcept {
    Logger::get_instance().log(output.str());
}

//------------------------------------------------------------------------------
std::string LoggerHelper::lvl_to_string(LogLevel level) const noexcept {
    switch (level) {
       case LogLevel::trace:
           return std::string("trace");
       case LogLevel::debug:
           return std::string("debug");
       case LogLevel::info:
           return std::string("info");
       case LogLevel::warning:
           return std::string("warning");
       case LogLevel::error:
           return std::string("error");
       case LogLevel::fatal:
           return std::string("fatal");
    }
    return std::string();
}

//------------------------------------------------------------------------------
void Logger::log(const std::string& data) const noexcept {
    std::cout << data << std::endl;
}

//------------------------------------------------------------------------------
const Logger& Logger::get_instance() {
    static std::unique_ptr<Logger> logger;

    if (logger == nullptr)
        logger = std::unique_ptr<Logger>(new Logger());

    return *logger;
}

}
