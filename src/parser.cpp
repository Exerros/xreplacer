#include "parser.hpp"

namespace epx_test {

    Parser::Parser(const path& configPath, ostream* output)
    {
        Configurator config(configPath, output);
        replacer = Replacer(config);
        maxStreamCount = std::move(config.maxStreamCount);
        path rootDirectory = std::move(config.rootDirectory);

        fs_iterator fsBegin(rootDirectory);
        fs_iterator fsEnd;

        for(const auto& file : rootDirectory) {
            files.push_back(file);
        }
        std::copy(fsBegin, fsEnd, std::back_inserter(files));

        for(const auto& p : files) {
            *output << p << std::endl;
        }
    }

}
