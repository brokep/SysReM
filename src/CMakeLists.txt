cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -g")


add_executable(sysrem main.cpp Statgen.cpp Genparser.cpp)
target_link_libraries(sysrem pthread)
