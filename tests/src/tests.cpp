#include "tests.hpp"
#include "test_runner.h"

namespace tests {

    void config_tests() {
        using namespace ya_test_runner;

        std::cerr << "Started config tests:\n";
        TestRunner tr;
        //проверка чтения правильного конфига
        RUN_TEST(tr, test_correct_config);
        //проверка чтения пустого конфига
        RUN_TEST(tr, test_void_config);
        //проверка конфига при неверном указании пути
        RUN_TEST(tr, test_uncorrect_rootdir);
        //проверка с неверным числом потоков
        RUN_TEST(tr, test_uncorrect_streams);
        //проверка с пустым блоком пар
        RUN_TEST(tr, test_null_pairs);
        //проверка с парами записанными в одну строку
        RUN_TEST(tr, test_oneline_pairs);
        //проверка с парами записанными как попало
        RUN_TEST(tr, test_strange_placed_pairs);
        //проверка поведения при отсутствии конфига
        RUN_TEST(tr, test_no_config_file);
        std::cerr << "Finished config tests.\n\n";
    }

    void replacer_tests() {
        using namespace ya_test_runner;

        std::cerr << "Started replacer tests:\n";
        TestRunner tr;
        //проверка проведения замены при корректных условиях
        RUN_TEST(tr, test_correct_replace);
        //проверка когда в файле нечего заменять
        RUN_TEST(tr, test_nothing_to_replace);
        //проверка когда в файле встречаются не все искомые пары
        RUN_TEST(tr, test_only_one_of_pairs);
        //проверка случая когда файла для замен нет
        RUN_TEST(tr, test_no_file_to_replace);
        std::cerr << "Finished replacer tests.\n\n";
    }

    void parser_tests() {
        using namespace ya_test_runner;

        std::cerr << "Started parser tests:\n";
        TestRunner tr;
        //проверка корректной работы
        RUN_TEST(tr, test_correct_parse);
        //проверка с корректным конфигом но отсутствующим путем
        RUN_TEST(tr, test_no_files);
        //проверка когда потоков больше чем файлов
        RUN_TEST(tr, test_too_much_streams);
        //проверка однопоточного исполнения
        RUN_TEST(tr, test_one_stream);
        //проверка работоспособности строк использующих различные символы
        RUN_TEST(tr, test_symbols);
        //проверка случая когда строка, на которую заменено значение, больше чем
        //строка которая была заменена
        RUN_TEST(tr, test_bigger);
        //Проверка случая когда заменяемая строка больше чем результирующая
        RUN_TEST(tr, test_smaller);
        std::cerr << "Finished parser tests.\n\n";
    }

    void test_correct_config() {
        using namespace ya_test_runner;

        string configDir("tests/test_correct_config");
        string root("tests/test_correct_config/dir");
        unsigned long streams(10);
        unordered_map<string, string> pairs;
        pairs["a"] = "b";
        pairs["c"] = "d";
        pairs["e"] = "f";

        auto configPath = create_valid_config(
                    configDir,
                    root,
                    static_cast<int>(streams),
                    pairs
                    );
        std::ostringstream tmpStream;
        epx_test::Configurator config(configPath, &tmpStream);

        ASSERT_EQUAL(config.maxStreamCount, streams);
        ASSERT_EQUAL(config.rootDirectory, root);
        for(const auto& [oldValue, newValue] : pairs) {
            ASSERT_EQUAL(config.pairs.at(oldValue), newValue);
        }
    }

    void test_void_config() {
        using namespace ya_test_runner;

        bool result = false;
        string configDir("tests/test_void_config");
        fs::create_directories(configDir);
        fs::path configPath = configDir + "/config.txt";
        ofstream configFile(configPath);
        configFile << '\n';
        configFile.close();

        std::ostringstream tmpStream;
        try {
            epx_test::Configurator config(configPath, &tmpStream);
        } catch (...) {
            result = true;
        }
        ASSERT(result);
    }

