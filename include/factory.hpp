#pragma once

#include <memory>
#include <string>

#include "pugixml.hpp"

#include "interface/base.hpp"

namespace xrep {
namespace factory {

using std::shared_ptr;
using std::string;
using pugi::xml_node;

//------------------------------------------------------------------------------
template<class T>
shared_ptr<interface::Interface> get_object(
        const string& instance,
        const xml_node& config) {
    return shared_ptr<T>(new T(instance, config));
}

}
}
