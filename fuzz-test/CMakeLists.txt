if(NOT FUZZ_TOOL)
    set(FUZZ_TOOL FUZZ_TOOL_NONE)
endif(NOT FUZZ_TOOL)

macro(add_fuzz_target_c name file)
    add_executable(${name} ${file})
    add_sanitizers(${name})
    target_link_libraries(${name} binson_light main_entry_c ${ARGN})
    target_compile_options(${name} PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow -Wcast-qual -std=c99)
endmacro(add_fuzz_target_c)

macro(add_fuzz_target_cpp name file)
    add_executable(${name} ${file})
    add_sanitizers(${name})
    target_link_libraries(${name} binson_light main_entry_cpp ${ARGN})
    target_compile_options(${name} PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow -std=c++11)
endmacro(add_fuzz_target_cpp)

add_library(main_entry_c main_entry.c)
target_compile_options(main_entry_c PRIVATE -DFUZZ_TOOL=${FUZZ_TOOL} -Werror -Wall -Wextra -Wpedantic -Wshadow -Wcast-qual -std=c99 -Wno-gnu-statement-expression)

add_fuzz_target_c(fuzz_binson fuzz_binson.c)
add_fuzz_target_c(fuzz_defined fuzz_defined.c)
add_fuzz_target_c(fuzz_goinoutarr fuzz_goinoutarr.c)
add_fuzz_target_c(fuzz_goinoutobj fuzz_goinoutobj.c)
add_fuzz_target_c(fuzz_parser_verify fuzz_parser_verify.c)
add_fuzz_target_c(fuzz_verify_array fuzz_verify_array.c)

if(WITH_PRINT)
    add_fuzz_target_c(fuzz_to_string fuzz_to_string.c)
endif(WITH_PRINT)

if(WITH_CPP)
    add_library(main_entry_cpp main_entry.cpp)
    target_compile_options(main_entry_cpp PRIVATE -DFUZZ_TOOL=${FUZZ_TOOL} -Werror -Wall -Wextra -Wpedantic -Wshadow -std=c++11)
    add_fuzz_target_cpp(fuzz_class fuzz_class.cpp binson_class)
endif(WITH_CPP)

file(GLOB files "../utest/test_data/valid_objects/*")
foreach(file ${files})
    get_filename_component(barename ${file} NAME)
    add_test(
        NAME verify_valid_${barename}
        COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/fuzz_parser_verify < ${file} > /dev/null 2&>1")
    if(WITH_PRINT)
    add_test(
        NAME print_valid_${barename}
        COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/fuzz_to_string < ${file} > /dev/null 2&>1")
    endif(WITH_PRINT)
endforeach()

file(GLOB files "../utest/test_data/bad_objects/*")
foreach(file ${files})
    get_filename_component(barename ${file} NAME)
    add_test(
        NAME verify_invalid_${barename}
        COMMAND sh -c "! ${CMAKE_CURRENT_BINARY_DIR}/fuzz_parser_verify < ${file} > /dev/null 2&>1")
    if(WITH_PRINT)
    add_test(
        NAME print_invalid_${barename}
        COMMAND sh -c "! ${CMAKE_CURRENT_BINARY_DIR}/fuzz_to_string < ${file} > /dev/null 2&>1")
    endif(WITH_PRINT)
endforeach()
