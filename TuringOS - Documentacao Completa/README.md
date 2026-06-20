# 🧠 TuringOS

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
```

---

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

## 📁 Estrutura do projeto

```text
TuringOS/
├── boot/
│   └── boot.asm
├── kernel/
│   ├── kernel.c
│   ├── vga.c
│   ├── terminal.c
│   ├── keyboard.c
│   ├── timer.c
│   ├── memory.c
│   ├── ramfs.c
│   ├── serial.c
│   ├── syscall.c
│   └── shell.c
├── include/
│   ├── vga.h
│   ├── terminal.h
│   ├── keyboard.h
│   ├── timer.h
│   ├── memory.h
│   ├── ramfs.h
│   ├── serial.h
│   ├── syscall.h
│   └── shell.h
├── iso/
│   └── boot/
│       └── grub/
│           └── grub.cfg
├── docs/
│   ├── images/
│   ├── architecture.md
│   ├── requirements.md
│   ├── execution-plan.md
│   ├── implementation-guide.md
│   ├── debugging.md
│   ├── reverse-engineering.md
│   ├── kanban.md
│   ├── risks.md
│   └── presentation-script.md
├── build/
├── linker.ld
├── Makefile
├── LICENSE
└── README.md
```

---

## 🚀 Como compilar e executar

```bash
make clean
make
make run
```

Outros comandos:

```bash
make iso
make debug
make clean
```

---

## 🧪 Resultado esperado inicial

```text
TuringOS v0.1
Kernel loaded successfully.
An educational Unix-like operating system.

turingos>
```

---

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

```bash
qemu-system-i386 -kernel build/turingos.bin -s -S
```

Abrir GDB:

```bash
gdb build/turingos.elf
```

Dentro do GDB:

```gdb
target remote localhost:1234
break kernel_main
continue
info registers
x/16xw $esp
disassemble
```

---

## 🗂️ Kanban

Colunas:

```text
Backlog
A fazer
Em desenvolvimento
Em teste
Concluído
```

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
```

---

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
```

---

## ⚠️ Limitações

O TuringOS é educacional e inicialmente não terá suporte POSIX, multitarefa real, modo usuário completo, paginação completa, sistema de arquivos persistente, rede, interface gráfica, drivers modernos, carregador ELF completo ou compatibilidade com programas Linux.

---

## 🔮 Funcionalidades futuras

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

---

## 👨‍💻 Autor

Desenvolvido por **Joseph Antony**.
