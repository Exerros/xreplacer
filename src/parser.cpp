#include "parser.hpp"

namespace epx_test {

//Конструктор создает объект конфигуратора, который считывает всю необходимую
//информацию из файла и оповещает о найденной информации пользователя. После
//этого эта информация перемещается в поля объектов Parser и Replacer. Далее
//происходит чтения древа файлов в поисках файлов в которых будет производится
//замена и выводится этот список файлов. Если при чтении древа файлов возникают
//ошибки то бросается фатальное исключение FileSystem_Error
    Parser::Parser(const fs::path& configPath, ostream* output)
    {
        //создаем конфигуратор и заполняем поля
        Configurator config;
        try {
            config = Configurator(configPath, output);
        } catch (...) {
            throw Config_Error();
        }
        maxStreamCount = std::move(config.maxStreamCount);
        fs::path rootDirectory = std::move(config.rootDirectory);
        outputStream = output;

        //пытаемся считать древо файлов при помощи рекурсивного указателя
        //из std::filesystem
        try {
            for(fs_iterator i(rootDirectory); i != fs_iterator(); i = ++i) {
                if(false == is_directory(i->status()))
                files.push_back(*i);
            }
        } catch(...) {
            throw FileSystem_Error();
        }

        //рассказываем пользователю, что нашли
        show_paths();
    }

//Функция для вывода информации о найденых файлах
    void Parser::show_paths() const {
        *outputStream << DELIMITER
                      << "\nFiles found: " << files.size() << '\n';
        for(const auto& p : files) {
            *outputStream << p << '\n';
        }
        *outputStream << DELIMITER << '\n';
        std::flush(*outputStream);
    }

//Функция управляющая запуском потоков обработки файлов. В начале создается
//объект Parser_Notificator для оповещения пользователя. Атомарный счетчик
//числа потоков используется для контроля за запущенными в данный момент
//потоками. Счетчик увеличивается в данной функции, но уменьшается самими
//потоками по завершению работы. Потоки хранятся в векторе указателей для
//удобного join и дальнейшего ожидания завершения этих потоков.
    void Parser::replace_data() const {
        Parser_Notificator notificator(outputStream);
        atomic<unsigned long>* streamCount = new atomic<unsigned long>(0);
        auto filesIter = files.begin();
        std::vector<std::thread*> t;

        //создаем потоки пока это необходимо и их число не превышает
        //максимального разрешенного количества
        while(filesIter != files.end()) {
            if(*streamCount < maxStreamCount) {
                t.push_back(new std::thread(
                    replace,
                    std::cref(replacer),
                    std::cref(*filesIter),
                    streamCount
                ));
                filesIter++;
                ++(*streamCount);
            } else {
                //для экономии ресурсов цикл ждет 5 ms, чтобы бесцельно не
                //проверять число запущеных в данный момент потоков
                sleep_for(TIME_TO_SLEEP);
            }
        }
        //подключаем потоки, чобы наша программа дожидалась завершения всех из
        //них и мы не получили ошибки при завершении работы функции main()
        for(const auto& thread : t) {
            thread->join();
        }
    }

//Функция для запуска метода класса Replacer в многопоточном режиме. Необходима
//т.к. метод не является статическим. Решено было сделать его не статическим,
//потому что объект Replacer во время замены не изменяется и невозможна ситуация
//гонки за данными
    void Parser::replace(
            const Replacer& replacer,
            const fs::path& p,
            atomic<unsigned long>* streamCounter
    ) {
        replacer.replace_in(p, streamCounter);
    }
}
