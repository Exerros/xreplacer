#pragma once

#include <sstream>
#include <iostream>

class STDOUT_Capturer {
    using string = std::string;
    using ostringstream = std::ostringstream;
    using streambuf = std::basic_streambuf<char>;

private:
    ostringstream ss;
    streambuf *old_buf;
public:
    STDOUT_Capturer()
        : ss()
        , old_buf()
        { std::cout.rdbuf(ss.rdbuf()); }

    ~STDOUT_Capturer() {
        std::cout.rdbuf(old_buf);
    }

    string get_str() {
        return ss.str();
    }
};
