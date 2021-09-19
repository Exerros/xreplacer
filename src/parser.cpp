#include "parser.hpp"

namespace xrep {

FileSystemParser::FileSystemParser(const fs_path& conf_root_dir)
    : root_dir(conf_root_dir)
    , objects()
{
    if((root_dir == "") || (std::filesystem::is_directory(root_dir) == false)) {
        throw exception::parser::UnCorrectRootDir();
    }
}

//------------------------------------------------------------------------------
void FileSystemParser::search_objects_to_replase() {
    LOG(info) << "Parser starts searching for objects";

    try {
        for (fs_iterator i(root_dir); i != fs_iterator(); i = ++i) {
            if (!is_directory(i->status()))
            objects.push_back(*i);
        }

    } catch (std::exception& ex) {
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

} // namespace xrep
