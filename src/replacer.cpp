#include "replacer.hpp"

namespace xrep {

FileDataReplacer::
FileDataReplacer(pairs_map config_pairs, unsigned int config_thread_count)
    : pairs(config_pairs)
    , thread_count(std::thread::hardware_concurrency())
{
    LOG(info) << "Configuring the Replacer";
    if (config_thread_count >= 1)
        thread_count = static_cast<unsigned int>(config_thread_count);
    else
        throw exception::replacer::IncorrectThreadsCount();

    LOG(info) << "Replaser configuration was successful"
              << NEXT_LINE_CONTINUE << thread_count << " streams will be used"
              << NEXT_LINE_CONTINUE << pairs.size() << " pairs were found";
}

//------------------------------------------------------------------------------
void FileDataReplacer::replase(std::vector<fs_path>& objects) const {
    std::vector<std::unique_ptr<std::thread>> treads {};
    auto separated_files = chop_objects_container(objects);

    LOG(info) << "Replacer starts processing files";

    for (const auto& files_group : separated_files) {
        treads.push_back(std::unique_ptr<std::thread>(new std::thread(
            replace_in_files,
            std::cref(files_group),
            std::cref(pairs))));
    }

    for (const auto& thread : treads) {
        thread->join();
    }

    LOG(info) << "Replacer has finished processing files";
}

//------------------------------------------------------------------------------
std::string FileDataReplacer::get_buffer_from(const fs_path& filePath) {
    unsigned long length {};
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

    if (file.good() != true)
        throw exception::replacer::FileReadException();
    file.close();

    return buffer;
}

//------------------------------------------------------------------------------
void FileDataReplacer::
write_buffer_to_file(const std::string& buffer, const fs_path& filePath) {
    std::ofstream output_file(filePath, std::ios::trunc);
    output_file << buffer;

    if (output_file.good() != true)
        throw exception::replacer::FileWriteException();
    output_file.close();
}

//------------------------------------------------------------------------------
void FileDataReplacer::replace_in_files(
        const std::vector<fs_path>& files_paths,
        const pairs_map& pairs)
{
    for (const auto& file : files_paths) {
        LOG(info) << "Starts a replacement in file " << file;

        std::string file_buffer(get_buffer_from(file));
        std::string temp {};

        for (const auto& [oldValue, newValue] : pairs) {
            std::regex_replace(
                std::back_inserter(temp),
                file_buffer.begin(),
                file_buffer.end(),
                std::regex(oldValue),
                newValue);

            file_buffer = std::move(temp);
        }

        write_buffer_to_file(file_buffer, file);

        LOG(info) << "Replacement completed in file " << file;
    }
}

//------------------------------------------------------------------------------
std::vector<std::vector<std::filesystem::path>>
FileDataReplacer::
chop_objects_container(std::vector<fs_path>& container) const {
    size_t object_count_for_thread {};

    if (container.size() == 1) { return { container }; }

    if (container.size() <= thread_count) {
        object_count_for_thread = 1;

    } else {
        object_count_for_thread = container.size() / thread_count;
    }

    std::vector<std::vector<fs_path>> result {};
    auto i = container.begin();
    auto j = std::min(container.end(), next(i, object_count_for_thread));

    while(i != container.end()) {
        result.push_back(std::vector(i, std::min(j, container.end())));
        i = j;
        j = std::min(container.end(), next(i, object_count_for_thread));
    }

    return result;
}

} // namespace xrep
