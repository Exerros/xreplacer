#pragma once

#include <string>
#include <ostream>
#include <forward_list>

#include "interface/interface.hpp"

#include "pugixml.hpp"

//------------------------------------------------------------------------------
namespace xrep {
namespace interface {

class LoggerInterface : Interface {
public:
    LoggerInterface() = default;
    ~LoggerInterface() = default;

    virtual void log(const std::string& message) const noexcept = 0;
    virtual void log_without_fix(const std::string& message) const noexcept = 0;
};

}
}
