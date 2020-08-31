cmake_minimum_required(VERSION 3.5)

project(ImageCompressor_QT LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

file(GLOB headers "headers/*.h")
file(GLOB impl "impl/*.cpp")

add_executable(ImageCompressor_QT main.cpp ${headers} ${impl})

target_link_libraries(ImageCompressor_QT PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
