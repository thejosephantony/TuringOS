# 🧠 TuringOS

<<<<<<< HEAD
> Um mini sistema operacional educacional inspirado em Unix, desenvolvido em C e Assembly para estudar, na prática, a interface entre hardware e software.

## 📌 Visão geral

**TuringOS** é um projeto acadêmico de um mini sistema operacional educacional. O objetivo não é competir com Linux, BSD, Minix ou xv6, mas construir um **kernel didático**, pequeno e progressivo, capaz de inicializar em uma máquina virtual, escrever diretamente na tela, interagir com dispositivos básicos e executar comandos simples.

O projeto foi pensado para a disciplina **Interface Hardware/Software**, com foco em boot, Assembly, kernel em C, geração de binário, linkedição com script próprio, execução em QEMU, escrita direta na memória VGA, drivers básicos, depuração com QEMU/GDB, engenharia reversa de binário sem código-fonte, planejamento com Kanban e versionamento com Git/GitHub.

---

## 🎯 Objetivo

Compreender como um sistema operacional funciona internamente, desde o momento em que a máquina virtual inicia até a execução de uma interface textual básica.

```text
QEMU/Hardware virtualizado
        ↓
GRUB
        ↓
Código Assembly inicial
        ↓
Kernel em C
        ↓
Drivers básicos
        ↓
Terminal
        ↓
Shell
        ↓
Comandos internos
=======
> Um mini sistema operacional educacional inspirado em Unix, criado para estudar a interface entre hardware e software, boot, kernel, C, Assembly, drivers básicos, depuração e organização de projeto.

## 📌 Visão geral

**TuringOS** é um sistema operacional educacional inspirado em Unix. O objetivo do projeto não é criar um sistema operacional completo como Linux, BSD, Minix ou xv6, mas construir um **mini kernel didático**, capaz de inicializar em uma máquina virtual, escrever diretamente na tela, interagir com dispositivos básicos e executar comandos simples em uma interface textual.

O projeto é voltado ao estudo prático de conceitos de:

- Sistemas Operacionais;
- Arquitetura de Computadores;
- Interface Hardware/Software;
- Programação em C;
- Assembly x86;
- geração de código de máquina e binários;
- drivers básicos;
- depuração com QEMU/GDB;
- engenharia reversa de binários;
- organização de desenvolvimento com Git e Kanban.

---

## 🎯 Objetivo do projeto

O objetivo principal do TuringOS é compreender como um sistema operacional funciona internamente, desde o processo de boot até a construção de uma interface textual simples.

Durante o desenvolvimento, serão estudados e implementados conceitos como:

- boot do sistema;
- carregamento do kernel pelo GRUB;
- código de entrada em Assembly;
- kernel em C;
- linkedição com linker script próprio;
- geração de binário executável;
- geração de imagem ISO inicializável;
- escrita direta na memória de vídeo VGA;
- comunicação com hardware virtualizado;
- portas de entrada e saída;
- teclado PS/2;
- timer/PIT;
- interrupções;
- terminal textual;
- shell simples;
- comandos internos;
- gerenciamento básico de memória;
- sistema de arquivos em memória;
- chamadas internas conceituais;
- depuração com QEMU, GDB, serial e `objdump`;
- engenharia reversa de binários sem acesso ao código-fonte;
- versionamento com Git;
- planejamento semanal com Kanban.

---

## 🧩 Ideia geral da arquitetura

A arquitetura inicial do TuringOS será baseada em um kernel simples, carregado pelo GRUB e executado no QEMU.

```text
+-----------------------------+
|            Shell            |
| help, clear, echo, about    |
+-----------------------------+
|   Chamadas internas          |
| print, read, clear, ticks   |
+-----------------------------+
|            Kernel           |
| terminal, memória, drivers  |
+-----------------------------+
|       Drivers básicos       |
| VGA, teclado, timer, serial |
+-----------------------------+
|         Hardware/QEMU       |
+-----------------------------+
```

O sistema será executado em uma plataforma virtualizada, permitindo testar o kernel sem instalar nada diretamente no computador físico.

Fluxo inicial esperado:

```text
BIOS/QEMU
   ↓
GRUB
   ↓
boot/boot.asm
   ↓
kernel_main()
   ↓
