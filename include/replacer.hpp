#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <ostream>
#include <string>
#include <filesystem>
#include <atomic>
#include <chrono>

#include "replace_notificator.hpp"
#include "configurator.hpp"
#include "functions.hpp"
#include "exception.hpp"

namespace epx_test {
    namespace fs = std::filesystem;
    using std::chrono::steady_clock;
    using std::unordered_map;
    using std::unordered_set;
    using std::ostream;
    using std::string;
    using std::atomic;
    using std::pair;
    using epx_func::get_buffer_from;
    using epx_func::write_buffer_to_file;

//Этот класс занимается заменой информации в файле и оповещением пользователя
//о начале и конце этого процесса.
    class Replacer {
    private:
//т.к. нам не важно в каком порядке будут производится замены, но важно
//отсутствие совпадающих замен на мой взгляд самым подходящим контейнером
//является unordered_map
        unordered_map<string, string> pairs;
        ostream* outputStream;
    public:
//Пустой конструктор используется для создания объекта в который позднее
//будет перемещена информация из config
        Replacer() = default;
        Replacer(Configurator& config);

//Функция которая заменяет информацию в указанном файле.
        void replace_in (
                const fs::path& filePath,
                atomic<unsigned long>* streamCounter
                ) const;
    };

}
