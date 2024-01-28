SOURCES=$(shell find src -name '*.c') 

make:
	clang -fsanitize=address -g -Wall -I./src/ui -I./src/fs -lncurses ${SOURCES}

debug:
	echo ${SOURCES}