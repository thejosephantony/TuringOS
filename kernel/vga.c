#include "vga.h"
#include <stddef.h>
#include <stdint.h>

void vga_putchar_at(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    VGA_MEMORY[index] = vga_entry(c, color);
}

static void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}


void vga_set_cursor(size_t x, size_t y) {
    uint16_t pos = y * VGA_WIDTH + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));

   // Habilitar cursor e definir formato (linha de início e fim)
    outb(0x3D4, 0x0A);          // registrador de início do cursor
    outb(0x3D5, 0x0D);          // começa na linha 13 (bloco grande)
    outb(0x3D4, 0x0B);          // registrador de fim do cursor
    outb(0x3D5, 0x0E);          // termina na linha 14 (sublinhado)

}

void vga_get_cursor(size_t *x, size_t *y) {
    uint16_t pos = 0;
    outb(0x3D4, 14);
    pos |= (inb(0x3D5) << 8);
    outb(0x3D4, 15);
    pos |= inb(0x3D5);
    *x = pos % VGA_WIDTH;
    *y = pos / VGA_WIDTH;
}