#include "functions.hpp"

    //Данная функция считывает буфер из файла и возвращает его функциям.
    char* epx_func::get_buffer_from(const string& filePath) {
        ifstream file(filePath);

        //Узнаем размер файла
        file.seekg(0, std::ios::end);
        long length = file.tellg();
        file.seekg(0, std::ios::beg);

        //Читаем буфер
        char* tmpBuf = new char[static_cast<unsigned long>(length)];
        file.read(tmpBuf, length);
        file.close();

        return tmpBuf;
    }
