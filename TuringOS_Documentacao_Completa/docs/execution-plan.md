# 🗓️ Plano de execução

## Estratégia

```text
Versão mínima: boot + kernel + VGA + terminal + QEMU + documentação
Versão recomendada: teclado + shell + comandos
Versão avançada: interrupções + timer + memória + RAMFS
```

## Semana 1 — Boot e kernel mínimo

Issues: `#2, #4, #5, #7, #10, #11, #12, #13`.

Meta: `GRUB → boot.asm → kernel_main()`.

## Semana 2 — VGA e terminal

Issues: `#14, #15`.

Meta: texto na tela via VGA e terminal básico.

## Semana 3 — Documentação e apresentação

Issues: `#16, #17, #18`.

Meta: depuração, engenharia reversa, slides e apresentação.

## Extensão

1. Teclado por polling
2. Shell com comandos
3. Porta serial
4. IDT e interrupções
5. Timer/PIT
6. `kmalloc`
7. RAMFS
8. Syscalls conceituais
