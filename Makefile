INVOC = @
build:
	gcc main.c includes/*.c -o webserver -lpigpio -lrt -lpthread

all: build
	rustc main.rs -o main

debug: 
	valgrind ./webserver
