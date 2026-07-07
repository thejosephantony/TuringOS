#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include "isr.h"   // para registers_t

void keyboard_init(void);
char keyboard_read_char(void);
uint32_t keyboard_get_irq_count(void);

// Protótipo da função handler (agora não-static)
void keyboard_irq_handler(registers_t* regs);

#endif