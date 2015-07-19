.PHONY: clock install test clean

clock:
	cd clock && make

install:
	cd clock && make install

test:
	cd test && make

.PHONY: clean
clean:
	cd test && make clean
	cd clock && make clean

.PHONY: dep_clean
dep_clean:
	cd test && make dep_clean
	cd clock && make dep_clean
