# TuringOS

**TuringOS** e um mini sistema operacional educacional inspirado em Unix, desenvolvido em **C freestanding** e **Assembly x86**, com foco na disciplina de **Interface Hardware/Software**.

O projeto demonstra, na pratica, conceitos fundamentais de baixo nivel: boot, GRUB/Multiboot, entrada em Assembly, kernel em C, linker script, acesso direto a memoria VGA, terminal, shell, leitura de teclado PS/2, automacao com Makefile, QEMU, GDB, Git/GitHub e engenharia reversa de binarios.

---

## Status atual

Versao atual do projeto:

```text
v0.4 - Shell interativo com teclado PS/2 por polling
```

Versoes concluidas:

| Versao | Nome | Status | Resumo |
|---|---|---|---|
| v0.1 | Kernel minimo | Concluido | Boot via GRUB, entrada em Assembly, kernel em C e escrita na VGA. |
| v0.2 | Driver VGA e terminal | Concluido | Separacao entre driver VGA, terminal e kernel. |
| v0.3 | Shell basico | Concluido | Prompt `turingos>` e comandos internos. |
| v0.4 | Teclado PS/2 por polling | Concluido | Comandos digitados no QEMU com Enter e Backspace. |
| v0.5 | Interrupcoes | Proximo | IDT, ISR, IRQ, PIC, IRQ0 e IRQ1. |

> Observacao: o teclado atual funciona por **polling**. A proxima etapa e implementar interrupcoes reais usando IDT, IRQ e PIC.

---

## Funcionalidades atuais

O TuringOS ja possui:

- Boot via GRUB/Multiboot;
- Entrada inicial em Assembly x86;
- Kernel em C freestanding;
- Linker script proprio;
- Escrita direta na memoria VGA `0xB8000`;
- Driver VGA modular;
- Terminal basico;
- Controle de linhas, cores e limpeza de tela;
- Shell interativo;
- Comandos internos;
- Teclado PS/2 por polling;
- Build automatizado com Makefile;
- Execucao no QEMU;
- Organizacao por issues, branches e Kanban.

---

## Comandos da shell

Ao executar o sistema no QEMU, o prompt principal e:

```text
turingos>
```

Comandos disponiveis:

| Comando | Funcao |
|---|---|
| `help` | Lista os comandos disponiveis. |
| `clear` | Limpa a tela. |
| `about` | Mostra informacoes sobre o projeto. |
| `version` | Mostra a versao atual do TuringOS. |
| `hardware` | Mostra informacoes basicas de hardware/ambiente. |
| `halt` | Para a execucao do kernel. |

---

## Arquitetura atual

Fluxo de inicializacao:

```text
QEMU
  ↓
GRUB
  ↓
boot/boot.asm
  ↓
kernel_main()
  ↓
VGA text mode + terminal
  ↓
keyboard PS/2 polling
  ↓
shell interativo
```

Camadas principais:

| Camada | Responsabilidade | Arquivos |
|---|---|---|
| Boot | Cabecalho Multiboot, pilha e entrada do kernel | `boot/boot.asm` |
| Kernel | Inicializacao geral | `kernel/kernel.c` |
| VGA | Escrita direta em video | `include/vga.h`, `kernel/vga.c` |
| Terminal | Abstracao de saida textual | `include/terminal.h`, `kernel/terminal.c` |
| Teclado | Leitura PS/2 por polling | `include/keyboard.h`, `kernel/keyboard.c` |
| Shell | Prompt e comandos internos | `include/shell.h`, `kernel/shell.c` |

---

## Estrutura do projeto

```text
TuringOS/
├── boot/
│   └── boot.asm
├── include/
│   ├── keyboard.h
│   ├── shell.h
│   ├── terminal.h
│   └── vga.h
├── kernel/
│   ├── kernel.c
│   ├── keyboard.c
│   ├── shell.c
│   ├── terminal.c
│   └── vga.c
├── iso/
│   └── boot/
│       └── grub/
│           └── grub.cfg
├── docs/
│   └── pdf/
├── scripts/
├── Makefile
├── linker.ld
└── README.md
```

---

## Dependencias

Ambiente recomendado: **WSL2 Ubuntu** ou Linux nativo.

