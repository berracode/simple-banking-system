CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
SRC_DIR = .
BUILD_DIR = build
BIN_DIR = bin

# All source files (including subdirectorios)
SRCS := $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)

# All generated objects
OBJS := $(patsubst $(SRC_DIR)/**/*.c,$(BUILD_DIR)/%.o,$(SRCS))

# name of program (Sysbansi for SImple BANking SYStem in reverse)
TARGET = sysbansi

# Rule for build executable program
$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Rule for build each object
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
