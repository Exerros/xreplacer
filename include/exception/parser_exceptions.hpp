#pragma once

#include "exception/base_exception.hpp"

namespace xrep::exception::parser {

//------------------------------------------------------------------------------
class NoObjects final : public FatalException {
public:
    const char* what() const noexcept override {
        return "Parser could not find files to replace the data";
    }
};

//------------------------------------------------------------------------------
class FileSearchError final : public FatalException {
public:
    const char* what() const noexcept override {
        return "File search error";
    }
};

} // namespace xrep::exception::parser

