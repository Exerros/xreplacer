#include "gtest/gtest.h"

#include <string>
#include <fstream>
#include <algorithm>

#include "testing_functions/stdout_capturer.hpp"
#include "parser.hpp"

//------------------------------------------------------------------------------
namespace tests {

class ParserTester : public ::testing::Test {};

TEST_F(ParserTester, PT_Prepare) {
    std::filesystem::create_directory("test_files/");
    std::filesystem::create_directory("test_files/files/");
    std::filesystem::create_directory("test_files/no_files/");

    ASSERT_TRUE(true);
}

//------------------------------------------------------------------------------
TEST_F(ParserTester, CorrectConstructing) {
    STDOUT_Capturer out {};
    std::fstream file("test_files/files/a.txt", std::ios::out);
    file.close();

    ASSERT_NO_THROW(xrep::FileSystemParser parser("test_files/files"));
}

//------------------------------------------------------------------------------
TEST_F(ParserTester, UnCorrectConstructing) {
    STDOUT_Capturer out {};

    ASSERT_ANY_THROW(xrep::FileSystemParser parser(""););
    ASSERT_ANY_THROW(xrep::FileSystemParser parser("test_files/files/a.txt"););
}

//------------------------------------------------------------------------------
TEST_F(ParserTester, FileSearch) {
    STDOUT_Capturer out {};
    std::fstream file("test_files/files/a.txt", std::ios::out);
    file.close();
    std::fstream file1("test_files/files/b.txt", std::ios::out);
    file1.close();
    std::fstream file2("test_files/files/c.txt", std::ios::out);
    file2.close();

    xrep::FileSystemParser parser("test_files/files");

    parser.search_objects_to_replase();
    auto file_list = parser.get_objects_to_replase();

    ASSERT_TRUE(std::find(file_list.begin(), file_list.end(),
                          "test_files/files/a.txt") != file_list.end());
    ASSERT_TRUE(std::find(file_list.begin(), file_list.end(),
                          "test_files/files/b.txt") != file_list.end());
    ASSERT_TRUE(std::find(file_list.begin(), file_list.end(),
                          "test_files/files/c.txt") != file_list.end());
}

//------------------------------------------------------------------------------
TEST_F(ParserTester, HasObjectsToReplace) {
    STDOUT_Capturer out {};
    std::fstream file("test_files/files/a.txt", std::ios::out);
    file.close();
    std::fstream file1("test_files/files/b.txt", std::ios::out);
    file1.close();
    std::fstream file2("test_files/files/c.txt", std::ios::out);
    file2.close();

    xrep::FileSystemParser parser("test_files/files");
    parser.search_objects_to_replase();

    ASSERT_TRUE(parser.has_objects_to_replace());
}

//------------------------------------------------------------------------------
TEST_F(ParserTester, PT_Clean) {
    std::filesystem::remove_all("test_files");

    ASSERT_TRUE(true);
}

}
//------------------------------------------------------------------------------
int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
