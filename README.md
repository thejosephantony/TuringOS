# TuringOS

**TuringOS** é um mini sistema operacional educacional inspirado em Unix, desenvolvido em **C freestanding** e **Assembly x86** para a disciplina de **Interface Hardware/Software**.

O projeto demonstra, de forma incremental, como um kernel é carregado, inicializa seus subsistemas, acessa dispositivos por memória e portas de entrada/saída, trata interrupções de hardware e disponibiliza uma interface textual própria.

---

## Estado atual

```text
Versão atual do projeto: v0.8
Versão implementada do kernel: v0.7
Implementação principal: concluída
Fase atual: documentação, depuração, engenharia reversa e apresentação
```

A implementação atual inclui:

- boot via GRUB e Multiboot;
- entrada inicial em Assembly x86;
- kernel em C freestanding;
- GDT e pilha inicial;
- driver VGA em modo texto;
- terminal com cursor, cores, limpeza e rolagem;
- shell interativo;
- teclado PS/2 orientado a interrupção;
- IDT, ISR, PIC e tratamento de IRQs;
- timer PIT em IRQ0;
- teclado em IRQ1;
- contagem de ticks e tempo de atividade;
- comandos de diagnóstico do kernel;
- biblioteca interna de strings, memória e conversão numérica;
- geração de binário ELF32 e ISO inicializável;
- execução e validação no QEMU;
- suporte à inspeção com GDB, `readelf`, `objdump`, `nm` e `hexdump`.

O TuringOS não representa um sistema operacional de propósito geral. Seu escopo é educacional e está concentrado nos mecanismos essenciais de interface entre hardware e software.

---

## Objetivos

O projeto foi desenvolvido para estudar e demonstrar:

- processo de boot de um kernel;
- integração entre Assembly e C;
- compilação freestanding;
- organização de um binário ELF32;
- uso de linker script próprio;
- acesso direto à memória VGA;
- comunicação com dispositivos por portas de I/O;
- leitura de teclado PS/2;
- polling e interrupções de hardware;
- configuração da IDT;
- remapeamento e controle do PIC;
- funcionamento de IRQ0 e IRQ1;
- programação do PIT;
- depuração com QEMU e GDB;
- análise de binários sem consultar diretamente o código-fonte;
- versionamento e gestão incremental pelo GitHub.

---

## Evolução do projeto

| Versão | Entrega | Situação |
|---|---|---|
| v0.1 | Kernel mínimo, GRUB, Multiboot, Assembly, C e VGA | Concluída |
| v0.2 | Driver VGA e abstração de terminal | Concluída |
| v0.3 | Shell básico e comandos internos | Concluída |
| v0.4 | Teclado PS/2 por polling | Concluída |
| v0.5 | IDT, ISR, PIC, IRQ0, IRQ1 e PIT | Concluída |
| v0.5.1 | Hardening do ELF, linker e pilha não executável | Concluída |
| v0.6 | `uptime`, `irqinfo`, `debug` e contadores de IRQ | Concluída |
| v0.7 | Biblioteca interna do kernel e comando `libtest` | Concluída |
| v0.8 | Documentação, depuração e engenharia reversa | Concluída |
| v1.0 | Consolidação documental, apresentação e entrega | Planejada |

---

## Funcionalidades implementadas

### Boot e inicialização

- cabeçalho Multiboot;
- carregamento pelo GRUB;
- entrada inicial em `boot/boot.asm`;
- configuração da pilha;
- configuração inicial da GDT;
- transferência de controle para `kernel_main`;
- interrupção segura da CPU com `cli` e `hlt`.

### Vídeo e terminal

- escrita direta na memória VGA `0xB8000`;
- modo texto 80 × 25;
- escrita de caracteres e strings;
- cores de primeiro plano e fundo;
- limpeza de tela;
- controle do cursor de hardware;
- quebra de linha;
- Backspace;
- rolagem do terminal.

### Shell

- prompt `turingos>`;
- leitura e interpretação de comandos;
- buffer de entrada;
- tratamento de Enter e Backspace;
- mensagens para comandos desconhecidos;
- comandos internos de informação, diagnóstico e controle.

### Teclado PS/2

- acesso às portas `0x60` e `0x64`;
- leitura e conversão de scancodes;
- implementação inicial por polling;
- evolução para tratamento por IRQ1;
- integração com o buffer consumido pela shell.

### Interrupções

