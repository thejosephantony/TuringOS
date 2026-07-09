# TuringOS

**TuringOS** é um mini sistema operacional educacional inspirado em Unix, desenvolvido em **C freestanding** e **Assembly x86**, com foco na disciplina de **Interface Hardware/Software**.

O projeto tem finalidade didática: demonstrar, passo a passo, como um kernel inicializa, interage com hardware virtualizado, escreve diretamente na memória de vídeo, lê teclado, organiza drivers, trata interrupções e gera binários executáveis em ambiente de baixo nível.

---

## Status atual

```text
Versão atual: v0.5-dev
Estado: em consolidação didática
```

O TuringOS já possui:

- boot via GRUB/Multiboot;
- entrada inicial em Assembly x86;
- kernel em C freestanding;
- driver VGA em modo texto;
- terminal próprio;
- shell interativo;
- leitura de teclado PS/2;
- base de interrupções;
- IDT;
- PIC;
- IRQ0;
- IRQ1;
- timer PIT inicializado;
- build automatizado com Makefile;
- execução no QEMU.

A versão atual **não representa a entrega final**. Ela representa uma fase de organização, consolidação e documentação para acompanhamento do professor.

---

## Roadmap

| Versão | Tema | Status |
|---|---|---|
| v0.1 | Kernel mínimo inicializável | Concluído |
| v0.2 | Driver VGA e terminal | Concluído |
| v0.3 | Shell básico | Concluído |
| v0.4 | Teclado PS/2 por polling | Concluído |
| v0.5 | Interrupções, IDT, PIC, IRQ0, IRQ1 e PIT | Em consolidação |
| v0.5.1 | Hardening técnico e ajustes internos | Próximo |
| v0.6 | Uptime, debug e comandos internos | Planejado |
| v0.7 | Biblioteca interna do kernel | Planejado |
| v0.8 | Depuração e engenharia reversa | Planejado |
| v1.0 | Entrega final e apresentação | Futuro |

---

## Objetivo do projeto

O objetivo do TuringOS é construir um pequeno sistema operacional educacional para estudar conceitos de interface entre hardware e software.

O projeto busca demonstrar:

- como um kernel é carregado;
- como Assembly e C interagem em baixo nível;
- como um binário de kernel é gerado;
- como o kernel acessa memória de vídeo;
- como um terminal textual pode ser implementado;
- como um shell simples pode ser criado;
- como o teclado PS/2 pode ser lido;
- como interrupções são configuradas;
- como IDT, PIC, IRQ e PIT se conectam;
- como depurar e analisar binários sem depender do código-fonte.

---

## Funcionalidades implementadas

### v0.1 - Kernel mínimo

- Estrutura inicial do projeto;
- boot via GRUB/Multiboot;
- arquivo `boot/boot.asm`;
- chamada para `kernel_main`;
- kernel em C freestanding;
- escrita inicial em VGA;
- `linker.ld`;
- Makefile;
- geração de `turingos.bin`;
- geração de ISO;
- execução no QEMU.

### v0.2 - VGA e terminal

- Driver VGA modular;
- terminal próprio;
- limpeza de tela;
- escrita de caracteres;
- escrita de strings;
- controle de linha e coluna;
- mensagens de inicialização;
- separação entre kernel, VGA e terminal.

### v0.3 - Shell básico

- prompt `turingos>`;
- estrutura `shell.c` e `shell.h`;
- comandos internos;
- comando `help`;
- comando `clear`;
- comando `about`;
- comando `version`;
- comando `hardware`;
- comando `halt`.

### v0.4 - Teclado PS/2 por polling

- leitura inicial de teclado PS/2;
- acesso às portas `0x60` e `0x64`;
- conversão básica de scancodes;
- tratamento de Enter;
- tratamento de Backspace;
- integração teclado + shell.

### v0.5-dev - Interrupções

- IDT;
- stubs de interrupção em Assembly;
- handlers em C;
- PIC;
- remapeamento do PIC;
- IRQ0;
- IRQ1;
- timer PIT;
- inicialização de timer antes de habilitar interrupções;
- base para teclado por interrupção;
- execução validada no QEMU.

---

## Arquitetura atual

Fluxo simplificado:

```text
QEMU
  ↓
GRUB / Multiboot
  ↓
boot/boot.asm
  ↓
kernel_main()
  ↓
VGA text mode
  ↓
terminal
  ↓
IDT + PIC
  ↓
IRQ0 / PIT timer
  ↓
IRQ1 / teclado
  ↓
shell interativo
```

Camadas principais:

| Camada | Responsabilidade | Arquivos |
|---|---|---|
| Boot | Entrada inicial, Multiboot e pilha | `boot/boot.asm` |
| Kernel | Inicialização geral do sistema | `kernel/kernel.c` |
| VGA | Escrita direta em vídeo | `include/vga.h`, `kernel/vga.c` |
| Terminal | Abstração textual | `include/terminal.h`, `kernel/terminal.c` |
| Shell | Interface de comandos | `include/shell.h`, `kernel/shell.c` |
| Teclado | Entrada PS/2 | `include/keyboard.h`, `kernel/keyboard.c` |
| IDT/ISR | Base de interrupções | `include/idt.h`, `include/isr.h`, `kernel/idt.c`, `kernel/isr.c` |
| PIC | Controlador de interrupções | `include/pic.h`, `kernel/pic.c` |
| Timer | PIT/IRQ0 | `include/timer.h`, `kernel/timer.c` |
| Port I/O | Entrada e saída por portas | `include/port.h` |

---

## Estrutura do projeto

