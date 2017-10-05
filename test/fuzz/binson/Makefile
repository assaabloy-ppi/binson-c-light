.PHONY: dry-run build build-test-stream

build:
	AFL_HARDEN=1 afl-gcc -fstack-protector-strong -O3 -std=c99 -DWITH_TO_STRING binson.c ../../../binson_light.c -o binson_fuzz.out

build-test-stream:
	AFL_HARDEN=1 afl-gcc -fstack-protector-strong -O3 -std=c99 -DTEST_STREAM_MAIN ../../../binson_light_test_stream.c ../../../binson_light.c -o binson_fuzz.out

fuzz:
	sudo bash -c 'for governor in $$(ls /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor); do \
  		echo "performance" > $$governor; \
	done'; \
	AFL_HARDEN=1 afl-fuzz -i input -o output ./binson_fuzz.out

fuzz-resume:
	AFL_HARDEN=1 afl-fuzz -i - -o output ./binson_fuzz.out	

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
