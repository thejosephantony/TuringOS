# TuringOS

> Mini sistema operacional educacional desenvolvido em C freestanding e Assembly x86 para o estudo prático da interface entre hardware e software.

## Visão geral

O **TuringOS** é um kernel educacional inspirado na organização e na interface textual de sistemas Unix.

O projeto demonstra como um sistema de baixo nível é carregado, inicializa seus subsistemas, acessa dispositivos, trata interrupções e disponibiliza uma shell própria.

A implementação utiliza:

- C freestanding;
- Assembly x86;
- GRUB e Multiboot;
- GNU Binutils;
- QEMU;
- GDB;
- Make;
- Git e GitHub.

Todo o processo de compilação, ligação, geração da ISO, execução, depuração e análise do binário é realizado com ferramentas abertas.

---

## Estado do projeto

| Item | Situação |
|---|---|
| Implementação principal do kernel | Concluída — v0.7 |
| Validação e documentação | Concluídas — v0.8 |
| Depuração com QEMU/GDB | Concluída |
| Engenharia reversa do ELF | Concluída |
| Evidências de execução | Registradas |
| Estado geral | **Pronto para entrega acadêmica** |

```text
Versão atual do projeto: v0.8
Versão implementada do kernel: v0.7
Estado: finalizado para entrega
```

O TuringOS possui finalidade educacional e não pretende ser um sistema operacional de propósito geral.

---

## Objetivos

O projeto foi desenvolvido para demonstrar:

- o processo de boot de um kernel;
- a integração entre Assembly x86 e C;
- a compilação em ambiente freestanding;
- a organização de um executável ELF32;
- o uso de um linker script próprio;
- a escrita direta na memória VGA;
- o acesso a dispositivos por portas de entrada e saída;
- a leitura de teclado PS/2;
- as diferenças entre polling e interrupções;
- a configuração da IDT;
- o remapeamento e controle do PIC;
- o funcionamento das IRQ0 e IRQ1;
- a programação do timer PIT;
- a criação de um terminal e de uma shell;
- a depuração remota com QEMU e GDB;
- a análise de um binário sem depender do código-fonte;
- o desenvolvimento incremental com Git, Issues e Pull Requests.

---

## Funcionalidades implementadas

### Boot e núcleo

- cabeçalho Multiboot;
- carregamento pelo GRUB;
- ponto de entrada em Assembly;
- configuração inicial da pilha;
- configuração da GDT;
- transferência de controle para `kernel_main`;
- kernel em C freestanding;
- instruções `cli`, `sti` e `hlt`.

### Vídeo e terminal

- escrita direta na memória VGA `0xB8000`;
- modo texto 80 × 25;
- escrita de caracteres e strings;
- cores de texto e fundo;
- limpeza de tela;
- controle do cursor;
- quebra de linha;
- Backspace;
- rolagem do terminal.

### Teclado e shell

- comunicação com o controlador PS/2;
- acesso às portas `0x60` e `0x64`;
- leitura inicial por polling;
- evolução para leitura orientada a interrupção pela IRQ1;
- conversão de scancodes;
- buffer de entrada;
- prompt interativo `turingos>`;
- interpretação de comandos;
- tratamento de comandos desconhecidos.

### Interrupções

- Interrupt Descriptor Table;
- stubs de interrupção em Assembly;
- handlers em C;
- tratamento inicial de exceções;
- remapeamento do PIC;
- mascaramento e desmascaramento de IRQs;
- envio de EOI;
- callbacks de interrupção;
- contadores de IRQ;
- IRQ0 para o timer;
- IRQ1 para o teclado.

### Timer PIT

- programação do canal 0 do PIT;
- frequência aproximada de 100 Hz;
- contagem de ticks;
- cálculo de tempo de atividade;
- consulta da frequência;
- integração com a shell.

### Diagnóstico interno

- leitura das máscaras do PIC;
- consulta do bit IF do registrador EFLAGS;
- contagem das IRQ0 e IRQ1;
- consulta da frequência do PIT;
- exibição do formato ELF32;
- identificação do modo freestanding;
- comandos `uptime`, `irqinfo` e `debug`.

### Biblioteca interna

O kernel possui uma pequena biblioteca própria, sem dependência da biblioteca padrão do C:

- `kstrlen`;
- `kstrcmp`;
- `kmemset`;
- `kmemcpy`;
- `kutoa`.

O comando `libtest` executa um autoteste dessas rotinas dentro do kernel.

