#include "configurator.hpp"

namespace epx_test {

    Configurator::Configurator(const string& filePath) {
        string fileBuf(move(get_buffer_from(filePath)));
        regex reg(ROOT_REGULAR_STRING);
        smatch match;

        if(regex_search(fileBuf, match, reg)) {
            rootDirectory = match[1];
        }

        reg = regex(STREAMS_REGULAR_STRING);
        if(regex_search(fileBuf, match, reg)) {
            maxStreamCount = std::atoi(match[1].str().data());
        }

    }

}
