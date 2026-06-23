#include "terminal.h"
#include "vga.h"

static void kernel_print_banner(void) {
    terminal_set_color(vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK));
    terminal_writeln("============================================================");
    terminal_writeln("                         TuringOS v0.4                       ");
    terminal_writeln("              Educational Unix-like Kernel                   ");
    terminal_writeln("============================================================");

    terminal_set_color(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    terminal_writeln("");
}

static void kernel_print_status(void) {
    terminal_set_color(vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
    terminal_writeln("[OK] Kernel initialized successfully");
    terminal_writeln("[OK] VGA text mode driver loaded");
    terminal_writeln("[OK] Terminal abstraction initialized");

    terminal_set_color(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    terminal_writeln("");
    terminal_writeln("Bootloader : GRUB / Multiboot");
    terminal_writeln("Kernel     : C + Assembly x86");
    terminal_writeln("Video      : VGA text mode");
    terminal_writeln("Status     : OK");
    terminal_writeln("");
}

void kernel_main(void) {
    terminal_initialize();

    kernel_print_banner();
    kernel_print_status();

    //terminal_set_color(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
    //terminal_writestring("turingos> ");

    // Inicia a shell (nunca retorna)
    shell_run();

    // (nunca chega aqui)
    while (1) {
        __asm__ volatile ("hlt");
    }
}
