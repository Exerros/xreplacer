#pragma once

#include "exception/base_exception.hpp"

namespace xrep::exception::replacer {

/**
 * @brief The IncorrectThreadsCount class
 */
class IncorrectThreadsCount final : non_FatalException {
public:
    const char* what() const noexcept override {
        return "The configuration file specifies an incorrect number of threads to run";
    }
};

//------------------------------------------------------------------------------
/**
 * @brief Exception thrown if an invalid number of handler threads is specified.
 */
class FileReadException final : non_FatalException {
public:
    const char* what() const noexcept override {
        return "File reading error";
    }
};

//------------------------------------------------------------------------------
/**
 * @brief Exception thrown in case of a file writing error.
 */
class FileWriteException final : non_FatalException {
public:
    const char* what() const noexcept override {
        return "File writing error";
    }
};

} // namespace xrep::exception::replacer

