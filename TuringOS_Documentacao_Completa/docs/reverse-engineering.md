# 🔍 Engenharia reversa sem código-fonte

## Objetivo

Analisar um binário relacionado ao TuringOS sem consultar o código-fonte.

## Ferramentas

```bash
hexdump
objdump
ndisasm
readelf
gdb
qemu-system-i386
```

## Etapa 1 — Inspeção hexadecimal

```bash
hexdump -C build/turingos.bin | head -n 40
```

## Etapa 2 — Cabeçalho ELF

```bash
readelf -h build/turingos.elf
```

## Etapa 3 — Seções

```bash
readelf -S build/turingos.elf
```

## Etapa 4 — Disassembly

```bash
objdump -d build/turingos.elf
ndisasm -b 32 build/turingos.bin | less
```

## Etapa 5 — Execução com GDB

```bash
qemu-system-i386 -kernel build/turingos.bin -s -S
gdb build/turingos.elf
```

```gdb
target remote localhost:1234
break kernel_main
continue
info registers
x/20i $eip
```

## Perguntas

1. Qual é o ponto de entrada?
2. Quais instruções aparecem no início?
3. Existe chamada para `kernel_main`?
4. O binário acessa endereços de hardware?
5. O comportamento no QEMU bate com a análise estática?

## Modelo de relatório

```text
Arquivo analisado:
Ferramentas usadas:
Ponto de entrada:
Seções identificadas:
Instruções principais:
Comportamento observado:
Conclusão:
```
