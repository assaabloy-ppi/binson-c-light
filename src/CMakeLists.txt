project(binson-c-light)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_library(binson_parser binson_parser.c)
target_compile_options(binson_parser PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow -Wcast-qual -std=c99)
add_sanitizers(binson_parser)
set_target_properties(binson_parser PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/../include")

add_library(binson_writer binson_writer.c)
target_compile_options(binson_writer PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow -Wcast-qual -std=c99)
add_sanitizers(binson_writer)
set_target_properties(binson_writer PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/../include")


add_library(binson_light binson_parser.c binson_writer.c)
target_compile_options(binson_light PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow -Wcast-qual -std=c99)
add_sanitizers(binson_light)
set_target_properties(binson_light PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/../include")

if(WITH_CPP)
    add_library(binson_class binson.cpp)
    target_compile_options(binson_class PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow -Wcast-qual -std=c++11)
    target_link_libraries(binson_class binson_light)
    add_sanitizers(binson_class)
    set_target_properties(binson_class PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/../include")
endif(WITH_CPP)
