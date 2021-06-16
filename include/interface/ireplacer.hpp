#pragma once

#include "interface/base.hpp"

namespace xrep {
namespace interface {

template<class ObjectContainer>
/**
 * @brief The ReplacerInterface class is the template interface of the
 *        substitution handler class. This class gets a container with objects
 *        for replacements and makes replacements according to the
 *        implementation.
 */
class ReplacerInterface : Interface {
public:
    ReplacerInterface() = default;
    virtual ~ReplacerInterface() = default;

    /**
     * @brief replase function starts the data replacement process according to
     *        the implementation.
     * @param container Is an object storing elements in which it is necessary
     *        to make replacements.
     */
    virtual unsigned long long replase(ObjectContainer& container) const = 0;
};

}
}
