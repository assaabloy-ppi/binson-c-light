binson:
	afl-gcc binson.c ../../../binson_light.c -o binson_fuzz.out
	afl-fuzz -i input -o output ./binson_fuzz.out
