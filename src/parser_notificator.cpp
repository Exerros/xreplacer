#include "parser_notificator.hpp"

namespace epx_test {

//Конструктор оповещает пользователя о начале замены строк в файлах(в целом)
//и запоминает момент в который она началась.
    Parser_Notificator::Parser_Notificator(ostream* output)
        :startTime(steady_clock::now())
        ,outputStream(output)
    {
        *outputStream << PARSER_START_MSG;
        std::flush(*outputStream);
    }

//Деструктор оповещает о завершении процесса замены информации в файлах
//и сообщает о том сколько времени было на это затрачено
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
