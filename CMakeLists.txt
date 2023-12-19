cmake_minimum_required(VERSION 3.26)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(untitled main.cpp
        BigInteger.h
        BigInteger.cpp
        Fractiron.h
        Fraction.cpp
        Button.h
        Screen.h
        Singleton.h
        TextBox.h
        TextBox.cpp
        FileManager.h
        FileManager.cpp)

target_link_libraries(untitled sfml-graphics sfml-audio)