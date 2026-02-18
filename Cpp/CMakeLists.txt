cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(net-ease-music-meta)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_library(main main.cpp)

add_library(lrc SHARED lrc.cpp)
target_link_libraries(lrc PUBLIC OpenMP::OpenMP_CXX)

add_library(info SHARED info.cpp)
target_link_libraries(info PUBLIC OpenMP::OpenMP_CXX)

add_executable(nemeta main)
target_link_libraries(nemeta PUBLIC OpenMP::OpenMP_CXX lrc info main)

find_package(wxWidgets REQUIRED COMPONENTS core base net)
include(${wxWidgets_USE_FILE})

add_library(download miniGUI/download.cpp)

add_library(main_frame miniGUI/main_frame.cpp)
target_link_libraries(main_frame PUBLIC download info)

add_executable(nemeta_gui miniGUI/gui_main.cpp)
target_link_libraries(nemeta_gui PUBLIC ${wxWidgets_LIBRARIES} main_frame)

file(COPY info DESTINATION .)
file(COPY lrc DESTINATION .)
