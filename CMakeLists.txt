cmake_minimum_required(VERSION 3.26.4)
project(UniversalConverter)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(UniversalConverter main.cpp
        core/BigInteger.h
        src/BigInteger.cpp
        core/Fraction.h
        src/Fraction.cpp
        app/Button.h
        app/Screen.h
        app/Singleton.h
        app/TextBox.h
        src/TextBox.cpp
        app/FileManager.h
        src/FileManager.cpp
        src/TextBox.cpp)

target_link_libraries(UniversalConverter PRIVATE sfml-graphics)
