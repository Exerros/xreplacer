#include "core.hpp"

namespace xrep {
namespace fs = std::filesystem;

//------------------------------------------------------------------------------
void XReplacerCore::init(int argc, char** argv) {
    path config_path;
    try {
        if((argc == 1) || (argc > 2)) {
            config_path = path(STANDART_CONFIG_PATH);

            conf = shared_ptr<config::XMLConfigurator>(
                        new config::XMLConfigurator(config_path));
            logger = shared_ptr<logger::Logger>(
                        new logger::Logger(conf->get_config_for("logger")));
            parser = shared_ptr<parser::FileSystemParser>(
                        new parser::FileSystemParser(
                            conf->get_config_for("parser")));
            replacer = shared_ptr<replacer::FileDataReplacer>(
                        new replacer::FileDataReplacer(
                            conf->get_config_for("replacer")));
        } else {
            config_path = path(argv[1]);
        }
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        exit(1);
    }
}

//------------------------------------------------------------------------------
int XReplacerCore::run() {
    logger->log("asd"/* Message about start */);
    try {
        auto objects_count = parser->search_objects_to_replase();
        logger->log(std::to_string(objects_count)/* Message about count of objects */);

        if(parser->has_objects_to_replace()) {
            replacer->replase(parser->get_objects_to_replase());
        } else throw exception::ParserException();
    } catch(std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        exit(2);
    }
    logger->log("asd"/* Message about finish */);
    return 0;
}


}
