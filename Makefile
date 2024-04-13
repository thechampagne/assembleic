TARGET = bascii

BUILD_DIR = build

CC ?= gcc
#CFLAGS ?= -Wall -Wextra -Wpedantic -Werror -Wshadow -Wformat=2 -Wconversion -Wunused-parameter
OBJS := $(BUILD_DIR)/bascii.o $(BUILD_DIR)/bascii_parser.o $(BUILD_DIR)/bascii_codegen.o


$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) -std=c89 $(OBJS) -o $@

$(BUILD_DIR)/bascii.o: bascii.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -std=c89 $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/bascii_parser.o: bascii_parser.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -std=c89 $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/bascii_codegen.o: bascii_codegen.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -std=c89 $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
