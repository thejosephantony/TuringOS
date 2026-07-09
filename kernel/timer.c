#include "timer.h"
#include "isr.h"
#include "pic.h"
#include "port.h"

static uint32_t tick_count = 0;

static void timer_callback(registers_t* regs) {
    (void)regs;
    tick_count++;
}

void timer_init(uint32_t frequency) {
    // Registra o handler para IRQ0
    irq_register_handler(0, timer_callback);

    // Configura o PIT
    uint32_t divisor = 1193180 / frequency;
    outb(0x43, 0x36);
    outb(0x40, (uint8_t)(divisor & 0xFF));
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));

    // Habilita IRQ0 no PIC (desmascara)
    uint8_t mask = inb(PIC1_DATA);
    mask &= ~(1 << 0);   // Zera bit 0 (IRQ0)
    outb(PIC1_DATA, mask);
}

uint32_t timer_get_ticks(void) {
    return tick_count;
}