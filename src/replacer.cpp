#include "replacer.hpp"

namespace epx_test {

//Конструктор перемещает всю необходимую конфигурацию из конфигуратора
    Replacer::Replacer(Configurator& config)
        :pairs(std::move(config.pairs))
        ,outputStream(config.outputStream)
        { }

//Функция для замены строк согласно конфигу. Для подсчета числа потоков
//используется атомарный счетчик из класса Parser. Увеличение счетчика
//происходит в классе Parser во избежание ситуации гонок
    void Replacer::replace_in(
            const fs::path& filePath,
            shared_ptr<atomic<unsigned long>> streamCounter
    ) const {
        //оповещаем о начале и читаем буфер
        Notificator notificator(filePath, outputStream);
        string fileBuf(get_buffer_from(filePath));
        string result;

        //ищем и заменяем строки
        for(const auto& [oldValue, newValue] : pairs) {
            regex_replace(
                std::back_inserter(result),
                fileBuf.begin(),
                fileBuf.end(),
                regex(oldValue),
                newValue
            );

            fileBuf = std::move(result);
        }

        //пишем буфер обратно в файл
        write_buffer_to_file(fileBuf, filePath);
        //уменьшаем счетчик потоков
        --(*streamCounter);
    }
}
