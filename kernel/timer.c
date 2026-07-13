#include "timer.h"
#include "isr.h"
#include "pic.h"
#include "port.h"

#define PIT_BASE_FREQUENCY    1193182u
#define DEFAULT_TIMER_FREQUENCY 100u

/*
 * tick_count e alterado pelo handler da IRQ0.
 * volatile impede que o compilador reutilize um valor antigo.
 */
static volatile uint32_t tick_count = 0;
static uint32_t timer_frequency = 0;

static void timer_callback(registers_t* regs) {
    (void)regs;
    tick_count++;
}

void timer_init(uint32_t frequency) {
    uint32_t divisor;
    uint8_t mask;

    if (frequency == 0) {
        frequency = DEFAULT_TIMER_FREQUENCY;
    }

    divisor = PIT_BASE_FREQUENCY / frequency;

    if (divisor == 0) {
        divisor = 1;
    }

    if (divisor > 65535u) {
        divisor = 65535u;
    }

    /*
     * Guarda a frequencia efetiva resultante do divisor inteiro.
     */
    timer_frequency = PIT_BASE_FREQUENCY / divisor;
    tick_count = 0;

    /*
     * Registra o callback da IRQ0.
     */
    irq_register_handler(0, timer_callback);

    /*
     * Canal 0 do PIT, acesso low/high byte, modo 3.
     */
    outb(0x43, 0x36);
    outb(0x40, (uint8_t)(divisor & 0xFF));
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));

    /*
     * Desmascara a IRQ0 no PIC mestre.
     */
    mask = inb(PIC1_DATA);
    mask &= (uint8_t)~(1u << 0);
    outb(PIC1_DATA, mask);
}

uint32_t timer_get_ticks(void) {
    return tick_count;
}

uint32_t timer_get_frequency(void) {
    return timer_frequency;
}

uint32_t timer_get_uptime_seconds(void) {
    if (timer_frequency == 0) {
        return 0;
    }

    return tick_count / timer_frequency;
}
