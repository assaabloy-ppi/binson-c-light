#!/bin/bash

harden_build_dir="build_afl_harden"
asan_build_dir="build_afl_asan"
debug_build_dir="build_debug"
libfuzzer_no_sanitizer_build_dir="build_libfuzzer_no_sanitizer"
libfuzzer_asan_build_dir="build_libfuzzer_asan"
libfuzzer_ubsan_build_dir="build_libfuzzer_ubsan"
libfuzzer_msan_build_dir="build_libfuzzer_msan"
testcases_dir="input"

valid_targets=(`ls -Sr fuzz_*.c | cut -d'.' -f1`)
output_dir=""
input_dir=""
target=${valid_targets[0]}
mode="afl"
num_cores=4
fuzz_args="-m none"
masterFuzzer=""
valid_target=0
binary_dir=$asan_build_dir

build_targets() {

    if [ -z ${AFL_CC+x} ]; then
        AFL_CC=afl-clang-fast
        AFL_CXX=afl-clang-fast++
    fi

    echo "Using AFL compiler $AFL_CC and $AFL_CXX"

    export AFL_HARDEN=1 && \
    mkdir -p $harden_build_dir && \
    cd $harden_build_dir && \
    cmake \
        -DCMAKE_CXX_COMPILER=$AFL_CXX \
        -DCMAKE_C_COMPILER=$AFL_CC -DBUILD_FUZZ_TESTS=ON \
        -DFUZZ_TOOL=FUZZ_TOOL_AFL \
        -DCMAKE_CXX_FLAGS="-O9" \
        -DCMAKE_C_FLAGS="-O9" ../.. && \
    make -j && \
    cd .. && \
    unset AFL_HARDEN && \
    export AFL_USE_ASAN=1 && \
    mkdir -p $asan_build_dir && \
    cd $asan_build_dir && \
    cmake \
        -DCMAKE_CXX_COMPILER=$AFL_CXX \
        -DCMAKE_C_COMPILER=$AFL_CC -DBUILD_FUZZ_TESTS=ON \
        -DFUZZ_TOOL=FUZZ_TOOL_AFL \
        -DCMAKE_CXX_FLAGS="-O9" \
        -DCMAKE_C_FLAGS="-O9" ../.. && \
    make -j && \
    unset AFL_USE_ASAN && \
    cd .. && \
    mkdir -p $debug_build_dir && \
    cd $debug_build_dir && \
    cmake \
        -DBUILD_FUZZ_TESTS=ON \
        -DFUZZ_TOOL=FUZZ_TOOL_NONE \
        -DSANITIZE_ADDRESS=On -DSANITIZE_UNDEFINED=On -DENABLE_COVERAGE=On -DCMAKE_BUILD_TYPE=Debug ../.. && \
    make -j && cd .. && \
    mkdir -p $libfuzzer_no_sanitizer_build_dir &&
    cd $libfuzzer_no_sanitizer_build_dir && \
    cmake \
        -DCMAKE_C_COMPILER_WORKS=1 \
        -DCMAKE_CXX_COMPILER_WORKS=1 \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_C_COMPILER=clang -DBUILD_FUZZ_TESTS=ON \
        -DFUZZ_TOOL=FUZZ_TOOL_LIBFUZZER \
        -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=fuzzer" \
        -DCMAKE_C_FLAGS="-g -O1 -fsanitize=fuzzer" \
        -DCMAKE_CXX_FLAGS="-g -O1 -fsanitize=fuzzer" ../.. && \
    make -j && cd .. &&
    mkdir -p $libfuzzer_asan_build_dir &&
    cd $libfuzzer_asan_build_dir && \
    cmake \
        -DCMAKE_C_COMPILER_WORKS=1 \
        -DCMAKE_CXX_COMPILER_WORKS=1 \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_C_COMPILER=clang -DBUILD_FUZZ_TESTS=ON \
        -DFUZZ_TOOL=FUZZ_TOOL_LIBFUZZER \
        -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=fuzzer,address" \
        -DCMAKE_C_FLAGS="-g -O1 -fsanitize=fuzzer,address" \
        -DCMAKE_CXX_FLAGS="-g -O1 -fsanitize=fuzzer,address" ../.. && \
    make -j && cd .. &&
    mkdir -p $libfuzzer_ubsan_build_dir &&
    cd $libfuzzer_ubsan_build_dir && \
    cmake \
        -DCMAKE_C_COMPILER_WORKS=1 \
        -DCMAKE_CXX_COMPILER_WORKS=1 \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_C_COMPILER=clang -DBUILD_FUZZ_TESTS=ON \
        -DFUZZ_TOOL=FUZZ_TOOL_LIBFUZZER \
        -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=fuzzer,signed-integer-overflow" \
        -DCMAKE_C_FLAGS="-g -O1 -fsanitize=fuzzer,signed-integer-overflow" \
        -DCMAKE_CXX_FLAGS="-g -O1 -fsanitize=fuzzer,signed-integer-overflow" ../.. && \
    make -j && cd .. &&
    mkdir -p $libfuzzer_msan_build_dir &&
    cd $libfuzzer_msan_build_dir && \
    cmake \
        -DCMAKE_C_COMPILER_WORKS=1 \
        -DCMAKE_CXX_COMPILER_WORKS=1 \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_C_COMPILER=clang -DBUILD_FUZZ_TESTS=ON \
        -DFUZZ_TOOL=FUZZ_TOOL_LIBFUZZER \
        -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=fuzzer,memory" \
        -DCMAKE_C_FLAGS="-g -O1 -fsanitize=fuzzer,memory" \
        -DCMAKE_CXX_FLAGS="-g -O1 -fsanitize=fuzzer,memory" ../.. && \
    make -j && cd .. &&
    return 0 || return 1
}



