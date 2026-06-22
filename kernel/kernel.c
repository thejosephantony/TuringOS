#include "terminal.h"

static void sleep_approx_seconds(int seconds) {
    volatile unsigned int loops = 0;
    volatile unsigned int target = seconds * 10000000;
    while (loops < target) loops++;
}

void kernel_main(void) {
    terminal_initialize();
    
    for (int i = 0; i < 30; i++) {
        terminal_writestring("Linha: ");
        terminal_putchar('0' + (i % 10));
        terminal_putchar('\n');
    }
    
    terminal_writestring("\nTestes OK! Limpando em instantes...\n");
    sleep_approx_seconds(2);
    
    terminal_clear();
    
    terminal_writestring("##### #   # ####  ### #   #  ###      ###   #### \n");
    terminal_writestring("  #   #   # #   #  #  ##  # #        #   # #    \n");
    terminal_writestring("  #   #   # ####   #  # # # #  ##    #   #  ###  \n");
    terminal_writestring("  #   #   # #  #   #  #  ## #   #    #   #     # \n");
    terminal_writestring("  #    ###  #   # ### #   #  ###      ###  ####  \n");
    terminal_writestring("v0.2\n");
    
    while (1) {
        __asm__ volatile ("hlt");
    }
}