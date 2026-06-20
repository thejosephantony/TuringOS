# ✅ Aderência aos requisitos da disciplina

## 1. Interface direta com hardware

O TuringOS realiza interação direta com hardware virtualizado pelo QEMU por meio de escrita VGA, portas de I/O, teclado PS/2, timer/PIT e serial.

Exemplo central:

```text
Endereço VGA em modo texto: 0xB8000
```

## 2. Código Assembly

O projeto utiliza Assembly no arquivo `boot/boot.asm` para declarar cabeçalho Multiboot, definir ponto de entrada, configurar pilha inicial e chamar `kernel_main`.

## 3. Geração de código de máquina e binário

```text
boot.asm      → boot.o
kernel.c      → kernel.o
vga.c         → vga.o
terminal.c    → terminal.o
        ↓
linker.ld
        ↓
turingos.bin
        ↓
turingos.iso
```

## 4. Gerenciamento de dispositivo não suportado diretamente

O TuringOS implementa drivers próprios para VGA, teclado PS/2, timer/PIT e serial.

## 5. Engenharia reversa de sistema sem código-fonte

Será feita análise de binário sem consultar código-fonte usando `hexdump`, `objdump`, `ndisasm`, `readelf` e GDB.

## 6. Depuração/prototipação virtual

O QEMU permite testar o sistema sem instalação física. O GDB permite breakpoints, inspeção de registradores e análise de memória.

## 7. Kanban semanal

O projeto usa GitHub Projects com colunas Backlog, A fazer, Em desenvolvimento, Em teste e Concluído.

## 8. Versionamento

O projeto usa Git, GitHub, branches, commits semânticos e tags.
