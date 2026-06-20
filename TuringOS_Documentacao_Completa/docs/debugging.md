# 🐞 Depuração

## Execução normal

```bash
make run
```

## Execução aguardando GDB

```bash
qemu-system-i386 -kernel build/turingos.bin -s -S
```

## Conexão com GDB

```bash
gdb build/turingos.elf
```

```gdb
target remote localhost:1234
break kernel_main
continue
info registers
disassemble
x/16xw $esp
```

## Análise de binário

```bash
nm build/turingos.elf
readelf -h build/turingos.elf
readelf -S build/turingos.elf
objdump -d build/turingos.elf
```

## Problemas comuns

### Tela preta

Verificar Multiboot, `linker.ld`, chamada para `kernel_main` e escrita VGA.

### Reboot infinito

Pode indicar triple fault, stack inválida ou interrupção sem handler.