print_help() {
    echo "Usage: $0 target (afl_asan|afl_harden) numCores"
    echo "Valid targets are:"
    for v in $valid_targets; do
        echo "   $v"
    done
}

if ! build_targets ; then
    echo "Error: Building of binaries failed."
    exit 1
fi

check_and_set_config() {

    valid_target=0

    for v in "${valid_targets[@]}"; do
        if [ "$v" = "$target" ]; then
            valid_target=1
            break
        fi
    done

    if [ $valid_target -eq "0" ]; then
        echo "Error: \"$target\" is not a valid target."
        print_help
        return 1
    fi


    input_dir="$testcases_dir/$target"

    if ! [ `find $input_dir -type f | wc -l` -gt 0 ]; then
        echo "Error: No valid testcases in $input_dir"
        return 1
    fi

    output_dir="output/$target"

    mkdir -p $output_dir

    if ! [ $num_cores -ge 0 2>/dev/null ]; then
        echo "Error: \"$num_cores\" not a valid number of cores."
        print_help
    fi

    if ! find $binary_dir -type f -executable -name $target > /dev/null; then
        echo "Error: Binary target does not exist, why not?"
    fi


    masterFuzzer="1Master$target"
    return 0
}


select_target() {
    while true; do
        echo "Select target:
        "

        i=1
        for v in "${valid_targets[@]}"; do
            echo "    [$i] $v"
            ((i++))
        done

        read -p "
    Select: " choice

        ((choice--))

        target=${valid_targets[choice]}

        if check_and_set_config; then
            return 0
        fi

    done

}

set_num_cores() {
    while true; do
        clear
        read -p "
    Select num cores [1-N]: " num_cores

        if check_and_set_config; then
            return 0
        fi

    done
}

