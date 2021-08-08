#pragma once

#include "exception/base_exception.hpp"

namespace xrep::exception::parser {

class NoRootDir final : FatalException {
public:
    const char* what() const noexcept override {
        return "There is no root directory for searching files in the settings file";
    }
};

//------------------------------------------------------------------------------
class NoObjects final : FatalException {
public:
    const char* what() const noexcept override {
        return "Parser could not find files to replace the data";
    }
};

//------------------------------------------------------------------------------
class FileSearchError final : FatalException {
public:
    const char* what() const noexcept override {
        return "File search error";
    }
};

}

