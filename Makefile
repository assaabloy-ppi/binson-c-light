.PHONY: test    

test:
	./build/binson_light_test
	ret=$$?;
	if [ $$ret; -ne  0 ];  then echo "\nSOME TESTS FAILED\n"; exit $$ret; fi;
	$(MAKE) -C ./test/fuzz/binson dry-run