#include "replacer.hpp"

#define DO_NOTHING ((void)())

namespace xrep {

FileDataReplacer::FileDataReplacer(const pugi::xml_node& config)
    : pairs()
    , thread_count(std::thread::hardware_concurrency())
{
    LOG(info) << "Configuring the Replacer";
    try {
        if(config.child("thread_count").value()) {
            int new_thread_count = std::atoi(
                        config.child("thread_count").value());

            if(new_thread_count >= 1)
                thread_count = static_cast<unsigned int>(new_thread_count);
            else
                throw exception::replacer::IncorrectThreadsCount();
        }

        for(const auto& child : config) {
            if(child.name() == pugi::string_t("pair")) {

                pairs.insert(std::make_pair(
                                 child.child("from").value(),
                                 child.child("to").value()));
            }
        }

        if(pairs.empty()) throw exception::replacer::NoPairs();
    }
    catch(std::exception& ex) {
        throw ex;
    }

    LOG(info) << "Replaser configuration was successful\n"
              << NEXT_LINE_CONTINUE << pairs.size() << " pairs were found";
}

//------------------------------------------------------------------------------
void FileDataReplacer::replase(std::vector<fs_path>& objects) const {
    std::vector<std::unique_ptr<std::thread>> t{ thread_count };
    auto separated_files = chop_objects_container(objects);

    LOG(info) << "Replacer starts processing files";

    for(const auto& files_group : separated_files) {
    t.push_back(std::unique_ptr<std::thread>(new std::thread(
        replace_in_files,
        std::cref(files_group),
        std::cref(pairs))));
    }

    for(const auto& thread : t) {
        thread->join();
    }

    LOG(info) << "Replacer has finished processing files";
}

//------------------------------------------------------------------------------
std::string FileDataReplacer::get_buffer_from(const fs_path& filePath) {
    unsigned long length(0);
    std::ifstream file;

    try {
        length = file_size(filePath);
        file.open(filePath);

    } catch (std::exception& ex) {
        LOG(error) << ex.what();
        throw exception::replacer::FileReadException();
    }

    std::string buffer(length, '\0');
    file.read(buffer.data(), static_cast<long>(length));

    if(file.good() != true)
        throw exception::replacer::FileReadException();
    file.close();

    return buffer;
}

//------------------------------------------------------------------------------
void FileDataReplacer::
write_buffer_to_file(const std::string& buffer, const fs_path& filePath) {
    std::ofstream output_file(filePath, std::ios::trunc);
    output_file << buffer;

    if(output_file.good() != true)
        throw exception::replacer::FileWriteException();
    output_file.close();
}

//------------------------------------------------------------------------------
void FileDataReplacer::replace_in_files(
        const std::vector<fs_path>& files_paths,
        const pairs_map& pairs)
{
    for(const auto& file : files_paths) {
        std::string file_buffer(get_buffer_from(file));
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

        write_buffer_to_file(file_buffer, file);
    }
}

//------------------------------------------------------------------------------
std::vector<std::vector<std::filesystem::path>>
FileDataReplacer::
chop_objects_container(std::vector<fs_path>& container) const{
    auto object_count_for_thread = container.size() / thread_count;

    if (object_count_for_thread == 1) return {container};

    std::vector<std::vector<fs_path>> result{object_count_for_thread};

    for (auto i = container.begin(), j = next(i, object_count_for_thread);
         j != container.end();
         i = j, j = next(i, object_count_for_thread))
    {
        result.push_back(std::vector(i, j));
    }

    return result;
}

}
