#pragma once

#include <ostream>
#include <forward_list>

#include "interface/ilogger.hpp"
#include "pugixml.hpp"

namespace xrep {
namespace logger {

//------------------------------------------------------------------------------
class Logger : interface::LoggerInterface {
private:
    std::forward_list<std::ostream&> streams;
    std::string prefix;
    std::string postfix;

public:
    Logger(const pugi::xml_node& config);
    ~Logger() override = default;

    void log(const std::string& message) const noexcept override;
    void log_without_fix(const std::string& message) const noexcept override;
};

}
}
