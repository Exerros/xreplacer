#include "core.hpp"

namespace xrep {
namespace fs = std::filesystem;

//------------------------------------------------------------------------------
void XReplacerCore::init(int argc, char** argv) {
    path config_path;
    if((argc == 1) || (argc > 2)) {
        config_path = path(STANDART_CONFIG_PATH);

        config::XMLConfigurator conf(config_path);
        logger::Logger logger(conf.get_config_for("logger"));
        parser::FileSystemParser(conf.get_config_for("parser"));
        replacer::FileDataReplacer replacer(conf.get_config_for("replacer"));
    } else {
        try {
            config_path = path(argv[1]);
        } catch (std::exception& ex) {
            throw ex;
        }
    }
}

//------------------------------------------------------------------------------
int XReplacerCore::run() {

    return 0;
}


}