select_mode() {
    while true; do
    clear
    read -p "Select mode:

    [1] AFL asan
    [2] AFL harden
    [3] libFuzzer no sanitizers
    [4] libFuzzer asan
    [5] libFuzzer ubsan
    [6] libFuzzer msan

    Select: " m
    case $m in
        [1]* ) mode="afl"; binary_dir=$asan_build_dir; fuzz_args="-m none"; break;;
        [2]* ) mode="afl"; binary_dir=$harden_build_dir; fuzz_args=""; break;;
        [3]* ) mode="libfuzzer"; binary_dir=$libfuzzer_no_sanitizer_build_dir; break;;
        [4]* ) mode="libfuzzer"; binary_dir=$libfuzzer_asan_build_dir; break;;
        [5]* ) mode="libfuzzer"; binary_dir=$libfuzzer_ubsan_build_dir; break;;
        [6]* ) mode="libfuzzer"; binary_dir=$libfuzzer_msan_build_dir; break;;

        * ) echo "Please select correct";;
    esac
    done

    check_and_set_config

}

do_cmin() {

    if [ "$mode" = "afl" ]; then
        do_cmin_afl && do_tmin_afl;
    elif [ "$mode" = "libfuzzer" ]; then
        do_cmin_libfuzzer;
    else
        echo "Not supported"
        return 1
    fi
}

do_cmin_libfuzzer() {

    if ! [ -d $output_dir/queue_all ]; then
        echo "No output dir detected, please start fuzz"
        return 1
    fi

    rm -rf $output_dir/queue_cmin
    mkdir -p $output_dir/queue_cmin
    ./$binary_dir/fuzz-test/$target $output_dir/queue_cmin $output_dir/queue_all -merge=1
    rm -rf $output_dir/queue_all
    mv $output_dir/queue_cmin $output_dir/queue_all

}

do_cmin_afl() {

    if ! [ -d $output_dir/queue_all ]; then
        echo "No output dir detected, please start fuzz"
        return 1
    fi

    rm -rf $output_dir/queue_cmin
    afl-cmin $fuzz_args -i $output_dir/queue_all -o $output_dir/queue_cmin -- ./$binary_dir/fuzz-test/$target

    echo "afl-cmin process done."

}

do_tmin_afl() {

    if ! [ -d $output_dir/queue_cmin ]; then
        echo "No cmin output dir detected, please start fuzz"
        return 1
    fi

    total=`ls $output_dir/queue_cmin | wc -l`
    mkdir -p $output_dir/queue_tmin

    for k in `seq 1 $num_cores $total`
    do
      for i in `seq 0 $(expr $num_cores - 1)`
      do
        file=`ls -Sr $output_dir/queue_cmin | sed $(expr $i + $k)"q;d"`
        if [ -f $output_dir/queue_cmin/$file ]; then
            afl-tmin -m none -i $output_dir/queue_cmin/$file -o $output_dir/queue_tmin/$file -- ./$binary_dir/fuzz-test/$target &
        fi
      done
      wait
    done

    rm -rf $output_dir/queue_all
    mv $output_dir/queue_tmin $output_dir/queue_all/
    echo "afl-tmin process done."
}

do_start_fuzz() {

    if [ "$mode" = "afl" ]; then
        do_continue_fuzz_afl;
    elif [ "$mode" = "libfuzzer" ]; then
        do_continue_fuzz_libfuzzer;
    else
        echo "Not supported"
        return 1
    fi

}

