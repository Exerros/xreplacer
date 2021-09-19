#pragma once

#include <vector>
#include <filesystem>

#include "interface/base.hpp"

namespace xrep::interface {

/**
 * @brief The interface of the class producing replacements according to the
 *        configuration in the passed objects.
 */
class ReplacerInterface : Interface {
    using fs_path = std::filesystem::path;

public:
    ReplacerInterface() = default;
    virtual ~ReplacerInterface() = default;

    /**
     * @brief A method that performs replacements in the passed files.
     *
     * @param container Сontainer with the objects in which the replacement will
     *        be made.
     */
    virtual void replace(std::vector<fs_path>& container) const = 0;
};

} // namespace xrep::interface
