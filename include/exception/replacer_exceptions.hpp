#pragma once

#include "exception/base_exception.hpp"

namespace xrep::exception::replacer {

/**
 * @brief Exception for when the number of handler threads <= 0.
 */
class IncorrectThreadsCount final : non_FatalException {
public:
    const char* what() const noexcept override {
        return "The configuration file specifies an incorrect number of threads to run";
    }
};

//------------------------------------------------------------------------------
/**
 * @brief Exception for cases where no replacement pairs have been received.
 */
class NoPairs final : non_FatalException {
public:
    const char* what() const noexcept override {
        return "Replacer did not get the pairs to replace.";
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

