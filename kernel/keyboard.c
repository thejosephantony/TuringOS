#include "keyboard.h"
#include "isr.h"
#include "pic.h"
#include "port.h"
#include <stddef.h>

#define KEYBOARD_BUFFER_SIZE 256

static volatile char key_buffer[KEYBOARD_BUFFER_SIZE];
static volatile size_t buffer_head = 0;
static volatile size_t buffer_tail = 0;

volatile uint32_t keyboard_irq_count = 0;

static char scancode_to_ascii(uint8_t scancode) {
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

void keyboard_irq_handler(registers_t* regs) {
    (void)regs;
    keyboard_irq_count++;

    uint8_t scancode = inb(0x60);
    if (scancode & 0x80) return; // tecla solta

    char ascii = scancode_to_ascii(scancode);
    if (ascii == 0) return;

    size_t next = (buffer_head + 1) % KEYBOARD_BUFFER_SIZE;
    if (next != buffer_tail) {
        key_buffer[buffer_head] = ascii;
        buffer_head = next;
    }
}

void keyboard_init(void) {
    irq_register_handler(1, keyboard_irq_handler);

    // Habilita IRQ1 no PIC (desmascara)
    uint8_t mask = inb(PIC1_DATA);
    mask &= ~(1 << 1);
    outb(PIC1_DATA, mask);

    // Habilita o teclado (comando PS/2)
    outb(0x64, 0xAE);
}

char keyboard_read_char(void) {
    while (buffer_head == buffer_tail) {
        __asm__ volatile ("hlt");
    }
    char c = key_buffer[buffer_tail];
    buffer_tail = (buffer_tail + 1) % KEYBOARD_BUFFER_SIZE;
    return c;
}

uint32_t keyboard_get_irq_count(void) {
    return keyboard_irq_count;
}