#include "tests_functions.hpp"

namespace tests {

    void create_directory(const fs::path& dirPath) {
        fs::create_directory(dirPath);
    }

    fs::path create_valid_config(
            const string& rootDir,
            const unsigned long streams,
            const unordered_map<string, string>& pairs
    ) {
        fs::path configPath = rootDir + "/config.txt";
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
        fs::path filePath = pathToFile + filename + ".txt";
        ofstream file(filePath);
        for(unsigned long i = 0; i < dataRepeatCount; ++i) {
            file << data << '\n';
        }
        file.close();

        return filePath;
    }
}
