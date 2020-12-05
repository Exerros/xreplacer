#include "functions.hpp"

namespace epx_func {

    //Данная функция считывает буфер из файла и возвращает его функциям.
    string get_buffer_from(const fs::path& filePath) {
        //Узнаем размер файла. если файла не существует то бросаем исключение
        unsigned long length(0);
        ifstream file;
        try {
            length = fs::file_size(filePath);
            file.open(filePath);
        } catch (...) {
            throw FileSystem_Error();
        }

        //Читаем буфер
        string buffer(length, '\0');
        file.read(buffer.data(), static_cast<long>(length));

        //Проверяем на наличие ошибок при чтении и закрываем
        if(file.good() != true) throw Buffer_Error();
        file.close();

        return buffer;
    }

    //Функция для записи буфера в файл
    void write_buffer_to_file(string& buffer, const fs::path& filePath){
        //открываем файл (стирая содержимое) и записываем буфер
        ofstream output_file(filePath, std::ios::trunc);
        output_file << std::move(buffer);

        //проверяем на ошибки при записи
        if(output_file.good() != true) throw Writing_Error();
        output_file.close();
    }

    string create_regex_string(const string& str) {
        string result;

        for(const auto& ch: str) {
            if(is_letter(ch)) {
                result.push_back(ch);
            } else {
                result = result + '[' + ch + "]{1}";
            }
        }
        return result;
    }

    bool is_letter(const char ch) {
        return (('A' <= ch) && ('Z' >= ch)) || (('a' <= ch) && ('z' >= ch));
    }

}
