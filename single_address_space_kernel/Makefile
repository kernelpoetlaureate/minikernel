# Makefile for building the ApotheOS kernel

# Compiler and assembler
CC = gcc
LD = ld
NASM = nasm

# Directories
SRC_DIR = .
BUILD_DIR = build

# Files
BOOTLOADER = $(SRC_DIR)/bootloader_c/bootloader.asm
KERNEL = $(SRC_DIR)/kernel.c
BOOTLOADER_BIN = $(BUILD_DIR)/bootloader.bin
KERNEL_BIN = $(BUILD_DIR)/kernel.o
OS_IMAGE = $(BUILD_DIR)/os_image.bin

# Flags
CFLAGS = -ffreestanding -m32 -nostdlib -nostartfiles
LDFLAGS = -Ttext 0x1000 --oformat binary
NASMFLAGS = -f bin

# Targets
all: $(OS_IMAGE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BOOTLOADER_BIN): $(BOOTLOADER) | $(BUILD_DIR)
	$(NASM) $(NASMFLAGS) $< -o $@

$(KERNEL_BIN): $(KERNEL) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OS_IMAGE): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	cat $^ > $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
