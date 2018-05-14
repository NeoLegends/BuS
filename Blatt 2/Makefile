BUILD_DIR = build
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

all: \
	$(BUILD_DIR)/prozesse \
	$(BUILD_DIR)/listen

$(BUILD_DIR)/%: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
