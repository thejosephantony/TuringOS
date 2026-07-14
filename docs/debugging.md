# Depuração do TuringOS com QEMU e GDB

## Objetivo

Registrar a depuração remota do TuringOS utilizando o servidor GDB incorporado ao QEMU.

## Ambiente

A atividade foi realizada no WSL2 com Ubuntu, QEMU, GDB configurado para i386 e o kernel ELF32 freestanding do TuringOS.

## Inicialização do QEMU

O QEMU foi iniciado pelo comando `make debug`.

O alvo executa `qemu-system-i386 -kernel build/turingos.bin -s -S`.

A opção `-s` abre o servidor GDB na porta 1234. A opção `-S` mantém a CPU pausada até o comando `continue`.

## Conexão

Em outro terminal, o GDB foi iniciado com `gdb build/turingos.bin`.

Foram utilizados os comandos:

- `set architecture i386`;
- `target remote localhost:1234`;
- `break kernel_main`;
- `continue`.

O breakpoint foi atingido em `kernel_main`.

## Inspeção

A CPU foi examinada com:

- `info registers`;
- `x/10i $eip`;
- `disassemble kernel_main`;
- `x/16wx $esp`;
- `si`.

Esses comandos permitiram observar registradores, instruções, pilha e execução passo a passo.

## Memória VGA

Após o boot, a execução foi interrompida pelo GDB.

A memória VGA foi examinada no endereço `0xB8000` com:

- `x/32hx 0xB8000`;
- `x/64cb 0xB8000`.

Cada célula do modo texto VGA contém um byte para o caractere e outro para o atributo de cor.

## Resultado

A atividade confirmou:

- conexão remota entre QEMU e GDB;
- arquitetura i386;
- breakpoint em `kernel_main`;
- inspeção dos registradores;
- desmontagem de instruções;
- inspeção da pilha;
- execução passo a passo;
- acesso direto à memória VGA;
- interrupção e retomada do kernel.
