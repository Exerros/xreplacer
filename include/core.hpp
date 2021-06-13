#pragma once

#include <string>
#include <filesystem>

#include "interface/iconfigurator.hpp"
#include "interface/iparser.hpp"
#include "interface/ilogger.hpp"
#include "interface/ireplacer.hpp"

#include "configurator.hpp"
#include "exception.hpp"
#include "logger.hpp"
#include "parser.hpp"
#include "replacer.hpp"

namespace xrep {

using std::filesystem::path;

#ifdef __unix__
constexpr auto STANDART_CONFIG_PATH = "/usr/local/etc/xreplacer/conf.xml";
#elif
constexpr auto STANDART_CONFIG_PATH = "";
#endif

//------------------------------------------------------------------------------
class XReplacerCore {
public:
    XReplacerCore() = default;
    ~XReplacerCore() = default;

    void init(int argc, char** argv) noexcept(false);
    int run() noexcept(false);
};

}

