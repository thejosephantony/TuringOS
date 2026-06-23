#include "keyboard.h"
#include <stdint.h>

static uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static int keyboard_has_data(void) {
    return inb(0x64) & 0x01;
}

static uint8_t keyboard_read_scancode(void) {
    return inb(0x60);
}

static char scancode_to_ascii(uint8_t scancode) {
    // Tabela básica (US layout, sem Shift)
    static const char table[] = {
        0,   0,   '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
        '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
        0,   'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
        0,   '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
        '*', 0,   ' '
    };
    if (scancode < sizeof(table))
        return table[scancode];
    return 0;
}

char keyboard_read_char(void) {
    while (!keyboard_has_data()) {
        // espera ocupada (polling)
    }
    uint8_t scancode = keyboard_read_scancode();
    if (scancode & 0x80) {
        // tecla solta – ignorar
        return 0;
    }
    return scancode_to_ascii(scancode);
}