### Organização e hardening do ELF

- linker script próprio;
- organização explícita de `.multiboot`, `.text`, `.rodata`, `.data` e `.bss`;
- segmento executável com permissões `R E`;
- segmento gravável com permissões `RW`;
- ausência de segmento `LOAD` com permissões `RWE`;
- objetos Assembly sem exigência de pilha executável.

---

## Arquitetura

```text
QEMU
  |
  v
GRUB / Multiboot
  |
  v
boot/boot.asm
  |
  +--> GDT
  +--> pilha inicial
  |
  v
kernel_main()
  |
  +--> VGA e terminal
  +--> IDT e ISR
  +--> PIC
  +--> PIT / IRQ0
  +--> teclado PS/2 / IRQ1
  +--> biblioteca interna
  |
  v
shell interativa
```

### Módulos principais

| Módulo | Responsabilidade |
|---|---|
| `boot/boot.asm` | Multiboot, GDT, pilha e entrada inicial |
| `kernel/kernel.c` | Coordenação da inicialização |
| `kernel/vga.c` | Operações de baixo nível no modo texto VGA |
| `kernel/terminal.c` | Terminal, cursor e rolagem |
| `kernel/keyboard.c` | Teclado PS/2 e buffer de entrada |
| `kernel/shell.c` | Interpretação e execução de comandos |
| `kernel/idt.c` | Construção e carregamento da IDT |
| `kernel/interrupt.asm` | Stubs de interrupção em Assembly |
| `kernel/isr.c` | Exceções, IRQs, callbacks e contadores |
| `kernel/pic.c` | Remapeamento, máscaras e EOI do PIC |
| `kernel/timer.c` | Configuração do PIT, ticks e uptime |
| `kernel/klib.c` | Biblioteca interna do kernel |
| `linker.ld` | Layout e permissões do ELF |
| `Makefile` | Build, ISO, execução, depuração e análise |

---

## Estrutura do repositório

```text
TuringOS/
├── boot/
│   └── boot.asm
├── include/
│   ├── idt.h
│   ├── isr.h
│   ├── keyboard.h
│   ├── klib.h
│   ├── pic.h
│   ├── port.h
│   ├── shell.h
│   ├── terminal.h
│   ├── timer.h
│   └── vga.h
├── kernel/
│   ├── idt.c
│   ├── interrupt.asm
│   ├── isr.c
│   ├── kernel.c
│   ├── keyboard.c
│   ├── klib.c
│   ├── pic.c
│   ├── shell.c
│   ├── terminal.c
│   ├── timer.c
│   └── vga.c
├── iso/
│   └── boot/
│       └── grub/
│           └── grub.cfg
├── docs/
│   ├── debugging.md
│   ├── reverse-engineering.md
│   ├── evidencias/
│   │   ├── README.md
│   │   ├── imagens/
│   │   └── logs/
│   └── pdf/
├── .gitattributes
├── .gitignore
├── LICENSE
├── Makefile
├── README.md
└── linker.ld
```

Os artefatos de compilação são gerados no diretório `build/` e não são versionados.

---

## Comandos da shell

| Comando | Função |
|---|---|
| `help` | Lista os comandos disponíveis |
| `clear` | Limpa a tela |
| `about` | Exibe informações sobre o projeto |
| `version` | Exibe a versão do kernel |
| `hardware` | Exibe arquitetura e dispositivos utilizados |
| `uptime` | Exibe tempo de atividade, ticks e frequência do PIT |
| `irqinfo` | Exibe contadores de IRQ e máscaras do PIC |
| `debug` | Exibe informações internas de execução |
| `libtest` | Executa o autoteste da biblioteca interna |
| `halt` | Desabilita interrupções e interrompe a CPU |

---

## Ambiente de desenvolvimento

Ambiente recomendado:

- Linux; ou
- Windows com WSL2 e Ubuntu.

### Dependências

```bash
sudo apt update

sudo apt install -y \
  build-essential \
  gcc-multilib \
  binutils \
  nasm \
  make \
  grub-pc-bin \
  grub-common \
  xorriso \
  mtools \
  qemu-system-x86 \
  gdb \
  git
```

---

## Compilação e execução

Na raiz do repositório:

```bash
make clean
make
make check
make iso
make run
```

O resultado esperado de `make check` é:

```text
Kernel reconhecido como Multiboot.
```

### Alvos do Makefile

