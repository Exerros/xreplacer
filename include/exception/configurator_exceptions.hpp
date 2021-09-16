#pragma once

#include "exception/base_exception.hpp"

namespace xrep::exception::configurator {

/**
 * @brief Exception thrown in case of an error when reading a file.
 */
class ReadingError final : public FatalException {
public:
    const char* what() const noexcept override {
        return "An error occurred while reading the configuration file";
    }
};

//------------------------------------------------------------------------------
/**
 * @brief Exception thrown in case of an invalid configuration file.
 */
class IncorrectConfigFile final : public FatalException {
public:
    const char* what() const noexcept override {
        return "Incorrect configuration file";
    }
};

} // namespace xrep::exception::configurator
