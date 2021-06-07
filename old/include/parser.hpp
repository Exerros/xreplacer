#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <ostream>
#include <algorithm>
#include <atomic>
#include <thread>
#include <chrono>
#include <functional>
#include <memory>

#include "parser_notificator.hpp"
#include "configurator.hpp"
#include "replacer.hpp"
#include "exception.hpp"

namespace xrep {
    namespace fs = std::filesystem;
    using std::chrono_literals::operator""ms;
    using std::this_thread::sleep_for;
    using std::ostream;
    using std::string;
    using std::vector;
    using std::atomic;
    using std::shared_ptr;
    using xrep::FileSystem_Error;

    using fs_iterator = fs::recursive_directory_iterator;

//данная константа используется для ограничения цикла запускающего потоки
    constexpr auto TIME_TO_SLEEP = 5ms;

//Основной класс данной программы. Использует функционал остальных описанных
//классов и реализует функционал самой программы.
    class Parser {
    private:
        Replacer replacer;
        vector<fs::path> files;
        unsigned long maxStreamCount;
        ostream* outputStream;

    public:
//В конструкторе происходит создание объекта Configurator, при помощи которого
//инициализируется и сам Parser и его поле Replacer. Также именно в этой функции
//происходит парсинг дерева файлов и оповещение пользователя о найденых файлах
//Если при чтении дерева файлов происходят ошибки то бросается исключение типа
//FileSystem_Error
        Parser(const fs::path& configPath, ostream* output);

//Эта функция занимается многопоточной заменой информации в файлах согласно
//конфигу. Также в этом классе создается объект Parser_Notificator который
//который оповещает о начале и конце процесса замены информации.
        void replace_data() const;
    private:
//данная функция выводит информацию о найденных файлах
        void show_paths() const;

//Данная функция вызывается в многопоточном режиме. Фактически она занимается
//вызовом функции замены из объекта Replacer переданного первым аргументом
        static void replace(
                const Replacer& replacer,
                const fs::path& p,
                shared_ptr<atomic<unsigned long>> streamCounter
                );
    };

}
