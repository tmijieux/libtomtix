cmake_minimum_required(VERSION 3.1.2)

project(libheap)
add_library(heap SHARED heap.c)
add_library(heap_static STATIC heap.c)
set_target_properties(heap_static PROPERTIES OUTPUT_NAME heap)