| Comando | Finalidade |
|---|---|
| `make` | Compila os fontes e gera `build/turingos.bin` |
| `make clean` | Remove os artefatos gerados |
| `make check` | Verifica se o kernel é Multiboot |
| `make iso` | Gera `build/turingos.iso` |
| `make run` | Executa a ISO no QEMU |
| `make debug` | Executa o QEMU pausado e abre o servidor GDB |
| `make readelf` | Exibe informações do ELF |
| `make disasm` | Desmonta o binário |
| `make hexdump` | Exibe os bytes iniciais do binário |

---

## Depuração com QEMU e GDB

Primeiro terminal:

```bash
make debug
```

Segundo terminal:

```bash
gdb build/turingos.bin
```

Comandos básicos:

```gdb
set architecture i386
target remote localhost:1234
break kernel_main
continue
info registers
x/32hx 0xB8000
```

A documentação completa está em [`docs/debugging.md`](docs/debugging.md).

---

## Engenharia reversa

A análise estática utiliza:

```bash
file build/turingos.bin
readelf -h build/turingos.bin
readelf -SW build/turingos.bin
readelf -lW build/turingos.bin
nm -n build/turingos.bin
objdump -d -M intel build/turingos.bin
strings build/turingos.bin
hexdump -C build/turingos.bin
```

A documentação completa está em [`docs/reverse-engineering.md`](docs/reverse-engineering.md).

---

## Documentação e evidências

| Artefato | Conteúdo |
|---|---|
| [`docs/debugging.md`](docs/debugging.md) | Depuração com QEMU e GDB |
| [`docs/reverse-engineering.md`](docs/reverse-engineering.md) | Análise estática do ELF32 |
| [`docs/evidencias/`](docs/evidencias/) | Capturas e logs de validação |
| [`docs/pdf/`](docs/pdf/) | Documentação acadêmica em PDF |

As evidências registram:

- boot e inicialização;
- funcionamento da shell;
- timer PIT e uptime;
- contadores de IRQ;
- máscaras do PIC;
- diagnóstico interno;
- `libtest` com resultado `PASS`;
- sessão remota do GDB;
- cabeçalho e seções ELF;
- segmentos e permissões;
- símbolos e strings;
- desmontagem do binário;
- ausência de segmento `RWE`.

---

## Histórico de versões

| Versão | Entrega | Situação |
|---|---|---|
| v0.1 | Kernel mínimo, GRUB, Multiboot, C e Assembly | Concluída |
| v0.2 | Driver VGA e terminal | Concluída |
| v0.3 | Shell básica | Concluída |
| v0.4 | Teclado PS/2 por polling | Concluída |
| v0.5 | IDT, ISR, PIC, IRQ0, IRQ1 e PIT | Concluída |
| v0.5.1 | Hardening do ELF e do linker | Concluída |
| v0.6 | Uptime, contadores de IRQ e diagnóstico | Concluída |
| v0.7 | Biblioteca interna e `libtest` | Concluída |
| v0.8 | Depuração, engenharia reversa e evidências | **Concluída** |

---

## Relação com a disciplina

| Tema | Aplicação no TuringOS |
|---|---|
| Interface hardware/software | VGA, PS/2, PIC, PIT e portas de I/O |
| Assembly x86 | Boot, GDT, stubs e interrupções |
| C de baixo nível | Kernel freestanding e drivers |
| Memória mapeada | Buffer VGA em `0xB8000` |
| Interrupções | IDT, ISR, IRQ0, IRQ1 e EOI |
| Temporização | Configuração do PIT |
| Binários | ELF32, linker script e ISO |
| Virtualização | Execução no QEMU |
| Depuração | QEMU e GDB |
| Engenharia reversa | `readelf`, `objdump`, `nm`, `strings` e `hexdump` |
| Gestão do projeto | Git, Issues, branches e Pull Requests |

---

## Limitações

O escopo atual não inclui:

- modo usuário;
- multitarefa preemptiva;
- escalonador de processos;
- paginação e memória virtual;
- chamadas de sistema completas;
- sistema de arquivos;
- driver de disco;
- rede;
- interface gráfica.

Essas limitações são compatíveis com o objetivo de um kernel educacional voltado à interface entre hardware e software.

---

## Autores

- Joseph Antony
- José Arthur

Projeto acadêmico desenvolvido para a disciplina **Interface Hardware/Software**.

---

## Licença

Este projeto é distribuído sob a licença [Apache 2.0](LICENSE).
