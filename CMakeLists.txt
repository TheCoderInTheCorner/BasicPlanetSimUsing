cmake_minimum_required(VERSION 3.10.0)
project(multipleBodies VERSION 0.1.0 LANGUAGES C CXX)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(multipleBodies main.cpp body.cpp)

target_link_libraries(multipleBodies PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

target_include_directories(multipleBodies PUBLIC Include)

include(CTest)
enable_testing()

