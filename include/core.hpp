#pragma once

#include <string>
#include <filesystem>
#include <iostream>

#include "interface.hpp"
#include "configurator.hpp"
#include "exception.hpp"
#include "logger.hpp"
#include "parser.hpp"
#include "replacer.hpp"

namespace xrep {

#if defined(__unix__)
    constexpr auto STANDART_CONFIG_PATH = "conf.json";
#elif defined(WIN32) || defined(__WIN32__) || defined (__WIN32)
    constexpr auto STANDART_CONFIG_PATH = "conf.json";
#endif

//------------------------------------------------------------------------------
/**
 * @brief The class containing the basic logic of the xReplacer.
 */
class XReplacerCore {
    using fs_path = std::filesystem::path;
    using config_ptr = std::unique_ptr<interface::ConfiguratorInterface>;
    using parser_ptr = std::unique_ptr<interface::ParserInterface>;
    using replacer_ptr = std::unique_ptr<interface::ReplacerInterface>;

private:
    config_ptr config;
    parser_ptr parser;
    replacer_ptr replacer;

public:
    XReplacerCore();
    ~XReplacerCore() = default;

    /**
     * @brief A method that initializes objects involved in the application.
     *
     * @param argc passed to the main function.
     *
     * @param argv passed to the main function.
     */
    void init(int argc, char** argv) noexcept(false);

    /**
     * @brief The method that starts the application.
     *
     * @return Application operation status code. If == 0, then the application
     *         ended correctly.
     */
    int run() noexcept(false);
};

} // namespace xrep

