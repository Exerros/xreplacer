#pragma once

#include <stdexcept>
#include <string>

namespace epx_test {
    using std::string;
    using std::exception;

//коды ошибок для удобства их расспозначания
    enum class Exception_Code {
        configErr,
        bufferErr,
        writingErr,
        fileSystemErr
    };
//Стандартные описания ошибок
    const auto
    CONFIG_ERR_COMMENT = "An error occurred while reading the config!",
    BUFFER_ERR_COMMENT = "An error occurred while reading the buffer!",
    WRITING_ERR_COMMENT = "An error occurred while writing a file!",
    FS_ERR_COMMENT = "An error occurred while handling the file system!";

//Фактически в данной программе ошибки в большинстве своем фатальны и должны
//приводить к завершению работы программы. Данный класс поможет оповестить
//пользователя о причинах завершения работы программы.
//Здесь намеренно применено наследование ради конструктора, чтобы не было
//необходимости заполнять описания исключений на месте, но для возможности
//удобного понимания какое исключение было получено передается Exception_Code.
    class Test_Exception : public exception {
    protected:
        const Exception_Code errCode;
        const char* errComm;
    public:
        Test_Exception(const Exception_Code code, const string& comm);

        const char* what() const noexcept;
        Exception_Code code() const noexcept;
    };

//Для случаев неверно заполненного конфига
    class Config_Error : public Test_Exception {
    public:
        Config_Error()
            :Test_Exception(Exception_Code::configErr, CONFIG_ERR_COMMENT)
            { }
    };

//ошибка при чтении буфера файла
    class Buffer_Error : public Test_Exception {
    public:
        Buffer_Error()
            :Test_Exception(Exception_Code::bufferErr, BUFFER_ERR_COMMENT)
            { }
    };
//ошибка при записи буфера в файл
    class Writing_Error : public Test_Exception {
    public:
        Writing_Error()
            :Test_Exception(Exception_Code::writingErr, WRITING_ERR_COMMENT)
            { }
    };
//ошибка при "прочесывании" указанного в конфиге пути
    class FileSystem_Error : public Test_Exception {
    public:
        FileSystem_Error()
            :Test_Exception(Exception_Code::fileSystemErr, FS_ERR_COMMENT)
            { }
    };
}
