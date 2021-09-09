#pragma once

#include <exception>
#include <cstring>

namespace xrep::exception {

class xReplacerException : std::exception {
public:
    xReplacerException() = default;
    virtual ~xReplacerException() = default;

    virtual const char* what() const noexcept { return "FUK"; };
};

//------------------------------------------------------------------------------
class non_FatalException : xReplacerException {
public:
    non_FatalException() = default;
    virtual ~non_FatalException() = default;

    virtual const char* what() const noexcept { return "FUK"; };
};

//------------------------------------------------------------------------------
class FatalException : xReplacerException {
public:
    FatalException() = default;
    virtual ~FatalException() = default;

    virtual const char* what() const noexcept { return "FUK"; };
};

} // namespace xrep::exception
