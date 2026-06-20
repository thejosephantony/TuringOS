# 🧩 Arquitetura do TuringOS

## Visão geral

```text
+------------------------------------------------+
| Shell                                          |
+------------------------------------------------+
| Chamadas internas conceituais                  |
+------------------------------------------------+
| Kernel                                         |
+------------------------------------------------+
| Drivers básicos                                |
+------------------------------------------------+
| Hardware virtualizado/QEMU                     |
+------------------------------------------------+
```

## Hardware virtualizado

Fornecido pelo QEMU: CPU x86, memória, VGA, teclado PS/2, timer/PIT e serial.

## Drivers

Módulos planejados: `vga.c`, `keyboard.c`, `timer.c` e `serial.c`.

## Kernel

Coordena inicialização, terminal, drivers, memória básica e shell.

## Terminal

Organiza saída textual, quebra de linha, cursor, limpeza de tela e rolagem futura.

## Shell

Interpreta comandos como `help`, `clear`, `about`, `version` e `echo`.

## Fluxo

```text
QEMU → GRUB → boot.asm → kernel_main → terminal_initialize → shell
```
