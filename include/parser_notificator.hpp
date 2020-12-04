#pragma once

#include <chrono>
#include <ostream>
#include <string>

namespace epx_test {
    using std::chrono::time_point;
    using std::chrono::steady_clock;
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::ostream;
    using std::string;

    const string
    PARSER_DELIMITER(80, '-'),
    PARSER_START_MSG("Replacement has started:\n"),
    PARSER_FINISH_MSG(
                   "Replacement is complete. Total replacement running time: ");

    class Parser_Notificator {
    private:
        decltype(steady_clock::now()) startTime;
        ostream* outputStream;
    public:
        Parser_Notificator(ostream* output);
        ~Parser_Notificator();
    };

}
