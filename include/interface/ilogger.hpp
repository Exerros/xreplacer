#pragma once

#include <string>

#include "interface/base.hpp"

namespace xrep::interface {

enum class LogLevel {
    trace,
    debug,
    info,
    warning,
    error,
    fatal
};

/**
 * TODO brief
 */
class LoggerInterface : Interface {
public:
    LoggerInterface() noexcept = default;
    virtual ~LoggerInterface() noexcept = default;

    /**
     * TODO brief
     */
    virtual void log(const std::string& data) const noexcept = 0;
};

}
