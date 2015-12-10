cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_FLAGS "-std=c99")
link_directories(${CMAKE_SOURCE_DIR})
add_executable(heap_sort main.c)
target_link_libraries(heap_sort heap)

