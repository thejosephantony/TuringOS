#include "shell.h"
#include "terminal.h"
#include "keyboard.h"
#include "timer.h"
#include "isr.h"
#include "pic.h"
#include "port.h"
#include "klib.h"

#include <stddef.h>
#include <stdint.h>

#define MAX_CMD_LEN 64

static const char* prompt = "turingos> ";

/*
 * Escreve um inteiro decimal sem depender da biblioteca padrao.
 */
static void shell_write_uint32(uint32_t value) {
    char buffer[11];

    kutoa(value, buffer, 10);
    terminal_writestring(buffer);
}

/*
 * Escreve um byte no formato hexadecimal 0xFF.
 */
static void shell_write_hex8(uint8_t value) {
    char buffer[3];

    kutoa(value, buffer, 16);

    terminal_writestring("0x");

    if (value < 16) {
        terminal_putchar('0');
    }

    terminal_writestring(buffer);
}

/*
 * Le o registrador EFLAGS para consultar o bit IF.
 */
static uint32_t shell_read_eflags(void) {
    uint32_t eflags;

    __asm__ volatile (
        "pushfl\n\t"
        "popl %0"
        : "=r"(eflags)
    );

    return eflags;
}

static void cmd_help(void) {
    terminal_writeln("Comandos disponiveis:");
    terminal_writeln("  help     - show this message");
    terminal_writeln("  clear    - clean the screen");
    terminal_writeln("  about    - system information");
    terminal_writeln("  version  - kernel version");
    terminal_writeln("  hardware - show hardware information");
    terminal_writeln("  uptime   - show system uptime and PIT ticks");
    terminal_writeln("  irqinfo  - show IRQ counters and PIC masks");
    terminal_writeln("  debug    - show kernel runtime diagnostics");
    terminal_writeln("  libtest  - test the internal kernel library");
    terminal_writeln("  halt     - stop the system");
}

static void cmd_clear(void) {
    terminal_clear();
}

static void cmd_about(void) {
    terminal_writeln(
        "TuringOS is a mini educational operating system inspired by Unix,"
    );
    terminal_writeln(
        "developed in C and x86 Assembly, with focus on Hardware/Software Interface."
    );
}

static void cmd_version(void) {
    terminal_writeln(
        "TuringOS v0.7-dev - Runtime diagnostics and IRQ counters"
    );
}

static void cmd_hardware(void) {
    terminal_writeln("Hardware information:");
    terminal_writeln("  Architecture : x86 32-bit");
    terminal_writeln("  Bootloader   : GRUB / Multiboot");
    terminal_writeln("  Kernel       : C + Assembly x86");
    terminal_writeln("  Video        : VGA text mode");
    terminal_writeln("  Keyboard     : PS/2 interrupt-driven (IRQ1)");
    terminal_writeln("  Timer        : PIT (IRQ0)");
    terminal_writeln("  Execution    : QEMU");
}

static void cmd_uptime(void) {
    uint32_t ticks = timer_get_ticks();
    uint32_t frequency = timer_get_frequency();
    uint32_t seconds = timer_get_uptime_seconds();

    terminal_writestring("Uptime: ");
    shell_write_uint32(seconds);
    terminal_writeln(" seconds");

    terminal_writestring("PIT ticks: ");
    shell_write_uint32(ticks);
    terminal_writeln("");

    terminal_writestring("PIT frequency: ");
    shell_write_uint32(frequency);
    terminal_writeln(" Hz");
}

static void cmd_irqinfo(void) {
    uint8_t master_mask = inb(PIC1_DATA);
    uint8_t slave_mask = inb(PIC2_DATA);

    terminal_writeln("IRQ information:");

    terminal_writestring("  IRQ0 timer count    : ");
    shell_write_uint32(irq_get_count(0));
    terminal_writeln("");

    terminal_writestring("  IRQ1 keyboard count : ");
    shell_write_uint32(irq_get_count(1));
    terminal_writeln("");

    terminal_writestring("  PIC master mask     : ");
    shell_write_hex8(master_mask);
    terminal_writeln("");

    terminal_writestring("  PIC slave mask      : ");
    shell_write_hex8(slave_mask);
    terminal_writeln("");

    terminal_writestring("  IRQ0 state          : ");
    terminal_writeln(
        (master_mask & (1u << 0)) == 0 ? "enabled" : "masked"
    );

    terminal_writestring("  IRQ1 state          : ");
    terminal_writeln(
        (master_mask & (1u << 1)) == 0 ? "enabled" : "masked"
    );
}

