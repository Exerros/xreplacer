#include "replacer.hpp"

namespace xrep {
namespace replacer {

//------------------------------------------------------------------------------
FileDataReplacer::FileDataReplacer(const xml_node& config)
    : pairs()
    , replace_counter()
    , stream_counter()
    , max_stream_count(1)
{
    try {
        if(config.child("stream_count").value()) {
            max_stream_count = std::atoi(config.child("prefix").value());

            if(max_stream_count < 1) throw exception::ConfigException();
        }
        for(const auto& child : config) {
            if(child.name() == pugi::string_t("pair")) {

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
string FileDataReplacer::get_buffer_from(const path& filePath) const {
    unsigned long length(0);
    ifstream file;

    try {
        length = file_size(filePath);
        file.open(filePath);
    } catch (...) {
        throw exception::ReplacerException();
    }

    string buffer(length, '\0');
    file.read(buffer.data(), static_cast<long>(length));

    if(file.good() != true) throw exception::ReplacerException();
    file.close();

    return buffer;
}

void
FileDataReplacer::
write_buffer_to_file(string& buffer, const path& filePath) const {
    ofstream output_file(filePath, std::ios::trunc);
    output_file << std::move(buffer);

    if(output_file.good() != true) throw exception::ReplacerException();
    output_file.close();
}

//------------------------------------------------------------------------------
unsigned long long
FileDataReplacer::replace_in_file(const path& file_path) const {
    string file_buffer(get_buffer_from(file_path));



}

}
}