Terminal/Shell
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
```

---

<<<<<<< HEAD
## ✅ Requisitos atendidos

| Requisito obrigatório | Atendimento no TuringOS |
|---|---|
| Interface direta com hardware | Escrita VGA em `0xB8000`, portas de I/O, teclado PS/2, timer/PIT e serial |
| Código Assembly | Entrada inicial em `boot/boot.asm`, cabeçalho Multiboot, configuração de pilha e chamada ao kernel |
| Geração de binário | Compilação C/Assembly, objetos, linkedição com `linker.ld`, geração de `turingos.bin` e ISO |
| Gerenciamento de dispositivo não suportado diretamente | Drivers próprios para VGA, teclado, timer e serial |
| Engenharia reversa sem código-fonte | Análise de binário com `hexdump`, `objdump`, `ndisasm`, `readelf` e GDB |
| Depuração/prototipação virtual | Execução no QEMU, depuração remota com GDB, logs via serial e inspeção de binário |
| Kanban semanal | GitHub Projects com issues, status e fases |
| Versionamento | Git/GitHub, branches, commits semânticos e tags |

---

## 🧩 Arquitetura conceitual

```text
+------------------------------------------------+
| Shell                                          |
| help, clear, about, version, echo              |
+------------------------------------------------+
| Chamadas internas conceituais                  |
| sys_write, sys_clear, sys_get_ticks            |
+------------------------------------------------+
| Kernel                                         |
| inicialização, terminal, memória               |
+------------------------------------------------+
| Drivers básicos                                |
| VGA, teclado, timer, serial                    |
+------------------------------------------------+
| Hardware virtualizado                          |
| QEMU                                           |
+------------------------------------------------+
```

---

## 🛠️ Tecnologias

- **C** — implementação principal do kernel;
- **Assembly x86** — entrada inicial e rotinas de baixo nível;
- **NASM** — montagem do código Assembly;
- **GCC** — compilação em modo freestanding;
- **LD** — linkedição com script próprio;
- **GRUB** — carregamento do kernel via Multiboot;
- **QEMU** — execução em máquina virtual;
- **GDB** — depuração;
- **Makefile** — automação;
- **Xorriso** — geração de ISO;
- **Git/GitHub** — versionamento;
- **GitHub Projects** — Kanban.

---

## 💻 Ambiente recomendado

```bash
sudo apt update
sudo apt install build-essential nasm qemu-system-x86 grub-pc-bin xorriso make gdb binutils
```

Opcional:

```bash
sudo apt install gcc-multilib
```

Verificação:
=======
## ✅ Aderência aos requisitos obrigatórios da disciplina

Esta seção mostra como o TuringOS atende aos requisitos obrigatórios da disciplina de Interface Hardware/Software.

| Requisito obrigatório | Como o TuringOS atende |
|---|---|
| Interface direta com o hardware | Escrita direta na memória VGA, acesso a portas de I/O, teclado PS/2, timer/PIT e serial |
| Código de montagem Assembly | Arquivo de entrada `boot/boot.asm`, cabeçalho Multiboot, configuração inicial da pilha e chamada ao kernel em C |
| Geração de código de máquina/binário | Compilação de C e Assembly para objetos, linkedição com `linker.ld`, geração de `turingos.bin` e ISO inicializável |
| Gerenciamento de dispositivo não suportado diretamente | Implementação própria de drivers básicos para VGA, teclado, timer e serial no ambiente virtualizado |
| Engenharia reversa de sistema sem código-fonte | Análise documentada de um binário de boot/kernel usando `objdump`, `ndisasm`, `hexdump`, `readelf` e GDB |
| Depuração/prototipação virtual da plataforma | Execução no QEMU, depuração com GDB, saída serial, análise de registradores e inspeção do binário |
| Planejamento semanal com Kanban | Organização das atividades em GitHub Projects ou quadro Kanban equivalente |
| Versionamento com Git | Uso de branches, commits semânticos, tags e histórico de evolução no GitHub |

---

## 🛠️ Tecnologias utilizadas

O projeto será desenvolvido usando:

- **C**: implementação da maior parte do kernel;
- **Assembly x86**: entrada inicial, rotinas de baixo nível e interação direta com a CPU;
- **NASM**: montagem do código Assembly;
- **GCC**: compilação do código C em modo freestanding;
- **LD**: linkedição do kernel com linker script próprio;
- **GRUB**: carregamento do kernel via padrão Multiboot;
- **QEMU**: execução do sistema em máquina virtual;
- **GDB**: depuração do kernel;
- **Makefile**: automação da compilação, execução e limpeza;
- **Xorriso**: geração da imagem ISO;
- **Git/GitHub**: versionamento do código-fonte;
- **GitHub Projects/Kanban**: planejamento semanal das atividades.

---

## 💻 Ambiente de desenvolvimento

Ambiente recomendado:

```text
Windows 11
└── WSL2 Ubuntu
    ├── GCC
    ├── Make
    ├── NASM
    ├── LD
    ├── GRUB
    ├── Xorriso
    ├── QEMU
    └── GDB
```

Instalação das ferramentas principais:

```bash
sudo apt update
sudo apt install build-essential nasm qemu-system-x86 grub-pc-bin xorriso make gdb
```

Opcionalmente, para facilitar compilação 32-bit no Linux:

```bash
sudo apt install gcc-multilib binutils
```

Verificação das ferramentas:
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b

```bash
gcc --version
make --version
nasm -v
qemu-system-i386 --version
grub-mkrescue --version
gdb --version
ld --version
objdump --version
```

---

<<<<<<< HEAD
## 📁 Estrutura do projeto

```text
TuringOS/
=======
## 📁 Estrutura inicial do projeto

Estrutura sugerida:

