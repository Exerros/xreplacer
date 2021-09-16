#include "gtest/gtest.h"

#include "testing_functions/config_creator.hpp"
#include "configurator.hpp"

//------------------------------------------------------------------------------
namespace tests {

class ConfiguratorTester : public ::testing::Test {};

TEST_F(ConfiguratorTester, CorrectConstructing) {
    ConfigCreator creator {};
    xrep::JsonConfigurator conf {"test/configurator/CorrectConstructing.json"};
}

TEST_F(ConfiguratorTester, UncorrectConfigConstructing) {
    ConfigCreator creator {};
    xrep::JsonConfigurator conf {
        "test/configurator/UncorrectConfigConstructing.json"};
}

TEST_F(ConfiguratorTester, DoubleValuesConfig) {
    ConfigCreator creator {};
    xrep::JsonConfigurator conf {"test/configurator/DoubleValuesConfig.json"};
}

TEST_F(ConfiguratorTester, VoidConfig) {
    ConfigCreator creator {};
    xrep::JsonConfigurator conf {"test/configurator/VoidConfig.json"};
}

TEST_F(ConfiguratorTester, CorrectGetConfigFor) {
    ConfigCreator creator {};
    xrep::JsonConfigurator conf {"test/configurator/CorrectGetConfigFor.json"};
}

TEST_F(ConfiguratorTester, TryToGetConfigForUnincludedClass) {
    ConfigCreator creator {};
    xrep::JsonConfigurator conf {
        "test/configurator/TryToGetConfigForUnincludedClass.json"};
}

TEST_F(ConfiguratorTester, TryToGetVoidConfigFor) {
    ConfigCreator creator {};
    xrep::JsonConfigurator conf {
        "test/configurator/TryToGetVoidConfigFor.json"};
}

TEST_F(ConfiguratorTester, CorrectGetConfigForWithDoubleData) {
    ConfigCreator creator {};
    xrep::JsonConfigurator conf {
        "test/configurator/CorrectGetConfigForWithDoubleData.json"};
}

}
//------------------------------------------------------------------------------
int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