    void test_uncorrect_rootdir() {
        using namespace ya_test_runner;

        bool result = false;
        string configDir("tests/test_uncorrect_rootdir");
        string root("tests/test_uncorrect_rootdir///\\.?1  \n1f");
        int streams(10);
        unordered_map<string, string> pairs;
        pairs["a"] = "b";
        pairs["c"] = "d";
        pairs["e"] = "f";

        auto configPath = create_valid_config(configDir, root, streams, pairs);
        std::ostringstream tmpStream;
        try {
            epx_test::Configurator config(configPath, &tmpStream);
        } catch (...) {
            result = true;
        }
        ASSERT(result);
    }

    void test_uncorrect_streams() {
        using namespace ya_test_runner;

        bool result = false;
        string configDir("tests/test_uncorrect_streams");
        string root("tests/test_uncorrect_streams/dir");
        int streams(-358);
        unordered_map<string, string> pairs;
        pairs["a"] = "b";
        pairs["c"] = "d";
        pairs["e"] = "f";

        auto configPath = create_valid_config(configDir, root, streams, pairs);
        std::ostringstream tmpStream;
        try {
            epx_test::Configurator config(configPath, &tmpStream);
        } catch (...) {
            result = true;
        }
        ASSERT(result);
    }

    void test_null_pairs() {
        using namespace ya_test_runner;

        bool result = false;
        string configDir("tests/test_null_pairs");
        string root("tests/test_null_pairs/dir");
        int streams(10);
        unordered_map<string, string> pairs;

        auto configPath = create_valid_config(configDir, root, streams, pairs);
        std::ostringstream tmpStream;
        try {
            epx_test::Configurator config(configPath, &tmpStream);
        } catch (...) {
            result = true;
        }
        ASSERT(result);
    }

    void test_oneline_pairs() {
        using namespace ya_test_runner;

        string configDir("tests/test_oneline_pairs/");
        string root("tests/test_oneline_pairs/dir");
        string pairs("\"a\"= \"b\"\"c\" =\"d\"\"e\"=\"f\"");
        int streams(10);
        unordered_map<string, string> correct_pairs;
        correct_pairs["a"] = "b";
        correct_pairs["c"] = "d";
        correct_pairs["e"] = "f";

        fs::create_directories(configDir);
        fs::path configPath = configDir + "/config.txt";
        ofstream configFile(configPath);
        configFile << "root: \"" << root << "\";\n"
               << "streams: " << streams << ";\n"
               << "replace:" << pairs << ";\n";

        configFile.close();

        std::ostringstream tmpStream;
        epx_test::Configurator config(configPath, &tmpStream);

        for(const auto& [oldValue, newValue] : correct_pairs) {
            ASSERT_EQUAL(config.pairs.at(oldValue), newValue);
        }
    }

    void test_strange_placed_pairs() {
        using namespace ya_test_runner;

        string configDir("tests/test_strange_placed_pairs/");
        string root("tests/test_strange_placed_pairs/dir");
        string pairs("\"a\"\t\t= \"b\"asdf\t\n\t\"c\" =\"d\"   11 \"e\"=\"f\"");
        int streams(10);
        unordered_map<string, string> correct_pairs;
        correct_pairs["a"] = "b";
        correct_pairs["c"] = "d";
        correct_pairs["e"] = "f";

        fs::create_directories(configDir);
        fs::path configPath = configDir + "/config.txt";
        ofstream configFile(configPath);
        configFile << "root: \"" << root << "\";\n"
               << "streams: " << streams << ";\n"
               << "replace:" << pairs << ";\n";

        configFile.close();

        std::ostringstream tmpStream;
        epx_test::Configurator config(configPath, &tmpStream);

        for(const auto& [oldValue, newValue] : correct_pairs) {
            ASSERT_EQUAL(config.pairs.at(oldValue), newValue);
        }
    }

    void test_no_config_file() {
        using namespace ya_test_runner;

        string configPath("tests/test_no_config_file/config.txt");
        std::ostringstream tmpStream;
        bool result = false;

        try {
            epx_test::Configurator config(configPath, &tmpStream);
        } catch (...) {
            result = true;
        }
        ASSERT(result);
    }

