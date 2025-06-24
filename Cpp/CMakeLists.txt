cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(net-ease-music-meta)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_library(main main.cpp)

add_library(lrc lrc.cpp)
target_link_libraries(lrc PUBLIC OpenMP::OpenMP_CXX)

add_library(info info.cpp)
target_link_libraries(info PUBLIC OpenMP::OpenMP_CXX)

add_library(metadata metadata.cpp)
target_link_libraries(metadata PUBLIC OpenMP::OpenMP_CXX)

add_library(meta_match meta_match.cpp)
target_link_libraries(meta_match PUBLIC metadata info lrc)

add_executable(nemeta main)
target_link_libraries(nemeta PUBLIC OpenMP::OpenMP_CXX lrc info main)

