CC = gcc
CFLAGS = -std=c23 -Wall -Isrc
LIBS = -lmingw32 -lSDL2main -lSDL2 \
       -mwindows -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va \
       -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 \
       -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid

SRC_DIR = src
OBJ_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = $(OBJ_DIR)/raycaster.exe

all: debug

debug: CFLAGS += -g
debug: $(TARGET)

release: CFLAGS += -O2 -static
release: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)