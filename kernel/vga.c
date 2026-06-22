#include "vga.h"

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return (uint8_t)fg | (uint8_t)(bg << 4);
}

uint16_t vga_entry(unsigned char character, uint8_t color) {
    return (uint16_t)character | (uint16_t)color << 8;
}

void vga_putchar_at(char character, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    VGA_MEMORY[index] = vga_entry(character, color);
}

static void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static uint8_t inb(uint16_t port) {
    uint8_t value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

void vga_set_cursor(size_t x, size_t y) {
    uint16_t position = (uint16_t)(y * VGA_WIDTH + x);

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(position & 0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));
}

void vga_get_cursor(size_t* x, size_t* y) {
    uint16_t position = 0;

    outb(0x3D4, 0x0E);
    position = (uint16_t)(inb(0x3D5) << 8);

    outb(0x3D4, 0x0F);
    position |= inb(0x3D5);

    *x = position % VGA_WIDTH;
    *y = position / VGA_WIDTH;
}
