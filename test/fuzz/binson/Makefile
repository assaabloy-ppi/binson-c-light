.PHONY: dry-run build build-test-stream

# -fsanitize=fuzzer,address,undefined
libfuzzer:	
	clang -g -Og -fsanitize=fuzzer,address,undefined -DWITH_TO_STRING -std=c99 \
				 ../../../binson_light.c test_fuzzer.c \
				-o test_fuzzer.out

libfuzzer-msan:
	clang -g -Og -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=fuzzer,memory \
				  -stdlib=libc++ -L/home/kotomysha/__1/libcxx_msan/lib -lc++ -lc++abi \
				 -I/home/kotomysha/__1/libcxx_msan/include -I/home/kotomysha/__1/libcxx_msan/include/c++/v1	\
	             -fsanitize-memory-track-origins=2 -DWITH_TO_STRING -std=c99 \
				 ../../../binson_light.c test_fuzzer.c \
				 -Wl,-rpath,/home/kotomysha/__1/libcxx_msan/lib  \
				-o test_fuzzer.out

libfuzz:
	export ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer-6.0
	export ASAN_OPTIONS=symbolize=1
	export MSAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer-6.0
	export MSAN_OPTIONS=symbolize=1
	export UBSAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer-6.0
	export UBSAN_OPTIONS=symbolize=1	
	./test_fuzzer.out -dict=binson.dict -artifact_prefix='./output/crashes/' ./input


build:
	AFL_HARDEN=1 afl-gcc -fstack-protector-strong -O3 -std=c99 -DWITH_TO_STRING binson.c ../../../binson_light.c -o binson_fuzz.out

build-test-stream:
	AFL_HARDEN=1 afl-gcc -fstack-protector-strong -O3 -std=c99 -DTEST_STREAM_MAIN ../../../binson_light_test_stream.c ../../../binson_light.c -o binson_fuzz.out

fuzz:
	sudo bash -c 'for governor in $$(ls /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor); do \
  		echo "performance" > $$governor; \
	done'; \
	AFL_HARDEN=1 afl-fuzz -x ./binson.dict -i input -o output ./binson_fuzz.out

fuzz-resume:
	AFL_HARDEN=1 afl-fuzz -x ./binson.dict -i - -o output ./binson_fuzz.out	

dry-run:
	crash_cnt=0; \
	for i in ./input/* ./cases/fixed/*; do \
	  echo "\n=====================\ntesting: $${i##*/}";  \
	  ./binson_fuzz.out < $$i;  \
	  ret=$$?; \
	  if [ $$ret -ne  0 ];  then crash_cnt=$$((crash_cnt+1)); fi;  \
	done; \
	echo "\n\nTOTAL CRASHES: $${crash_cnt}\n"; \
	exit 11;

cmin:
	afl-cmin -i input -o input2 ./binson_fuzz.out

crashes-tmin:
	mkdir -p ./output/crashes-tmin
	for i in ./output/crashes/*; do   \
	  afl-tmin -i ./output/crashes/$${i##*/} -o ./output/crashes-tmin/$${i##*/} ./binson_fuzz.out;  \
	done
	#for i in ./output/hangs; do afl-tmin -i ./output/hangs/$i -o ./output/hangs-tmin/$i ./binson_fuzz.out done


	
input-tmin:
	mkdir -p ./input-tmin
	for i in ./input/*; do   \
	  afl-tmin -i ./input/$${i##*/} -o ./input-tmin/$${i##*/} ./binson_fuzz.out;  \
	done
