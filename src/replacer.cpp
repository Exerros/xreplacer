#include "replacer.hpp"

namespace epx_test {

    Replacer::Replacer(Configurator& config)
        :pairs(std::move(config.pairs))
        ,searchSymbols(std::move(config.searchSymbols))
        ,maxSearchSize(std::move(config.maxSearchSize))
        ,outputStream(std::move(config.outputStream))
        { }

    void Replacer::replace_in(const path& filePath) const {
        notify_started(filePath);

        string fileBuf(get_buffer_from(filePath));

        for(const auto& [oldValue, newValue] : pairs) {
            regex_replace(
                fileBuf.begin(),
                fileBuf.begin(),
                fileBuf.end(),
                regex(oldValue),
                newValue
            );
        }

        write_buffer_to_file(fileBuf, filePath);

        notify_finished(filePath);
    }

    //Более быстрый и менее читаемый вариант replace_in
    //логика в целом та же, но для сокращения числа операций пришлось
    //использовать комбинацию из вложенных циклов.
    //В данной реализации минимизируется число операций:
    //буфер данных проверяется лишь один раз, но сразу на все лексемы, а если
    //точнее то проверяется наличие лексем начинающихся с проверяемого символа
    //после этого происходит попытка замены в подстроке размером с самую длинную
    //лексему. После этого происходит проверка замены и если замена была
    //произведена, то итератор i сдвигается на следующую позицию после лексемы
    //пропуская часть ненужных проверок.
    void Replacer::fast_replace_in(const path& filePath) const {
        notify_started(filePath);
        string fileBuf(get_buffer_from(filePath));
        unsigned long replaceCount = 0;
        auto i = fileBuf.begin();

        //пока буфер не пуст
        while(i != fileBuf.end()) {
            //проверяем является ли символ началом лексемы
            for(const auto& ch : searchSymbols) {
                if(*i == ch) {
                    //пытаемся заменить
                    for(const auto& [oldValue, newValue] : pairs) {
                        auto iTmp = regex_replace(
                            i,
                            i,
                            min(next(i, maxSearchSize), fileBuf.end()),
                            regex(oldValue),
                            newValue);

                        //Если замена произошла засчитываем ее и производим
                        //сдвиг в ее конец
                        if(string(i,next(i, newValue.length())) == newValue) {
                            ++replaceCount;//подсчитываем число замен
                            i = prev(iTmp);//prev чтобы не перешагнуть за end
                            break;//выходим в цикл проверки символа
                        }
                    }
                    break; // выходим в while если символ - начало лексемы
                }
            }
            i = next(i);
        }
        write_buffer_to_file(fileBuf, filePath);
        notify_finished(filePath, replaceCount);
    }
}
