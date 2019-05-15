include_directories(${CMAKE_SOURCE_DIR}/include)

macro(add_fuzz_target name file)
    add_executable(${name} ${file})
    add_sanitizers(${name})
    target_link_libraries(${name} binson_light ${ARGN})
endmacro(add_fuzz_target)

add_fuzz_target(fuzz_binson fuzz_binson.c)
add_fuzz_target(fuzz_defined fuzz_defined.c)
add_fuzz_target(fuzz_goinoutarr fuzz_goinoutarr.c)
add_fuzz_target(fuzz_goinoutobj fuzz_goinoutobj.c)
add_fuzz_target(fuzz_parser_verify fuzz_parser_verify.c)

if(WITH_PRINT)
add_fuzz_target(fuzz_to_string fuzz_to_string.c)
endif(WITH_PRINT)

add_fuzz_target(fuzz_class fuzz_class.cpp binson_class)
target_compile_options(fuzz_class PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow -Wcast-qual -std=c++11)

file(GLOB files "${CMAKE_SOURCE_DIR}/utest/test_data/valid_objects/*")
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

file(GLOB files "${CMAKE_SOURCE_DIR}/utest/test_data/bad_objects/*")
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
