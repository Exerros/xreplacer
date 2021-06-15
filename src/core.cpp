#include "core.hpp"

namespace xrep {
namespace fs = std::filesystem;

//------------------------------------------------------------------------------
void XReplacerCore::init(int argc, char** argv) {
    path config_path;
    if((argc == 1) || (argc > 2)) {
        config_path = path(STANDART_CONFIG_PATH);

        conf = config::XMLConfigurator(config_path);
        logger = logger::Logger(conf.get_config_for("logger"));
        parser = parser::FileSystemParser(conf.get_config_for("parser"));
        replacer = replacer::FileDataReplacer(conf.get_config_for("replacer"));
    } else {
        try {
            config_path = path(argv[1]);
        } catch (std::exception& ex) {
            std::cerr << ex.what() << std::endl;
            exit(1);
        }
    }
}

//------------------------------------------------------------------------------
int XReplacerCore::run() {
    logger.log("asd"/* Message about start */);
    try {
        parser.search_objects_to_replase();


        if(parser.has_objects_to_replace()) {
            replacer.replase(parser.get_objects_to_replase());
        } else throw exception::ParserException();
    } catch(std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        exit(2);
    }
    logger.log("asd"/* Message about finish */);
    return 0;
}


}
