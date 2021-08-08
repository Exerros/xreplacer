#include "parser.hpp"

namespace xrep {

FileSystemParser::FileSystemParser(const pugi::xml_node& config)
    : root_dir()
    , objects()
{
    LOG(info) << "Configuring the Parser";
    if(config.child("root_dir").value()) {
        root_dir = fs_path(config.child("root_dir").value());

    } else {
        throw exception::parser::NoRootDir();
    }
    LOG(info) << "Parser configuration was successful";
}

//------------------------------------------------------------------------------
void FileSystemParser::search_objects_to_replase() {
    LOG(info) << "Parser starts searching for objects";

    try {
        for(fs_iterator i(root_dir); i != fs_iterator(); i = ++i) {
            if(false == is_directory(i->status()))
            objects.push_back(*i);
        }

    } catch(std::exception& ex) {
        LOG(error) << ex.what();
        throw exception::parser::FileSearchError();
    }

    if(objects.empty()) throw exception::parser::NoObjects();

    LOG(info) << "Parser starts searching for objects"
              << NEXT_LINE_CONTINUE << objects.size() << " files were found";
}

//------------------------------------------------------------------------------
std::vector<std::filesystem::path>&
FileSystemParser::get_objects_to_replase() {
    return objects;
}

//------------------------------------------------------------------------------
bool FileSystemParser::has_objects_to_replace() const {
    return !objects.empty();
}

}
