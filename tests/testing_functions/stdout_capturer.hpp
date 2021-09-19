#pragma once

#include <sstream>
#include <iostream>

namespace tests {
/**
 * @brief This class is designed to intercept information sent to STDOUT.
 */
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
        { old_buf = std::cout.rdbuf(ss.rdbuf()); }

    ~STDOUT_Capturer() {
        std::cout.rdbuf(old_buf);
    }

    /**
     * @brief A method that returns the information sent to STDOUT as a string.
     *
     * @return Information from STDOUT.
     */
    string get_str() {
        return ss.str();
    }
};

} // namespace tests
