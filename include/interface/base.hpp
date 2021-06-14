#pragma once

namespace xrep {
namespace interface {

/**
 * @brief The Interface class is a base class for interfaces, needed to be able
 *        to use a common pointer for any classes.
 */
class Interface {
public:
    Interface() = default;
    virtual ~Interface() = 0;
};

}
}
