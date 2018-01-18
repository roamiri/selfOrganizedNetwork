cmake_minimum_required(VERSION 2.6)
project(selfOrganizedNetwork)
SET(CMAKE_CXX_FLAGS "-std=c++0x")



add_executable(selfOrganizedNetwork main.cpp manager.cpp mmwavebs.cpp)

target_link_libraries(selfOrganizedNetwork -lpthread)

install(TARGETS selfOrganizedNetwork RUNTIME DESTINATION bin)
