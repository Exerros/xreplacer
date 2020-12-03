#include "configurator.hpp"

namespace epx_test {

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


    Configurator::Configurator(const string& filePath, ostream* output)
        :maxStreamCount()
        ,maxSearchSize()
        ,outputStream(output)
    {
        string fileBuf(get_buffer_from(filePath));

        rootDirectory = search(ROOT_REGULAR_STRING, fileBuf, ROOT_MATCH_INDEX);
        maxStreamCount = std::stoul(search(
            STREAMS_REGULAR_STRING,
            fileBuf,
            STREAMS_MATCH_INDEX
        ));
        string pairsBlock = search(
            REPLACE_REGULAR_STRING,
            fileBuf,
            PAIRS_MATCH_INDEX
        );

        regex reg(PAIR_REGULAR_STRING);
        smatch match;

        while(true == regex_search(pairsBlock, match, reg)) {
            if(match[1].str().size() > maxSearchSize)
                maxSearchSize = match[1].str().length();

            searchSymbols.insert(match[1].str()[0]);
            pairs.insert(make_pair(move(match[1]), move(match[3])));
            pairsBlock = match.suffix();
        }

        show_data();
    }

    //Простая функция для отображения считанной из конфига информации
    void Configurator::show_data() const {
        *outputStream << DELIMITER << '\n'
                      << FILLER << "Config  data:" << FILLER
                      << '\n' << DELIMITER
                      << "\nPath to directory with files: \""
                      << rootDirectory << "\"\n"
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
        *outputStream << DELIMITER << '\n';
        std::flush(*outputStream);
    }
}
