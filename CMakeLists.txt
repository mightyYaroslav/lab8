cmake_minimum_required(VERSION 2.8.7)

include_directories(include)

file(GLOB LIB_SOURCES "src/*.c")

project(lab8)
# to build executable target with name a.out
add_executable(${CMAKE_PROJECT_NAME} "main.c" ${LIB_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} libjansson.so)
target_link_libraries(${CMAKE_PROJECT_NAME} libevent.so)
