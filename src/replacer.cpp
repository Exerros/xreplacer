#include "replacer.hpp"

namespace xrep {
namespace replacer {

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

            if(pairs.size() == 0) throw exception::ConfigException();
        }
    } catch(...) {
        throw exception::ConfigException();
    }
}

bool FileDataReplacer::replase(fs::path& object) const {

}
}
}