```text
turing-os/
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
├── boot/
│   └── boot.asm
├── kernel/
│   ├── kernel.c
<<<<<<< HEAD
│   ├── vga.c
│   ├── terminal.c
=======
│   ├── terminal.c
│   ├── vga.c
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
│   ├── keyboard.c
│   ├── timer.c
│   ├── memory.c
│   ├── ramfs.c
│   ├── serial.c
<<<<<<< HEAD
│   ├── syscall.c
│   └── shell.c
├── include/
│   ├── vga.h
│   ├── terminal.h
=======
│   └── shell.c
├── include/
│   ├── terminal.h
│   ├── vga.h
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
│   ├── keyboard.h
│   ├── timer.h
│   ├── memory.h
│   ├── ramfs.h
│   ├── serial.h
<<<<<<< HEAD
│   ├── syscall.h
=======
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
│   └── shell.h
├── iso/
│   └── boot/
│       └── grub/
│           └── grub.cfg
├── docs/
│   ├── images/
<<<<<<< HEAD
│   ├── architecture.md
│   ├── requirements.md
│   ├── execution-plan.md
│   ├── implementation-guide.md
│   ├── debugging.md
│   ├── reverse-engineering.md
│   ├── kanban.md
│   ├── risks.md
│   └── presentation-script.md
=======
│   ├── reverse-engineering.md
│   ├── debugging.md
│   └── kanban.md
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
├── build/
├── linker.ld
├── Makefile
├── LICENSE
└── README.md
```

---

## 🚀 Como compilar e executar

<<<<<<< HEAD
=======
Depois que o `Makefile` estiver pronto, o projeto poderá ser compilado com:

```bash
make
```

Para gerar a ISO:

```bash
make iso
```

Para executar no QEMU:

```bash
make run
```

Para executar em modo de depuração:

```bash
make debug
```

Para limpar arquivos gerados:

```bash
make clean
```

Fluxo recomendado:

>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
```bash
make clean
make
make run
```

<<<<<<< HEAD
Outros comandos:

```bash
make iso
make debug
make clean
```

=======
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
---

## 🧪 Resultado esperado inicial

<<<<<<< HEAD
```text
TuringOS v0.1
Kernel loaded successfully.
=======
Ao executar no QEMU, a versão inicial deverá exibir algo semelhante a:

```text
TuringOS v0.1
Kernel loaded successfully.

>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
An educational Unix-like operating system.

