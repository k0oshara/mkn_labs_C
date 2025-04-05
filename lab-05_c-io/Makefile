.PHONY: all clean

CFLAGS = -I$(INC_DIR)

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

TARGET = lab-05_c-io

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS)) 

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	gcc $^ -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
