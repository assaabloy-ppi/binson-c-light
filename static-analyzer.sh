#!/bin/sh

# Works with the docker found in fuzz-test/docker

REPORT_DIR="html"


SCAN_OPT="-enable-checker alpha.core.BoolAssignment \
    -enable-checker alpha.core.CastSize \
    -enable-checker alpha.core.CastToStruct \
    -enable-checker alpha.core.DynamicTypeChecker \
    -enable-checker alpha.core.FixedAddr \
    -enable-checker alpha.core.IdenticalExpr \
    -enable-checker alpha.core.PointerArithm \
    -enable-checker alpha.core.PointerSub \
    -enable-checker alpha.core.SizeofPtr \
    -enable-checker alpha.core.TestAfterDivZero \
    -enable-checker alpha.deadcode.UnreachableCode \
    -enable-checker alpha.security.ArrayBound \
    -enable-checker alpha.security.ArrayBoundV2 \
    -enable-checker alpha.security.MallocOverflow \
    -enable-checker alpha.security.ReturnPtrRange \
    -enable-checker alpha.security.taint.TaintPropagation \
    -enable-checker alpha.unix.Chroot \
    -enable-checker alpha.unix.PthreadLock \
    -enable-checker alpha.unix.SimpleStream \
    -enable-checker alpha.unix.Stream \
    -enable-checker alpha.unix.cstring.BufferOverlap \
    -enable-checker alpha.unix.cstring.NotNullTerminated \
    -enable-checker alpha.unix.cstring.OutOfBounds \
    -enable-checker nullability.NullableDereferenced \
    -enable-checker nullability.NullablePassedToNonnull \
    -enable-checker optin.performance.Padding \
    -enable-checker security.FloatLoopCounter \
    -enable-checker security.insecureAPI.rand \
    -enable-checker security.insecureAPI.strcpy"


SCAN_BUILD=$(find /usr -type f -executable -name scan-build | sort | tail -1)
CCC_ANALYZER=$(find /usr -type f -executable -name ccc-analyzer | sort | tail -1)
CXX_ANALYZER=$(find /usr -type f -executable -name c++-analyzer | sort | tail -1)

mkdir -p Debug
cd Debug
$SCAN_BUILD -v -o $REPORT_DIR $SCAN_OPT cmake -DCMAKE_CXX_COMPILER=$CXX_ANALYZER -DCMAKE_C_COMPILER=$CCC_ANALYZER ..
make clean
$SCAN_BUILD -v -o $REPORT_DIR $SCAN_OPT make -j


cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
cppcheck --project=compile_commands.json --enable=all

cd ..
sh tis-analyze.sh