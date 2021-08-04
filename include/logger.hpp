#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>
#include <memory>

#include "pugixml.hpp"

#include "interface/ilogger.hpp"
#include "exception.hpp"

//------------------------------------------------------------------------------
#define LOG(LEVEL) xrep::LoggerHelper() << xrep::interface::LogLevel::LEVEL

//------------------------------------------------------------------------------
namespace xrep {

enum class LogLevel {
    trace,
    debug,
    info,
    warning,
    error,
    fatal
};

//------------------------------------------------------------------------------
class LoggerHelper {
    using sstream = std::ostringstream;
    using system_clock = std::chrono::system_clock;
    using time_point = system_clock::time_point;

private:
    time_point log_time;
    sstream output;

public:
    LoggerHelper() noexcept;
    ~LoggerHelper() noexcept;

private:
    std::string lvl_to_string(LogLevel level) const noexcept;

public:
    template<class T>
    LoggerHelper& operator <<(const T& data) {
        output << data;
        return *this;
    }

    template<LogLevel>
    LoggerHelper& operator <<(LogLevel lvl) noexcept {
        auto time = system_clock::to_time_t(log_time);
        output << std::put_time(std::localtime(&time), "%T")
               << std::setw(10) << " [" << lvl_to_string(lvl) << "] ";
        return *this;
    }
};

//------------------------------------------------------------------------------
class Logger final : public interface::LoggerInterface {
public:
    Logger() noexcept = default;
    ~Logger() noexcept override = default;

    void log(const std::string& data) const noexcept override;

    static const Logger& get_instance();
};

}
