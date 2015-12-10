add_library(node_queue SHARED node_queue.c)
target_link_libraries(node_queue list_node)
add_subdirectory(example)
install(TARGETS node_queue DESTINATION libs)
