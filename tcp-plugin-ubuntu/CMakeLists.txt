project(clixon-plugin-tcp)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -fPIC -DHAVE_CONFIG_H -fopenmp -D_DEBUG")

file(GLOB_RECURSE SOURCES *.cpp)

find_library(libcligen_loc NAMES libcligen.so)
find_library(libclixon_loc NAMES libclixon.so)
find_library(libclixon_backend_loc NAMES libclixon_backend.so)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${libcligen_loc} ${libclixon_loc} ${libclixon_backend_loc})