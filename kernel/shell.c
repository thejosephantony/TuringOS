#include "shell.h"
#include "terminal.h"
#include "keyboard.h"   // para ler caracteres
#include <stddef.h>

#define MAX_CMD_LEN 64

static const char* prompt = "turingos> ";

// Comandos internos

static void cmd_help(void) {
    terminal_writeln("Comandos disponiveis:");
    terminal_writeln("  help    - show this message");
    terminal_writeln("  clear   - clean the screen");
    terminal_writeln("  about   - system information");
    terminal_writeln("  version - kernel version");
    terminal_writeln("  halt    - turn off the system");
}

static void cmd_clear(void) {
    terminal_clear();
}

static void cmd_about(void) {
    terminal_writeln("TuringOS is a mini educational operating system inspired by Unix,");
    terminal_writeln("developed in C and x86 Assembly, with a focus on Hardware/Software Interface.");
}

static void cmd_version(void) {
    terminal_writeln("TuringOS v0.4 (basic shell)");
}

static void cmd_halt(void) {
    terminal_writeln("Shutting down...");
    while (1) {
        __asm__ volatile ("hlt");
    }
}

// Executa um comando (string sem \n)

static void shell_execute(const char* cmd) {
    // Comparação simples (strcmp será implementado na v0.8)
    if (cmd[0] == 'h' && cmd[1] == 'e' && cmd[2] == 'l' && cmd[3] == 'p' && cmd[4] == '\0')
        cmd_help();
    else if (cmd[0] == 'c' && cmd[1] == 'l' && cmd[2] == 'e' && cmd[3] == 'a' && cmd[4] == 'r' && cmd[5] == '\0')
        cmd_clear();
    else if (cmd[0] == 'a' && cmd[1] == 'b' && cmd[2] == 'o' && cmd[3] == 'u' && cmd[4] == 't' && cmd[5] == '\0')
        cmd_about();
    else if (cmd[0] == 'v' && cmd[1] == 'e' && cmd[2] == 'r' && cmd[3] == 's' && cmd[4] == 'i' && cmd[5] == 'o' && cmd[6] == 'n' && cmd[7] == '\0')
        cmd_version();
    else if (cmd[0] == 'h' && cmd[1] == 'a' && cmd[2] == 'l' && cmd[3] == 't' && cmd[4] == '\0')
        cmd_halt();
    else {
        terminal_writestring("Unknown command: ");
        terminal_writestring(cmd);
        terminal_writeln("");
        terminal_writeln("Type 'help' for a list of commands.");
    }
}

// Loop principal da shell

void shell_run(void) {
    char buffer[MAX_CMD_LEN];
    size_t pos = 0;

    terminal_writeln("Welcome to TuringOS!");
    terminal_writeln("Type 'help' for available commands.\n");

    while (1) {
        // Exibe o prompt
        terminal_writestring(prompt);

        // Limpa o buffer
        pos = 0;
        buffer[0] = '\0';

        // Lê caracteres até Enter
        while (1) {
            char c = keyboard_read_char();
            if (c == 0) continue;   // tecla solta ou inválida

            if (c == '\n') {
                terminal_putchar('\n');
                break;
            } else if (c == '\b') {
                if (pos > 0) {
                    pos--;
                    terminal_putchar('\b');
                }
            } else if (pos < MAX_CMD_LEN - 1) {
                buffer[pos++] = c;
                terminal_putchar(c);
            }
        }

        buffer[pos] = '\0';

        // Se não digitou nada, continua
        if (pos == 0) continue;

        // Executa o comando
        shell_execute(buffer);
    }
}