turingos>
```

---

<<<<<<< HEAD
## 🗺️ Roadmap

### v0.1 — Boot e kernel mínimo

- [ ] Estrutura inicial do projeto
- [ ] Ambiente de desenvolvimento
- [ ] `boot.asm` com Multiboot
- [ ] `kernel.c` com `kernel_main`
- [ ] `linker.ld`
- [ ] `grub.cfg`
- [ ] `Makefile`
- [ ] Execução no QEMU

### v0.2 — VGA e terminal

- [ ] Driver VGA em modo texto
- [ ] Escrita direta em `0xB8000`
- [ ] Limpeza de tela
- [ ] Controle de linha/coluna
- [ ] Terminal básico
- [ ] Mensagem inicial

### v0.3 — Debug e engenharia reversa

- [ ] Documentação de depuração com QEMU/GDB
- [ ] Análise de binário com `objdump`
- [ ] Análise com `hexdump`
- [ ] Análise com `ndisasm`
- [ ] Identificação do ponto de entrada
- [ ] Comparação entre análise estática e execução

### v0.4 — Teclado e shell

- [ ] Leitura de teclado por polling
- [ ] Conversão de scancodes
- [ ] Buffer de comando
- [ ] Shell simples
- [ ] Comandos `help`, `clear`, `about`, `version`, `echo`

### v0.5 — Interrupções e timer

- [ ] IDT
- [ ] ISR
- [ ] IRQ
- [ ] PIC
- [ ] Timer/PIT
- [ ] Comandos `ticks` e `uptime`

### v0.6 — Memória e RAMFS

- [ ] `kmalloc` simples
- [ ] Comando `mem`
- [ ] RAMFS
- [ ] Comandos `ls`, `cat`, `touch`, `write`

### v1.0 — Versão de apresentação

- [ ] Kernel organizado
- [ ] Terminal funcional
- [ ] Shell funcional
- [ ] Drivers básicos
- [ ] Documentação completa
- [ ] Prints ou GIFs
- [ ] Slides
- [ ] Demonstração em QEMU

---

## 🔍 Engenharia reversa sem código-fonte

A etapa de engenharia reversa analisará um binário sem consultar seu código-fonte.

```bash
hexdump -C build/turingos.bin | head
objdump -D -b binary -m i386 build/turingos.bin
ndisasm -b 32 build/turingos.bin | less
readelf -h build/turingos.elf
```

Objetivos:

- identificar formato do binário;
- localizar ponto de entrada;
- observar instruções Assembly;
- identificar chamadas e saltos;
- comparar o comportamento observado no QEMU;
- documentar conclusões.

---

## 🐞 Depuração

Execução aguardando GDB:
=======
## 🧱 Fases de desenvolvimento

O desenvolvimento será dividido em fases incrementais. Cada fase adiciona uma nova camada ao sistema.

### ✅ Fase 0 — Planejamento do projeto

Objetivo: definir nome, escopo, repositório, documentação inicial e organização do trabalho.

Entregas esperadas:

```text
[ ] Nome definido
[ ] Repositório criado
[ ] README inicial escrito
[ ] Estrutura de pastas criada
[ ] Escopo definido
[ ] Kanban criado
[ ] Issues iniciais criadas
```

---

### ✅ Fase 1 — Ambiente de desenvolvimento

Objetivo: preparar o ambiente para compilar e executar o kernel.

Entregas esperadas:

```text
[ ] GCC instalado
[ ] NASM instalado
[ ] Make instalado
[ ] QEMU instalado
[ ] GRUB/Xorriso instalados
[ ] GDB instalado
[ ] Ferramentas verificadas
```

---

### ✅ Fase 2 — Boot inicial com GRUB

Objetivo: fazer o GRUB carregar o kernel do TuringOS.

Arquivos principais:

```text
boot/boot.asm
linker.ld
iso/boot/grub/grub.cfg
Makefile
```

Responsabilidades do `boot.asm`:

- definir o cabeçalho Multiboot;
- definir o ponto de entrada do kernel;
- configurar uma pilha inicial;
- chamar `kernel_main()` em C.

Entregas esperadas:

```text
[ ] Cabeçalho Multiboot criado
[ ] Pilha inicial configurada
[ ] Entrada do kernel definida
[ ] GRUB carrega o kernel
[ ] QEMU executa o kernel
```

---

### ✅ Fase 3 — Kernel mínimo em C

Objetivo: criar o primeiro código em C do kernel.

Arquivo principal:

```text
kernel/kernel.c
```

Exemplo conceitual:

```c
void kernel_main(void) {
    // Código inicial do kernel
}
```

Nesta fase, o kernel não deve depender de bibliotecas de alto nível do sistema operacional hospedeiro, como:

```c
printf();
scanf();
malloc();
fopen();
```

Essas funções dependem de um sistema operacional já existente. Como o TuringOS será o próprio sistema operacional, várias funcionalidades precisarão ser implementadas manualmente.

Entregas esperadas:

```text
[ ] `kernel_main()` criado
[ ] `boot.asm` chama `kernel_main()`
[ ] Código C compila em modo freestanding
[ ] Kernel é linkado corretamente
[ ] QEMU executa o kernel
```

---

### ✅ Fase 4 — Driver de vídeo VGA

Objetivo: criar a primeira forma de saída na tela.

Em modo texto VGA, é possível escrever caracteres diretamente na memória de vídeo no endereço:

```text
0xB8000
```

Cada caractere ocupa dois bytes:

```text
Byte 1: caractere
Byte 2: atributo/cor
```

Exemplo conceitual:

```c
volatile char* video = (volatile char*) 0xB8000;

video[0] = 'T';
video[1] = 0x07;
```

Arquivos principais:

```text
kernel/vga.c
include/vga.h
```

Funções iniciais:

```c
void vga_putchar(char c);
void vga_write(const char* str);
void vga_clear(void);
void vga_set_color(unsigned char color);
```

Entregas esperadas:

```text
[ ] Escrever caractere na tela
[ ] Escrever string na tela
[ ] Limpar tela
[ ] Controlar posição do cursor
[ ] Controlar cor básica
```

---

### ✅ Fase 5 — Terminal básico

Objetivo: criar uma camada de terminal acima do driver VGA.

O driver VGA escreve diretamente na tela. O terminal organiza essa escrita de forma mais amigável.

Arquivos principais:

```text
kernel/terminal.c
include/terminal.h
```

Funções sugeridas:

```c
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* str);
void terminal_writeln(const char* str);
void terminal_clear(void);
```

Responsabilidades do terminal:

- quebra de linha;
- avanço do cursor;
- limpeza da tela;
- controle de linhas e colunas;
- rolagem de tela futuramente.

Entregas esperadas:

```text
[ ] Terminal inicializado
[ ] Escrita de texto organizada
[ ] Quebra de linha funcionando
[ ] Prompt exibido
```

---

### ✅ Fase 6 — Makefile e automação

Objetivo: automatizar o processo de compilação, linkedição, geração da ISO, execução e depuração.

Comandos desejados:

```bash
make
make iso
make run
make debug
make clean
```

Entregas esperadas:

```text
[ ] Compilar Assembly
[ ] Compilar C
[ ] Linkar kernel
[ ] Gerar `turingos.bin`
[ ] Gerar `turingos.iso`
[ ] Executar com `make run`
[ ] Depurar com `make debug`
```

---

### ✅ Fase 7 — Entrada pelo teclado

Objetivo: permitir que o usuário digite comandos.

O teclado PS/2 envia códigos chamados **scancodes**. O kernel precisa ler esses códigos e convertê-los em caracteres.

Arquivos principais:

```text
kernel/keyboard.c
include/keyboard.h
```

Funções iniciais:

```c
void keyboard_init(void);
char keyboard_getchar(void);
```

Conceitos estudados:

- portas de entrada e saída;
- instruções `in` e `out`;
- scancodes;
- buffer de entrada;
- tratamento básico de teclas;
- interrupções de teclado futuramente.

Entregas esperadas:

```text
[ ] Teclado inicializado
[ ] Leitura de tecla funcionando
[ ] Caracteres aparecem na tela
[ ] Backspace básico
[ ] Enter funcionando
[ ] Buffer de comando criado
```

---

### ✅ Fase 8 — Shell simples

Objetivo: criar uma interface textual para interpretar comandos do usuário.

Arquivos principais:

```text
kernel/shell.c
include/shell.h
```

Comandos iniciais:

```bash
help
clear
about
version
echo
```

Exemplo de uso:

```text
TuringOS v0.1

