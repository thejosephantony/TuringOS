#include "terminal.h"
#include "vga.h"

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static volatile uint16_t* terminal_buffer;

static size_t terminal_strlen(const char* str) {
    size_t length = 0;

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

static void terminal_scroll(void) {
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t source = y * VGA_WIDTH + x;
            const size_t destination = (y - 1) * VGA_WIDTH + x;
            terminal_buffer[destination] = terminal_buffer[source];
        }
    }

    for (size_t x = 0; x < VGA_WIDTH; x++) {
        const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
        terminal_buffer[index] = vga_entry(' ', terminal_color);
    }

    terminal_row = VGA_HEIGHT - 1;
    terminal_column = 0;
}

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;

    terminal_clear();
}

void terminal_clear(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }

    terminal_row = 0;
    terminal_column = 0;
    vga_set_cursor(terminal_column, terminal_row);
}

void terminal_set_color(uint8_t color) {
    terminal_color = color;
}

void terminal_putchar(char character) {
    if (character == '\n') {
        terminal_column = 0;
        terminal_row++;
    } else if (character == '\r') {
        terminal_column = 0;
    } else if (character == '\b') {
        if (terminal_column > 0) {
            terminal_column--;
            const size_t index = terminal_row * VGA_WIDTH + terminal_column;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    } else {
        const size_t index = terminal_row * VGA_WIDTH + terminal_column;
        terminal_buffer[index] = vga_entry(character, terminal_color);
        terminal_column++;
    }

    if (terminal_column >= VGA_WIDTH) {
        terminal_column = 0;
        terminal_row++;
    }

    if (terminal_row >= VGA_HEIGHT) {
        terminal_scroll();
    }

    vga_set_cursor(terminal_column, terminal_row);
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char* data) {
    terminal_write(data, terminal_strlen(data));
}

void terminal_writeln(const char* data) {
    terminal_writestring(data);
    terminal_putchar('\n');
}
