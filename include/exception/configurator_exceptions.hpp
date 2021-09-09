#pragma once

#include "exception/base_exception.hpp"

namespace xrep::exception::configurator {

class ReadingError final : FatalException {
public:
    const char* what() const noexcept override {
        return "An error occurred while reading the configuration file";
    }
};

//------------------------------------------------------------------------------
class IncorrectConfigFile final : FatalException {
public:
    const char* what() const noexcept override {
        return "Incorrect configuration file";
    }
};

} // namespace xrep::exception::configurator
