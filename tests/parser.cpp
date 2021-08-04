#include "gtest/gtest.h"

#include <utility>
#include <string>
#include <sstream>

#include "testing_functions/stdout_capturer.hpp"
#include "parser.hpp"

//------------------------------------------------------------------------------
namespace tests {

class ParserTester : public ::testing::Test {};

TEST_F(ParserTester, CorrectConstructing) {
}

TEST_F(ParserTester, UncorrectConfig) { //foreach
}

TEST_F(ParserTester, CorrectSearchFiles) {
}

TEST_F(ParserTester, NoOneFileToReplace) {
}

TEST_F(ParserTester, CorrectGetObjects) {
}

TEST_F(ParserTester, GetNoOneObject) {
}

TEST_F(ParserTester, HasObjectsToReplace) {
}

TEST_F(ParserTester, HasNoObjectsToReplace) {
}

}
//------------------------------------------------------------------------------
int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
