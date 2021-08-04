#pragma once

#include <exception>
#include <cstring>

namespace xrep {

//------------------------------------------------------------------------------
class BaseException : std::exception {
public:
    BaseException() = default;
    virtual ~BaseException() = default;

    virtual const char* what() const noexcept = 0;
};

//------------------------------------------------------------------------------
class ConfigException final : BaseException {
public:
    const char* what() const noexcept override {
        return "Incorrect configuration file";
    }
};

//------------------------------------------------------------------------------
class ParserException final : BaseException {
public:
    const char* what() const noexcept override {
        return "An error occurred while parsing the files, maybe you passed the wrong root directory or no matching files were found";
    }
};

//------------------------------------------------------------------------------
class ReplacerException final : BaseException {
public:
    const char* what() const noexcept override {
        return "An error occurred during information replacement, perhaps the input file was incorrect or no data was found for replacement";
    }
};

}
