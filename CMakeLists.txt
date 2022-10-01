cmake_minimum_required(VERSION 3.23)
project(graphing_calculator)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(SFML_INCLUDE_DIR "/home/tosiek/Documents/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "/home/tosiek/Documents/SFML-2.5.1/lib")
set(SFML_DIR "/home/tosiek/Documents/SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(graphing_calculator main.cpp Application/app.cpp Application/app.h Application/menu.cpp Application/menu.h Application/window.cpp Application/window.h Application/UI/button.cpp Application/UI/button.h Application/UI/object.cpp Application/UI/object.h Application/UI/caption.cpp Application/UI/caption.h Application/calculator.cpp Application/calculator.h Application/graph.cpp Application/graph.h Application/plot.cpp Application/plot.h Application/UI/textbox.cpp Application/UI/textbox.h Application/manual.cpp Application/manual.h)

include(FindPkgConfig)
find_package(az_math REQUIRED)
include_directories(${AZ_MATH_INCLUDE_DIR})
find_package (Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${AZ_MATH_LIBRARY} sfml-graphics sfml-window sfml-system)