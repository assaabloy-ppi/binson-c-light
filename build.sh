#!/bin/bash

mkdir -p DebugSan && \
cd DebugSan && \
cmake -DCMAKE_BUILD_TYPE=Debug -DSANITIZE_ADDRESS=On -DSANITIZE_UNDEFINED=On -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON -DBUILD_EXAMPLES=On -DWITH_PRINT=On -DWITH_CPP=On ..  && \
make -j8 && \
ctest -j8 && \
exit 0 || exit -1
