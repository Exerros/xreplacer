#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>
#include <memory>

#include "interface/ilogger.hpp"
#include "exception.hpp"

//------------------------------------------------------------------------------
#define LOG(LEVEL) xrep::LoggerHelper(xrep::LogLevel::LEVEL)
#define NEXT_LINE_CONTINUE "\n" << std::string(19, ' ')
#define BORDER std::string(61, '-')

//------------------------------------------------------------------------------
namespace xrep {

enum class LogLevel {
    trace = 0,
    debug,
    info,
    warning,
    error,
    fatal
};

//------------------------------------------------------------------------------
/**
 * @brief A class that converts the received information into a string and
 *        formats the message for further transfer to the logger.
 */
class LoggerHelper {
    using sstream = std::ostringstream;
    using system_clock = std::chrono::system_clock;
    using time_point = system_clock::time_point;

private:
    sstream output;

public:
    /**
     * @brief Constructor that creates a message with the specified logging
     *        level.
     *
     * @param level The level of importance of the message.
     */
    LoggerHelper(LogLevel level) noexcept;

    /**
     * @brief The destructor gets the logger instance and passes its log
     *        method the message stored in this object.
     */
    ~LoggerHelper() noexcept;

    /**
     * @brief A shift operator that works completely analogous to stream from
     *        the STL library.
     *
     * @param data Information placed in the message.
     *
     * @return Similarly stream from STL for multiple entries in one message.
     */
    template<class T>
    LoggerHelper& operator <<(const T& data) {
        output << data;
        return *this;
    }

private:
    /**
     * @brief The method transforms the log level into text.
     *
     * @param level Message Logging Level.
     *
     * @return String expression for the name of the logging level.
     */
    std::string lvl_to_string(LogLevel level) const noexcept;
};

//------------------------------------------------------------------------------
/**
 * @brief Information logging class in STDOUT.
 */
class Logger final : public interface::LoggerInterface {
public:
    Logger() noexcept = default;
    ~Logger() noexcept override = default;

    /**
     * @brief A method that puts the message into the stream.
     *
     * @param data The message that will be transmitted.
     */
    void log(const std::string& data) const noexcept override;

    /**
     * @brief Static function that returns a reference to the logger singleton.
     *
     * @return Reference to the logger object.
     */
    static const Logger& get_instance();
};

} // namespace xrep