    void test_correct_replace() {
        using namespace ya_test_runner;

        string configDir("tests/test_correct_replace");
        string root("tests/test_correct_replace/dir");
        int streams(1);
        unordered_map<string, string> pairs;
        pairs["a"] = "b";
        pairs["c"] = "d";
        pairs["e"] = "f";

        auto configPath = create_valid_config(configDir, root, streams, pairs);
        create_directory(root);
        auto filePath = create_file_and_fill(root, "file", "a c e ", 50);
        std::ostringstream correct_result;
        fill_stream(correct_result, "b d f ", 50);

        std::ostringstream tmpStream;
        std::ostringstream result;

        std::atomic<unsigned long> tmpCounter;
        epx_test::Configurator config(configPath, &tmpStream);
        epx_test::Replacer replacer(config);
        replacer.replace_in(filePath, &tmpCounter);

        ifstream resultFile(filePath);
        result << resultFile.rdbuf();

        ASSERT_EQUAL(correct_result.str(), result.str());
    }

    void test_nothing_to_replace() {
        using namespace ya_test_runner;

        string configDir("tests/test_nothing_to_replace");
        string root("tests/test_nothing_to_replace/dir");
        int streams(1);
        unordered_map<string, string> pairs;
        pairs["a"] = "b";
        pairs["c"] = "d";
        pairs["e"] = "f";

        auto configPath = create_valid_config(configDir, root, streams, pairs);
        create_directory(root);
        auto filePath = create_file_and_fill(root, "file", "b d f ", 50);
        std::ostringstream correct_result;
        fill_stream(correct_result, "b d f ", 50);

        std::ostringstream tmpStream;
        std::ostringstream result;

        std::atomic<unsigned long> tmpCounter;
        epx_test::Configurator config(configPath, &tmpStream);
        epx_test::Replacer replacer(config);
        replacer.replace_in(filePath, &tmpCounter);

        ifstream resultFile(filePath);
        result << resultFile.rdbuf();

        using type = decltype (correct_result.str());
        ASSERT_EQUAL(
                    std::hash<type>{}(correct_result.str()),
                    std::hash<type>{}(result.str())
                    );
    }

    void test_only_one_of_pairs() {
        using namespace ya_test_runner;

        string configDir("tests/test_only_one_of_pairs");
        string root("tests/test_only_one_of_pairs/dir");
        int streams(1);
        unordered_map<string, string> pairs;
        pairs["a"] = "b";
        pairs["c"] = "d";
        pairs["e"] = "f";

        auto configPath = create_valid_config(configDir, root, streams, pairs);
        create_directory(root);
        auto filePath = create_file_and_fill(root, "file", "a a a\n", 50);
        std::ostringstream correct_result;
        fill_stream(correct_result, "b b b\n", 50);

        std::ostringstream tmpStream;
        std::ostringstream result;

        std::atomic<unsigned long> tmpCounter;
        epx_test::Configurator config(configPath, &tmpStream);
        epx_test::Replacer replacer(config);
        replacer.replace_in(filePath, &tmpCounter);

        ifstream resultFile(filePath);
        result << resultFile.rdbuf();
        resultFile.close();

        using type = decltype (correct_result.str());
        ASSERT_EQUAL(
                    std::hash<type>{}(correct_result.str()),
                    std::hash<type>{}(result.str())
                    );
    }

    void test_no_file_to_replace() {
        using namespace ya_test_runner;

        string configDir("tests/test_no_file_to_replace");
        string root("tests/test_no_file_to_replace/dir");
        int streams(1);
        unordered_map<string, string> pairs;
        pairs["a"] = "b";
        pairs["c"] = "d";
        pairs["e"] = "f";
        auto filePath = root + '/' + "file.txt";
        bool result = false;
        auto configPath = create_valid_config(configDir, root, streams, pairs);

        std::ostringstream tmpStream;
        std::atomic<unsigned long> tmpCounter;

        epx_test::Configurator config(configPath, &tmpStream);
        epx_test::Replacer replacer(config);
        try {
            replacer.replace_in(filePath, &tmpCounter);
        } catch (...) {
            result = true;
        }
        ASSERT(result);
    }

