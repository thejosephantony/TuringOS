#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/*
 * Inicializa o PIT e registra o handler da IRQ0.
 */
void timer_init(uint32_t frequency);

/*
 * Informacoes de tempo mantidas pelo timer.
 */
uint32_t timer_get_ticks(void);
uint32_t timer_get_frequency(void);
uint32_t timer_get_uptime_seconds(void);

#endif
