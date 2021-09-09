#pragma once

#include "exception/base_exception.hpp"

namespace xrep::exception::replacer {

class IncorrectThreadsCount final : non_FatalException {
public:
    const char* what() const noexcept override {
        return "The configuration file specifies an incorrect number of threads to run";
    }
};

//------------------------------------------------------------------------------
class FileReadException final : non_FatalException {
public:
    const char* what() const noexcept override {
        return "File reading error";
    }
};

//------------------------------------------------------------------------------
class FileWriteException final : non_FatalException {
public:
    const char* what() const noexcept override {
        return "File writing error";
    }
};

} // namespace xrep::exception::replacer

