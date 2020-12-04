#include "parser.hpp"

namespace epx_test {

    Parser::Parser(const path& configPath, ostream* output)
    {
        Configurator config(configPath, output);
        replacer = Replacer(config);
        maxStreamCount = std::move(config.maxStreamCount);
        path rootDirectory = std::move(config.rootDirectory);
        outputStream = output;

        try {
            for(fs_iterator i(rootDirectory); i != fs_iterator(); i = ++i) {
                if(false == is_directory(i->status()))
                files.push_back(*i);
            }
        } catch(std::filesystem::filesystem_error) {
            throw FileSystem_Error();
        }

        show_paths();
    }

    void Parser::show_paths() const {
        *outputStream << DELIMITER
                      << "\nFiles found: " << files.size() << '\n';
        for(const auto& p : files) {
            *outputStream << p << '\n';
        }
        *outputStream << DELIMITER << '\n';
        std::flush(*outputStream);
    }

    void Parser::replace_data() const {
        for(const auto& file : files)
        replacer.fast_replace_in(file);
    }

}
