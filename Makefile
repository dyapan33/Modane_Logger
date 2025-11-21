# Define the compiler and flags [THIS FILE IS FOR UNIX SYSTEMS]
CC = g++
CFLAGS = -Wall -std=c++20

Filename = libmodane

# List C++ source files
CPP_SRC = Logger.cpp

# Rule to build the final executable
all:
	$(CC) $(CFLAGS) -c $(CPP_SRC) # g++ -Wall -std=c++20 -c Logger.cpp
	ar rcs $(Filename) Logger.o
run:
	sudo ./Build/Main