turingos> help
Comandos disponíveis:
help      - mostra os comandos
clear     - limpa a tela
about     - mostra informações do sistema
version   - mostra a versão
echo      - imprime um texto

turingos>
```

Entregas esperadas:

```text
[ ] Prompt funcionando
[ ] Comando help
[ ] Comando clear
[ ] Comando about
[ ] Comando version
[ ] Comando echo
```

---

### ✅ Fase 9 — Interrupções

Objetivo: implementar suporte básico a interrupções.

Interrupções permitem que o hardware avise o processador quando algo acontece, como:

- uma tecla foi pressionada;
- o timer disparou;
- ocorreu uma exceção;
- um dispositivo precisa de atenção.

Arquivos sugeridos:

```text
kernel/idt.c
kernel/isr.c
kernel/irq.c
include/idt.h
include/isr.h
include/irq.h
```

Conceitos estudados:

- IDT;
- ISR;
- IRQ;
- PIC;
- exceções da CPU;
- interrupções de hardware.

Entregas esperadas:

```text
[ ] IDT criada
[ ] Exceções básicas tratadas
[ ] IRQs configuradas
[ ] Interrupções habilitadas
[ ] Teclado usando interrupção
[ ] Timer usando interrupção
```

---

### ✅ Fase 10 — Timer

Objetivo: adicionar um contador de tempo ao sistema.

O timer permite que o kernel conte ticks e futuramente implemente escalonamento de tarefas.

Arquivos principais:

```text
kernel/timer.c
include/timer.h
```

Funções sugeridas:

```c
void timer_init(void);
unsigned int timer_get_ticks(void);
void timer_sleep(unsigned int ticks);
```

Comandos no shell:

```bash
ticks
uptime
```

Exemplo:

```text
turingos> ticks
Ticks: 1524
```

Entregas esperadas:

```text
[ ] Timer inicializado
[ ] Contador de ticks
[ ] Comando ticks
[ ] Comando uptime
```

---

### ✅ Fase 11 — Gerenciamento básico de memória

Objetivo: criar um gerenciamento simples de memória dentro do kernel.

Inicialmente, não será necessário implementar paginação completa. O primeiro passo pode ser um alocador linear simples.

Arquivos principais:

```text
kernel/memory.c
include/memory.h
```

Funções iniciais:

```c
void memory_init(void);
void* kmalloc(unsigned int size);
void memory_dump(void);
```

Ideia inicial:

```text
heap_start → área livre de memória → heap_end
```

Cada chamada a `kmalloc` avança um ponteiro. Esse modelo inicial não precisa liberar memória com `free`; ele serve para estudo e prototipação.

Comando no shell:

```bash
mem
```

Exemplo:

```text
turingos> mem
Kernel heap used: 1024 bytes
```

Entregas esperadas:

```text
[ ] Área de heap definida
[ ] `kmalloc` simples
[ ] Comando mem
[ ] Exibição de memória usada
```

---

### ✅ Fase 12 — Sistema de arquivos em memória

Objetivo: criar um sistema de arquivos simples em RAM.

Nome sugerido:

```text
RAMFS
```

Nesta fase, o sistema ainda não grava em disco. Os arquivos existem apenas enquanto o sistema está rodando.

Arquivos principais:

```text
kernel/ramfs.c
include/ramfs.h
```

Estrutura conceitual:

```c
struct file {
    char name[32];
    char content[256];
    int used;
};
```

Comandos do shell:

```bash
ls
cat
touch
write
```

Exemplo:

```text
turingos> touch readme.txt
turingos> write readme.txt Hello
turingos> ls
readme.txt
turingos> cat readme.txt
Hello
```

Entregas esperadas:

```text
[ ] Criar arquivo em memória
[ ] Listar arquivos
[ ] Escrever conteúdo
[ ] Ler conteúdo
[ ] Comandos ls, cat, touch e write
```

---

### ✅ Fase 13 — Chamadas internas conceituais

Objetivo: criar uma camada conceitual semelhante a chamadas de sistema.

Nesta fase, não é necessário haver separação real entre modo usuário e modo kernel. O objetivo é organizar a arquitetura.

Exemplos:

```c
int sys_write(const char* str);
int sys_clear(void);
int sys_get_ticks(void);
```

Ideia:

```text
Shell
  ↓
