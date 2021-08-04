#pragma once

#include <string>
#include <filesystem>
#include <iostream>

#include "interface/iconfigurator.hpp"
#include "interface/iparser.hpp"
#include "interface/ireplacer.hpp"

#include "configurator.hpp"
#include "exception.hpp"
#include "logger.hpp"
#include "parser.hpp"
#include "replacer.hpp"

namespace xrep {

#ifdef __unix__
constexpr auto STANDART_CONFIG_PATH = "/usr/local/etc/xreplacer/conf.xml";
#elif
constexpr auto STANDART_CONFIG_PATH = "";
#endif

//------------------------------------------------------------------------------
class XReplacerCore {
    using fs_path = std::filesystem::path;
    using config_ptr = std::unique_ptr<interface::ConfiguratorInterface>;
    using parser_ptr = std::unique_ptr<interface::ParserInterface>;
    using replacer_ptr = std::unique_ptr<interface::ReplacerInterface>;

private:
    config_ptr config;
    parser_ptr parser;
    replacer_ptr replacer;

public:
    XReplacerCore();
    ~XReplacerCore() = default;

    void init(int argc, char** argv) noexcept(false);
    int run() noexcept(false);
};

}

