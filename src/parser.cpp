#include "parser.hpp"

#define REMOVE_UNUSED(x) (void)x

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
        } catch(std::exception* ex) {
            REMOVE_UNUSED(ex);
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
        Parser_Notificator notificator(outputStream);
        atomic<unsigned long>* streamCount = new atomic<unsigned long>(0);
        auto filesIter = files.begin();
        std::vector<std::thread*> t;

        while(filesIter != files.end()) {
            if(*streamCount < maxStreamCount) {
                t.push_back(new std::thread(
                    replase,
                    std::cref(replacer),
                    std::cref(*filesIter),
                    streamCount
                ));
                filesIter++;
                ++(*streamCount);
            } else {
                sleep_for(10ms);
            }
        }
        for(const auto& thread : t) {
            thread->join();
        }
        std::flush(*outputStream);
    }
    void Parser::replase(
            const Replacer& replacer,
            const path& p,
            atomic<unsigned long>* streamCounter
    ) {
        replacer.replace_in(p, streamCounter);
    }
}