static void cmd_debug(void) {
    uint32_t eflags = shell_read_eflags();
    uint8_t master_mask = inb(PIC1_DATA);
    uint8_t slave_mask = inb(PIC2_DATA);

    terminal_writeln("Kernel debug information:");
    terminal_writeln("  Version            : v0.7-dev");
    terminal_writeln("  Executable format  : ELF32");
    terminal_writeln("  Compilation mode   : freestanding");

    terminal_writestring("  Interrupt flag     : ");
    terminal_writeln(
        (eflags & (1u << 9)) != 0 ? "enabled" : "disabled"
    );

    terminal_writestring("  Timer frequency    : ");
    shell_write_uint32(timer_get_frequency());
    terminal_writeln(" Hz");

    terminal_writestring("  Timer ticks        : ");
    shell_write_uint32(timer_get_ticks());
    terminal_writeln("");

    terminal_writestring("  Uptime             : ");
    shell_write_uint32(timer_get_uptime_seconds());
    terminal_writeln(" seconds");

    terminal_writestring("  PIC master mask    : ");
    shell_write_hex8(master_mask);
    terminal_writeln("");

    terminal_writestring("  PIC slave mask     : ");
    shell_write_hex8(slave_mask);
    terminal_writeln("");
}


static void cmd_libtest(void) {
    const char source[] = "TuringOS";

    char copy[16];
    char decimal[11];
    char hexadecimal[9];

    int passed = 1;

    kmemset(copy, 0, sizeof(copy));
    kmemcpy(copy, source, kstrlen(source) + 1);

    kutoa(2026, decimal, 10);
    kutoa(0x2A, hexadecimal, 16);

    if (kstrlen(source) != 8) {
        passed = 0;
    }

    if (kstrcmp(copy, source) != 0) {
        passed = 0;
    }

    if (kstrcmp(decimal, "2026") != 0) {
        passed = 0;
    }

    if (kstrcmp(hexadecimal, "2A") != 0) {
        passed = 0;
    }

    terminal_writeln("Kernel library self-test:");

    terminal_writestring("  kstrlen  : ");
    shell_write_uint32((uint32_t)kstrlen(source));
    terminal_writeln("");

    terminal_writestring("  kmemcpy  : ");
    terminal_writeln(copy);

    terminal_writestring("  kutoa 10 : ");
    terminal_writeln(decimal);

    terminal_writestring("  kutoa 16 : ");
    terminal_writeln(hexadecimal);

    terminal_writestring("  result    : ");
    terminal_writeln(passed ? "PASS" : "FAIL");
}

static void cmd_halt(void) {
    terminal_writeln("System halted.");

    __asm__ volatile ("cli");

    while (1) {
        __asm__ volatile ("hlt");
    }
}

/*
 * Executa um comando digitado pelo usuario.
 */
static void shell_execute(const char* cmd) {
    if (kstrcmp(cmd, "help") == 0) {
        cmd_help();
    } else if (kstrcmp(cmd, "clear") == 0) {
        cmd_clear();
    } else if (kstrcmp(cmd, "about") == 0) {
        cmd_about();
    } else if (kstrcmp(cmd, "version") == 0) {
        cmd_version();
    } else if (kstrcmp(cmd, "hardware") == 0) {
        cmd_hardware();
    } else if (kstrcmp(cmd, "uptime") == 0) {
        cmd_uptime();
    } else if (kstrcmp(cmd, "irqinfo") == 0) {
        cmd_irqinfo();
    } else if (kstrcmp(cmd, "debug") == 0) {
        cmd_debug();
    } else if (kstrcmp(cmd, "libtest") == 0) {
        cmd_libtest();
    } else if (kstrcmp(cmd, "halt") == 0) {
        cmd_halt();
    } else {
        terminal_writestring("Unknown command: ");
        terminal_writestring(cmd);
        terminal_writeln("");
        terminal_writeln("Type 'help' for a list of commands.");
    }
}

/*
 * Loop principal da shell.
 */
void shell_run(void) {
    char buffer[MAX_CMD_LEN];
    size_t pos = 0;

    terminal_writeln("Welcome to TuringOS!");
    terminal_writeln("Type 'help' for available commands.");
    terminal_writeln("");

    while (1) {
        terminal_writestring(prompt);

        pos = 0;
        buffer[0] = '\0';

        while (1) {
            char c = keyboard_read_char();

            if (c == 0) {
                continue;
            }

            if (c == '\n' || c == '\r') {
                terminal_putchar('\n');
                break;
            }

            if (c == '\b') {
                if (pos > 0) {
                    pos--;
                    buffer[pos] = '\0';
                    terminal_putchar('\b');
                }

                continue;
            }

            if (pos < MAX_CMD_LEN - 1) {
                buffer[pos] = c;
                pos++;
                buffer[pos] = '\0';
                terminal_putchar(c);
            }
        }

        if (pos == 0) {
            continue;
        }

        shell_execute(buffer);
    }
}
