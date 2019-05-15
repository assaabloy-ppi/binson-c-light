#!/bin/bash

mkdir -p DebugSan && \
cd DebugSan && \
cmake -DCMAKE_BUILD_TYPE=Debug -DSANITIZE_ADDRESS=On -DSANITIZE_UNDEFINED=On -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON ..  && \
make -j8 && \
ctest -j8 && \
cd ..  && \
mkdir -p coverage  && \
lcov -b . \
    -d DebugSan/src/CMakeFiles/binson_parser.dir \
    -d DebugSan/src/CMakeFiles/binson_writer.dir \
    -d DebugSan/src/CMakeFiles/binson_class.dir \
    --no-recursion \
    --no-external \
    --capture --output-file coverage/coverage.info  && \
genhtml -o coverage coverage/coverage.info  && \
exit 0 || exit -1
