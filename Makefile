# Define the compiler and flags [THIS FILE IS FOR UNIX SYSTEMS]
CC = g++
CFLAGS = -Wall -std=c++20

# List C++ source files
CPP_SRC = Logger.cpp

# Rule to build the final executable
all:
	g++ -c $(CPP_SRC)
	ar rcs libmodane.a Logger.o
run:
	sudo ./Build/Main
