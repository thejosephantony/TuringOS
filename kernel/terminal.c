#include "terminal.h"
#include "vga.h"
#include <stddef.h>

// ============================
// FUNÇÃO AUXILIAR: strlen
// ============================
static size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

// ============================
// ESTADO GLOBAL
// ============================
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

// ============================
// SCROLL
// ============================
static void terminal_scroll(void) {
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t src = y * VGA_WIDTH + x;
            const size_t dst = (y - 1) * VGA_WIDTH + x;
            terminal_buffer[dst] = terminal_buffer[src];
        }
    }
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
        terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
    terminal_row = VGA_HEIGHT - 1;
    terminal_column = 0;
}

// ============================
// LIMPAR TELA (NOVA FUNÇÃO)
// ============================
void terminal_clear(void) {
    // Preenche toda a tela com espaços
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
    // Reseta posição do cursor
    terminal_row = 0;
    terminal_column = 0;
    vga_set_cursor(0, 0);
}

// ============================
// INICIALIZAR TERMINAL
// ============================
void terminal_initialize(void) {
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*)VGA_MEMORY;
    terminal_clear();  // <-- REUTILIZA A FUNÇÃO
}

// ============================
// terminal_putchar
// ============================
void terminal_putchar(char c) {
    switch (c) {
        case '\n':
            terminal_row++;
            terminal_column = 0;
            break;
        case '\r':
            terminal_column = 0;
            break;
        case '\b':
            if (terminal_column > 0) {
                terminal_column--;
                terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] =
                    vga_entry(' ', terminal_color);
            }
            break;
        default:
            terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] =
                vga_entry(c, terminal_color);
            terminal_column++;
            break;
    }

    if (terminal_column >= VGA_WIDTH) {
        terminal_row++;
        terminal_column = 0;
    }

    if (terminal_row >= VGA_HEIGHT) {
        terminal_scroll();
    }

    vga_set_cursor(terminal_column, terminal_row);
}

// ============================
// terminal_write e terminal_writestring
// ============================
void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}