SOURCES=$(shell find src -name '*.c') 

make:
	clang -fsanitize=address -g -Wall -I./src/ui -I./src/fs -lncursesw ${SOURCES}

debug:
	echo ${SOURCES}