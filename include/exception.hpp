#pragma once

#include <exception>

namespace xrep {
namespace exception {

//------------------------------------------------------------------------------
class BaseException : std::exception {
public:
    BaseException() = default;
    virtual ~BaseException() = default;

    virtual const char* what() const noexcept = 0;
};

//------------------------------------------------------------------------------
class ConfigException : BaseException {
public:
    ConfigException() = default;
    ~ConfigException() override = default;

    const char* what() const noexcept override {
        return "";
    }
};

}
}
