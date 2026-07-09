#ifndef IDT_H
#define IDT_H

#include <stdint.h>

// Estrutura de uma entrada da IDT (8 bytes)
typedef struct {
    uint16_t base_low;     // Base inferior
    uint16_t sel;          // Seletor de segmento (código kernel = 0x08)
    uint8_t  always0;      // Sempre 0
    uint8_t  flags;        // Flags (presente, DPL, tipo)
    uint16_t base_high;    // Base superior
} __attribute__((packed)) idt_entry_t;

// Estrutura do ponteiro da IDT (lida pelo LIDT)
typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

extern idt_entry_t idt_entries[256];
extern idt_ptr_t idt_ptr;

void idt_init(void);
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

#endif