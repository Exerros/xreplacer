#include "gtest/gtest.h"

#include <utility>
#include <string>
#include <sstream>

#include "testing_functions/functions.hpp"
#include "logger.hpp"

//------------------------------------------------------------------------------
namespace tests {

class LoggerTester : public ::testing::Test {};

TEST_F(LoggerTester, CorrectConstructing) {
}

TEST_F(LoggerTester, UncorrectConfig) { //foreach
}

TEST_F(LoggerTester, NoFiles) {
}

TEST_F(LoggerTester, NoStreams) {
}

TEST_F(LoggerTester, LogToNothing) {
}

TEST_F(LoggerTester, LogToFile) {
}

TEST_F(LoggerTester, LogToStream) {
}

TEST_F(LoggerTester, LogToFileAndStream) {
}

TEST_F(LoggerTester, LogWithTime) {
}

TEST_F(LoggerTester, LogWithoutTime) {
}

}
