#include "idt.h"
#include <stddef.h>

// Tabela IDT (256 entradas)
idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

// Declaração das funções externas Assembly
extern void idt_load(void);
extern void isr0(void);
extern void isr1(void);

#define DECLARE_ISR(n) extern void isr##n(void);
#define DECLARE_IRQ(n) extern void irq##n(void);

// ISRs 0-31
extern void isr0(void);  extern void isr1(void);  extern void isr2(void);  extern void isr3(void);
extern void isr4(void);  extern void isr5(void);  extern void isr6(void);  extern void isr7(void);
extern void isr8(void);  extern void isr9(void);  extern void isr10(void); extern void isr11(void);
extern void isr12(void); extern void isr13(void); extern void isr14(void); extern void isr15(void);
extern void isr16(void); extern void isr17(void); extern void isr18(void); extern void isr19(void);
extern void isr20(void); extern void isr21(void); extern void isr22(void); extern void isr23(void);
extern void isr24(void); extern void isr25(void); extern void isr26(void); extern void isr27(void);
extern void isr28(void); extern void isr29(void); extern void isr30(void); extern void isr31(void);

// IRQs 0-15
extern void irq0(void);  extern void irq1(void);  extern void irq2(void);  extern void irq3(void);
extern void irq4(void);  extern void irq5(void);  extern void irq6(void);  extern void irq7(void);
extern void irq8(void);  extern void irq9(void);  extern void irq10(void); extern void irq11(void);
extern void irq12(void); extern void irq13(void); extern void irq14(void); extern void irq15(void);

// Ponteiros para todas as funções (usado para instalar)
void* isr_routines[48] = {
    isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7,
    isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15,
    isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23,
    isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31,
    irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7,
    irq8, irq9, irq10, irq11, irq12, irq13, irq14, irq15
};

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags = flags;
}

void idt_init(void) {
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt_entries;

    // Limpa a IDT
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    // Instala ISRs (0-31) e IRQs (32-47)
    for (int i = 0; i < 48; i++) {
        uint32_t base = (uint32_t)isr_routines[i];
        // Flags: Presente, Ring 0, Tipo 0xE (Interrupt Gate)
        uint8_t flags = 0x8E; // 1000 1110
        idt_set_gate(i, base, 0x08, flags);
    }

    // Carrega a IDT usando a função assembly
    idt_load();
}