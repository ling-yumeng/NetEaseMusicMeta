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
add_executable(nemeta_gui minimumWindow.cpp)
target_link_libraries(nemeta_gui ${wxWidgets_LIBRARIES} info)

file(COPY info DESTINATION .)
file(COPY lrc DESTINATION .)
