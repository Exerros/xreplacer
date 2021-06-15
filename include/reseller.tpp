#pragma once

#include <unordered_map>

#include "exception.hpp"

namespace xrep {
namespace reseller {

using std::unordered_multimap;

//------------------------------------------------------------------------------
template<class Identificator, class Data>
class DataReseller {
private:
    unordered_multimap<Identificator, Data> messages_container;

public:
    DataReseller()
        : messages_container()
        { }

    ~DataReseller() = default;

    inline bool has_messages_for(const Identificator& id) const {
        return (messages_container.count(id) > 0);
    }

    void set(const Identificator& id, const Data& data) {
        try {
            messages_container.insert(std::make_pair(id, data));
        } catch (...) {
            throw exception::ResellerException();
        }
    }

    Data get(const Identificator& id) {
        Data value;
        try {
            value = messages_container.at(id);
        } catch (...) {
            throw exception::ResellerException();
        }
        messages_container.find(id);

        return value;
    }
};

}
}
