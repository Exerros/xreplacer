#include "parser.hpp"

namespace xrep {
namespace parser {

//------------------------------------------------------------------------------
FileSystemParser::FileSystemParser(const xml_node& config)
    : root_dir()
    , objects()
{
    if(config.child("root_dir").value()) {
        root_dir = path(config.child("root_dir").value());

    } else {
        throw exception::ConfigException();
    }
}

//------------------------------------------------------------------------------
unsigned int FileSystemParser::search_objects_to_replase() {
    unsigned int objects_count = 0;

    try {
        for(fs_iterator i(root_dir); i != fs_iterator(); i = ++i) {
            if(false == is_directory(i->status()))
            objects.push_front(*i);
            ++objects_count;
        }
    } catch(...) {
        throw exception::ParserException();
    }

    if(objects.empty()) throw exception::ParserException();

    return objects_count;
}

//------------------------------------------------------------------------------
forward_list<path>& FileSystemParser::get_objects_to_replase() {
    return objects;
}

//------------------------------------------------------------------------------
bool FileSystemParser::has_objects_to_replace() const {
    return !objects.empty();
}

}
}
