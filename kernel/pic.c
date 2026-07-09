#include "port.h"
#include "pic.h"
#include <stdint.h>

void pic_remap(uint8_t offset1, uint8_t offset2) {
    // Salva máscaras atuais
    uint8_t mask1 = inb(PIC1_DATA);
    uint8_t mask2 = inb(PIC2_DATA);

    // Inicia sequência de inicialização
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    
    // Define offsets
    outb(PIC1_DATA, offset1);
    outb(PIC2_DATA, offset2);
    
    // Comunicação entre PICs (master tem slave no IRQ2)
    outb(PIC1_DATA, 0x04);  // IRQ2 -> Slave
    outb(PIC2_DATA, 0x02);  // Slave ID
    
    // Modo 8086
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);
    
    // Restaura máscaras
    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);
}

void pic_send_eoi(uint8_t irq) {
    if (irq >= 8) {
        outb(PIC2_COMMAND, 0x20);
    }
    outb(PIC1_COMMAND, 0x20);
}

void pic_disable(void) {
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
}