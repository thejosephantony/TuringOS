# ⚠️ Riscos e contingência

## Boot não funcionar

Mitigação: usar GRUB, validar Multiboot com `grub-file` e testar incrementalmente.

## Ambiente WSL/QEMU dar erro

Mitigação: documentar instalação e testar versões das ferramentas.

## Teclado atrasar

Mitigação: tratar teclado como versão recomendada e começar por polling.

## Interrupções complexas

Mitigação: deixar IDT/IRQ/PIC como fase avançada.

## Escopo crescer demais

Mitigação: separar mínimo, recomendado e avançado.

## Engenharia reversa superficial

Mitigação: incluir comandos, saídas, análise e conclusão.
