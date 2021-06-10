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
            exit 1;
        }
    }

}

}
