#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "exception.hpp"

namespace tests {
    using std::string;
    using std::unordered_map;
    using std::ofstream;
    using std::ostringstream;
    namespace fs = std::filesystem;

    //Создает указанный путь
    void create_directory(const fs::path& dirPath);

    //Создает корректный файл конфига с указанными значениями
    fs::path create_valid_config(
            const string& configDir,
            const string& rootDir,
            const int streams,
            const unordered_map<string, string>& pairs
            );

    //создает файл с указанным именем и заполняет его указанным количеством
    //повторений строки data
    fs::path create_file_and_fill(
            const string& pathToFile,
            const string& filename,
            const string& data,
            const unsigned long dataRepeatCount
            );

    void fill_stream(
            ostringstream& stream,
            const string& data,
            const unsigned long count
            );

}
