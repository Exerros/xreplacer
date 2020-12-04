#include "replace_notificator.hpp"

namespace epx_test {

    static std::mutex outputMutex;

    Notificator::Notificator(const path& path, ostream* output)
        :filePath(path)
        ,outputStream(output)
        ,startTime(steady_clock::now())
    {
        const lock_guard<std::mutex> lock(outputMutex);
        *outputStream << START_MSG << filePath << '\n';
    }

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
    }
}
