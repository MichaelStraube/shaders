cmake_minimum_required(VERSION 3.8)

project(shaders LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
add_compile_options(-Wall -Wextra)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(shaders
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/glwidget.cpp
    src/glwidget.h
    src/matrix.cpp
    src/matrix.h
    src/starfield.cpp
    src/starfield.h
    src/digitalrain.cpp
    src/digitalrain.h
    src/resources.qrc
)

target_link_libraries(shaders PRIVATE Qt5::Widgets)
