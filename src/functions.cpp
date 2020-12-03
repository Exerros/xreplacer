#include "functions.hpp"

    //Данная функция считывает буфер из файла и возвращает его функциям.
    char* epx_func::get_buffer_from(const string& filePath) {
        ifstream file(filePath);

        //Узнаем размер файла
        file.seekg(0, std::ios::end);
        long length = file.tellg();
        file.seekg(0, std::ios::beg);
        if(length == 0) throw Buffer_Error();

        //Читаем буфер
        char* tmpBuf = new char[static_cast<unsigned long>(length)];
        file.read(tmpBuf, length);

        if(file.fail()) throw Buffer_Error();
        file.close();

        return tmpBuf;
    }

    //Функция для записи буфера в файл
    void epx_func::write_buffer_to_file(
        string&& buffer,
        const string& filePath
    ){
        //открываем файл (стирая содержимое) и записываем буфер
        ofstream output_file(filePath, std::ios::trunc);
        output_file << buffer;

        //проверяем на ошибки при записи
        if(output_file.fail()) throw Writing_Error();
        output_file.close();
    }