- Interrupt Descriptor Table;
- stubs em Assembly;
- handlers em C;
- tratamento inicial de exceções;
- remapeamento do PIC;
- envio de EOI;
- registro de callbacks de IRQ;
- contadores para as IRQs;
- IRQ0 para o PIT;
- IRQ1 para o teclado.

### Timer PIT

- programação do canal 0 do PIT;
- frequência de aproximadamente 100 Hz;
- contagem de ticks;
- cálculo de tempo de atividade;
- consulta da frequência efetiva;
- exposição das informações pela shell.

### Diagnóstico interno

- leitura das máscaras do PIC;
- contagem de eventos em IRQ0 e IRQ1;
- consulta do bit IF do registrador EFLAGS;
- exibição do formato e modo de compilação do kernel;
- comandos de diagnóstico executados em tempo real.

### Biblioteca interna

A biblioteca interna reduz duplicações e evita dependência da biblioteca padrão do C:

- `kstrlen`;
- `kstrcmp`;
- `kmemset`;
- `kmemcpy`;
- `kutoa`.

O comando `libtest` executa um autoteste dessas rotinas dentro do próprio kernel.

### Hardening do binário

- objetos Assembly marcados sem necessidade de pilha executável;
- separação entre segmentos executáveis e graváveis;
- remoção do segmento ELF com permissões simultâneas de leitura, escrita e execução;
- organização explícita de `.multiboot`, `.text`, `.rodata`, `.data` e `.bss`;
- manutenção do cabeçalho Multiboot no início do binário.

---

## Arquitetura

Fluxo simplificado de inicialização:

```text
QEMU
  |
  v
GRUB / Multiboot
  |
  v
boot/boot.asm
  |
  v
GDT + pilha inicial
  |
  v
kernel_main()
  |
  +--> VGA e terminal
  |
  +--> IDT
  |
  +--> PIC
  |
  +--> PIT / IRQ0
  |
  +--> teclado PS/2 / IRQ1
  |
  v
shell interativo
```

Módulos principais:

