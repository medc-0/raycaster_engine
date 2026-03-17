CC = gcc
WINDRES = windres
CFLAGS = -std=c23 -Wall -Wextra -Isrc

SDL_LIBS = -lmingw32 -lSDL2main -lSDL2
PORTABILITY_LIBS = -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid

SRC_DIR = src
OBJ_DIR = build
TARGET = $(OBJ_DIR)/raycaster.exe

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all debug release clean prep

all: debug

prep:
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"

debug: CFLAGS += -g
debug: LDFLAGS = $(SDL_LIBS)
debug: prep $(TARGET)

release: CFLAGS += -O2
release: LDFLAGS = -static -mwindows -Wl,--dynamicbase -Wl,--nxcompat $(SDL_LIBS) $(PORTABILITY_LIBS)
release: prep $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@if exist "$(OBJ_DIR)" rmdir /s /q "$(OBJ_DIR)"