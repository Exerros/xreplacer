#include "replacer.hpp"

namespace xrep {

//------------------------------------------------------------------------------
FileDataReplacer::FileDataReplacer(const pugi::xml_node& config)
    : pairs()
    , stream_counter()
    , max_stream_count(1)
    , threading_sleep_time(5ms)
{
    try {
        if(config.child("stream_count").value()) {
            max_stream_count = std::atoi(config.child("prefix").value());

            if(max_stream_count < 1) throw ConfigException();
        }

        if(config.child("thread_start_waiting_ms").value()) {
            threading_sleep_time = duration_t(std::atoi(
                        config.child("thread_start_waiting_ms").value()));

            if(threading_sleep_time < 5ms) throw ConfigException();
        }

        for(const auto& child : config) {
            if(child.name() == pugi::string_t("pair")) {

                pairs.insert(std::make_pair(
                                 child.child("from").value(),
                                 child.child("to").value()));
            }
        }
    } catch(...) {
        throw ConfigException();
    }

    if(pairs.empty()) throw ConfigException();
}

//------------------------------------------------------------------------------
void FileDataReplacer::replase(std::forward_list<fs_path>& objects) const {
    counter_ptr stream_counter(new std::atomic<unsigned int>(0));
    auto files_iter = objects.begin();
    std::vector<std::unique_ptr<std::thread>> t;

    while(files_iter != objects.end()) {
        if(*stream_counter < max_stream_count) {
            t.push_back(std::unique_ptr<std::thread>(new std::thread(
                    replace_in_file,
                    std::cref(files_iter),
                    stream_counter)));

            files_iter++;
            ++(*stream_counter);

        } else {
            sleep_for(threading_sleep_time);
        }
    }
    for(const auto& thread : t) {
        thread->join();
    }
}

//------------------------------------------------------------------------------
std::string FileDataReplacer::get_buffer_from(const fs_path& filePath) {
    unsigned long length(0);
    std::ifstream file;

    try {
        length = file_size(filePath);
        file.open(filePath);

    } catch (...) {
        throw ReplacerException();
    }

    std::string buffer(length, '\0');
    file.read(buffer.data(), static_cast<long>(length));

    if(file.good() != true) throw ReplacerException();
    file.close();

    return buffer;
}

//------------------------------------------------------------------------------
void
FileDataReplacer::
write_buffer_to_file(const std::string& buffer, const fs_path& filePath) {
    std::ofstream output_file(filePath, std::ios::trunc);
    output_file << buffer;

    if(output_file.good() != true) throw ReplacerException();
    output_file.close();
}

//------------------------------------------------------------------------------
void FileDataReplacer::replace_in_file(
        const fs_path& file_path,
        const pairs_map& pairs,
        counter_ptr stream_counter) {
    std::string file_buffer(get_buffer_from(file_path));
    std::string result;

    for(const auto& [oldValue, newValue] : pairs) {
        std::regex_replace(
            std::back_inserter(result),
            file_buffer.begin(),
            file_buffer.end(),
            std::regex(oldValue),
            newValue);

        file_buffer = std::move(result);
    }

    write_buffer_to_file(file_buffer, file_path);
    --(*stream_counter);
}

}