    void test_correct_parse() {
        using namespace ya_test_runner;

        string configDir("tests/test_correct_parse");
        string root("tests/test_correct_parse/dir/");
        int streams(10);
        unordered_map<string, string> pairs;
        pairs["hello"] = "HELLO";
        pairs["world"] = "WORLD";
        pairs["apple"] = "ApPlE";
        pairs["orange"] = "Orange";
        auto configPath = create_valid_config(configDir, root, streams, pairs);
        std::vector<fs::path> files;
        for(char ch = 'a'; ch <= 'z'; ++ch) {
            files.push_back(create_file_and_fill(
                        root,
                        string(3, ch),
                        "hello world apple orange\n",
                        50
                        ));
        }
        std::ostringstream tmpStream;
        epx_test::Parser parser(configPath, &tmpStream);
        parser.replace_data();
        std::ostringstream correct_result;
        fill_stream(
                    correct_result,
                    "HELLO WORLD ApPlE Orange\n",
                    50
                    );
        using type = decltype (correct_result.str());
        auto correct_hash = std::hash<type>{}(correct_result.str());

        for(const auto& filePath : files) {
            std::ostringstream result(epx_test::get_buffer_from(filePath));

            ASSERT_EQUAL(correct_hash, std::hash<type>{}(result.str()));
            result.clear();
        }
    }

    void test_no_files() {
        using namespace ya_test_runner;

        string configDir("tests/test_no_files");
        string root("tests/test_no_files/dir/");
        int streams(10);
        unordered_map<string, string> pairs;
        pairs["hello"] = "HELLO";
        pairs["world"] = "WORLD";
        pairs["apple"] = "ApPlE";
        pairs["orange"] = "Orange";
        auto configPath = create_valid_config(configDir, root, streams, pairs);
        std::ostringstream tmpStream;
        bool result = false;

        try {
            epx_test::Parser parser(configPath, &tmpStream);
        } catch (...) {
            result = true;
        }
        ASSERT(result);
    }

    void test_too_much_streams() {
        using namespace ya_test_runner;

        string configDir("tests/test_too_much_streams");
        string root("tests/test_too_much_streams/dir/");
        int streams(100);
        unordered_map<string, string> pairs;
        pairs["hello"] = "HELLO";
        pairs["world"] = "WORLD";
        pairs["apple"] = "ApPlE";
        pairs["orange"] = "Orange";
        auto configPath = create_valid_config(configDir, root, streams, pairs);
        std::vector<fs::path> files;
        for(char ch = 'a'; ch <= 'z'; ++ch) {
            files.push_back(create_file_and_fill(
                        root,
                        string(3, ch),
                        "hello world apple orange\n",
                        50
                        ));
        }
        std::ostringstream tmpStream;
        epx_test::Parser parser(configPath, &tmpStream);
        parser.replace_data();
        std::ostringstream correct_result;
        fill_stream(
                    correct_result,
                    "HELLO WORLD ApPlE Orange\n",
                    50
                    );
        using type = decltype (correct_result.str());
        auto correct_hash = std::hash<type>{}(correct_result.str());

        for(const auto& filePath : files) {
            std::ostringstream result(epx_test::get_buffer_from(filePath));

            ASSERT_EQUAL(correct_hash, std::hash<type>{}(result.str()));
            result.clear();
        }
    }

    void test_one_stream() {
        using namespace ya_test_runner;

        string configDir("tests/test_too_much_streams");
        string root("tests/test_too_much_streams/dir/");
        int streams(1);
        unordered_map<string, string> pairs;
        pairs["hello"] = "HELLO";
        pairs["world"] = "WORLD";
        pairs["apple"] = "ApPlE";
        pairs["orange"] = "Orange";
        auto configPath = create_valid_config(configDir, root, streams, pairs);
        std::vector<fs::path> files;
        for(char ch = 'a'; ch < 'a' + 10; ++ch) {
            files.push_back(create_file_and_fill(
                        root,
                        string(3, ch),
                        "hello world apple orange\n",
                        50
                        ));
        }
        std::ostringstream tmpStream;
        epx_test::Parser parser(configPath, &tmpStream);
        parser.replace_data();
        std::ostringstream correct_result;
        fill_stream(
                    correct_result,
                    "HELLO WORLD ApPlE Orange\n",
                    50
                    );
        using type = decltype (correct_result.str());
        auto correct_hash = std::hash<type>{}(correct_result.str());

        for(const auto& filePath : files) {
            std::ostringstream result(epx_test::get_buffer_from(filePath));

            ASSERT_EQUAL(correct_hash, std::hash<type>{}(result.str()));
            result.clear();
        }
    }

