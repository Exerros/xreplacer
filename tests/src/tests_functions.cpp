#include "tests_functions.hpp"

namespace tests {

    fs::path create_valid_config(
            const string& configDir,
            const string& rootDir,
            const int streams,
            const unordered_map<string, string>& pairs
    ) {
        fs::create_directories(configDir);
        fs::path configPath = configDir + "/config.txt";
        ofstream config(configPath);
        config << "root: \"" << rootDir << "\";\n"
               << "streams: " << streams << ";\n"
               << "replace:";
        for(const auto& [oldValue, newValue] : pairs) {
            config << "\n\"" << oldValue << "\" = \"" << newValue << "\"";
        }
        config << ";";
        config.close();

        return configPath;
    }

    fs::path create_file_and_fill(
            const string& pathToFile,
            const string& filename,
            const string& data,
            const unsigned long dataRepeatCount
    ) {
        fs::create_directories(pathToFile);
        fs::path filePath = pathToFile + '/' + filename + ".txt";
        ofstream file(filePath, std::ios::trunc);
        for(unsigned long i = 0; i < dataRepeatCount; ++i) {
            file << data;
        }
        file.close();

        return filePath;
    }

    void fill_stream(
            ostringstream& stream,
            const string& data,
            const unsigned long count
    ) {
        for(unsigned long i = 0; i < count; ++i) {
            stream << data;
        }
        std::flush(stream);
    }
}
