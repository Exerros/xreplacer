#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include "exception.hpp"

namespace epx_func {
    using std::string;
    using std::ifstream;
    using std::ofstream;
    using std::filesystem::path;
    using epx_test::Buffer_Error;
    using epx_test::Writing_Error;

    string get_buffer_from(const path& filePath);
    void write_buffer_to_file(string& buffer, const path& filePath);

}
