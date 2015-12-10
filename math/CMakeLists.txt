add_library(math SHARED math.c)
target_link_libraries(math m)
install(TARGETS math DESTINATION penguins/lib)
