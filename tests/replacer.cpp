#include "gtest/gtest.h"

#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "testing_functions/stdout_capturer.hpp"
#include "replacer.hpp"
#include "exception.hpp"

//------------------------------------------------------------------------------
namespace tests {
    using pairs_map = std::unordered_map<std::string, std::string>;
    using rpair = std::pair<std::string, std::string>;
    using fs_path = std::filesystem::path;

class ReplacerTester : public ::testing::Test {};

TEST_F(ReplacerTester, PT_Prepare) {
    std::filesystem::create_directory("test_files/");
    std::filesystem::create_directory("test_files/files/");
    std::filesystem::create_directory("test_files/files/test1");
    std::filesystem::create_directory("test_files/files/test4");

    {
        std::ofstream test1_a("test_files/files/test1/a.txt",
                            std::ios::out | std::ios::trunc);
        for (size_t i = 0; i < 1000; i++) { test1_a << "111 "; }
        test1_a.close();
    }

    {
        std::ofstream test1_b("test_files/files/test1/b.txt",
                            std::ios::out | std::ios::trunc);
        for (size_t i = 0; i < 1000; i++) { test1_b << "222 "; }
        test1_b.close();
    }

    {
        std::ofstream test1_c("test_files/files/test1/c.txt",
                        std::ios::out | std::ios::trunc);
        for (size_t i = 0; i < 1000; i++) { test1_c << "333 "; }
        test1_c.close();
    }

    {
        std::ofstream test1_d("test_files/files/test1/d.txt",
                            std::ios::out | std::ios::trunc);
        for (size_t i = 0; i < 1000; i++) { test1_d << "111 222 333 "; }
        test1_d.close();
    }

    {
        std::ofstream test4_a("test_files/files/test4/a.txt",
                            std::ios::out | std::ios::trunc);
        for (size_t i = 0; i < 1000; i++) { test4_a << "111 "; }
        test4_a.close();
    }

    {
        std::ofstream test4_b("test_files/files/test4/b.txt",
                            std::ios::out | std::ios::trunc);
        for (size_t i = 0; i < 1000; i++) { test4_b << "222 "; }
        test4_b.close();
    }

    {
        std::ofstream test4_c("test_files/files/test4/c.txt",
                        std::ios::out | std::ios::trunc);
        for (size_t i = 0; i < 1000; i++) { test4_c << "333 "; }
        test4_c.close();
    }

    {
        std::ofstream test4_d("test_files/files/test4/d.txt",
                            std::ios::out | std::ios::trunc);
        for (size_t i = 0; i < 1000; i++) { test4_d << "111 222 333 "; }
        test4_d.close();
    }

    ASSERT_TRUE(true);
}

//------------------------------------------------------------------------------
TEST_F(ReplacerTester, CorrectConstructing) {
    STDOUT_Capturer out {};
    pairs_map pairs {{"a", "aa"}, {"b", "bb"}};
    int thread_count = 1;

    ASSERT_NO_THROW(xrep::FileDataReplacer replacer(pairs, thread_count));
}

//------------------------------------------------------------------------------
TEST_F(ReplacerTester, NoPairsConstructing) {
    STDOUT_Capturer out {};
    pairs_map pairs {};
    int thread_count = 1;

    ASSERT_THROW(xrep::FileDataReplacer replacer(pairs, thread_count),
                 xrep::exception::replacer::NoPairs);
}

//------------------------------------------------------------------------------
TEST_F(ReplacerTester, UncorrectThreadsConstructing) {
    STDOUT_Capturer out {};
    pairs_map pairs {{"a", "aa"}, {"b", "bb"}};
    int thread_count = -1;

    ASSERT_ANY_THROW(xrep::FileDataReplacer replacer(pairs, thread_count));
}

//------------------------------------------------------------------------------
TEST_F(ReplacerTester, ReplacingOneThread) {
    STDOUT_Capturer out {};
    pairs_map pairs {{"111", "aaa"}, {"222", "bbb"}, {"333", "ccc"}};
    int thread_count = 1;
    std::vector<fs_path> paths {"test_files/files/test1/a.txt",
                                "test_files/files/test1/b.txt",
                                "test_files/files/test1/c.txt",
                                "test_files/files/test1/d.txt"};

    xrep::FileDataReplacer replacer(pairs, thread_count);
    replacer.replace(paths);

    {
        std::ostringstream test1_a {};
        for (size_t i = 0; i < 1000; i++) { test1_a << "aaa "; }

        std::ifstream file_a("test_files/files/test1/a.txt", std::ios::in);
        size_t length_a = std::filesystem::file_size(
                                                "test_files/files/test1/a.txt");
        std::string data_a(length_a, '\0');
        file_a.read(data_a.data(), length_a);

        ASSERT_EQ(data_a, test1_a.str());
    }
    {
        std::ostringstream test1_b {};
        for (size_t i = 0; i < 1000; i++) { test1_b << "bbb "; }

        std::ifstream file_b("test_files/files/test1/b.txt", std::ios::in);
        size_t length_b = std::filesystem::file_size(
                                                "test_files/files/test1/b.txt");
        std::string data_b(length_b, '\0');
        file_b.read(data_b.data(), length_b);

        ASSERT_EQ(data_b, test1_b.str());
    }

    {
        std::ostringstream test1_c {};
        for (size_t i = 0; i < 1000; i++) { test1_c << "ccc "; }

        std::ifstream file_c("test_files/files/test1/c.txt", std::ios::in);
        size_t length_c = std::filesystem::file_size(
                                                "test_files/files/test1/c.txt");
        std::string data_c(length_c, '\0');
        file_c.read(data_c.data(), length_c);

        ASSERT_EQ(data_c, test1_c.str());
    }

    {
        std::ostringstream test1_d {};
        for (size_t i = 0; i < 1000; i++) { test1_d << "aaa bbb ccc "; }

        std::ifstream file_d("test_files/files/test1/d.txt", std::ios::in);
        size_t length_d = std::filesystem::file_size(
                                                "test_files/files/test1/d.txt");
        std::string data_d(length_d, '\0');
        file_d.read(data_d.data(), length_d);

        ASSERT_EQ(data_d, test1_d.str());
    }
}

//------------------------------------------------------------------------------
TEST_F(ReplacerTester, Replacing4Threads) {
    STDOUT_Capturer out {};
    pairs_map pairs {{"111", "aaa"}, {"222", "bbb"}, {"333", "ccc"}};
    int thread_count = 4;
    std::vector<fs_path> paths {"test_files/files/test4/a.txt",
                                "test_files/files/test4/b.txt",
                                "test_files/files/test4/c.txt",
                                "test_files/files/test4/d.txt"};

    {
        xrep::FileDataReplacer replacer(pairs, thread_count);
        replacer.replace(paths);

        std::ostringstream test1_a {};
        for (size_t i = 0; i < 1000; i++) { test1_a << "aaa "; }

        std::ifstream file_a("test_files/files/test4/a.txt", std::ios::in);
        size_t length_a = std::filesystem::file_size(
                                                "test_files/files/test4/a.txt");
        std::string data_a(length_a, '\0');
        file_a.read(data_a.data(), length_a);

        ASSERT_EQ(data_a, test1_a.str());
    }

    {
        std::ostringstream test1_b {};
        for (size_t i = 0; i < 1000; i++) { test1_b << "bbb "; }

        std::ifstream file_b("test_files/files/test4/b.txt", std::ios::in);
        size_t length_b = std::filesystem::file_size(
                                                "test_files/files/test4/b.txt");
        std::string data_b(length_b, '\0');
        file_b.read(data_b.data(), length_b);

        ASSERT_EQ(data_b, test1_b.str());
    }

    {
        std::ostringstream test1_c {};
        for (size_t i = 0; i < 1000; i++) { test1_c << "ccc "; }

        std::ifstream file_c("test_files/files/test4/c.txt", std::ios::in);
        size_t length_c = std::filesystem::file_size(
                                                "test_files/files/test4/c.txt");
        std::string data_c(length_c, '\0');
        file_c.read(data_c.data(), length_c);

        ASSERT_EQ(data_c, test1_c.str());
    }

    {
        std::ostringstream test1_d {};
        for (size_t i = 0; i < 1000; i++) { test1_d << "aaa bbb ccc "; }

        std::ifstream file_d("test_files/files/test4/d.txt", std::ios::in);
        size_t length_d = std::filesystem::file_size(
                                                "test_files/files/test4/d.txt");
        std::string data_d(length_d, '\0');
        file_d.read(data_d.data(), length_d);

        ASSERT_EQ(data_d, test1_d.str());
    }
}

//------------------------------------------------------------------------------
TEST_F(ReplacerTester, PT_Clean) {
    std::filesystem::remove_all("test_files");

    ASSERT_TRUE(true);
}

}
//------------------------------------------------------------------------------
int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
