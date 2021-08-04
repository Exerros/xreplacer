#include "core.hpp"

namespace xrep {

XReplacerCore::XReplacerCore()
    : config(nullptr)
    , parser(nullptr)
    , replacer(nullptr)
    { }

void XReplacerCore::init(int argc, char** argv) {
    fs_path config_path;
    if((argc == 1) || (argc > 2)) {
        config_path = fs_path(STANDART_CONFIG_PATH);

        config = config_ptr(new XMLConfigurator(config_path));
        parser = parser_ptr(
                    new FileSystemParser(config->get_config_for("parser")));
        replacer = replacer_ptr(
                    new FileDataReplacer(config->get_config_for("replacer")));

    } else {
        try {
            config_path = fs_path(argv[1]);

        } catch (std::exception& ex) {
            std::cerr << ex.what() << std::endl;
            exit(1);
        }
    }
}

//------------------------------------------------------------------------------
int XReplacerCore::run() {
    try {
        parser->search_objects_to_replase();

        if(parser->has_objects_to_replace()) {
            replacer->replase(parser->get_objects_to_replase());

        } else throw exception::ParserException();

    } catch(std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        exit(2);
    }

    return 0;
}


}
