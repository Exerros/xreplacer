#include "replace_notificator.hpp"

namespace epx_test {

//Мьютекс используется для защиты от ситуации гонки за данными в виде
//смешанного вывода информации от потоков
    static std::mutex outputMutex;

//блокируем мьютекс и сообщаем о начале процесса замен информации
    Notificator::Notificator(const path& path, ostream* output)
        :filePath(path)
        ,outputStream(output)
        ,startTime(steady_clock::now())
    {
        const lock_guard<std::mutex> lock(outputMutex);
        *outputStream << START_MSG << filePath << '\n';
        std::flush(*outputStream);
    }

//блокируем мьютекс и сообщаем о завершении процесса и выводим
//затраченное время
    Notificator::~Notificator() {
        const lock_guard<std::mutex> lock(outputMutex);
        auto totalTime = duration_cast<milliseconds>(
            duration(steady_clock::now() - startTime
        ));

        *outputStream << FINISH_MSG
                      << filePath
                      << TIME_MSG
                      << totalTime.count()
                      << "ms\n";
        std::flush(*outputStream);
    }
}
