
include_directories(..)
add_executable(writer writer.c)
target_link_libraries(writer binson_writer binson_parser)

add_executable(parser parser.c)
target_link_libraries(parser binson_parser)


add_executable(class class.cpp)
target_link_libraries(class binson_parser binson_writer binson_class)
