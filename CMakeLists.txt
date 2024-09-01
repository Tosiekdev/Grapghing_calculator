cmake_minimum_required(VERSION 3.23)
project(graphing_calculator)

set(CMAKE_CXX_STANDARD 20)

set(SFML_INCLUDE_DIR "~/Documents/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "~/Documents/SFML-2.5.1/lib")
set(SFML_DIR "~/Documents/SFML-2.5.1/lib/cmake/SFML")

include(FetchContent)
FetchContent_Declare(lexy URL https://lexy.foonathan.net/download/lexy-src.zip)

FetchContent_MakeAvailable(lexy)

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR ./function-parser/include ./imgui ./imgui-sfml)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(graphing_calculator main.cpp Application/app.cpp Application/app.hpp Application/menu.cpp
        Application/menu.hpp Application/window.cpp Application/window.hpp
        Application/calculator.cpp Application/calculator.hpp
        Application/manual.cpp Application/manual.hpp
        imgui-sfml/imgui-SFML.h
        imgui/imgui.cpp imgui/imgui_widgets.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui-sfml/imgui-SFML.cpp
        imgui/imgui_demo.cpp
        Application/useful_functions.hpp Application/useful_functions.cpp
        Application/function_tools.hpp Application/function_tools.cpp
        Application/canvas.hpp Application/canvas.cpp
        )

include(FindPkgConfig)
find_package (Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} -lGL sfml-graphics sfml-window sfml-system foonathan::lexy)
