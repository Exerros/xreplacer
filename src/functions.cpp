#include "functions.hpp"

namespace epx_func {

    //Данная функция считывает буфер из файла и возвращает его функциям.
    string get_buffer_from(const path& filePath) {
        ifstream file(filePath);

        //Узнаем размер файла
        file.seekg(0, std::ios::end);
        long length = file.tellg();
        file.seekg(0, std::ios::beg);

        //Читаем буфер
        char* tmpBuf = new char[static_cast<unsigned long>(length)];
        file.read(tmpBuf, length);

        //Проверяем на наличие ошибок при чтении и закрываем
        if(file.good() != true) throw Buffer_Error();
        file.close();

        string result(std::move(tmpBuf));
        delete[](tmpBuf);
        return result;
    }

    //Функция для записи буфера в файл
    void write_buffer_to_file(string& buffer, const path& filePath){
        //открываем файл (стирая содержимое) и записываем буфер
        ofstream output_file(filePath, std::ios::trunc);
        output_file << std::move(buffer);

        //проверяем на ошибки при записи
        if(output_file.good() != true) throw Writing_Error();
        output_file.close();
    }

}
