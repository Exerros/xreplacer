#pragma once

#include <exception>
#include <cstring>

namespace xrep::exception {

class xReplacerException : public std::exception {
public:
    xReplacerException() = default;
    virtual ~xReplacerException() = default;

    virtual const char* what() const noexcept { return "FUK"; };
};

//------------------------------------------------------------------------------
class non_FatalException : public xReplacerException {
public:
    non_FatalException() = default;
    virtual ~non_FatalException() = default;

    virtual const char* what() const noexcept { return "FUK"; };
};

//------------------------------------------------------------------------------
class FatalException : public xReplacerException {
public:
    FatalException() = default;
    virtual ~FatalException() = default;

    virtual const char* what() const noexcept { return "FUK"; };
};

} // namespace xrep::exception
