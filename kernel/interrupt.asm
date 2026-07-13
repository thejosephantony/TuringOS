; kernel/interrupt.asm
; Stubs para interrupções (exceções e IRQs)

section .text

; Macro para criar stubs de ISR sem código de erro
%macro ISR_NOERR 1
global isr%1
isr%1:
    cli
    push 0          ; Código de erro dummy (0)
    push %1         ; Número da interrupção
    jmp isr_common_stub
%endmacro

; Macro para criar stubs de ISR com código de erro
%macro ISR_ERR 1
global isr%1
isr%1:
    cli
    push %1         ; Número da interrupção
    jmp isr_common_stub
%endmacro

; Macro para criar stubs de IRQ
%macro IRQ 2
global irq%1
irq%1:
    cli
    push 0
    push %2         ; Número da interrupção (IDT)
    jmp irq_common_stub
%endmacro

; ---------- Exceções (0-31) ----------
ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERR   8
ISR_NOERR 9
ISR_ERR   10
ISR_ERR   11
ISR_ERR   12
ISR_ERR   13
ISR_ERR   14
ISR_NOERR 15
ISR_NOERR 16
ISR_ERR   17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_ERR   21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_ERR   30
ISR_NOERR 31

; ---------- IRQs (32-47) ----------
; IRQ0 (Timer)  -> IDT 32
; IRQ1 (Keyboard) -> IDT 33
IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

; ---------- Stub Comum para Exceções ----------
extern isr_handler
isr_common_stub:
    pusha           ; Salva EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10    ; Carrega o seletor de dados do kernel
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp        ; Passa o ponteiro para a estrutura de registros
    call isr_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8      ; Remove o número da interrupção e o código de erro
    iret

; ---------- Stub Comum para IRQs ----------
extern irq_handler
irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call irq_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

; ---------- Função para carregar a IDT ----------
global idt_load
extern idt_ptr
idt_load:
    lidt [idt_ptr]
    ret
; Informa ao linker que este objeto não exige pilha executável.
section .note.GNU-stack noalloc noexec nowrite progbits
