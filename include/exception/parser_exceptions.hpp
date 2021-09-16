#pragma once

#include "exception/base_exception.hpp"

namespace xrep::exception::parser {

//------------------------------------------------------------------------------
/**
 * @brief Exception thrown if no files are found in the specified root path.
 */
class NoObjects final : public FatalException {
public:
    const char* what() const noexcept override {
        return "Parser could not find files to replace the data";
    }
};

//------------------------------------------------------------------------------
/**
 * @brief Exception thrown in case of a file search error.
 */
class FileSearchError final : public FatalException {
public:
    const char* what() const noexcept override {
        return "File search error";
    }
};

} // namespace xrep::exception::parser

