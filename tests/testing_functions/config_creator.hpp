#pragma once

#include <filesystem>
#include <fstream>

#include "pugixml.hpp"

class ConfigCreator {
    using path = std::filesystem::path;
    using xml_document = pugi::xml_document;
    using xml_node = pugi::xml_node;

private:
    xml_document data{};
public:
    ConfigCreator() = default;
    ~ConfigCreator() = default;

    void add_node(const xml_node& node) {

    }

    void add_value(const xml_node& node) {

    }

    void write_file(const path& config_path) const {

    }

    const xml_node& get_data() const { return data; }
};
