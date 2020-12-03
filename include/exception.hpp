#pragma once

#include <stdexcept>
#include <string>

namespace epx_test {
    using std::string;
    using std::exception;

    enum class Exception_Code {
        configErr,
        bufferErr,
        writingErr
    };

    const string EXCEPTION_COMMENTS[] = {
        "An error occurred while reading the config",
        "An error occurred while reading the buffer",
        "An error occurred while writing a file"
    };

    class Test_Exception : public exception {
    protected:
        const Exception_Code errCode;
        const char* errComm;
    public:
        Test_Exception(const Exception_Code code, const string& comm);

        const char* what() const noexcept;
        Exception_Code code() const noexcept;
    };

    class Config_Error : public Test_Exception {
    public:
        Config_Error()
            :Test_Exception(Exception_Code::configErr, EXCEPTION_COMMENTS[0])
            { }
    };

    class Buffer_Error : public Test_Exception {
    public:
        Buffer_Error()
            :Test_Exception(Exception_Code::bufferErr, EXCEPTION_COMMENTS[1])
            { }
    };

    class Writing_Error : public Test_Exception {
    public:
        Writing_Error()
            :Test_Exception(Exception_Code::writingErr, EXCEPTION_COMMENTS[2])
            { }
    };
}
