#pragma once

#include <string>

#include "interface/base.hpp"

namespace xrep::interface {

/**
 * @brief The LoggerInterface The interface of the class responsible for
 *        outputting information to the terminal.
 */
class LoggerInterface : Interface {
public:
    LoggerInterface() noexcept = default;
    virtual ~LoggerInterface() noexcept = default;

    /**
     * @brief Method that outputs information to STDOUT
     *
     * @param data Output message
     */
    virtual void log(const std::string& data) const noexcept = 0;
};

} // namespace xrep::interface
