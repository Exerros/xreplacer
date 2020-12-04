#include "replace_notificator.hpp"

namespace epx_test {

    Notificator::Notificator(const path& path, ostream* output)
        :filePath(path)
        ,outputStream(output)
        ,startTime(steady_clock::now())
        ,replaceCount(0)
    {
        *outputStream << START_MSG << filePath << std::endl;
    }

    Notificator::~Notificator() {
        auto totalTime = duration_cast<milliseconds>(
            duration(steady_clock::now() - startTime
        ));

        *outputStream << FINISH_MSG << filePath;

        if(replaceCount != 0)
            *outputStream << COUNT_MSG << replaceCount;

        *outputStream << TIME_MSG << totalTime.count() << "ms" << std::endl;
    }
}
