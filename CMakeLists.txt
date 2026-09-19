cmake_minimum_required(VERSION 3.28)

project(MyImGuiProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

#=============== blocks and links ===============#

add_executable(MyImGuiProject

        src/main.cpp

        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp

        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(MyImGuiProject
        PRIVATE
                #block_of "imgui.h"
                ${CMAKE_SOURCE_DIR}/imgui

                #block_of <GLFW/glfw3.h>
                ${CMAKE_SOURCE_DIR}/glfw/include
)

target_link_libraries(MyImGuiProject
    PRIVATE
        ${CMAKE_SOURCE_DIR}/glfw/lib-vc2026/glfw3.lib
)