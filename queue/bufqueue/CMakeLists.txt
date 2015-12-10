add_library(queue SHARED queue.c)
add_subdirectory(example)
install(TARGETS queue DESTINATION libs)
