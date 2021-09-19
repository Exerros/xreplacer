#include "gtest/gtest.h"

#include "testing_functions/config_creator.hpp"
#include "testing_functions/stdout_capturer.hpp"
#include "configurator.hpp"

//------------------------------------------------------------------------------
namespace tests {

class ConfiguratorTester : public ::testing::Test {};

TEST_F(ConfiguratorTester, CT_Prepare) {
    std::filesystem::create_directory("test_files/");
    std::filesystem::create_directory("test_files/files/");
    std::filesystem::create_directory("test_files/configurator/");

    ASSERT_TRUE(true);
}

//------------------------------------------------------------------------------
TEST_F(ConfiguratorTester, CorrectConstructing) {
    STDOUT_Capturer out {};
    ConfigCreator creator {};
    creator.set_root_dir("test_files/files/");
    creator.set_thread_count(4);
    creator.add_pair("from", "to");
    creator.write_to_file("test_files/configurator/CorrectConstructing.json");

    ASSERT_NO_THROW(xrep::JsonConfigurator conf {
                           "test_files/configurator/CorrectConstructing.json"});
}

//------------------------------------------------------------------------------
TEST_F(ConfiguratorTester, UncorrectConfigConstructing) {
    STDOUT_Capturer out {};
    ConfigCreator creator {};
    creator.set_root_dir("");
    creator.set_thread_count(-23567);
    creator.write_to_file(
                "test_files/configurator/UncorrectConfigConstructing.json");

    ASSERT_ANY_THROW(xrep::JsonConfigurator conf {
                   "test_files/configurator/UncorrectConfigConstructing.json"});
}

//------------------------------------------------------------------------------
TEST_F(ConfiguratorTester, VoidConfig) {
    STDOUT_Capturer out {};
    ConfigCreator creator {};
    creator.write_to_file("test_files/configurator/VoidConfig.json");

    ASSERT_ANY_THROW(xrep::JsonConfigurator conf {
                                    "test_files/configurator/VoidConfig.json"});
}

//------------------------------------------------------------------------------
TEST_F(ConfiguratorTester, CorrectRootDir) {
    STDOUT_Capturer out {};
    ConfigCreator creator {};
    creator.set_root_dir("test_files/files/");
    creator.set_thread_count(4);
    creator.add_pair("from", "to");
    creator.write_to_file("test_files/configurator/VoidConfig.json");

    xrep::JsonConfigurator conf {"test_files/configurator/VoidConfig.json"};
    ASSERT_EQ(conf.get_root_dir(), creator.get_root_dir());
}

//------------------------------------------------------------------------------
TEST_F(ConfiguratorTester, CorrectThreadCount) {
    STDOUT_Capturer out {};
    ConfigCreator creator {};
    creator.set_root_dir("test/files/");
    creator.set_thread_count(4);
    creator.add_pair("from", "to");
    creator.write_to_file("test_files/configurator/VoidConfig.json");

    xrep::JsonConfigurator conf {"test_files/configurator/VoidConfig.json"};
    ASSERT_EQ(conf.get_thread_count(), creator.get_thread_count());
}

//------------------------------------------------------------------------------
TEST_F(ConfiguratorTester, CorrectPairs) {
    STDOUT_Capturer out {};
    ConfigCreator creator {};
    creator.set_root_dir("test_files/files/");
    creator.set_thread_count(4);
    creator.add_pair("from", "to");
    creator.write_to_file("test_files/configurator/VoidConfig.json");

    xrep::JsonConfigurator conf {"test_files/configurator/VoidConfig.json"};
    ASSERT_EQ(conf.get_pairs().size(), 1);
    ASSERT_EQ(conf.get_pairs()["from"], "to");
}

//------------------------------------------------------------------------------
TEST_F(ConfiguratorTester, CT_Clean) {
    std::filesystem::remove_all("test_files");

    ASSERT_TRUE(true);
}

}
//------------------------------------------------------------------------------
int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
