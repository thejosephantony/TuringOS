#ifndef ISR_H
#define ISR_H

#include <stdint.h>

// Estrutura dos registros salvos pelo stub assembly
typedef struct {
    uint32_t gs, fs, es, ds;  // Segmentos
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // GP registers
    uint32_t int_no, err_code; // Número da int e erro
    uint32_t eip, cs, eflags, user_esp, ss; // CPU push
} registers_t;

// Handlers
void isr_handler(registers_t regs);
void irq_handler(registers_t* regs); 

// Registra callbacks para IRQs
typedef void (*irq_handler_t)(registers_t* regs);
void irq_register_handler(uint8_t irq, irq_handler_t handler);


#endif