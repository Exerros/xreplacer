#include "replacer.hpp"

namespace xrep {
namespace replacer {

//------------------------------------------------------------------------------
FileDataReplacer::FileDataReplacer(const xml_node& config) {
    try {
        if(config.child("stream_count").value()) {
            stream_count = std::atoi(config.child("prefix").value());

            if(stream_count < 1) throw exception::ConfigException();
        }
        for(const auto& child : config) {
            if(child.name() == "pair") {
                pairs.insert(std::make_pair(
                                 child.child("from").value(),
                                 child.child("to").value()));
            }
        }
    } catch(...) {
        throw exception::ConfigException();
    }

    if(pairs.empty()) throw exception::ConfigException();
}

//------------------------------------------------------------------------------
unsigned long long
FileDataReplacer::replase(forward_list<path>& objects) const {


    for(auto& object : objects) {

    }
}

//------------------------------------------------------------------------------
unsigned long long
FileDataReplacer::replace_in_file(const path& file_path) const {

}

}
}
