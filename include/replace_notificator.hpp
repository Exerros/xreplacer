#pragma once

#include <chrono>
#include <filesystem>
#include <ostream>
#include <string>
#include <mutex>

namespace epx_test {
    namespace fs = std::filesystem;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::steady_clock;
    using std::chrono::time_point;
    using std::chrono::duration;
    using std::lock_guard;
    using std::ostream;
    using std::string;
    using std::mutex;

    constexpr auto
    START_MSG = "Replacement started in file: ",
    FINISH_MSG = "Replacement finished in file: ",
    TIME_MSG = ". Total time of operation ";

//Данный класс используется для оповещении о запущенном потоке обработки
//файла и расчета затраченного на это времени
    class Notificator {
    private:
        const fs::path& filePath;
        ostream* outputStream;
        decltype(steady_clock::now()) startTime;
    public:
//оповещает о начале замены информации в файле и запоминает момент когда это
//произошло.
        Notificator(const fs::path& filePath, ostream* output);

//расчитывает время работы и оповещает о завершении замены
        ~Notificator();
    };
}

