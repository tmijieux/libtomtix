cmake_minimum_required(VERSION 3.0.2)

project(Bubble_sort C)
set(CMAKE_C_FLAGS "-std=c99")

add_library(bubble_sort SHARED cbubble_sort.c ibubble_sort.c fbubble_sort.c dbubble_sort.c)
add_library(bubble_sort_static STATIC cbubble_sort.c ibubble_sort.c fbubble_sort.c dbubble_sort.c)
set_target_properties(bubble_sort_static PROPERTIES OUTPUT_NAME bubble_sort)

add_executable(example main.c)
target_link_libraries(example bubble_sort)
