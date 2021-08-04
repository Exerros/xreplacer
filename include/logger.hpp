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

using interface::LogLevel;

//------------------------------------------------------------------------------
class LoggerHelper {
    using sstream = std::ostringstream;
    using system_clock = std::chrono::system_clock;

private:
    sstream output;

public:
    LoggerHelper() noexcept;
    ~LoggerHelper() noexcept;

private:
    std::string lvl_to_string(LogLevel level);

public:
    template<class T>
    LoggerHelper& operator <<(const T& data) {
        output << data;
        return *this;
    }

    template<LogLevel>
    LoggerHelper& operator <<(LogLevel lvl) noexcept {
        auto time_point = system_clock::now();
        output << std::setw(10) << time_point
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
