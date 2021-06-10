#pragma once

#include <ostream>
#include <forward_list>

#include "interface/base_interface.hpp"

#include "pugixml.hpp"

//------------------------------------------------------------------------------
namespace xrep {
namespace interface {

class LoggerInterface : BaseInterface {
public:
    LoggerInterface() = default;
    ~LoggerInterface() = default;
    
    virtual void add_stream(const std::ostream& stream) = 0;
    virtual void log(const std::string& message) const noexcept = 0;

    virtual void set_prefix(const std::string& message) const noexcept = 0;
    virtual void set_postfix(const std::string& message) const noexcept = 0;
};

}
}
