#include "isr.h"
#include "pic.h"
#include "terminal.h"
#include "vga.h"
#include "keyboard.h"

/*
 * Callbacks registrados para as 16 IRQs do PIC.
 */
static irq_handler_t irq_handlers[16] = {0};

/*
 * Contadores usados pelos comandos de diagnostico.
 */
static volatile uint32_t irq_counts[16] = {0};

static const char* exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t regs) {
    uint32_t int_no = regs.int_no;

    terminal_set_color(
        vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK)
    );

    terminal_writestring("EXCEPTION: ");

    if (int_no < 32) {
        terminal_writestring(exception_messages[int_no]);
    } else {
        terminal_writestring("Unknown");
    }

    terminal_writestring(" (");

    if (int_no >= 10) {
        terminal_putchar((char)('0' + ((int_no / 10) % 10)));
    }

    terminal_putchar((char)('0' + (int_no % 10)));
    terminal_writestring(")\n");
    terminal_writestring("System Halted.\n");

    __asm__ volatile ("cli");

    while (1) {
        __asm__ volatile ("hlt");
    }
}

void irq_handler(registers_t* regs) {
    uint8_t irq;

    if (regs->int_no < 32 || regs->int_no >= 48) {
        return;
    }

    irq = (uint8_t)(regs->int_no - 32);
    irq_counts[irq]++;

    /*
     * O teclado possui tratamento especifico porque alimenta
     * o buffer consumido pela shell.
     */
    if (irq == 1) {
        keyboard_irq_handler(regs);
    } else if (irq_handlers[irq] != 0) {
        irq_handlers[irq](regs);
    }

    pic_send_eoi(irq);
}

void irq_register_handler(uint8_t irq, irq_handler_t handler) {
    if (irq < 16) {
        irq_handlers[irq] = handler;
    }
}

uint32_t irq_get_count(uint8_t irq) {
    if (irq >= 16) {
        return 0;
    }

    return irq_counts[irq];
}
