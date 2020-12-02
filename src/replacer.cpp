#include "replacer.hpp"

namespace epx_test {

    Replacer::Replacer(const string& filePath)
    {
        ifstream configFile(filePath);

        configFile.seekg(0, std::ios::end);
        long length = configFile.tellg();
        configFile.seekg(0, std::ios::beg);
        char* tmpBuf = new char[static_cast<unsigned long>(length)];

        configFile.read(tmpBuf, length);
        configFile.close();
        delete[](tmpBuf);

        string fileBuf(std::move(tmpBuf));
        regex reg(upper_regular_string);
        smatch match;

        regex_search(fileBuf, match, reg);
        reg = regex(lower_regular_string);
        fileBuf = match[1].str();

        while(true == regex_search(fileBuf, match, reg)) {
            pairs.insert(make_pair(std::move(match[1]), std::move(match[3])));
            fileBuf = match.suffix();
        }
    }

//    pair<uint32_t, string> Replacer::operator() (const string& filePath) const {
//        ifstream file(filePath);
//        uint32_t replaceCount = 0;

//        return make_pair(replaceCount, std::move(filePath));
//    }
}
