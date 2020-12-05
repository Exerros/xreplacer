#include "configurator.hpp"

namespace epx_test {

//функция выполняет поиск регулярного выражения regStr в буфере и возвращает
//совпадение с указанным индексом. Если совпадений с указанным регулярным
//выражение найдено не было то бросается критическое исключение Config_Error
    decltype(auto) Configurator::search(
            const string& regStr,
            const string& buffer,
            const unsigned long index
    ) const {
        regex reg(regStr);
        smatch match;

        bool search_result = regex_search(buffer, match, reg);
        if(search_result == false) {
            throw Config_Error();
        }

        return match[index];
    }

//конструктор занимается парсингом переданного в види пути файла конфигурации.
//для опевещения пользователя используется указанный поток, также он будет
// в дальнейшем передан классам Parser и Replacer
    Configurator::Configurator(const fs::path& filePath, ostream* output)
        :maxStreamCount()
        ,outputStream(output)
    {
        //читаем буфер из файла
        string fileBuf(get_buffer_from(filePath));

        //ищем путь к рабочей директории
        rootDirectory = search(ROOT_REGULAR_STRING, fileBuf, ROOT_MATCH_INDEX);
        //ищем максимальное количество потоков, если число не корректно
        //бросаем исключение
        long tmpStreamCount = std::stol(search(
            STREAMS_REGULAR_STRING,
            fileBuf,
            STREAMS_MATCH_INDEX
        ));
        if(tmpStreamCount <= 0) {
            throw Config_Error();
        } else {
            maxStreamCount = static_cast<unsigned long>(tmpStreamCount);
        }
        //ищем блок с парами для замены
        string pairsBlock = search(
            REPLACE_REGULAR_STRING,
            fileBuf,
            PAIRS_MATCH_INDEX
        );

        //ищем сами пары и помещаем их в контейнер
        regex reg(PAIR_REGULAR_STRING);
        smatch match;
        while(true == regex_search(pairsBlock, match, reg)) {
            pairs.insert(make_pair(move(match[1]), move(match[3])));
            pairsBlock = match.suffix();
        }
        if(pairs.size() == 0) throw Config_Error();

        //оповещаем пользователя о том, что нашли
        show_data();
    }

    //Простая функция для отображения считанной из конфига информации в
    //отформатированном виде
    void Configurator::show_data() const {
        *outputStream << DELIMITER << '\n'
                      << TITLE << '\n'
                      << DELIMITER
                      << "\nPath to directory with files: "
                      << rootDirectory << "\n"
                      << DELIMITER
                      << "\nMaximum number of streams: "
                      << maxStreamCount << "\n"
                      << DELIMITER
                      << "\nPairs of replacements:\n";

        for(const auto& [oldValue, newValue] : pairs) {
            *outputStream << '\"' << oldValue
                          << "\" will be replaced to \""
                          << newValue << "\"\n";
        }
        std::flush(*outputStream);
    }
}
