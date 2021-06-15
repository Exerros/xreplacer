#pragma once

#include <exception>
#include <cstring>

namespace xrep {
namespace exception {

//------------------------------------------------------------------------------
class BaseException : std::exception {
public:
    BaseException() = default;
    virtual ~BaseException() = default;

    virtual const char* what() const noexcept = 0;
};

//------------------------------------------------------------------------------
class ConfigException : BaseException {
public:
    const char* what() const noexcept override {
        return "Incorrect configuration file";
    }
};

//------------------------------------------------------------------------------
class ParserException : BaseException {
public:
    const char* what() const noexcept override {
        return "An error occurred while parsing the files, maybe you passed the wrong root directory or no matching files were found";
    }
};

//------------------------------------------------------------------------------
class ReplacerException : BaseException {
public:
    const char* what() const noexcept override {
        return "An error occurred during information replacement, perhaps the input file was incorrect or no data was found for replacement";
    }
};

//------------------------------------------------------------------------------
class ResellerException : BaseException {
public:
    const char* what() const noexcept override {
        return "An error occurred while trying to read or write data to the storage.";
    }
};

}
}
