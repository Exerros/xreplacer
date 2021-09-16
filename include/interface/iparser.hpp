#pragma once

#include <vector>
#include <filesystem>

#include "interface/base.hpp"

namespace xrep::interface {

/**
 * @brief The interface of the class responsible for obtaining objects that need
 *        to be replaced.
 */
class ParserInterface : Interface {
    using fs_path = std::filesystem::path;

public:
    ParserInterface() = default;
    virtual ~ParserInterface() = default;


    /**
     * @brief Method to search for objects along a specified path.
     */
    virtual void search_objects_to_replase() = 0;

    /**
     * @brief The method for passing found items outside the class.
     *
     * @return A container with elements, references to them, or any other
     *         object that stores elements that need to be replaced.
     */
    virtual std::vector<fs_path>& get_objects_to_replase() = 0;

    /**
     * @brief The method is designed to get information about whether there
     *        are items that are meant to be replaced.
     *
     * @return True if the necessary objects were found.
     */
    virtual bool has_objects_to_replace() const = 0;
};

} // namespace xrep::interface
