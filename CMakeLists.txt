cmake_minimum_required(VERSION 3.23)
project(graphing_calculator)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "../SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "../SFML-2.5.1/lib")
set(SFML_DIR "../SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR ./AZ-math ./imgui ./imgui-sfml)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(graphing_calculator main.cpp Application/app.cpp Application/app.h Application/menu.cpp
        Application/menu.h Application/window.cpp Application/window.h Application/UI/button.cpp
        Application/UI/button.h Application/UI/object.cpp Application/UI/object.h
        Application/UI/caption.cpp Application/UI/caption.h Application/calculator.cpp Application/calculator.h
        Application/graph.cpp Application/graph.h Application/plot.cpp Application/plot.h Application/UI/textbox.cpp
        Application/UI/textbox.h Application/manual.cpp Application/manual.h
        ./AZ-math/azmath.cpp
        imgui/imgui.cpp imgui/imgui_widgets.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui-sfml/imgui-SFML.cpp
        imgui/imgui_demo.cpp
        Application/useful_functions.h Application/useful_functions.cpp
        Application/function_tools.h Application/function_tools.cpp
        Application/canvas.h Application/canvas.cpp
        )

include(FindPkgConfig)
find_package (Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} -lGL sfml-graphics sfml-window sfml-system)
