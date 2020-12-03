#pragma once

#include <string>
#include <fstream>

#include "functions.hpp"

namespace epx_func {
    using std::string;
    using std::ifstream;

    char* get_buffer_from(const string& filePath);

}
