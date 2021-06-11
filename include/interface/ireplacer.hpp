#pragma once

#include "interface.hpp"

namespace xrep {
namespace interface {

template<class T>
class ReplacerInterface : Interface {
public:
    ReplacerInterface() = default;
    virtual ~ReplacerInterface() = default;

    virtual bool replase(T& object) const = 0;
};

}
}
