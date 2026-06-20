# 🎤 Roteiro de apresentação

## Abertura

O TuringOS é um mini sistema operacional educacional inspirado em Unix, desenvolvido em C e Assembly para estudar a interface entre hardware e software.

## Motivação

A proposta é mostrar na prática como um computador passa do boot para a execução de um kernel simples.

## Tecnologias

C, Assembly x86, NASM, GCC, LD, GRUB, QEMU, GDB, Makefile, Git e GitHub Projects.

## Arquitetura

```text
Shell → Chamadas internas → Kernel → Drivers → Hardware/QEMU
```

## Fluxo de boot

```text
QEMU → GRUB → boot.asm → kernel_main()
```

## Requisitos atendidos

Interface direta com hardware, Assembly, geração de binário, gerenciamento de dispositivo, engenharia reversa sem código-fonte, depuração, Kanban e Git.

## Demonstração

```bash
make clean
make
make run
```

## Encerramento

O TuringOS demonstra o caminho entre hardware virtualizado, boot, Assembly, kernel em C, drivers básicos, terminal e documentação técnica.
