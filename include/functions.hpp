#pragma once

#include <string>
#include <fstream>

#include "exception.hpp"

namespace epx_func {
    using std::string;
    using std::ifstream;
    using std::ofstream;
    using epx_test::Buffer_Error;
    using epx_test::Writing_Error;

    char* get_buffer_from(const string& filePath);
    void write_buffer_to_file(string&& buffer, const string& filePath);

}
