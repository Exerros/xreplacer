#pragma once

#include <ostream>
#include <forward_list>

#include "pugixml.hpp"

namespace xrep {
namespace logger {

//------------------------------------------------------------------------------
class LoggerInterface {
protected:
    std::string begin_msg;
    std::string end_msg;

public:
    LoggerInterface() = default;
    virtual ~LoggerInterface() = default;

    virtual void add_stream(const std::ostream& stream) = 0;
    virtual void log(const std::string& message) const noexcept = 0;

    virtual void write_in_begin(const std::string& message) const noexcept = 0;
    virtual void write_in_end(const std::string& message) const noexcept = 0;

};

//------------------------------------------------------------------------------
class Logger : LoggerInterface {
private:
    std::forward_list<std::ostream&> streams;

public:
    Logger(const pugi::xml_node& config);
    ~Logger() override = default;
 
    void add_stream(const std::ostream& stream) override;
    void log(const std::string& message) const noexcept override;
};

}
}
