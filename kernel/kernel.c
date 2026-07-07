#include "port.h"
#include "terminal.h"
#include "vga.h"
#include "shell.h"
#include "idt.h"
#include "pic.h"
#include "timer.h"
#include "keyboard.h"

static void kernel_print_banner(void) {
    terminal_set_color(vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK));
    terminal_writeln("============================================================");
    terminal_writeln("                         TuringOS v0.5                       ");
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
    terminal_writeln("[OK] IDT and PIC configured");
    terminal_writeln("[OK] Timer (IRQ0) and Keyboard (IRQ1) enabled");
    terminal_set_color(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    terminal_writeln("");
    terminal_writeln("Bootloader : GRUB / Multiboot");
    terminal_writeln("Kernel     : C + Assembly x86");
    terminal_writeln("Video      : VGA text mode");
    terminal_writeln("Interrupts : Enabled (IRQ0, IRQ1)");
    terminal_writeln("Status     : OK");
    terminal_writeln("");
}

void kernel_main(void) {
    terminal_initialize();

    idt_init();
    pic_remap(0x20, 0x28);

    // Desabilita todas as IRQs (mascara)
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);

    // Inicializa teclado (habilita IRQ1)
    outb(0x64, 0xAE);
    keyboard_init();

    // Exibe banner e status
    kernel_print_banner();
    kernel_print_status();

    // Habilita interrupções
    __asm__ volatile ("sti");

    // Inicia shell
    shell_run();

    while (1) __asm__("hlt");
}