Chamadas internas conceituais
  ↓
Kernel
  ↓
Drivers
```

Entregas esperadas:

```text
[ ] `sys_write`
[ ] `sys_clear`
[ ] `sys_get_ticks`
[ ] Shell usando camada interna
[ ] Organização em camadas
```

---

### ✅ Fase 14 — Organização Unix-like

Objetivo: aproximar o projeto da filosofia Unix, sem tentar implementar um Unix real.

Ideias aplicadas:

- terminal como interface principal;
- comandos pequenos e simples;
- separação entre camadas;
- nomes inspirados em Unix;
- organização modular;
- recursos tratados de forma uniforme;
- shell como principal forma de interação.

Comandos previstos:

```bash
help
clear
about
version
echo
mem
ticks
uptime
ls
cat
touch
write
```

Ideias futuras:

```bash
ps
kill
run
whoami
pwd
mkdir
rm
```

Entregas esperadas:

```text
[ ] Shell organizado
[ ] Comandos documentados
[ ] Estrutura modular
[ ] README atualizado
```

---

### ✅ Fase 15 — Documentação e apresentação

Objetivo: transformar o projeto em algo apresentável para a disciplina e para o GitHub.

O README deve explicar:

- objetivo do projeto;
- tecnologias utilizadas;
- como compilar;
- como executar;
- arquitetura;
- fases implementadas;
- aderência aos requisitos obrigatórios;
- limitações;
- próximos passos;
- prints ou GIFs do sistema rodando.

Sugestão de seção para demonstração:

```markdown
## Demonstração

![TuringOS rodando no QEMU](docs/images/turingos-demo.png)
```

Entregas esperadas:

```text
[ ] README completo
[ ] Código organizado
[ ] Makefile funcionando
[ ] Prints adicionados
[ ] Documentação técnica criada
[ ] Projeto pronto para apresentação
```

---

## 🗓️ Cronograma sugerido

### Versão mínima — 2 a 3 semanas

```text
Semana 1:
- configurar ambiente;
- criar estrutura do projeto;
- configurar GRUB;
- criar kernel mínimo;
- executar no QEMU.

Semana 2:
- implementar VGA;
- implementar terminal;
- adicionar limpeza de tela;
- automatizar com Makefile.

Semana 3:
- documentar engenharia reversa;
- documentar depuração;
- organizar Kanban;
- preparar apresentação.
```

### Versão recomendada — 4 a 6 semanas

```text
Semana 1:
- ambiente;
- GRUB;
- kernel mínimo;
- QEMU.

Semana 2:
- driver VGA;
- terminal;
- Makefile.

Semana 3:
- teclado;
- shell;
- comandos básicos.

Semana 4:
- interrupções;
- timer;
- comandos ticks/uptime.

Semana 5:
- memória simples;
- RAMFS inicial.

Semana 6:
- documentação;
- testes;
- prints;
- apresentação final.
```

### Versão avançada — 8 a 12 semanas

```text
Semanas 1-2:
- boot;
- kernel;
- VGA;
- terminal.

Semanas 3-4:
- teclado;
- shell;
- comandos.

Semanas 5-6:
- interrupções;
- timer;
- memória.

Semanas 7-8:
- RAMFS;
- chamadas internas conceituais.

Semanas 9-10:
- tarefas/processos simples;
- escalonamento cooperativo experimental.

