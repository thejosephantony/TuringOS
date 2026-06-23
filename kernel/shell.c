#include "shell.h"
#include "terminal.h"
#include "keyboard.h"
#include <stddef.h>

#define MAX_CMD_LEN 64

static const char* prompt = "turingos> ";

/*
 * Comparacao simples de strings.
 *
 * Como o kernel ainda nao usa a biblioteca padrao do C,
 * nao usamos strcmp(). Esta funcao sera substituida futuramente
 * por uma biblioteca propria do kernel.
 */
static int shell_string_equals(const char* a, const char* b) {
    size_t i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return 0;
        }

        i++;
    }

    return a[i] == '\0' && b[i] == '\0';
}

/*
 * Comandos internos da shell.
 */

static void cmd_help(void) {
    terminal_writeln("Comandos disponiveis:");
    terminal_writeln("  help     - show this message");
    terminal_writeln("  clear    - clean the screen");
    terminal_writeln("  about    - system information");
    terminal_writeln("  version  - kernel version");
    terminal_writeln("  hardware - show hardware information");
    terminal_writeln("  halt     - stop the system");
}

static void cmd_clear(void) {
    terminal_clear();
}

static void cmd_about(void) {
    terminal_writeln("TuringOS is a mini educational operating system inspired by Unix,");
    terminal_writeln("developed in C and x86 Assembly, with focus on Hardware/Software Interface.");
}

static void cmd_version(void) {
    terminal_writeln("TuringOS v0.4 - Interactive shell with PS/2 keyboard polling");
}

static void cmd_hardware(void) {
    terminal_writeln("Hardware information:");
    terminal_writeln("  Architecture : x86 32-bit");
    terminal_writeln("  Bootloader   : GRUB / Multiboot");
    terminal_writeln("  Kernel       : C + Assembly x86");
    terminal_writeln("  Video        : VGA text mode");
    terminal_writeln("  Keyboard     : PS/2 polling");
    terminal_writeln("  Execution    : QEMU");
}

static void cmd_halt(void) {
    terminal_writeln("System halted.");

    while (1) {
        __asm__ volatile ("hlt");
    }
}

/*
 * Executa um comando digitado pelo usuario.
 */
static void shell_execute(const char* cmd) {
    if (shell_string_equals(cmd, "help")) {
        cmd_help();
    } else if (shell_string_equals(cmd, "clear")) {
        cmd_clear();
    } else if (shell_string_equals(cmd, "about")) {
        cmd_about();
    } else if (shell_string_equals(cmd, "version")) {
        cmd_version();
    } else if (shell_string_equals(cmd, "hardware")) {
        cmd_hardware();
    } else if (shell_string_equals(cmd, "halt")) {
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
