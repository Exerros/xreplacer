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
