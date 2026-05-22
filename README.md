# 🧠 TuringOS

**TuringOS** é um sistema operacional educacional inspirado em Unix, desenvolvido com o objetivo de estudar, na prática, conceitos fundamentais de Sistemas Operacionais, Arquitetura de Computadores, Interface Hardware-Software, C e Assembly.

O projeto não tem como objetivo criar um sistema operacional completo como Linux, BSD ou Minix, mas sim construir um **mini kernel educacional**, capaz de inicializar em uma máquina virtual, escrever diretamente na tela, interagir com dispositivos básicos, executar comandos simples e demonstrar conceitos internos de um sistema operacional.

---

## 📌 Objetivo do Projeto

O objetivo principal do TuringOS é compreender como um sistema operacional funciona internamente, desde o processo de boot até a criação de uma interface textual básica.

Durante o desenvolvimento, serão estudados conceitos como:

- boot do sistema;
- kernel;
- código de montagem em Assembly;
- geração de binário executável;
- escrita direta na memória de vídeo;
- interface direta com hardware virtualizado;
- drivers básicos;
- interrupções;
- teclado;
- timer;
- gerenciamento básico de memória;
- terminal;
- shell;
- comandos internos;
- sistema de arquivos em memória;
- chamadas de sistema conceituais;
- depuração com QEMU/GDB;
- versionamento com Git;
- organização semanal com Kanban.

---

## 🧩 Ideia Geral

A arquitetura inicial do TuringOS será baseada em um kernel simples carregado pelo GRUB e executado no QEMU.

```text
+-----------------------------+
|           Shell             |
| help, clear, echo, about    |
+-----------------------------+
|       Chamadas internas     |
| print, read, clear, etc.    |
+-----------------------------+
|           Kernel            |
| memória, terminal, drivers  |
+-----------------------------+
|      Drivers básicos        |
| vídeo, teclado, timer       |
+-----------------------------+
|        Hardware/QEMU        |
+-----------------------------+
```

O sistema será executado em uma plataforma virtualizada, permitindo testar o kernel sem instalar nada diretamente no computador físico.

---

## 🛠️ Tecnologias Utilizadas

O projeto será desenvolvido usando:

- **C** — para a maior parte do kernel;
- **Assembly x86** — para entrada inicial e rotinas de baixo nível;
- **Makefile** — para automatizar a compilação;
- **LD** — para linkedição do kernel;
- **GRUB** — para carregar o kernel;
- **QEMU** — para executar o sistema operacional em máquina virtual;
- **GDB** — para depuração;
- **Git/GitHub** — para versionamento do código-fonte;
- **GitHub Projects/Kanban** — para planejamento semanal das atividades;
- **WSL2 Ubuntu** ou Linux nativo — ambiente de desenvolvimento recomendado.

---

## 💻 Ambiente de Desenvolvimento

O ambiente recomendado é:

