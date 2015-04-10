cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -g -Wall")


add_executable(sysrem main.cpp Timer.cpp Reader.cpp MemStat.cpp CPUStat.cpp
    DiskStat.cpp ProcStat.cpp ProcMan.cpp)
#target_link_libraries(sysrem pthread)