```text
TuringOS/
├── boot/
│   └── boot.asm
├── include/
│   ├── idt.h
│   ├── isr.h
│   ├── keyboard.h
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
│   ├── keyboard.c
│   ├── kernel.c
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
│   ├── pdf/
│   ├── images/
│   └── logs/
├── Makefile
├── linker.ld
├── README.md
├── LICENSE
└── .gitignore
```

---

## Comandos da shell

Ao executar o TuringOS no QEMU, o prompt principal é:

```text
turingos>
```

Comandos disponíveis:

| Comando | Função |
|---|---|
| `help` | Lista os comandos disponíveis |
| `clear` | Limpa a tela |
| `about` | Mostra informações sobre o projeto |
| `version` | Mostra a versão atual |
| `hardware` | Mostra informações básicas de hardware/ambiente |
| `halt` | Para a execução do kernel |

---

## Ambiente de desenvolvimento

Ambiente recomendado:

```text
Windows + WSL2 Ubuntu
ou
Linux nativo
```

Dependências principais:

```bash
sudo apt update
sudo apt install -y build-essential nasm make gcc-multilib binutils \
  qemu-system-x86 qemu-system-gui qemu-utils \
  grub-pc-bin grub-common xorriso mtools gdb git gh
```

Verificação:

```bash
gcc --version
nasm -v
make --version
ld --version
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

| Comando | Função |
|---|---|
| `make clean` | Remove arquivos gerados |
| `make` | Compila Assembly e C e gera o binário do kernel |
| `make check` | Verifica se o binário é Multiboot |
| `make iso` | Gera a ISO bootável |
| `make run` | Executa o TuringOS no QEMU |
| `make debug` | Executa o QEMU preparado para GDB |
| `make disasm` | Gera desmontagem do binário |
| `make readelf` | Exibe informações ELF |
| `make hexdump` | Exibe bytes do binário |

---

## Depuração com QEMU/GDB

Fluxo planejado para depuração:

```bash
make debug
```

Em outro terminal:

```bash
gdb build/turingos.bin
```

Dentro do GDB:

```gdb
target remote localhost:1234
break kernel_main
continue
info registers
x/16xw 0xB8000
```

Essa etapa será documentada com mais detalhes em:

```text
docs/debugging.md
```

---

## Engenharia reversa sem código-fonte

Ferramentas previstas para análise do binário:

```bash
file build/turingos.bin
readelf -h build/turingos.bin
readelf -S build/turingos.bin
objdump -d build/turingos.bin
hexdump -C build/turingos.bin | head
strings build/turingos.bin
```

Objetivo didático:

```text
Mostrar que é possível analisar características do kernel gerado
sem consultar diretamente o código-fonte.
```

Essa etapa será documentada em:

```text
docs/reverse-engineering.md
```

---

## Cronograma semanal

| Semana | Tema | Status |
|---|---|---|
| Semana 1 | Estrutura inicial, ambiente, boot, kernel mínimo | Concluído |
| Semana 2 | VGA, terminal e organização modular | Concluído |
| Semana 3 | Shell básico e teclado PS/2 por polling | Concluído |
| Semana 4 | Interrupções, IDT, PIC, IRQ0, IRQ1 e PIT | Em consolidação |
| Semana 5 | Organização didática, documentação e evidências | Em andamento |

---

## Organização no GitHub

O projeto utiliza:

- Git;
- GitHub;
- branches por funcionalidade;
- commits incrementais;
- issues por etapa;
- GitHub Project/Kanban;
- Pull Requests;
- documentação em Markdown e PDF.

Organização sugerida do Project:

```text
Done:
  - Kernel mínimo
  - VGA
  - Terminal
  - Shell
  - Teclado PS/2
  - Base de interrupções

In Progress:
  - Consolidação da v0.5
  - README didático
  - Cronograma semanal
  - Plano completo
  - Evidências de execução

Todo:
  - Debug com QEMU/GDB
  - Engenharia reversa sem código-fonte
  - Slides
  - Hardening técnico
  - Comandos uptime/debug
```

---

## Relação com a disciplina

| Requisito | Como o TuringOS atende |
|---|---|
| Interface direta com hardware | VGA `0xB8000`, portas PS/2 e PIC |
| Código Assembly | `boot/boot.asm` e `kernel/interrupt.asm` |
| Geração de binário | `turingos.bin` e `turingos.iso` |
| Dispositivos | VGA, teclado PS/2 e PIT |
| Interrupções | IDT, ISR, PIC, IRQ0 e IRQ1 |
| Prototipação virtual | QEMU |
| Depuração | QEMU/GDB |
| Engenharia reversa | `readelf`, `objdump`, `hexdump`, `strings` |
| Gestão do projeto | GitHub Issues e GitHub Project |
| Versionamento | Git, branches, commits e Pull Requests |

---

## Limitações atuais

O TuringOS ainda é um kernel educacional em desenvolvimento. Atualmente, ele ainda não possui:

- modo usuário;
- sistema de arquivos real;
- alocador dinâmico de memória;
- paginação;
- multitarefa;
- syscalls completas;
- driver de disco;
- interface gráfica.

Essas limitações são esperadas nesta fase. O objetivo atual é consolidar a base de kernel, interrupções, documentação e evidências.

---

## Próximos passos

Próximas melhorias planejadas:

- organizar documentação em `docs/`;
- criar cronograma semanal detalhado;
- documentar GitHub Project;
- documentar depuração com QEMU/GDB;
- documentar engenharia reversa sem código-fonte;
- adicionar evidências de execução;
- corrigir warnings de linker;
- melhorar `linker.ld`;
- adicionar comandos `uptime`, `debug` e `irqinfo`;
- criar biblioteca interna do kernel;
- preparar roteiro de apresentação.

---

## Autor

Joseph Antony e José Arthur

Projeto acadêmico da disciplina **Interface Hardware/Software**.

---

## Licença

Este projeto possui finalidade educacional.
