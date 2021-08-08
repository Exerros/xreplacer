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
class IncorrectSleepTime final : non_FatalException {
public:
    const char* what() const noexcept override {
        return "In the configuration file there is an invalid waiting time between attempts to create threads";
    }
};

//------------------------------------------------------------------------------
class NoPairs final : non_FatalException {
public:
    const char* what() const noexcept override {
        return "The configuration file does not specify the pairs to replace";
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

}

