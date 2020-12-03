#include "exception.hpp"

namespace epx_test {

    Test_Exception::Test_Exception(
        const Exception_Code code,
        const string& comm
    )
        :errCode(code)
        ,errComm(comm.c_str())
        { }

    const char* Test_Exception::what() const noexcept {
        return errComm;
    }

    Exception_Code Test_Exception::code() const noexcept {
        return errCode;
    }

}