do_continue_fuzz_libfuzzer() {

    mkdir -p $output_dir
    if ! [ -d $output_dir/queue_all ]; then
        mkdir -p $output_dir/queue_all
        cp $input_dir/* $output_dir/queue_all/
    fi

    ./$binary_dir/fuzz-test/$target $output_dir/queue_all -jobs=$num_cores -dict=binson.dict -verbosity=0

}

do_continue_fuzz_afl() {
    mkdir -p $output_dir
    if ! [ -d $output_dir/queue_all ]; then
        mkdir -p $output_dir/queue_all
        cp $input_dir/* $output_dir/queue_all/
    fi

    rm -rf $output_dir/fuzzer*
    #for a in $(seq 1 $num_cores); do
    #    cp -r $output_dir/queue_all $output_dir/fuzzer$a/queue
    #done

    screen -dmS $masterFuzzer afl-fuzz -x binson.dict $fuzz_args -i $output_dir/queue_all -o $output_dir -M fuzzer1 -- ./$binary_dir/fuzz-test/$target
    sleep 1

    if ! screen -list | grep -q $masterFuzzer; then
        echo "Error: Master fuzzing start failed."
        afl-fuzz -x fuzz.dict $fuzz_args -i $output_dir/queue_all -o $output_dir -M fuzzer1 -- ./$binary_dir/fuzz-test/$target
        exit 1
    fi

    for a in $(seq 2 $num_cores); do
        slaveFuzzer=$a"Slave$target"
        screen -dmS $slaveFuzzer afl-fuzz -x fuzz.dict $fuzz_args -i $output_dir/queue_all -o $output_dir -S fuzzer$a -- ./$binary_dir/fuzz-test/$target
    done

    screen -x $masterFuzzer

    for a in $(seq 2 $num_cores); do
        slaveFuzzer=$a"Slave$target"
        screen -x $slaveFuzzer -X stuff "^C"
    done

    for a in $(seq 1 $num_cores); do
        if [ -d $output_dir/fuzzer$a/queue ]; then
            mkdir -p $output_dir/queue_all
            mkdir -p $output_dir/crashes_all
            mkdir -p $output_dir/hangs_all
            cp $output_dir/fuzzer$a/queue/* $output_dir/queue_all/ > /dev/null 2>&1
            cp $output_dir/fuzzer$a/crashes/* $output_dir/crashes_all/ > /dev/null 2>&1
            cp $output_dir/fuzzer$a/hangs/* $output_dir/hangs_all/ > /dev/null 2>&1
        fi
    done

}

do_copy_output() {

    source_dir=""

    while true; do
        clear
        read -p "
    What files do you want to copy to input?
    Only inputs resulting in return code 0 will be copied.

    [1] Raw output from afl-fuzz
    [2] Output from afl-cmin and afl-tmin
    [0] Quit

    Select: " yn
        case $yn in
            [1]* ) source_dir=$output_dir/queue_all;;
            [2]* ) source_dir=$output_dir/queue_tmin;;
            [0]* ) return 0;;
            * ) echo "Please answer yes or no.";;
        esac

        if ! [ -d $source_dir ]; then
            echo "No source dir detected, please check configuration."
        else
            break
        fi

    done

    for file in `find $source_dir -type f`; do
        if ./$debug_build_dir/$target < $file > /dev/null ; then
            mdname=$(md5sum $file | awk '{print $1}')
            echo "Copying file $file to name $mdname"
            cp -f $file $input_dir/$mdname
        fi
    done

}

do_reset() {
    rm -rf $output_dir
    mkdir -p $output_dir
    echo "$output_dir deleted"
}

do_dry_run() {
    find $input_dir -type f -exec sh -c "cat {} | ./$debug_build_dir/$target > /dev/null && echo \"Return with 0: {}\"" \;
    find $output_dir/queue_all -type f -exec sh -c "cat {} | ./$debug_build_dir/$target > /dev/null && echo \"Return with 0: {}\"" \;
    lcov --base-directory $debug_build_dir --directory $debug_build_dir --capture --output-file $debug_build_dir/coverage.info
    genhtml -o $debug_build_dir/coverage_report $debug_build_dir/coverage.info
    echo "Coverage report in $(pwd)/$debug_build_dir/coverage_report/index.html"
}

main_menu() {

    check_and_set_config

    while true; do
        clear
        read -p "Fuzzing tool

    [1] Select target [$target]
    [2] Select mode [$binary_dir]
    [3] Select num cores [$num_cores]
    [4] Start fuzz (Press CTRL+C to break)
    [5] cmin and tmin
    [6] Copy output to input
    [7] Reset
    [8] Dry run with coverage
    [0] Quit

    Select: " yn
        case $yn in
            [1]* ) select_target;;
            [2]* ) select_mode;;
            [3]* ) set_num_cores;;
            [4]* ) do_start_fuzz;;
            [5]* ) do_cmin;;
            [6]* ) do_copy_output;;
            [7]* ) do_reset;;
            [8]* ) do_dry_run;;
            [0]* ) return 0;;
            * ) echo "Please answer yes or no.";;
        esac

    done
}

main_menu