```text
Windows 11
└── WSL2 Ubuntu
    ├── GCC
    ├── Make
    ├── NASM ou GNU AS
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

Verificação das ferramentas:

```bash
gcc --version
make --version
nasm -v
qemu-system-i386 --version
grub-mkrescue --version
gdb --version
```

---

## 📁 Estrutura Inicial do Projeto

Estrutura sugerida para o TuringOS:

```text
turing-os/
├── boot/
│   └── boot.s
├── kernel/
│   ├── kernel.c
│   ├── terminal.c
│   ├── vga.c
│   ├── keyboard.c
│   ├── timer.c
│   ├── memory.c
│   ├── ramfs.c
│   └── shell.c
├── include/
│   ├── terminal.h
│   ├── vga.h
│   ├── keyboard.h
│   ├── timer.h
│   ├── memory.h
│   ├── ramfs.h
│   └── shell.h
├── iso/
│   └── boot/
│       └── grub/
│           └── grub.cfg
├── docs/
│   ├── images/
│   ├── reverse-engineering.md
│   ├── kanban.md
│   └── debugging.md
├── linker.ld
├── Makefile
├── LICENSE
└── README.md
```

---

# ✅ Aderência aos Requisitos Obrigatórios da Disciplina

Esta seção descreve como o projeto TuringOS atende aos requisitos obrigatórios definidos para o trabalho.

---

## 1. Interface direta com o hardware

O TuringOS realiza interface direta com componentes de hardware virtualizados pela plataforma QEMU.

O projeto não utiliza chamadas de alto nível de um sistema operacional já existente para executar suas funcionalidades internas. Em vez disso, o próprio kernel acessa diretamente recursos de baixo nível, como:

- memória de vídeo em modo texto VGA;
- portas de entrada e saída;
- teclado PS/2;
- timer do sistema;
- interrupções de hardware;
- porta serial para depuração.

Um exemplo de acesso direto ao hardware é a escrita na memória de vídeo VGA, localizada no endereço:

```text
0xB8000
```

Nesse modelo, cada caractere exibido na tela é escrito diretamente na memória de vídeo, sem o uso de funções como `printf`.

---

## 2. Código de montagem Assembly

O projeto utiliza código Assembly para realizar tarefas de baixo nível que não podem ser feitas diretamente em C no início da execução do sistema.

O código Assembly será utilizado principalmente para:

- definir o ponto de entrada do kernel;
- configurar a pilha inicial;
- incluir o cabeçalho Multiboot;
- transferir o controle para o kernel em C;
- manipular instruções específicas da arquitetura;
- acessar portas de entrada e saída;
- configurar rotinas de interrupção.

Arquivo principal relacionado:

```text
boot/boot.s
```

Fluxo inicial:

```text
GRUB → boot.s → kernel_main()
```

---

## 3. Geração de código de máquina e binário

O TuringOS gera código de máquina a partir de arquivos escritos em C e Assembly.

O processo de compilação envolve:

1. montagem do código Assembly;
2. compilação do código C;
3. geração de arquivos objeto;
4. linkedição com linker script próprio;
5. geração do kernel binário;
6. geração de uma imagem ISO inicializável;
7. execução no QEMU.

Fluxo geral:

```text
boot.s       → boot.o
kernel.c     → kernel.o
vga.c        → vga.o
terminal.c   → terminal.o
             ↓
          linker.ld
             ↓
        turingos.bin
             ↓
        turingos.iso
```

Dessa forma, o projeto demonstra o processo de transformação de código-fonte em código de máquina executável pela plataforma virtualizada.

---

## 4. Gerenciamento de dispositivo não suportado diretamente

O TuringOS implementa drivers próprios para dispositivos básicos, em vez de depender de drivers prontos do sistema operacional hospedeiro.

Os dispositivos inicialmente tratados pelo kernel serão:

- tela em modo texto VGA;
- teclado PS/2;
- timer/PIT;
- porta serial para depuração.

Esses dispositivos são acessados diretamente pelo kernel por meio de endereços de memória, portas de entrada/saída e interrupções.

Exemplos de drivers planejados:

```text
kernel/vga.c
kernel/keyboard.c
kernel/timer.c
kernel/serial.c
```

Isso demonstra o gerenciamento de dispositivos em uma plataforma onde o sistema operacional desenvolvido ainda não possui suporte nativo pronto.

---

## 5. Engenharia reversa de sistemas em código-fonte

Durante o desenvolvimento do TuringOS, serão estudados sistemas operacionais educacionais e materiais de referência com código-fonte aberto.

O objetivo não é copiar diretamente esses sistemas, mas analisar sua estrutura para compreender como kernels reais ou educacionais organizam:

- boot;
- drivers;
- interrupções;
- memória;
- terminal;
- chamadas de sistema;
- organização modular do código.

Projetos e referências que podem ser analisados:

- xv6;
- Minix;
- exemplos da OSDev Wiki;
- JamesM's Kernel Development Tutorials;
- The Little Book About OS Development;
- pequenos kernels educacionais open source.

A engenharia reversa será aplicada por meio de:

- leitura orientada do código-fonte;
- identificação dos módulos principais;
- comparação com a arquitetura do TuringOS;
- documentação das decisões de projeto;
- adaptação conceitual sem cópia direta.

Perguntas que guiarão essa análise:

```text
Como o xv6 organiza processos?
Como a OSDev Wiki inicializa a IDT?
Como kernels educacionais lidam com VGA?
Como o GRUB transfere controle para o kernel?
Como um kernel mínimo organiza memória e interrupções?
```

A documentação dessa etapa ficará em:

```text
docs/reverse-engineering.md
```

---

## 6. Técnicas de depuração e prototipação virtual da plataforma

O desenvolvimento será realizado em ambiente virtualizado, utilizando o QEMU.

O uso do QEMU permite testar o sistema operacional sem instalá-lo diretamente em uma máquina física, reduzindo riscos e facilitando a depuração.

Ferramentas utilizadas:

- QEMU;
- GDB;
- logs no terminal;
- porta serial virtual;
- Makefile;
- testes incrementais;
- `objdump`.

Exemplo de execução:

```bash
make run
```

Exemplo de depuração com GDB:

```bash
qemu-system-i386 -kernel turingos.bin -s -S
gdb turingos.bin
```

Técnicas previstas:

- execução incremental;
- inspeção de registradores;
- análise de mensagens de erro do QEMU;
- depuração com breakpoints;
- uso de saída serial para logs do kernel;
- testes por módulos;
- análise do binário gerado com `objdump`.

A documentação dessa etapa ficará em:

```text
docs/debugging.md
```

---

## 7. Planejamento semanal das atividades com Kanban

O desenvolvimento do projeto será organizado semanalmente usando metodologia Kanban.

O quadro Kanban poderá ser organizado em colunas como:

```text
A fazer
Em desenvolvimento
Em teste
Concluído
```

Exemplo de planejamento semanal:

```text
Semana 1:
- configurar ambiente;
- criar estrutura do projeto;
- compilar kernel mínimo;
- executar no QEMU.

