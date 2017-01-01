#Folders that contains th source and exec files
SRC_DIR = ./src/
DEBUG_DIR = ./build/debug/
RELEASE_DIR=./build/release/

#As recomended by SDL
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

#OBJS specifies which files to compile as part of the project
OBJS = $(SRC_DIR)getting_image.cpp
#CC specifies which compiler we're using
CC = g++
#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w $(SDL_CFLAGS)
#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = $(SDL_LDFLAGS)
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = loading_image
DEBUG_OBJ_NAME = $(DEBUG_DIR)$(OBJ_NAME)
RELEASE_OBJ_NAME = $(RELEASE_DIR)$(OBJ_NAME)
#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
debug: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(DEBUG_OBJ_NAME)
release: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(RELEASE_OBJ_NAME)