    void test_symbols() {
        using namespace ya_test_runner;

        string configDir("tests/test_symbols");
        string root("tests/test_symbols/dir/");
        int streams(10);
        unordered_map<string, string> pairs;
        pairs["<. ,!@%&-_=>"] = "!!!SYMBOLS!!!";
        auto configPath = create_valid_config(configDir, root, streams, pairs);
        std::vector<fs::path> files;
        for(char ch = 'a'; ch <= 'z'; ++ch) {
            files.push_back(create_file_and_fill(
                        root,
                        string(3, ch),
                        "<. ,!@%&-_=> \n",
                        50
                        ));
        }
        std::ostringstream tmpStream;
        epx_test::Parser parser(configPath, &tmpStream);
        parser.replace_data();
        std::ostringstream correct_result;
        fill_stream(
                    correct_result,
                    "!!!SYMBOLS!!! \n",
                    50
                    );
        using type = decltype (correct_result.str());
        auto correct_hash = std::hash<type>{}(correct_result.str());

        for(const auto& filePath : files) {
            string result(epx_test::get_buffer_from(filePath));
            ASSERT_EQUAL(correct_hash, std::hash<type>{}(result));
        }
    }

    void test_bigger() {
        using namespace ya_test_runner;

        string configDir("tests/test_bigger");
        string root("tests/test_bigger/dir/");
        int streams(10);
        unordered_map<string, string> pairs;
        pairs["small"] = "VERY BIG";
        auto configPath = create_valid_config(configDir, root, streams, pairs);
        std::vector<fs::path> files;
        for(char ch = 'a'; ch <= 'z'; ++ch) {
            files.push_back(create_file_and_fill(
                        root,
                        string(3, ch),
                        "small \n",
                        50
                        ));
        }
        std::ostringstream tmpStream;
        epx_test::Parser parser(configPath, &tmpStream);
        parser.replace_data();
        std::ostringstream correct_result;
        fill_stream(
                    correct_result,
                    "VERY BIG \n",
                    50
                    );
        using type = decltype (correct_result.str());
        auto correct_hash = std::hash<type>{}(correct_result.str());

        for(const auto& filePath : files) {
            string result(epx_test::get_buffer_from(filePath));
            ASSERT_EQUAL(correct_hash, std::hash<type>{}(result));
        }
    }

    void test_smaller() {
        using namespace ya_test_runner;

        string configDir("tests/test_smaller");
        string root("tests/test_smaller/dir/");
        int streams(10);
        unordered_map<string, string> pairs;
        pairs["VERY BIG"] = "small";
        auto configPath = create_valid_config(configDir, root, streams, pairs);
        std::vector<fs::path> files;
        for(char ch = 'a'; ch <= 'z'; ++ch) {
            files.push_back(create_file_and_fill(
                        root,
                        string(3, ch),
                        "VERY BIG \n",
                        50
                        ));
        }
        std::ostringstream tmpStream;
        epx_test::Parser parser(configPath, &tmpStream);
        parser.replace_data();
        std::ostringstream correct_result;
        fill_stream(
                    correct_result,
                    "small \n",
                    50
                    );
        using type = decltype (correct_result.str());
        auto correct_hash = std::hash<type>{}(correct_result.str());

        for(const auto& filePath : files) {
            string result(epx_test::get_buffer_from(filePath));
            ASSERT_EQUAL(correct_hash, std::hash<type>{}(result));
        }
    }
}
