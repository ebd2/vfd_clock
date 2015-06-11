.PHONY: clock install test clean

clock:
	cd clock && make

install:
	cd clock && make install

test:
	cd test && make

clean:
	cd test && make clean
	cd clock && make clean