Instalacao das ferramentas:

```bash
sudo apt update
sudo apt install -y build-essential nasm make gcc-multilib binutils \
  qemu-system-x86 qemu-system-gui qemu-utils grub-pc-bin grub-common \
  xorriso mtools gdb git gh
```

Verificacao:

```bash
gcc --version
nasm -v
make --version
qemu-system-i386 --version
grub-mkrescue --version
gdb --version
git --version
```

---

## Como compilar e executar

Na raiz do projeto:

```bash
make clean
make
make check
make iso
make run
```

Significado dos comandos:

| Comando | Funcao |
|---|---|
| `make` | Compila Assembly e C, gerando o binario do kernel. |
| `make check` | Verifica compatibilidade Multiboot. |
| `make iso` | Gera a ISO bootavel. |
| `make run` | Executa o TuringOS no QEMU. |
| `make clean` | Remove arquivos gerados. |

---

## Depuracao com QEMU/GDB

Fluxo recomendado:

```bash
make debug
```

Em outro terminal:

```bash
gdb build/turingos.bin
(gdb) target remote localhost:1234
(gdb) break kernel_main
(gdb) continue
(gdb) info registers
(gdb) x/16xw 0xB8000
```

---

## Engenharia reversa sem codigo-fonte

Comandos recomendados para analisar o binario:

```bash
make clean
make
file build/turingos.bin
readelf -h build/turingos.bin
readelf -S build/turingos.bin
objdump -d build/turingos.bin | less
hexdump -C build/turingos.bin | head
strings build/turingos.bin
ndisasm -b 32 build/turingos.bin | head
```

Esses comandos permitem identificar formato do binario, secoes, simbolos, strings e trechos em Assembly sem consultar diretamente o codigo-fonte.

---

## Roadmap

| Versao | Objetivo | Status |
|---|---|---|
| v0.1 | Kernel minimo inicializavel | Concluido |
| v0.2 | Driver VGA e terminal | Concluido |
| v0.3 | Shell basico | Concluido |
| v0.4 | Teclado PS/2 por polling | Concluido |
| v0.5 | Interrupcoes, IDT, ISR, IRQ e PIC | Proximo |
| v0.6 | Timer PIT | Planejado |
| v0.7 | Biblioteca interna do kernel | Planejado |
| v0.8 | Depuracao e engenharia reversa | Planejado |
| v0.9 | Consolidacao tecnica | Planejado |
| v1.0 | Entrega final | Planejado |

---

## Proxima etapa: v0.5 - Interrupcoes

A proxima branch recomendada:

```bash
git switch main
git pull origin main
git switch -c feature/interrupts
```

Objetivos da v0.5:

- Criar IDT;
- Criar stubs Assembly;
- Criar handlers em C;
- Remapear PIC;
- Enviar EOI ao PIC;
- Preparar IRQ0 para timer;
- Preparar IRQ1 para teclado;
- Usar `iret`/`iretd` para retorno correto das interrupcoes.

---

## Relacao com a disciplina

| Requisito | Atendimento no TuringOS |
|---|---|
| Interface direta com hardware | VGA `0xB8000` e portas PS/2 `0x64`/`0x60`. |
| Codigo Assembly | `boot/boot.asm`. |
| Geracao de binario | `turingos.bin` e `turingos.iso`. |
| Dispositivo/driver | Driver VGA e teclado PS/2 inicial. |
| Prototipacao virtual | QEMU. |
| Depuracao | QEMU + GDB. |
| Engenharia reversa | `objdump`, `readelf`, `hexdump`, `strings`, `ndisasm`. |
| Kanban | GitHub Project com issues por etapa. |
| Versionamento | Git, branches, commits, PRs e tags. |

---

## Observacoes tecnicas

- O TuringOS ainda nao possui modo usuario;
- Ainda nao possui sistema de arquivos;
- Ainda nao possui gerenciamento de memoria avancado;
- Ainda nao usa interrupcoes reais para teclado;
- Ainda nao possui timer PIT;
- Essas limitacoes sao esperadas na v0.4 e fazem parte do roadmap.

---

## Autor

Joseph Antony

Projeto academico de Interface Hardware/Software.
