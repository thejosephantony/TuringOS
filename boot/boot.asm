; TuringOS - boot.asm
; Entrada inicial do kernel usando Multiboot e NASM.

BITS 32

section .multiboot
align 4

MULTIBOOT_MAGIC    equ 0x1BADB002
MULTIBOOT_FLAGS    equ 0x00000000
MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

dd MULTIBOOT_MAGIC
dd MULTIBOOT_FLAGS
dd MULTIBOOT_CHECKSUM

section .bss
align 16

stack_bottom:
    resb 16384
stack_top:

section .text
global start
extern kernel_main

; ---------- GDT personalizada ----------
gdt_start:
    ; Descritor nulo
    dd 0x0
    dd 0x0

; Descritor de código (0x08)
gdt_code:
    dw 0xFFFF       ; limite 0-15
    dw 0x0000       ; base 0-15
    db 0x00         ; base 16-23
    db 0x9A         ; presente, ring0, executável, leitura
    db 0xCF         ; granularidade 4KB, 32 bits, limite 16-19
    db 0x00         ; base 24-31

; Descritor de dados (0x10)
gdt_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0x92         ; presente, ring0, dados, escrita
    db 0xCF
    db 0x00
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

; Seletores (em bytes)
CODE_SEG equ gdt_code - gdt_start   ; 0x08
DATA_SEG equ gdt_data - gdt_start   ; 0x10

; ---------- Ponto de entrada ----------
start:
    ; Carrega a GDT personalizada
    lgdt [gdt_descriptor]

    ; Atualiza os segmentos de dados
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Atualiza o seletor de código com um far jump
    jmp CODE_SEG:.reload_cs
.reload_cs:

    ; Configura pilha
    mov esp, stack_top

    ; Chama o kernel em C
    call kernel_main

.hang:
    cli
    hlt
    jmp .hang
; Informa ao linker que este objeto não exige pilha executável.
section .note.GNU-stack noalloc noexec nowrite progbits
