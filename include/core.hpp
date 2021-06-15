#pragma once

#include <string>
#include <filesystem>
#include <iostream>
#include <memory>

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
using std::string;
using std::shared_ptr;

#ifdef __unix__
constexpr auto STANDART_CONFIG_PATH = "/usr/local/etc/xreplacer/conf.xml";
#elif
constexpr auto STANDART_CONFIG_PATH = "";
#endif

//------------------------------------------------------------------------------
class XReplacerCore {
private:
    shared_ptr<config::XMLConfigurator> conf = nullptr;
    shared_ptr<logger::Logger> logger = nullptr;
    shared_ptr<parser::FileSystemParser> parser = nullptr;
    shared_ptr<replacer::FileDataReplacer> replacer = nullptr;

public:
    XReplacerCore() = default;
    ~XReplacerCore() = default;

    void init(int argc, char** argv) noexcept(false);
    int run() noexcept(false);
};

}

