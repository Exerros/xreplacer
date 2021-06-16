#pragma once

#include "interface/base.hpp"

namespace xrep {
namespace interface {

template<class Container>
/**
 * @brief The ParserInterface class is a template class interface for finding
 *        items in which you want to make a replacement. Template parameters
 *        allow you to specify all necessary data formats for working of this
 *        class.
 */
class ParserInterface : Interface {
public:
    ParserInterface() = default;
    virtual ~ParserInterface() = default;

    /**
     * @brief search_objects_to_replase is a search function for the items you
     *        need.
     * @param search_point this parameter specifies the search area for items.
     */
    virtual unsigned int search_objects_to_replase() = 0;

    /**
     * @brief get_objects_to_replase is a function for passing found items
     *        outside the class.
     * @return A container with elements, references to them, or any other
     *         object that stores elements that need to be replaced.
     */
    virtual Container& get_objects_to_replase() = 0;

    /**
     * @brief has_objects_to_replace is the function is designed to get
     *        information about whether there are items that are meant to be
     *        replaced.
     * @return True if the necessary objects were found.
     */
    virtual bool has_objects_to_replace() const = 0;
};

}
}
