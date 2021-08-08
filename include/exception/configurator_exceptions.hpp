#pragma once

#include "exception/base_exception.hpp"

namespace xrep::exception::configurator {

class IncorrectConfigFile final : FatalException {
public:
    const char* what() const noexcept override {
        return "Incorrect configuration file";
    }
};

//------------------------------------------------------------------------------
class NoSettingsForItem final : non_FatalException {
public:
    const char* what() const noexcept override {
        return "No settings for the item";
    }
};

}
