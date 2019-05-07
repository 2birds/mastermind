CC=g++
# CPPFLAGS=-g -Iincludes # -fPIC -no-pie
CPPFLAGS=-g -Iincludes 

SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

LIBDIRS := -L"/usr/lib/x86_64-linux-gnu/"
LDFLAGS := -lboost_system -lboost_program_options

mastermind: $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBDIRS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

clean:
	rm $(OBJ_DIR)/* 
