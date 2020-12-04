#include "replacer.hpp"

namespace epx_test {

//Конструктор перемещает всю необходимую конфигурацию из конфигуратора
    Replacer::Replacer(Configurator& config)
        :pairs(std::move(config.pairs))
        ,outputStream(std::move(config.outputStream))
        { }

//Функция для замены строк согласно конфигу. Для подсчета числа потоков
//используется атомарный счетчик из класса Parser. Увеличение счетчика
//происходит в классе Parser во избежание ситуации гонок
    void Replacer::replace_in(
            const path& filePath,
            atomic<unsigned long>* streamCounter
    ) const {
        //оповещаем о начале и читаем буфер
        Notificator notificator(filePath, outputStream);
        string fileBuf(get_buffer_from(filePath));

        //ищем и заменяем строки
        for(const auto& [oldValue, newValue] : pairs) {
            regex_replace(
                fileBuf.begin(),
                fileBuf.begin(),
                fileBuf.end(),
                regex(oldValue),
                newValue
            );
        }

        //пишем буфер обратно в файл
        write_buffer_to_file(fileBuf, filePath);
        //уменьшаем счетчик потоков
        --(*streamCounter);
    }
}
