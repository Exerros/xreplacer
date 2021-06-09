#pragma once

#include <filesystem>

#include "configurator.hpp"
#include "exception.hpp"
#include "logger.hpp"
#include "parser.hpp"
#include "replacer.hpp"

//------------------------------------------------------------------------------
namespace xrep {

class XReplacerCore {
public:
    XReplacerCore() = default;
    ~XReplacerCore() = default;

    bool init(int );
};

}

