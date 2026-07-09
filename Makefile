# TuringOS - Makefile
# Build do kernel, geração da ISO e execução no QEMU.

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
VGA_OBJ = $(BUILD_DIR)/vga.o
TERMINAL_OBJ = $(BUILD_DIR)/terminal.o
SHELL_OBJ = $(BUILD_DIR)/shell.o
KEYBOARD_OBJ = $(BUILD_DIR)/keyboard.o
INTERRUPT_OBJ = $(BUILD_DIR)/interrupt.o
IDT_OBJ = $(BUILD_DIR)/idt.o
ISR_OBJ = $(BUILD_DIR)/isr.o
PIC_OBJ = $(BUILD_DIR)/pic.o
TIMER_OBJ = $(BUILD_DIR)/timer.o
KEYBOARD_OBJ = $(BUILD_DIR)/keyboard.o

OBJECTS = $(BOOT_OBJ) $(KERNEL_OBJ) $(VGA_OBJ) $(TERMINAL_OBJ) $(SHELL_OBJ) $(KEYBOARD_OBJ) $(INTERRUPT_OBJ) $(IDT_OBJ) $(ISR_OBJ) $(PIC_OBJ) $(TIMER_OBJ)

CFLAGS = -m32 -Iinclude -ffreestanding -fno-builtin -fno-pic -fno-pie -fno-stack-protector -nostdlib -Wall -Wextra
LDFLAGS = -m elf_i386 -T linker.ld -nostdlib

.PHONY: all check iso run debug clean disasm readelf hexdump

all: $(KERNEL_BIN)

$(BUILD_DIR):
>mkdir -p $(BUILD_DIR)

$(BOOT_OBJ): boot/boot.asm | $(BUILD_DIR)
>$(AS) -f elf32 boot/boot.asm -o $(BOOT_OBJ)

$(KERNEL_OBJ): kernel/kernel.c | $(BUILD_DIR)
>$(CC) $(CFLAGS) -c kernel/kernel.c -o $(KERNEL_OBJ)

$(VGA_OBJ): kernel/vga.c include/vga.h | $(BUILD_DIR)
>$(CC) $(CFLAGS) -c kernel/vga.c -o $(VGA_OBJ)

$(TERMINAL_OBJ): kernel/terminal.c include/terminal.h include/vga.h | $(BUILD_DIR)
>$(CC) $(CFLAGS) -c kernel/terminal.c -o $(TERMINAL_OBJ)

$(SHELL_OBJ): kernel/shell.c include/shell.h include/terminal.h include/keyboard.h | $(BUILD_DIR)
>$(CC) $(CFLAGS) -c kernel/shell.c -o $(SHELL_OBJ)

$(KEYBOARD_OBJ): kernel/keyboard.c include/keyboard.h include/isr.h | $(BUILD_DIR)
>$(CC) $(CFLAGS) -c kernel/keyboard.c -o $(KEYBOARD_OBJ)

$(KERNEL_BIN): $(OBJECTS)
>$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(OBJECTS)
>cp $(KERNEL_BIN) $(ISO_DIR)/boot/turingos.bin

$(INTERRUPT_OBJ): kernel/interrupt.asm | $(BUILD_DIR)
>$(AS) -f elf32 kernel/interrupt.asm -o $(INTERRUPT_OBJ)

$(IDT_OBJ): kernel/idt.c include/idt.h | $(BUILD_DIR)
>$(CC) $(CFLAGS) -c kernel/idt.c -o $(IDT_OBJ)

$(ISR_OBJ): kernel/isr.c include/isr.h include/pic.h | $(BUILD_DIR)
>$(CC) $(CFLAGS) -c kernel/isr.c -o $(ISR_OBJ)

$(PIC_OBJ): kernel/pic.c include/pic.h | $(BUILD_DIR)
>$(CC) $(CFLAGS) -c kernel/pic.c -o $(PIC_OBJ)

$(TIMER_OBJ): kernel/timer.c include/timer.h include/isr.h | $(BUILD_DIR)
>$(CC) $(CFLAGS) -c kernel/timer.c -o $(TIMER_OBJ)

check: $(KERNEL_BIN)
>grub-file --is-x86-multiboot $(KERNEL_BIN)
>@echo "Kernel reconhecido como Multiboot."

iso: $(KERNEL_BIN)
>grub-mkrescue -o $(KERNEL_ISO) $(ISO_DIR)

run: iso
>qemu-system-i386 -cdrom $(KERNEL_ISO)

debug: $(KERNEL_BIN)
>qemu-system-i386 -kernel $(KERNEL_BIN) -s -S

disasm: $(KERNEL_BIN)
>objdump -d $(KERNEL_BIN)

readelf: $(KERNEL_BIN)
>readelf -h $(KERNEL_BIN)

hexdump: $(KERNEL_BIN)
>hexdump -C $(KERNEL_BIN) | head -n 40

clean:
>rm -rf $(BUILD_DIR)
>rm -f $(ISO_DIR)/boot/turingos.bin
