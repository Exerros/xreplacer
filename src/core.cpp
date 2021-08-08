#include "core.hpp"

namespace xrep {

XReplacerCore::XReplacerCore()
    : config(nullptr)
    , parser(nullptr)
    , replacer(nullptr)
    { }

//------------------------------------------------------------------------------
void XReplacerCore::init(int argc, char** argv) {
    LOG(info) << BORDER << "Initialization of xReplaser started";

    try {
        fs_path config_path;

        if((argc == 1) || (argc > 2)) {
            config_path = fs_path(STANDART_CONFIG_PATH);

            config = config_ptr(new XMLConfigurator(config_path));
            parser = parser_ptr(
                    new FileSystemParser(config->get_config_for("parser")));
            replacer = replacer_ptr(
                    new FileDataReplacer(config->get_config_for("replacer")));

        } else {
            config_path = fs_path(argv[1]);

        }
    } catch (std::exception& ex) {
        LOG(fatal) << ex.what();
        exit(1);
    }

    LOG(info) << "xReplaser initialization completed successfully\n" << BORDER;
}

//------------------------------------------------------------------------------
int XReplacerCore::run() {
    LOG(info) << "xReplaser starts processing files";
    try {
        parser->search_objects_to_replase();

        if(parser->has_objects_to_replace()) {
            replacer->replase(parser->get_objects_to_replase());

        } else throw exception::parser::NoObjects();

    } catch(std::exception& ex) {
        LOG(fatal) << ex.what();
        exit(2);
    }
    LOG(info) << "xReplaser has finished processing files\n" << BORDER;

    return 0;
}


}
