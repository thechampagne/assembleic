TARGET = assembleic

BUILD_DIR = build

CC ?= gcc
#CFLAGS ?= -Wall -Wextra -Wpedantic -Werror -Wshadow -Wformat=2 -Wconversion -Wunused-parameter
OBJS := $(BUILD_DIR)/assembleic.o $(BUILD_DIR)/assembleic_parser.o $(BUILD_DIR)/assembleic_codegen.o


$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) -std=c89 $(OBJS) -o $@

$(BUILD_DIR)/assembleic.o: assembleic.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -std=c89 $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/assembleic_parser.o: assembleic_parser.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -std=c89 $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/assembleic_codegen.o: assembleic_codegen.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -std=c89 $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