| Módulo | Responsabilidade |
|---|---|
| `boot/boot.asm` | Cabeçalho Multiboot, GDT, pilha e entrada inicial |
| `kernel/kernel.c` | Coordenação da inicialização do sistema |
| `kernel/vga.c` | Operações de baixo nível no modo texto VGA |
| `kernel/terminal.c` | Abstração textual, cursor e rolagem |
| `kernel/keyboard.c` | Teclado PS/2 e buffer de entrada |
| `kernel/shell.c` | Interpretação e execução de comandos |
| `kernel/idt.c` | Construção e carregamento da IDT |
| `kernel/interrupt.asm` | Stubs de interrupção em Assembly |
| `kernel/isr.c` | Exceções, IRQs, callbacks e contadores |
| `kernel/pic.c` | Remapeamento, máscaras e EOI do PIC |
| `kernel/timer.c` | Configuração do PIT, ticks e uptime |
| `kernel/klib.c` | Biblioteca interna do kernel |
| `linker.ld` | Layout do ELF e permissões dos segmentos |
| `Makefile` | Build, ISO, execução e análise |

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
│   └── pdf/
├── .gitattributes
├── .gitignore
├── LICENSE
├── Makefile
├── README.md
└── linker.ld
```

Os diretórios de build e os artefatos gerados durante a compilação não são versionados.

---

## Comandos da shell

| Comando | Função |
|---|---|
| `help` | Lista os comandos disponíveis |
| `clear` | Limpa a tela |
| `about` | Exibe uma descrição do projeto |
| `version` | Exibe a versão atual do kernel |
| `hardware` | Exibe informações da arquitetura e dos dispositivos |
| `uptime` | Exibe tempo de atividade, ticks e frequência do PIT |
| `irqinfo` | Exibe contadores de IRQ e máscaras do PIC |
| `debug` | Exibe informações internas de execução do kernel |
| `libtest` | Executa o autoteste da biblioteca interna |
| `halt` | Desabilita interrupções e interrompe a CPU |

Exemplo:

```text
turingos> uptime
Uptime: 12 seconds
PIT ticks: 1204
PIT frequency: 100 Hz
```

---

## Pré-requisitos

Ambiente recomendado:

- Linux nativo; ou
- Windows com WSL2 e uma distribuição Ubuntu.

Instalação das dependências no Ubuntu/WSL:

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

Na raiz do projeto:

```bash
make clean
make
make check
make iso
make run
```

| Comando | Finalidade |
|---|---|
| `make` | Compila os fontes e gera `build/turingos.bin` |
| `make clean` | Remove artefatos de compilação |
| `make check` | Verifica se o kernel é reconhecido como Multiboot |
| `make iso` | Gera `build/turingos.iso` |
| `make run` | Inicializa a ISO no QEMU |
| `make debug` | Inicia o QEMU para conexão do GDB |
| `make readelf` | Exibe informações do ELF |
| `make disasm` | Desmonta o binário do kernel |
| `make hexdump` | Exibe bytes iniciais do binário |

Resultado esperado:

```text
Kernel reconhecido como Multiboot.
```

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

Comandos iniciais no GDB:

```gdb
target remote localhost:1234
break kernel_main
continue
info registers
x/16xw 0xB8000
```

A etapa documental de depuração deve registrar:

- conexão remota;
- breakpoint em `kernel_main`;
- inspeção dos registradores;
- execução passo a passo;
- inspeção da memória VGA;
- análise do fluxo entre Assembly e C.

---

## Análise do binário

O kernel pode ser analisado sem consultar diretamente os fontes:

```bash
file build/turingos.bin
readelf -h build/turingos.bin
readelf -S build/turingos.bin
readelf -l build/turingos.bin
nm build/turingos.bin
objdump -D -M intel build/turingos.bin
hexdump -C build/turingos.bin | head
strings build/turingos.bin
```

Essas ferramentas permitem identificar:

- formato ELF32;
- arquitetura Intel 80386;
- endereço de entrada;
- seções e segmentos;
- permissões de memória;
- símbolos do kernel;
- strings embutidas;
- instruções de máquina.

---

## Relação com a disciplina

| Tema | Aplicação no TuringOS |
|---|---|
| Interface hardware/software | VGA, PS/2, PIC, PIT e portas de I/O |
| Assembly x86 | Boot, GDT, stubs e retorno de interrupções |
| C de baixo nível | Kernel freestanding e drivers |
| Memória mapeada | Buffer VGA em `0xB8000` |
| Interrupções | IDT, ISR, IRQ0, IRQ1 e EOI |
| Temporização | Programação e leitura do PIT |
| Binários | ELF32, linker script e ISO |
| Virtualização | Execução no QEMU |
| Depuração | QEMU e GDB |
| Engenharia reversa | `readelf`, `objdump`, `nm`, `strings` e `hexdump` |
| Gestão do projeto | Git, Issues, Pull Requests e GitHub Project |

---

## Cronograma consolidado

| Etapa | Conteúdo | Situação |
|---|---|---|
| Semana 1 | Ambiente, estrutura, boot e kernel mínimo | Concluída |
| Semana 2 | VGA e terminal | Concluída |
| Semana 3 | Shell e teclado PS/2 | Concluída |
| Semana 4 | Interrupções, PIC, IRQs e PIT | Concluída |
| Semana 5 | Hardening, diagnósticos e biblioteca interna | Concluída |
| Semana 6 | Organização do repositório e atualização do plano | Em andamento |
| Semana 7 | Depuração, engenharia reversa e evidências | Planejada |
| Semana 8 | Slides, apresentação e consolidação final | Planejada |

---

## Gestão do projeto

O desenvolvimento utiliza:

- issues para representar atividades;
- branches por funcionalidade ou correção;
- commits incrementais;
- Pull Requests para integração;
- GitHub Project com os estados `Todo`, `In Progress` e `Done`;
- rastreabilidade entre planejamento, implementação e validação.

A implementação principal está concluída até a v0.7. As atividades abertas estão concentradas na documentação e na apresentação.

---

## Limitações

O escopo atual não inclui:

- modo usuário;
- multitarefa preemptiva;
- escalonador de processos;
- paginação e memória virtual;
- alocador dinâmico completo;
- chamadas de sistema;
- sistema de arquivos;
- driver de disco;
- rede;
- interface gráfica.

Esses itens não fazem parte do escopo principal desta versão educacional.

---

## Próximas atividades

- atualizar o plano de desenvolvimento;
- consolidar o cronograma;
- documentar a depuração com QEMU/GDB;
- documentar a engenharia reversa;
- registrar evidências de build e execução;
- revisar o GitHub Project;
- preparar os slides;
- ensaiar a demonstração no QEMU.

---

## Autores

- Joseph Antony
- José Arthur

Projeto acadêmico da disciplina **Interface Hardware/Software**.

---

## Licença

Distribuído sob a licença Apache 2.0. Consulte o arquivo [`LICENSE`](LICENSE).
