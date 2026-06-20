# 🛠️ Guia de implementação

## `boot.asm`

Responsabilidades: cabeçalho Multiboot, ponto de entrada, stack e chamada a `kernel_main`.

## `kernel.c`

Responsabilidades: inicializar terminal, mostrar mensagem inicial e manter loop principal.

## `linker.ld`

Responsabilidades: definir `ENTRY(_start)` e organizar `.text`, `.rodata`, `.data` e `.bss`.

## `grub.cfg`

```cfg
menuentry "TuringOS" {
    multiboot /boot/turingos.bin
    boot
}
```

## VGA

Endereço: `0xB8000`.

Funções planejadas:

```c
void vga_clear(void);
void vga_putchar(char c);
void vga_write(const char* str);
void vga_set_color(unsigned char color);
```

## Terminal

Funções planejadas:

```c
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* str);
void terminal_writeln(const char* str);
void terminal_clear(void);
```

## Teclado

Começar por polling usando portas `0x60` e `0x64`.

## Shell

Comandos iniciais: `help`, `clear`, `about`, `version`, `echo`.
