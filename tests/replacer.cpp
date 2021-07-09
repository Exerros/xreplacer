#include "gtest/gtest.h"

#include <utility>
#include <string>
#include <sstream>

#include "testing_functions/stdout_capturer"
#include "replacer.hpp"

//------------------------------------------------------------------------------
namespace tests {

class ReplacerTester : public ::testing::Test {};

TEST_F(ReplacerTester, CorrectConstructing) {
}

TEST_F(ReplacerTester, UncorrectConfig) { //foreach
}

TEST_F(ReplacerTester, CorrectReplace) {
}

TEST_F(ReplacerTester, NothingToReplace) {
}

}
