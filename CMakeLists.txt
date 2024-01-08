cmake_minimum_required(VERSION 3.26.4)
project(UniversalConverter)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(UniversalConverter main.cpp
        BigInteger.h
        BigInteger.cpp
        Fraction.h
        Fraction.cpp
        Button.h
        Screen.h
        Singleton.h
        TextBox.h
        TextBox.cpp
        FileManager.h
        FileManager.cpp
        TextBox.cpp)

target_link_libraries(UniversalConverter PRIVATE sfml-graphics)
