.PHONY: all

dry:
	crash_cnt=0; \
	for i in ./build/bin/*;  do \
	  echo "\n=====================\ntesting: $${i##*/}";  \
	  ../../build/binson_light_test_stream < $$i;  \
	  ret=$$?; \
	  if [ $$ret -eq  0 ];  then rm $$i; fi; \
	  if [ $$ret -ne  0 ];  then crash_cnt=$$((crash_cnt+1)); fi;  \
	done; \
	echo "\n\nTOTAL CRASHES: $${crash_cnt}\n"; \
	exit 11;
