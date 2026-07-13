#ifndef ISR_H
#define ISR_H

#include <stdint.h>

/*
 * Registros salvos pelos stubs Assembly.
 */
typedef struct {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp;
    uint32_t ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, user_esp, ss;
} registers_t;

/*
 * Handlers principais.
 */
void isr_handler(registers_t regs);
void irq_handler(registers_t* regs);

/*
 * Registro de callbacks das IRQs.
 */
typedef void (*irq_handler_t)(registers_t* regs);

void irq_register_handler(uint8_t irq, irq_handler_t handler);

/*
 * Retorna quantas vezes uma IRQ foi recebida.
 */
uint32_t irq_get_count(uint8_t irq);

#endif
