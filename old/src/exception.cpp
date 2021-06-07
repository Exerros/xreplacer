#include "exception.hpp"

namespace epx_test {

//Здесь описаны все функции класса исключений
    Test_Exception::Test_Exception(
        const Exception_Code code,
        const char* comm
    )
        :errCode(code)
        ,errComm(comm)
        { }

    const char* Test_Exception::what() const noexcept {
        return errComm;
    }

    Exception_Code Test_Exception::code() const noexcept {
        return errCode;
    }

}
