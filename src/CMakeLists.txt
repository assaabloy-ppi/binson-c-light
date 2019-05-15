include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(binson_parser binson_parser.c)
target_compile_options(binson_parser PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow -Wcast-qual -std=c99)
add_sanitizers(binson_parser)

add_library(binson_writer binson_writer.c)
target_compile_options(binson_writer PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow -Wcast-qual -std=c99)
add_sanitizers(binson_writer)

add_library(binson_light binson_parser.c binson_writer.c)
target_compile_options(binson_light PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow -Wcast-qual -std=c99)
add_sanitizers(binson_light)

add_library(binson_class binson.cpp)
target_compile_options(binson_class PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow -Wcast-qual -std=c++11)
add_sanitizers(binson_class)