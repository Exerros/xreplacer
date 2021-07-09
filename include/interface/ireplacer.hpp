#pragma once

#include <forward_list>
#include <filesystem>

#include "interface/base.hpp"

namespace xrep::interface {

/**
 * @brief The ReplacerInterface class is the template interface of the
 *        substitution handler class. This class gets a container with objects
 *        for replacements and makes replacements according to the
 *        implementation.
 */
class ReplacerInterface : Interface {
    using fs_path = std::filesystem::path;

public:
    ReplacerInterface() = default;
    virtual ~ReplacerInterface() = default;

    /**
     * @brief replase function starts the data replacement process according to
     *        the implementation.
     * @param container Is an object storing elements in which it is necessary
     *        to make replacements.
     */
    virtual void replase(std::forward_list<fs_path>& container) const = 0;
};

}
