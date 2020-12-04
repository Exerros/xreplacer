#include "replacer.hpp"

namespace epx_test {

    Replacer::Replacer()
        :pairs()
        ,searchSymbols()
        ,maxSearchSize()
        ,outputStream()
        { }

    Replacer::Replacer(Configurator& config)
        :pairs(std::move(config.pairs))
        ,searchSymbols(std::move(config.searchSymbols))
        ,maxSearchSize(std::move(config.maxSearchSize))
        ,outputStream(std::move(config.outputStream))
        { }

    void Replacer::replace_in(
            const path& filePath,
            atomic<unsigned long>* streamCounter
    ) const {
        std::flush(*outputStream);
        Notificator notificator(filePath, outputStream);
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
        --(*streamCounter);
    }
}