Semanas 11-12:
- documentação;
- refinamento;
- apresentação final.
```

---

## 📊 Roadmap

### TuringOS v0.1 — Kernel mínimo

```text
[ ] Boot com GRUB
[ ] Kernel em C
[ ] Entrada em Assembly
[ ] Escrita na tela
[ ] Limpar tela
[ ] Terminal básico
[ ] Makefile
[ ] Execução no QEMU
```

### TuringOS v0.2 — Terminal e comandos fixos

```text
[ ] Driver VGA melhorado
[ ] Cores no terminal
[ ] Prompt `turingos>`
[ ] Comando help
[ ] Comando clear
[ ] Comando about
[ ] Comando version
```

### TuringOS v0.3 — Teclado e shell

```text
[ ] Entrada de teclado
[ ] Buffer de comandos
[ ] Shell simples
[ ] Comando echo
```

### TuringOS v0.4 — Interrupções e timer

```text
[ ] IDT
[ ] ISR
[ ] IRQ
[ ] Timer
[ ] Comando ticks
[ ] Comando uptime
```

### TuringOS v0.5 — Memória e RAMFS

```text
[ ] `kmalloc` simples
[ ] Comando mem
[ ] RAMFS inicial
[ ] Comando ls
[ ] Comando cat
[ ] Comando touch
[ ] Comando write
```

### TuringOS v1.0 — Versão de apresentação

```text
[ ] Kernel organizado
[ ] Shell funcional
[ ] Drivers básicos
[ ] Memória simples
[ ] RAMFS
[ ] Engenharia reversa documentada
[ ] Depuração documentada
[ ] Kanban atualizado
[ ] README completo
[ ] Demonstração em QEMU
```

---

## 🔍 Engenharia reversa de sistema sem código-fonte

Além do estudo de referências abertas, o projeto terá uma etapa específica de **engenharia reversa sem acesso ao código-fonte**.

Nessa etapa, será analisado um binário relacionado ao processo de boot ou a um kernel mínimo. O objetivo é compreender o comportamento do binário observando sua estrutura e suas instruções de máquina.

Ferramentas previstas:

```bash
objdump
ndisasm
hexdump
readelf
gdb
qemu-system-i386
```

Aspectos que serão analisados:

- formato do binário;
- ponto de entrada;
- cabeçalhos e seções;
- instruções Assembly principais;
- chamadas e desvios;
- endereços relevantes;
- relação entre instruções e comportamento observado no QEMU;
- comparação entre análise estática e execução dinâmica.

Exemplos de comandos:

```bash
objdump -D -b binary -m i386 turingos.bin
hexdump -C turingos.bin | head
ndisasm -b 32 turingos.bin | less
gdb turingos.bin
```

A documentação ficará em:

```text
docs/reverse-engineering.md
```

O estudo de projetos com código-fonte aberto, como xv6, Minix e exemplos da OSDev Wiki, será usado apenas como **referência conceitual complementar**, não como substituto da etapa de engenharia reversa sem código-fonte.

---

## 🐞 Depuração e prototipação virtual

O desenvolvimento será realizado em ambiente virtualizado usando QEMU.

O uso do QEMU permite testar o sistema operacional sem instalá-lo em uma máquina física, reduzindo riscos e facilitando a depuração.

Ferramentas utilizadas:

- QEMU;
- GDB;
- logs via porta serial;
- Makefile;
- `objdump`;
- `hexdump`;
- testes incrementais.

Exemplo de execução simples:

```bash
make run
```

Exemplo de execução aguardando conexão do GDB:
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b

```bash
qemu-system-i386 -kernel build/turingos.bin -s -S
```

<<<<<<< HEAD
Abrir GDB:

```bash
gdb build/turingos.elf
=======
Exemplo de depuração:

```bash
gdb build/turingos.bin
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
```

Dentro do GDB:

```gdb
target remote localhost:1234
break kernel_main
continue
info registers
<<<<<<< HEAD
x/16xw $esp
disassemble
=======
```

A documentação ficará em:

```text
docs/debugging.md
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
```

---

<<<<<<< HEAD
## 🗂️ Kanban

Colunas:

```text
Backlog
=======
## 🗂️ Planejamento com Kanban

O desenvolvimento será acompanhado por um quadro Kanban, preferencialmente usando GitHub Projects.

Colunas sugeridas:

```text
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
A fazer
Em desenvolvimento
Em teste
Concluído
```

<<<<<<< HEAD
Issues iniciais:

```text
#2  Criar estrutura inicial do projeto
#4  Configurar ambiente de desenvolvimento
#5  Criar boot.asm com cabeçalho Multiboot
#7  Criar kernel.c com kernel_main
#10 Criar linker.ld
#11 Criar grub.cfg
#12 Criar Makefile inicial
#13 Executar kernel mínimo no QEMU
#14 Implementar driver VGA em modo texto
#15 Criar terminal básico
#16 Criar documentação de depuração com QEMU/GDB
#17 Criar documentação de engenharia reversa sem código-fonte
#18 Preparar slides de apresentação
=======
Exemplo de tarefas iniciais:

```text
[ ] Configurar ambiente no WSL2
[ ] Criar estrutura inicial do projeto
[ ] Criar boot.asm com cabeçalho Multiboot
[ ] Criar linker.ld
[ ] Criar kernel.c
[ ] Criar Makefile
[ ] Gerar primeira ISO
[ ] Executar no QEMU
[ ] Implementar escrita VGA
[ ] Implementar terminal básico
[ ] Documentar engenharia reversa
[ ] Documentar depuração com GDB
```

A documentação ficará em:

```text
docs/kanban.md
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
```

---

<<<<<<< HEAD
## 🌱 Versionamento

Branches sugeridas:

```text
main
dev
feature/project-structure
feature/boot
feature/minimal-kernel
feature/vga-driver
feature/terminal
feature/build-system
feature/debugging-docs
feature/reverse-engineering-docs
feature/keyboard
feature/shell
feature/interrupts
feature/timer
feature/memory
feature/ramfs
```

Commits sugeridos:

