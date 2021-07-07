#include "replacer.hpp"

namespace xrep::replacer {

//------------------------------------------------------------------------------
FileDataReplacer::FileDataReplacer(const xml_node& config)
    : pairs()
    , stream_counter()
    , max_stream_count(1)
    , threading_sleep_time(5ms)
{
    try {
        if(config.child("stream_count").value()) {
            max_stream_count = std::atoi(config.child("prefix").value());

            if(max_stream_count < 1) throw exception::ConfigException();
        }

        if(config.child("thread_start_waiting").value()) {
            threading_sleep_time = duration_t(std::atoi(
                        config.child("thread_start_waiting").value()));

            if(threading_sleep_time < 5ms) throw exception::ConfigException();
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
    shared_ptr<atomic<unsigned long long>> replace_counter(
                new atomic<unsigned long long>(0));
    shared_ptr<atomic<unsigned int>> stream_counter(new atomic<unsigned int>(0));
    auto files_iter = objects.begin();
    std::deque<std::thread*> t;
    bool threads_more_than_used = false;

    while(files_iter != objects.end()) {
        if(*stream_counter < max_stream_count) {
            t.push_front(new std::thread(
                    replace_in_file,
                    std::cref(files_iter),
                    stream_counter));

            files_iter++;
            ++(*stream_counter);

            if(threads_more_than_used) {
                t.pop_back();
            }
        } else {
            sleep_for(threading_sleep_time);
            threads_more_than_used = true;
        }
    }
    for(const auto& thread : t) {
        thread->join();
    }

    return *replace_counter;
}

//------------------------------------------------------------------------------
string FileDataReplacer::get_buffer_from(const path& filePath) {
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


//------------------------------------------------------------------------------
void
FileDataReplacer::
write_buffer_to_file(const string& buffer, const path& filePath) {
    ofstream output_file(filePath, std::ios::trunc);
    output_file << buffer;

    if(output_file.good() != true) throw exception::ReplacerException();
    output_file.close();
}

//------------------------------------------------------------------------------
void FileDataReplacer::replace_in_file(
        const path& file_path,
        const pairs_map& pairs,
        shared_ptr<atomic<unsigned int>> stream_counter) {
    string file_buffer(get_buffer_from(file_path));
    string result;

    for(const auto& [oldValue, newValue] : pairs) {
        regex_replace(
            std::back_inserter(result),
            file_buffer.begin(),
            file_buffer.end(),
            regex(oldValue),
            newValue);

        file_buffer = std::move(result);
    }

    write_buffer_to_file(file_buffer, file_path);
    --(*stream_counter);
}

}
