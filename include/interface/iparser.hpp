#pragma once

#include <forward_list>
#include <memory>

#include "interface.hpp"

#include "pugixml.hpp"

namespace xrep {
namespace interface {
using std::forward_list;
using std::unique_ptr;

template<class Input, class Output>
class ParserInterface : Interface {
public:
    ParserInterface() = default;
    virtual ~ParserInterface() = default;

    virtual bool search_objects_to_replase(const Input& search_point) const = 0;
    virtual forward_list<unique_ptr<Output>> get_objects_to_replase() const = 0;
};

}
}
