# TuringOS - Makefile
# Automatiza a montagem, compilação, linkedição, geração da ISO e execução no QEMU.

.RECIPEPREFIX := >

AS = nasm
CC = gcc
LD = ld

BUILD_DIR = build
ISO_DIR = iso

KERNEL_BIN = $(BUILD_DIR)/turingos.bin
KERNEL_ISO = $(BUILD_DIR)/turingos.iso

BOOT_OBJ = $(BUILD_DIR)/boot.o
KERNEL_OBJ = $(BUILD_DIR)/kernel.o

CFLAGS = -m32 -ffreestanding -fno-builtin -fno-pic -fno-pie -fno-stack-protector -nostdlib -Wall -Wextra
LDFLAGS = -m elf_i386 -T linker.ld -nostdlib

.PHONY: all check iso run debug clean

all: $(KERNEL_BIN)

$(BUILD_DIR):
>mkdir -p $(BUILD_DIR)

$(BOOT_OBJ): boot/boot.asm | $(BUILD_DIR)
>$(AS) -f elf32 boot/boot.asm -o $(BOOT_OBJ)

$(KERNEL_OBJ): kernel/kernel.c | $(BUILD_DIR)
>$(CC) $(CFLAGS) -c kernel/kernel.c -o $(KERNEL_OBJ)

$(KERNEL_BIN): $(BOOT_OBJ) $(KERNEL_OBJ)
>$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(BOOT_OBJ) $(KERNEL_OBJ)
>cp $(KERNEL_BIN) $(ISO_DIR)/boot/turingos.bin

check: $(KERNEL_BIN)
>grub-file --is-x86-multiboot $(KERNEL_BIN)
>@echo "Kernel reconhecido como Multiboot."

iso: $(KERNEL_BIN)
>grub-mkrescue -o $(KERNEL_ISO) $(ISO_DIR)

run: iso
>qemu-system-i386 -cdrom $(KERNEL_ISO)

debug: $(KERNEL_BIN)
>qemu-system-i386 -kernel $(KERNEL_BIN) -s -S

clean:
>rm -rf $(BUILD_DIR)
>rm -f $(ISO_DIR)/boot/turingos.bin
