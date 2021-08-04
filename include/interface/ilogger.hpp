#pragma once

#include <string>

#include "interface/base.hpp"

namespace xrep::interface {

class LoggerInterface : Interface {
public:
    LoggerInterface() noexcept = default;
    virtual ~LoggerInterface() noexcept = default;

    virtual void log(const std::string& data) const noexcept = 0;
};

}