Semana 2:
- implementar driver VGA;
- criar terminal básico;
- implementar clear e print.

Semana 3:
- implementar entrada de teclado;
- criar shell simples;
- adicionar comandos help, clear e about.

Semana 4:
- configurar interrupções;
- implementar timer;
- adicionar comandos ticks e uptime.

Semana 5:
- implementar gerenciamento básico de memória;
- criar RAMFS inicial;
- adicionar comandos ls e cat.

Semana 6:
- revisar código;
- documentar arquitetura;
- gravar demonstração;
- preparar apresentação final.
```

Cada atividade deverá ser registrada como tarefa no quadro Kanban do GitHub Projects ou ferramenta equivalente.

A documentação dessa etapa ficará em:

```text
docs/kanban.md
```

---

## 8. Versionamento do código-fonte com Git

O código-fonte do TuringOS será versionado em um repositório Git.

O versionamento permitirá acompanhar a evolução do projeto, registrar mudanças importantes e organizar o desenvolvimento por fases.

Estratégia sugerida:

```text
main        → versão estável
dev         → desenvolvimento principal
feature/*   → novas funcionalidades
```

Exemplos de branches:

```text
feature/vga-driver
feature/keyboard-driver
feature/shell
feature/timer
feature/memory
feature/ramfs
```

Exemplos de commits:

```text
feat: add multiboot header
feat: implement VGA text output
feat: add terminal clear function
feat: create basic shell prompt
fix: correct cursor position on new line
docs: update project roadmap
```

Também poderão ser usadas tags para marcar versões:

```text
v0.1 - boot e kernel mínimo
v0.2 - terminal básico
v0.3 - shell inicial
v0.4 - interrupções e timer
v0.5 - memória e RAMFS
v1.0 - versão final da apresentação
```

---

## 📌 Resumo de Atendimento aos Requisitos

| Requisito obrigatório | Atendimento no TuringOS |
|---|---|
| Interface direta com o hardware | Escrita VGA, teclado, timer, portas de I/O |
| Código Assembly | Boot inicial, entrada do kernel, rotinas de baixo nível |
| Geração de código de máquina/binário | Compilação C/Assembly, linkedição e ISO |
| Gerenciamento de dispositivo não suportado | Drivers próprios para VGA, teclado, timer e serial |
| Engenharia reversa de sistema em código-fonte | Estudo documentado de xv6, Minix, OSDev e kernels educacionais |
| Depuração/prototipação virtual | QEMU, GDB, serial debug, objdump e testes incrementais |
| Kanban semanal | GitHub Projects com tarefas por fase |
| Versionamento | Git, branches, commits semânticos e tags |

---

# 🚀 Fases de Desenvolvimento

O desenvolvimento do TuringOS será dividido em fases. Cada fase adiciona uma camada nova ao sistema.

---

## ✅ Fase 0 — Planejamento do Projeto

### Objetivo

Definir o escopo inicial do sistema operacional.

Nesta fase, o foco é decidir o que o TuringOS será e, principalmente, o que ele **não será** neste primeiro momento.

### O que fazer

- Definir o nome do projeto.
- Definir o objetivo acadêmico.
- Definir o escopo inicial.
- Criar o repositório no GitHub.
- Criar o `README.md`.
- Criar a estrutura de pastas.
- Criar o quadro Kanban.
- Definir as primeiras issues do projeto.

### Escopo inicial recomendado

O TuringOS deve começar como um mini sistema operacional com:

- boot pelo GRUB;
- kernel em C;
- entrada inicial em Assembly;
- saída de texto na tela;
- limpeza da tela;
- terminal simples;
- comandos básicos;
- execução no QEMU.

### O que evitar no começo

Nesta fase inicial, não tentar implementar:

- interface gráfica;
- rede;
- sistema de arquivos real persistente;
- multitarefa completa;
- `fork`/`exec` reais;
- drivers complexos;
- suporte a pendrive/HD real.

### Entrega da fase

```text
[OK] Nome definido
[OK] Repositório criado
[OK] Estrutura de pastas criada
[OK] README inicial escrito
[OK] Escopo definido
[OK] Kanban criado
```

---

## ✅ Fase 1 — Ambiente de Desenvolvimento

### Objetivo

Preparar o ambiente para compilar e executar o kernel.

### O que fazer

Instalar as ferramentas necessárias:

```bash
sudo apt update
sudo apt install build-essential nasm qemu-system-x86 grub-pc-bin xorriso make gdb
```

Verificar se as ferramentas foram instaladas corretamente:

```bash
gcc --version
make --version
nasm -v
qemu-system-i386 --version
grub-mkrescue --version
gdb --version
```

### Ferramentas importantes

| Ferramenta | Função |
|---|---|
| GCC | Compilar código C |
| NASM/GAS | Montar código Assembly |
| LD | Linkar os arquivos objeto |
| Make | Automatizar a compilação |
| GRUB | Carregar o kernel |
| QEMU | Executar o SO virtualmente |
| GDB | Depurar o kernel |
| Xorriso | Gerar imagem ISO |

### Entrega da fase

Ao final desta fase, o ambiente deve conseguir executar comandos como:

```bash
make
qemu-system-i386
grub-mkrescue
gdb
```

---

## ✅ Fase 2 — Boot Inicial com GRUB

### Objetivo

Fazer o GRUB carregar o kernel do TuringOS.

Nesta fase, não será criado um bootloader próprio. O GRUB será usado para facilitar o desenvolvimento.

### Por que usar GRUB?

Criar um bootloader do zero é uma tarefa mais difícil. Usar GRUB permite focar primeiro no kernel.

O fluxo será:

```text
BIOS/QEMU
   ↓
GRUB
   ↓
Kernel do TuringOS
```

### Arquivos principais

```text
boot/boot.s
linker.ld
iso/boot/grub/grub.cfg
Makefile
```

### O que fazer

Criar um arquivo Assembly inicial com cabeçalho Multiboot.

Esse arquivo será responsável por:

- informar ao GRUB que o kernel é carregável;
- definir o ponto de entrada do kernel;
- configurar uma pilha inicial;
- chamar a função principal do kernel em C.

### Entrega da fase

Ao final da fase, o GRUB deve conseguir carregar o kernel.

Resultado esperado:

```text
TuringOS iniciado
```

---

## ✅ Fase 3 — Kernel Mínimo em C

### Objetivo

Criar o primeiro código em C do kernel.

### O que fazer

Criar o arquivo:

```text
kernel/kernel.c
```

Com uma função principal do kernel:

```c
void kernel_main(void) {
    // Código inicial do kernel
}
```

Nesta fase, o kernel ainda não usa bibliotecas padrão como em um programa comum.

Em um sistema operacional próprio, normalmente você não pode usar diretamente:

```c
printf()
scanf()
malloc()
fopen()
```

Essas funções dependem de um sistema operacional já existente. Como o TuringOS é o próprio sistema operacional, muitas dessas funcionalidades precisam ser criadas manualmente.

### Entrega da fase

```text
[OK] boot.s chama kernel_main()
[OK] kernel.c compila
[OK] kernel é linkado
[OK] QEMU executa o kernel
```

---

## ✅ Fase 4 — Driver de Vídeo em Modo Texto

### Objetivo

Criar a primeira forma de saída na tela.

Em modo texto VGA, é possível escrever caracteres diretamente na memória de vídeo, no endereço:

```text
0xB8000
```

### Ideia

Cada caractere na tela usa dois bytes:

```text
Byte 1: caractere
Byte 2: cor
```

Exemplo conceitual:

```c
volatile char* video = (volatile char*) 0xB8000;

video[0] = 'T';
video[1] = 0x07;
```

Isso escreve a letra `T` na tela.

### O que implementar

Criar arquivos:

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

### Resultado esperado

Ao rodar no QEMU, deve aparecer algo como:

```text
TuringOS v0.1
Kernel loaded successfully.
```

### Entrega da fase

```text
[OK] Escrever caractere na tela
[OK] Escrever string na tela
[OK] Limpar tela
[OK] Controlar posição do cursor
[OK] Controlar cor básica
```

---

## ✅ Fase 5 — Terminal Básico

### Objetivo

Criar uma camada de terminal acima do driver VGA.

O driver VGA escreve diretamente na tela. O terminal organiza essa escrita de forma mais amigável.

### O que implementar

Criar arquivos:

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

### Funcionalidades

O terminal deve cuidar de:

- quebra de linha;
- avanço do cursor;
- limpeza da tela;
- limite de linhas e colunas;
- rolagem de tela futuramente.

### Resultado esperado

A tela deve mostrar:

```text
TuringOS v0.1
An educational Unix-like operating system.

turingos>
```

### Entrega da fase

```text
[OK] Terminal inicializado
[OK] Escrita de texto organizada
[OK] Quebra de linha funcionando
[OK] Prompt inicial exibido
```

---

## ✅ Fase 6 — Makefile e Automação da Compilação

### Objetivo

Automatizar a compilação do projeto.

### O que fazer

Criar um `Makefile` capaz de:

- compilar arquivos Assembly;
- compilar arquivos C;
- linkar o kernel;
- gerar a ISO;
- executar no QEMU;
- limpar arquivos temporários;
- preparar modo de depuração.

### Comandos desejados

```bash
make
make iso
make run
make debug
make clean
```

### Exemplo de fluxo

```bash
make clean
make
make run
```

### Entrega da fase

O projeto deve ser executado com apenas:

```bash
make run
```

---

## ✅ Fase 7 — Entrada pelo Teclado

### Objetivo

Permitir que o usuário digite comandos.

Essa fase já é mais difícil, porque envolve leitura de hardware.

### Ideia

O teclado PS/2 normalmente envia códigos chamados **scancodes**. O kernel precisa ler esses códigos e convertê-los em caracteres.

### O que implementar

Criar arquivos:

```text
kernel/keyboard.c
include/keyboard.h
```

Funções iniciais:

```c
char keyboard_getchar(void);
void keyboard_init(void);
```

### Conceitos envolvidos

Nesta fase, serão estudados:

- portas de entrada/saída;
- instruções `in` e `out`;
- scancodes;
- interrupções de teclado;
- buffer de entrada.

### Resultado esperado

O usuário deve conseguir digitar algo na tela:

```text
turingos> help
```

### Entrega da fase

```text
[OK] Teclado inicializado
[OK] Teclas aparecem na tela
[OK] Backspace básico
[OK] Enter funcionando
[OK] Buffer de comando criado
```

---

## ✅ Fase 8 — Shell Simples

### Objetivo

Criar um shell básico para interpretar comandos do usuário.

O shell será uma camada simples que recebe uma string digitada pelo usuário e executa uma ação correspondente.

### Arquivos sugeridos

```text
kernel/shell.c
include/shell.h
```

### Comandos iniciais

```bash
help
clear
about
version
echo
```

### Exemplo de uso

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

### Entrega da fase

```text
[OK] Prompt funcionando
[OK] Comando help
[OK] Comando clear
[OK] Comando about
[OK] Comando version
[OK] Comando echo
```

---

## ✅ Fase 9 — Interrupções

### Objetivo

Implementar suporte básico a interrupções.

Interrupções são fundamentais para um sistema operacional. Elas permitem que o hardware avise o processador quando algo acontece.

Exemplos:

- uma tecla foi pressionada;
- o timer disparou;
- ocorreu uma exceção;
- um dispositivo precisa de atenção.

### Conceitos importantes

Nesta fase, serão estudados:

- IDT;
- ISR;
- IRQ;
- PIC;
- exceções da CPU;
- interrupções de hardware.

### O que implementar

Arquivos sugeridos:

```text
kernel/idt.c
kernel/isr.c
kernel/irq.c
include/idt.h
include/isr.h
include/irq.h
```

### Resultado esperado

O kernel deve conseguir registrar e tratar interrupções básicas.

Exemplo:

```text
[OK] IDT initialized
[OK] Interrupts enabled
```

### Entrega da fase

```text
[OK] IDT criada
[OK] Exceções básicas tratadas
[OK] IRQs configuradas
[OK] Teclado usando interrupção
[OK] Timer usando interrupção
```

---

## ✅ Fase 10 — Timer

### Objetivo

Adicionar um contador de tempo ao sistema.

O timer permite que o kernel conte ticks e futuramente implemente escalonamento de tarefas.

### O que implementar

Criar arquivos:

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

### Comandos no shell

Adicionar comandos:

```bash
ticks
uptime
```

Exemplo:

```text
turingos> ticks
Ticks: 1524
```

### Entrega da fase

```text
[OK] Timer inicializado
[OK] Contador de ticks
[OK] Comando ticks
[OK] Comando uptime
```

---

## ✅ Fase 11 — Gerenciamento Básico de Memória

### Objetivo

Criar um gerenciamento simples de memória dentro do kernel.

No início, não é necessário implementar paginação completa. O primeiro passo pode ser um alocador simples.

### O que implementar

Criar arquivos:

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

### Ideia inicial

Pode ser usado um alocador linear simples:

```text
heap_start → [ área livre de memória ] → heap_end
```

Cada chamada a `kmalloc` avança um ponteiro.

### Limitação

Esse modelo inicial não precisa liberar memória com `free`. Ele serve apenas para estudo.

### Comandos no shell

```bash
mem
```

Exemplo:

```text
turingos> mem
Kernel heap used: 1024 bytes
```

### Entrega da fase

```text
[OK] Área de heap definida
[OK] kmalloc simples
[OK] Comando mem
[OK] Exibição de memória usada
```

---

## ✅ Fase 12 — Sistema de Arquivos em Memória

### Objetivo

Criar um sistema de arquivos simples em RAM.

Nesta fase, o sistema ainda não grava no disco. Os arquivos existem apenas enquanto o sistema está rodando.

### Nome sugerido

```text
RAMFS
```

### O que implementar

Criar arquivos:

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

### Comandos do shell

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

### Entrega da fase

```text
[OK] Criar arquivo em memória
[OK] Listar arquivos
[OK] Escrever conteúdo
[OK] Ler conteúdo
[OK] Comandos ls, cat, touch e write
```

---

## ✅ Fase 13 — Chamadas de Sistema Conceituais

### Objetivo

Criar uma camada conceitual parecida com chamadas de sistema.

Nesta fase, não precisa haver ainda separação real entre modo usuário e modo kernel. O objetivo inicial é organizar a arquitetura.

### Exemplo de chamadas

```c
int sys_write(const char* str);
int sys_clear(void);
int sys_get_ticks(void);
```

### Ideia

O shell não deve acessar tudo diretamente. Ele pode usar funções internas que representam chamadas ao kernel.

```text
Shell
  ↓
Syscalls conceituais
  ↓
Kernel
  ↓
Drivers
```

### Entrega da fase

```text
[OK] sys_write
[OK] sys_clear
[OK] sys_get_ticks
[OK] organização em camada
```

---

## ✅ Fase 14 — Organização Unix-like

### Objetivo

Aproximar o projeto da filosofia Unix.

O TuringOS não será um Unix real, mas pode seguir algumas ideias:

- terminal como interface principal;
- comandos pequenos e simples;
- separação entre camadas;
- nomes inspirados em Unix;
- organização modular;
- recursos tratados de forma uniforme;
- shell como principal forma de interação.

### Ideias de comandos

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

### Ideias futuras

```bash
ps
kill
run
whoami
pwd
mkdir
rm
```

### Entrega da fase

```text
[OK] Shell organizado
[OK] Comandos documentados
[OK] Estrutura parecida com Unix
[OK] README atualizado
```

---

## ✅ Fase 15 — Documentação e Apresentação

### Objetivo

Transformar o projeto em algo apresentável para faculdade e GitHub.

### O que documentar

O README deve explicar:

- objetivo do projeto;
- tecnologias usadas;
- como compilar;
- como executar;
- arquitetura;
- fases implementadas;
- aderência aos requisitos obrigatórios;
- limitações;
- próximos passos;
- prints ou GIFs do sistema rodando.

### Comandos de execução

Exemplo:

```bash
git clone https://github.com/seu-usuario/turing-os.git
cd turing-os
make run
```

### Sugestão de seção para prints

```markdown
## Demonstração

![TuringOS rodando no QEMU](docs/images/turingos-demo.png)
```

### Entrega da fase

```text
[OK] README completo
[OK] Código organizado
[OK] Makefile funcionando
[OK] Prints adicionados
[OK] Projeto pronto para apresentação
```

---

# 🗓️ Cronograma Sugerido

## Versão mínima — 2 a 3 semanas

```text
Semana 1:
- ambiente
- boot
- kernel mínimo
- escrita na tela

Semana 2:
- terminal
- clear
- comandos fixos
- Makefile

Semana 3:
- documentação
- organização
- apresentação
```

## Versão recomendada — 4 a 6 semanas

```text
Semana 1:
- ambiente
- GRUB
- kernel mínimo
- QEMU

Semana 2:
- driver VGA
- terminal
- Makefile

Semana 3:
- teclado
- shell
- comandos básicos

Semana 4:
- interrupções
- timer
- comandos ticks/uptime

Semana 5:
- memória simples
- RAMFS

Semana 6:
- documentação
- testes
- prints
- apresentação
```

## Versão avançada — 8 a 12 semanas

```text
Semanas 1-2:
- boot
- kernel
- tela
- terminal

Semanas 3-4:
- teclado
- shell
- comandos

Semanas 5-6:
- interrupções
- timer
- memória

Semanas 7-8:
- RAMFS
- syscalls conceituais

Semanas 9-10:
- tarefas/processos simples

Semanas 11-12:
- documentação
- refinamento
- apresentação final
```

---

# 📊 Roadmap do Projeto

## TuringOS v0.1

```text
[ ] Boot com GRUB
[ ] Kernel em C
[ ] Escrita na tela
[ ] Limpar tela
[ ] Terminal básico
[ ] Makefile
[ ] Execução no QEMU
```

## TuringOS v0.2

```text
[ ] Driver VGA melhorado
[ ] Cores no terminal
[ ] Prompt turingos>
[ ] Comandos help, clear, about e version
```

## TuringOS v0.3

```text
[ ] Entrada de teclado
[ ] Buffer de comandos
[ ] Shell simples
[ ] Comando echo
```

## TuringOS v0.4

```text
[ ] IDT
[ ] Interrupções
[ ] Timer
[ ] Comandos ticks e uptime
```

## TuringOS v0.5

```text
[ ] kmalloc simples
[ ] Comando mem
[ ] RAMFS inicial
[ ] Comandos ls, cat, touch e write
```

## TuringOS v1.0

```text
[ ] Kernel organizado
[ ] Shell funcional
[ ] Drivers básicos
[ ] Memória simples
[ ] RAMFS
[ ] Documentação completa
[ ] Demonstração em QEMU
```

---

# 🧪 Como Compilar

Depois que o Makefile estiver pronto, o projeto deverá ser compilado com:

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

Para depurar:

```bash
make debug
```

Para limpar arquivos gerados:

```bash
make clean
```

---

# 🧠 Conceitos Estudados

Durante o desenvolvimento do TuringOS, serão estudados:

## Sistemas Operacionais

- kernel;
- boot;
- interrupções;
- processos;
- memória;
- terminal;
- drivers;
- chamadas de sistema;
- sistema de arquivos.

## Arquitetura de Computadores

- registradores;
- pilha;
- modo protegido;
- portas de entrada e saída;
- interrupções de hardware;
- memória de vídeo;
- timer;
- teclado.

## Programação em C

- ponteiros;
- structs;
- arrays;
- manipulação de memória;
- funções;
- organização modular;
- compilação separada.

## Assembly

- ponto de entrada;
- configuração inicial;
- chamadas entre Assembly e C;
- instruções de baixo nível;
- manipulação de registradores;
- código de montagem;
- geração de objeto binário.

## Engenharia de Software

- organização em módulos;
- documentação;
- Git;
- commits semânticos;
- branches;
- Kanban;
- roadmap;
- controle de versões.

---

# ⚠️ Limitações do Projeto

O TuringOS é um projeto educacional. Portanto, inicialmente ele não terá:

- suporte completo a POSIX;
- multitarefa real;
- modo usuário completo;
- sistema de arquivos persistente;
- rede;
- interface gráfica;
- suporte a drivers modernos;
- compatibilidade com programas Linux;
- segurança robusta.

Essas funcionalidades podem ser estudadas futuramente.

---

# 🔮 Possíveis Funcionalidades Futuras

Funcionalidades que podem ser adicionadas em versões futuras:

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

# 🎓 Valor Acadêmico

Este projeto é útil para disciplinas como:

- Sistemas Operacionais;
- Arquitetura de Computadores;
- Interface Hardware-Software;
- Programação em C;
- Programação em Assembly;
- Compiladores;
- Estruturas de Dados;
- Engenharia de Software.

O TuringOS ajuda a compreender, na prática, como um computador sai do estado inicial de boot e passa a executar um sistema organizado capaz de interagir com o usuário.

---

# 📚 Referências Recomendadas

Algumas referências úteis para estudar durante o projeto:

- Andrew S. Tanenbaum — Sistemas Operacionais Modernos;
- Abraham Silberschatz — Operating System Concepts;
- OSDev Wiki;
- Intel Software Developer Manuals;
- GNU GRUB Manual;
- QEMU Documentation;
- The Little Book About OS Development;
- JamesM's Kernel Development Tutorials;
- xv6: A Simple, Unix-like Teaching Operating System;
- Minix.

---

# 🧾 Licença

Este projeto pode ser distribuído sob a licença MIT.

Exemplo:

```text
MIT License

Copyright (c) 2026 Joseph Antony

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files...
```

---

# 👨‍💻 Autor

Desenvolvido por **Joseph Antony**.

Projeto acadêmico e educacional voltado ao estudo de Sistemas Operacionais, C, Assembly, Arquitetura de Computadores e Interface Hardware-Software.

---

# 🧠 TuringOS

> Um mini sistema operacional educacional inspirado em Unix, criado para compreender como kernels funcionam por dentro.

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
├── Git/Kanban
└── Unix-like concepts
```
