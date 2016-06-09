add_library(node_queue SHARED nqueue.c nqueue.h)
add_subdirectory(example)
install(TARGETS node_queue DESTINATION libs)