```text
chore: create initial project structure
docs: add development environment instructions
feat: add multiboot header
feat: add minimal kernel main
build: add linker script
build: add grub configuration
build: add Makefile
feat: implement VGA text output
feat: add terminal abstraction
docs: add debugging guide
docs: add reverse engineering notes
=======
## 🌱 Estratégia de versionamento

O projeto será versionado com Git e hospedado no GitHub.

Estratégia sugerida de branches:

```text
main         → versão estável
/dev         → desenvolvimento principal
feature/*    → novas funcionalidades
fix/*        → correções
```

Exemplos de branches:

```text
feature/boot
feature/vga-driver
feature/terminal
feature/keyboard-driver
feature/shell
feature/timer
feature/memory
feature/ramfs
feature/reverse-engineering-docs
```

Exemplos de commits semânticos:

```text
feat: add multiboot header
feat: implement VGA text output
feat: add terminal clear function
feat: create basic shell prompt
feat: add keyboard scancode reader
fix: correct cursor position on new line
docs: update reverse engineering notes
docs: add debugging guide
chore: configure Makefile build targets
```

Tags sugeridas:

```text
v0.1 - boot e kernel mínimo
v0.2 - terminal básico
v0.3 - shell inicial
v0.4 - interrupções e timer
v0.5 - memória e RAMFS
v1.0 - versão final da apresentação
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
```

---

<<<<<<< HEAD
## ⚠️ Limitações

O TuringOS é educacional e inicialmente não terá suporte POSIX, multitarefa real, modo usuário completo, paginação completa, sistema de arquivos persistente, rede, interface gráfica, drivers modernos, carregador ELF completo ou compatibilidade com programas Linux.
=======
## 🧠 Conceitos estudados

### Sistemas Operacionais

- kernel;
- boot;
- interrupções;
- processos;
- memória;
- terminal;
- drivers;
- chamadas de sistema;
- sistema de arquivos.

### Arquitetura de Computadores

- registradores;
- pilha;
- modo protegido;
- portas de entrada e saída;
- interrupções de hardware;
- memória de vídeo;
- timer;
- teclado.

### Programação em C

- ponteiros;
- structs;
- arrays;
- manipulação de memória;
- funções;
- organização modular;
- compilação separada;
- ambiente freestanding.

### Assembly

- ponto de entrada;
- cabeçalho Multiboot;
- configuração inicial da pilha;
- chamadas entre Assembly e C;
- instruções de baixo nível;
- manipulação de registradores;
- geração de objeto binário.

### Engenharia de Software

- organização em módulos;
- documentação;
- Git;
- commits semânticos;
- branches;
- Kanban;
- roadmap;
- controle de versões.

---

## ⚠️ Limitações do projeto

O TuringOS é um projeto educacional. Inicialmente, ele não terá:

- suporte completo a POSIX;
- multitarefa real;
- modo usuário completo;
- sistema de arquivos persistente;
- rede;
- interface gráfica;
- drivers modernos;
- compatibilidade com programas Linux;
- segurança robusta;
- carregamento de programas externos ELF.

Essas funcionalidades podem ser estudadas em versões futuras.
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b

---

## 🔮 Funcionalidades futuras

<<<<<<< HEAD
- multitarefa cooperativa;
- escalonador Round-Robin;
- paginação;
- modo usuário;
- syscalls reais via interrupção;
- carregador ELF;
- driver ATA/IDE;
- sistema de arquivos persistente;
- comandos `ps`, `kill`, `run`, `pwd`, `mkdir`, `rm`;
- suporte a programas externos.
=======
Possíveis evoluções do projeto:

```text
[ ] Multitarefa cooperativa
[ ] Escalonador Round-Robin
[ ] Paginação
[ ] Modo usuário
[ ] System calls reais via interrupção
[ ] ELF loader
[ ] Sistema de arquivos persistente
[ ] Driver ATA/IDE
[ ] Comando ps
[ ] Comando kill
[ ] Comando run
[ ] Suporte a programas externos
```

---

## 🎓 Valor acadêmico

Este projeto é útil para disciplinas como:

- Interface Hardware/Software;
- Sistemas Operacionais;
- Arquitetura de Computadores;
- Programação em C;
- Programação em Assembly;
- Compiladores;
- Estruturas de Dados;
- Engenharia de Software.

O TuringOS ajuda a compreender, na prática, como um computador sai do estado inicial de boot e passa a executar um sistema organizado capaz de interagir com o usuário.

---

## 📚 Referências recomendadas

- Andrew S. Tanenbaum — *Sistemas Operacionais Modernos*;
- Abraham Silberschatz — *Operating System Concepts*;
- OSDev Wiki;
- Intel Software Developer Manuals;
- GNU GRUB Manual;
- QEMU Documentation;
- The Little Book About OS Development;
- JamesM's Kernel Development Tutorials;
- xv6: A Simple, Unix-like Teaching Operating System;
- Minix.

---

## 🧾 Licença

Este projeto pode ser distribuído sob a licença MIT.

```text
MIT License

Copyright (c) 2026 Joseph Antony

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files...
```
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b

---

## 👨‍💻 Autor

Desenvolvido por **Joseph Antony**.
<<<<<<< HEAD
=======

Projeto acadêmico e educacional voltado ao estudo de Interface Hardware/Software, Sistemas Operacionais, C, Assembly, Arquitetura de Computadores e engenharia reversa de binários.

---

## 🧠 TuringOS

```text
TuringOS
├── Boot
├── Kernel
├── Terminal
├── Drivers
├── Memória
├── Shell
├── RAMFS
├── Debug
├── Engenharia reversa
├── Git/Kanban
└── Unix-like concepts
```
>>>>>>> 79253055cd461b09c50f9a937e62af3f5da12a3b
