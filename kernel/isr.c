#include "isr.h"
#include "pic.h"
#include "terminal.h"
#include "vga.h"
#include "keyboard.h"

// Array de handlers para IRQs (inicialmente NULL)
static irq_handler_t irq_handlers[16] = {0};

// Handlers para exceções (apenas para debug)
static const char* exception_messages[] = {
    "Division By Zero", "Debug", "Non Maskable Interrupt", "Breakpoint",
    "Into Detected Overflow", "Out of Bounds", "Invalid Opcode", "No Coprocessor",
    "Double Fault", "Coprocessor Segment Overrun", "Bad TSS", "Segment Not Present",
    "Stack Fault", "General Protection Fault", "Page Fault", "Unknown Interrupt",
    "Coprocessor Fault", "Alignment Check", "Machine Check", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved"
};

void isr_handler(registers_t regs) {
    terminal_set_color(vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK));
    terminal_writestring("EXCEPTION: ");
    terminal_writestring(exception_messages[regs.int_no]);
    terminal_writestring(" (");
    terminal_putchar('0' + (regs.int_no / 10));
    terminal_putchar('0' + (regs.int_no % 10));
    terminal_writestring(")\n");
    terminal_writestring("System Halted.\n");
    while (1) {
        __asm__ volatile ("hlt");
    }
}

void irq_handler(registers_t* regs) {
    if (regs->int_no >= 32 && regs->int_no < 48) {
        uint8_t irq = regs->int_no - 32;
        if (irq == 1) {
            keyboard_irq_handler(regs);
        } else if (irq_handlers[irq] != 0) {
            irq_handlers[irq](regs);
        }
        pic_send_eoi(irq);
    }
}

void irq_register_handler(uint8_t irq, irq_handler_t handler) {
    if (irq < 16) {
        irq_handlers[irq] = handler;
    }
}