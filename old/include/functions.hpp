#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include "exception.hpp"

namespace xrep_func {
    namespace fs = std::filesystem;
    using std::string;
    using std::ifstream;
    using std::ofstream;
    using xrep::Buffer_Error;
    using xrep::Writing_Error;
    using xrep::FileSystem_Error;

//этот класс содержит функционал применяемый различными классами данной
//программы. В частности чтением буфера занимаются Configurator и Replacer

//Чтение буфера. При возникновении ошибок бросает исключение Buffer_Error
    string get_buffer_from(const fs::path& filePath);

//Запись буфера. При возникновении ошибок бросает исключение Writing_Error
    void write_buffer_to_file(string& buffer, const fs::path& filePath);

//Функция обработки найденых в конфиге строк для замены в вид подходящий для
//работы класса regex
    string create_regex_string(const string& str);

//Проверка является ли переданный символ буквой
    inline bool is_letter(const char ch);
}
