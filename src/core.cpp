#include "core.hpp"

namespace xrep {
namespace fs = std::filesystem;

bool XReplacerCore::init(int argc, char** argv) {
    fs::path config_path;
    if((argc == 1) || (argc > 2)) {
        config_path = fs::path(STANDART_CONFIG_PATH);
    } else {
        try {
            config_path = fs::path(argv[1]);
        } catch (...) {
            std::cout << "Uncorrect arguments" << std::endl;
            exit(1);
        }
    }

    config::XMLConfigurator conf(config_path);
    logger::Logger logger(conf.get_config_for("logger"));
    parser::FileSystemParser(conf.get_config_for("logger"));
    replacer::FileDataReplacer replacer(conf.get_config_for("replacer"));
}

}
