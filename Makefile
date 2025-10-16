# Define the compiler and flags [THIS FILE IS FOR LINUX]
CC = g++
CFLAGS = -Wall -std=c++20

# Shared Library Information
SHARED_LIB_PATH = Src/Vendor/Lib/Raylib/
SHARED_LIB_NAME = raylib

# Define include and library paths
INCLUDES = -I./Src/Vendor/Include/
LIB_PATHS = -L$(SHARED_LIB_PATH)

# Define libraries to link
LIBS =  -l$(SHARED_LIB_NAME)
# Linking flags
LDFLAGS += -L$(SHARED_LIB_PATH) -Wl,-rpath,$(SHARED_LIB_PATH)

# List C++ source files
CPP_SRC = $(wildcard Src/*.cpp) $(wildcard Src/Vendor/Include/Raylib/*.cpp) $(wildcard Src/Vendor/Include/Logger/*.cpp)

# List C source files
# C_SRC =

# Generate object file names for C++ files
CPP_OBJ = $(CPP_SRC:.cpp=.o)

# The C object file must match the source file's directory
# C_OBJ = $(C_SRC:.c=.o)

# Combine all object files
OBJ = $(CPP_OBJ) $(C_OBJ)

TARGET = Main

# Rule to build the final executable
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIB_PATHS) $^ -o $@ $(LDFLAGS) $(LIBS)
	mv Src/*.o ObjFiles/
	mv $(TARGET) Build/

# Rule for C++ compilation
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Explicit rule for C compilation, specifying the output path
# $(C_OBJ): $(C_SRC)
#	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Running the file
run:
	sudo ./Build/Main

# Clean up
clean:
	rm -f ObjFiles/*.o Build/Main

