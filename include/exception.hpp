#pragma once

#include <stdexcept>
#include <string>

namespace epx_test {
    using std::string;
    using std::exception;

    enum class Exception_Code {
        configErr,
        bufferErr,
        writingErr,
        fileSystemErr
    };

    const auto
    CONFIG_ERR_COMMENT = "An error occurred while reading the config!",
    BUFFER_ERR_COMMENT = "An error occurred while reading the buffer!",
    WRITING_ERR_COMMENT = "An error occurred while writing a file!",
    FS_ERR_COMMENT = "An error occurred while handling the file system!";

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
            :Test_Exception(Exception_Code::configErr, CONFIG_ERR_COMMENT)
            { }
    };

    class Buffer_Error : public Test_Exception {
    public:
        Buffer_Error()
            :Test_Exception(Exception_Code::bufferErr, BUFFER_ERR_COMMENT)
            { }
    };

    class Writing_Error : public Test_Exception {
    public:
        Writing_Error()
            :Test_Exception(Exception_Code::writingErr, WRITING_ERR_COMMENT)
            { }
    };

    class FileSystem_Error : public Test_Exception {
    public:
        FileSystem_Error()
            :Test_Exception(Exception_Code::fileSystemErr, FS_ERR_COMMENT)
            { }
    };
}
