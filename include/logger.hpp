#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>
#include <memory>

#include "pugixml.hpp"

#include "interface/ilogger.hpp"
#include "exception.hpp"

//------------------------------------------------------------------------------
#define LOG(LEVEL) xrep::LoggerHelper(xrep::LogLevel::LEVEL)
#define NEXT_LINE_CONTINUE "\n" << std::string(19, ' ')
#define BORDER std::string(80, '-') << '\n'

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
    sstream output;

public:
    LoggerHelper(LogLevel level) noexcept;
    ~LoggerHelper() noexcept;

    template<class T>
    LoggerHelper& operator <<(const T& data) {
        output << data;
        return *this;
    }

private:
    std::string lvl_to_string(LogLevel level) const noexcept;
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
