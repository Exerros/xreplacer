# Тестовое задание для компании [Everypixel](https://www.everypixel.com/)
### Задача состояла в разработке парсера файлов. Его задачи:
- [x] Парсить каталог файлов/папок произвольной вложенности
- [x] В каждом из файлов менять все вхождения шаблона на текст замены.
- [x] Работать в несколько потоков
- [x] Сообщать пользователю, что работа выполнена

### Также у программы должен быть конфиг файл со следующими данными:
- [x] Количество потоков на парсинг файлов
- [x] Адрес корневой директории с файлами и папками
- [x] Перечисление шаблонов и их замен (неограниченное количество)

### Дополнительные требования:  
- [x] С++11 или выше
- [x] Программа должна работать только с использованием библиотеки STL
- [x] Выполненное задание должно располагаться на Github или Bitbucket. 
- [x] Написание unit-тестов будет являться дополнительным плюсом.

# Необходимо для сборки

Сборка программы производилась на операционной системе Debian 10.
Для сборки необходим CMake версии 2.8 или старше и компилятор с поддержкой C++17.
Также, в моей реализации библиотеки STL **thread** используется библиотека **pthread**, 
если ваша реализация отличается, то возможно вам придется изменить CMakeLists.txt.
  
# Как собрать проект

Переместитесь в директорию в которую хотите скопировать проект и скопируйте команды в терминал:
> git clone https://github.com/Exerros/Everypixel_test.git  
> mkdir Everypixel_test/build  
> cd Everypixel_test/build  
> cmake ..  
> cmake --build . 

Для запуска используйте команду:  
> ./everypixel_test  
или  
> ./everypixel_test <путь до config.txt>  
### Ознакомьтесь с тем как правильно заполнить файл конфигурации и обязательно создайте его перед запуском программы.

# Как запустить тесты

Аналогично обычной сборке, переместитесь в директорию куда хотите поместить проект и скопируйте команды в терминал:
> git clone https://github.com/Exerros/Everypixel_test.git  
> mkdir Everypixel_test/build  
> cd Everypixel_test/build  
> cmake .. -DBUILD_TESTS=ON  
> cmake --build .  
> ./everypixel_test  

Как вы могли заметить для компиляции программы с включением тестов и их запуска используется ключ BUILD_TEST со значением ON. 
По умолчанию программа собирается в рабочем режиме и тесты не включаются в ее программный код.  

Результаты работы тестов помещаются в директорию **/tests**.

# Как правильно заполнить config
Файл конфигурации содержит 3 поля:  
> root: "<корневая директория>";  
> streams: <число потоков>;  
> replace: <"шаблон замены" = "результат замены">(любое количество раз);  

Каждое поле должно заканчиваться символом ';' и не должно содержать его внутри себя.  
Каждое поле может содержать любое число пробелов между названием и значением, либо не содержать их совсем. Также можно разнести их на разные строки.  
В поле replase может содержаться любое число пар. Они могут быть либо записаны как в одну строку, либо разнесены на разные строки, либо и то и то сразу, **НО** <шаблон замены> и <результат замены> должны находиться на одной строке.  
Шаблоны замены могут содержать символы не зарезервированные синтаксисом ECMAScript, в частности символы:  
> . , ! @ % & - _ = < > (этот список может быть не полным)  

Дополнительную информацию вы можете посмотреть в файлах тестов. Они компилируются при указании вышеописанного ключа BUILD_TESTS и располагаются в директории **/tests**.
# Introduction
###  
This program was developed in December 2020 as a test job for everypixel. Xreplacer is capable of multithreading the file tree of any nesting and making replacements according to the configuration file. Now in Sep 2021 I am updating this project to correct the existing flaws.

# Software description
###  
This program is designed for multi-threaded recursive information replacement in files. Everything is extremely simple:  
1. Specify in the configuration file the root directory, the required number of threads and replacement pairs (what to replace);  
2. Run;  
3. Done, information in files was been replaced.  

# Required
###  
* The nlohmann_json library version 3.20 or higher is required to build the program.  
* To build the program, cmake version 3.20 was used and operation on lower versions is not guaranteed.  
* To build tests you need gtest version 1.10 or higher.  
* To build the documentation you will need doxygen.  

# Building
###  
There are several options for building an application:  
* XREPLACER_BUILD_SHARED - Compiles the program libraries dynamically.  
* XREPLACER_BUILD_DOCS - Whether to collect documentation when building the program.  
* XREPLACER_BUILD_TESTS - whether to collect tests when building the program.  

To build the program, run the following set of commands from the directory with the source files:  

> mkdir build  
> cd build  
> cmake ..  
> cmake --build .  

After that you will find all the necessary program files in the build/bin directory.  

If you want to change one of the above options, specify the "-D" key to the cmake file preparation command:  

>cmake .. -DXREPLACER_BUILD_DOCS=ON  

Also, if you have built a program with tests, you can test it with CTest. To do this, from the build directory call the command:  

> ctest  

The tests themselves are located in the build/tests directory.  

# Configuration
###  
An example configuration file can be found in the conf directory and is additionally copied into the build/bin directory when building.
* root_dir is the root directory within which all files will be recursively processed.
* thread_count is a value that sets the number of handler threads that will be used when the program runs. If you don't know how many threads your computer supports at the same time, specify e.g. 100. In cases where you specify more threads than your computer supports, the optimal number of threads will be used instead.
* pairs - pairs of values "from" -> "to", indicating what to replace. Not only direct values are supported here, but also regular expressions in ECMAScript language.
