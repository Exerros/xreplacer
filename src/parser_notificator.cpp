#include "parser_notificator.hpp"

namespace epx_test {

    Parser_Notificator::Parser_Notificator(ostream* output)
        :startTime(steady_clock::now())
        ,outputStream(output)
    {
        *outputStream << PARSER_START_MSG;
        std::flush(*outputStream);
    }

    Parser_Notificator::~Parser_Notificator() {
        auto time = duration_cast<milliseconds>(
                    duration(steady_clock::now() - startTime
        ));
        *outputStream << PARSER_DELIMITER << '\n'
                      << PARSER_FINISH_MSG
                      << time.count() << "ms\n"
                      << PARSER_DELIMITER
                      << std::endl;
    }
}
