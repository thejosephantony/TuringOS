# TuringOS

**TuringOS** é um mini sistema operacional educacional inspirado em Unix, desenvolvido em **C** e **Assembly x86**, com o objetivo de estudar, na prática, conceitos de **Interface Hardware/Software**, **Sistemas Operacionais**, **Arquitetura de Computadores**, **geração de código de máquina**, **drivers básicos**, **depuração** e **engenharia reversa de binários sem código-fonte**.

O projeto é carregado pelo **GRUB**, executado em ambiente virtualizado com **QEMU** e construído de forma incremental, partindo de um kernel mínimo até uma estrutura mais organizada com driver VGA, terminal, shell, teclado, interrupções e documentação técnica.

---

## Status atual

Versão atual do projeto:

```text
v0.1 — Kernel mínimo inicializável
Status: concluído
```

A versão atual já realiza o fluxo básico de inicialização:

```text
QEMU
 ↓
GRUB
 ↓
boot/boot.asm
 ↓
kernel_main()
 ↓
VGA text mode
```

Funcionalidades já implementadas:

* Boot via GRUB;
* Cabeçalho Multiboot em Assembly;
* Entrada inicial em `boot.asm`;
* Configuração manual da pilha;
* Chamada de código C a partir do Assembly;
* Kernel mínimo em C;
* Escrita direta na memória VGA em `0xB8000`;
* Script de linkedição com `linker.ld`;
* Configuração do GRUB em `grub.cfg`;
* Makefile para build, ISO e execução no QEMU;
* Execução bem-sucedida no QEMU.

Mensagem exibida atualmente no QEMU:

```text
TuringOS v0.1 - Kernel loaded successfully.
```

---

## Objetivo do projeto

O objetivo principal do TuringOS é demonstrar, de forma prática e didática, como software de baixo nível interage diretamente com o hardware.

O projeto busca responder perguntas como:

* Como um kernel é carregado?
* Qual é o papel de um bootloader?
* Por que Assembly ainda é necessário em sistemas operacionais?
* Como o C pode ser usado sem sistema operacional?
* Como escrever diretamente na memória de vídeo?
* Como gerar um binário inicializável?
* Como depurar um kernel com QEMU e GDB?
* Como analisar um binário sem depender do código-fonte?

---

## Relação com Interface Hardware/Software

O TuringOS atende aos principais pontos estudados na disciplina de Interface Hardware/Software, incluindo:

| Requisito                           | Como o TuringOS atende                                             |
| ----------------------------------- | ------------------------------------------------------------------ |
| Interface direta com hardware       | Escrita direta na memória VGA em `0xB8000`                         |
| Código Assembly                     | Entrada inicial em `boot/boot.asm`                                 |
| Código de máquina/binário           | Geração de `turingos.bin` e `turingos.iso`                         |
| Gerenciamento de dispositivo        | Driver VGA e, futuramente, teclado PS/2                            |
| Engenharia reversa sem código-fonte | Análise do binário com `objdump`, `readelf`, `hexdump` e `ndisasm` |
| Depuração/prototipação virtual      | Execução com QEMU e depuração com GDB                              |
| Planejamento semanal                | Organização por versões, issues, milestones e Kanban               |
| Versionamento                       | Uso de Git, branches, commits e Pull Requests                      |

---

## Tecnologias utilizadas

* C freestanding;
* Assembly x86 com NASM;
* GRUB;
* Multiboot;
* Linker script;
* GCC 32 bits;
* GNU LD;
* Makefile;
* QEMU;
* GDB;
* Git e GitHub;
* WSL/Linux.

---

## Estrutura atual do projeto

```text
TuringOS/
├── boot/
│   └── boot.asm
├── kernel/
│   └── kernel.c
├── iso/
│   └── boot/
│       └── grub/
│           └── grub.cfg
├── docs/
│   └── pdf/
│       └── TuringOS_Plano_Desenvolvimento_Completo.pdf
├── include/
├── scripts/
├── Makefile
├── linker.ld
├── README.md
└── LICENSE
```

---

## Principais arquivos

### `boot/boot.asm`

Arquivo Assembly responsável pela entrada inicial do kernel.

Ele contém:

* Cabeçalho Multiboot;
* Definição do ponto de entrada `start`;
* Configuração da pilha;
* Chamada para `kernel_main`;
* Loop final de segurança.

### `kernel/kernel.c`

Arquivo inicial do kernel em C.

Atualmente ele:

* Limpa a tela VGA;
* Escreve uma mensagem diretamente na memória de vídeo;
* Demonstra a execução de código C sem sistema operacional.

### `linker.ld`

Script de linkedição responsável por organizar o kernel na memória.

Ele define:

* Ponto de entrada;
* Endereço inicial em `1M`;
* Seções `.multiboot`, `.text`, `.rodata`, `.data` e `.bss`.

### `iso/boot/grub/grub.cfg`

Arquivo de configuração do GRUB.

Ele informa ao GRUB que deve carregar:

```text
/boot/turingos.bin
```

como kernel Multiboot.

### `Makefile`

Automatiza o processo de:

* Montagem do Assembly;
* Compilação do C;
* Linkedição do kernel;
* Geração da ISO;
* Execução no QEMU;
* Limpeza dos arquivos gerados.

---

## Ambiente de desenvolvimento

O ambiente recomendado é Linux ou WSL.

### Instalação das dependências

No WSL/Ubuntu:

```bash
sudo apt update
sudo apt install -y build-essential nasm make gcc-multilib binutils qemu-system-x86 qemu-system-gui qemu-utils grub-pc-bin grub-common xorriso mtools gdb git
```

### Verificação das ferramentas

```bash
gcc --version
make --version
nasm -v
ld --version
qemu-system-i386 --version
grub-mkrescue --version
gdb --version
git --version
```

---

## Como compilar

Na raiz do projeto:

```bash
make clean
make
```

Esse comando gera:

```text
build/turingos.bin
```

e copia o kernel para:

```text
iso/boot/turingos.bin
```

---

## Como verificar o kernel Multiboot

```bash
make check
```

Resultado esperado:

```text
Kernel reconhecido como Multiboot.
```

---

## Como gerar a ISO

```bash
make iso
```

A ISO será gerada em:

```text
build/turingos.iso
```

---

## Como executar no QEMU

```bash
make run
```

Resultado esperado:

```text
TuringOS v0.1 - Kernel loaded successfully.
```

---

## Como depurar com QEMU e GDB

O projeto será documentado para permitir depuração com QEMU e GDB.

Execução em modo debug:

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
```

Essa etapa será expandida na documentação de depuração.

---

## Engenharia reversa sem código-fonte

Um dos objetivos do projeto é demonstrar análise de binários gerados pelo kernel sem depender diretamente do código-fonte.

Ferramentas previstas:

```text
objdump
readelf
hexdump
xxd
ndisasm
strings
```

Exemplos de comandos:

```bash
objdump -d build/turingos.bin
readelf -h build/turingos.bin
hexdump -C build/turingos.bin | head
strings build/turingos.bin
```

Atividades esperadas:

* Identificar o ponto de entrada do kernel;
* Identificar seções do binário;
* Localizar strings no binário;
* Observar instruções Assembly geradas;
* Comparar código C com Assembly produzido;
* Documentar o comportamento do binário sem consultar o código-fonte.

---

## Roadmap

| Versão | Nome                           | Objetivo                                       | Status    |
| ------ | ------------------------------ | ---------------------------------------------- | --------- |
| v0.1   | Kernel mínimo                  | Inicializar kernel via GRUB e escrever na VGA  | Concluído |
| v0.2   | Driver VGA e terminal          | Organizar saída de vídeo em módulos            | Próximo   |
| v0.3   | Interface textual inicial      | Criar tela inicial mais apresentável           | Planejado |
| v0.4   | Shell básico                   | Criar comandos internos simples                | Planejado |
| v0.5   | Teclado PS/2                   | Ler entrada do teclado                         | Planejado |
| v0.6   | Interrupções                   | Criar IDT, ISR, IRQ e PIC                      | Planejado |
| v0.7   | Timer PIT                      | Adicionar noção de tempo/ticks                 | Planejado |
| v0.8   | Biblioteca do kernel           | Criar funções próprias de string e memória     | Planejado |
| v0.9   | Depuração e engenharia reversa | Documentar QEMU, GDB e análise binária         | Planejado |
| v1.0   | Entrega final                  | Consolidar código, documentação e apresentação | Planejado |

---

## Próxima etapa: v0.2 — Driver VGA e terminal

A próxima etapa será transformar o código VGA simples em uma estrutura modular.

Estrutura planejada:

```text
include/
├── drivers/
│   └── vga.h
├── kernel/
│   └── terminal.h
└── lib/
    └── types.h

kernel/
├── main.c
├── drivers/
│   └── vga.c
└── terminal/
    └── terminal.c
```

Objetivos da v0.2:

* Criar driver VGA separado;
* Criar camada de terminal;
* Controlar linha e coluna;
* Implementar quebra de linha;
* Implementar limpeza de tela;
* Implementar cores;
* Criar funções `terminal_write` e `terminal_writeln`;
* Atualizar o Makefile para múltiplos arquivos C.

Resultado visual esperado:

```text
TuringOS v0.2
Kernel initialized successfully.

Bootloader : GRUB / Multiboot
Kernel     : C + Assembly x86
Video      : VGA text mode
Status     : OK
```

Melhorias possíveis da etapa:

* Scroll de tela;
* Cursor visual;
* Tema de cores;
* Mensagens com prefixos `[OK]`, `[INFO]`, `[WARN]`;
* Tela inicial formatada com bordas;
* Logs de inicialização.

---

## Futuras funcionalidades

Após a versão inicial, o TuringOS poderá evoluir com:

* Shell interativo;
* Driver de teclado PS/2;
* Leitura de scancodes;
* Interrupções;
* Timer PIT;
* Biblioteca própria de strings;
* Funções de memória;
* `kprintf` simplificado;
* Sistema de arquivos em RAM;
* Gerenciamento de memória;
* Chamadas de sistema conceituais;
* Driver serial;
* Interface textual avançada;
* Modo gráfico experimental via framebuffer.

---

## Melhorias futuras

Possíveis melhorias técnicas:

* Separar permissões de segmentos no `linker.ld`;
* Corrigir aviso de `.note.GNU-stack`;
* Criar scripts auxiliares em `scripts/`;
* Criar GitHub Actions para validar build;
* Criar releases versionadas;
* Criar tags `v0.1`, `v0.2`, `v1.0`;
* Criar GIF ou vídeo de demonstração;
* Criar documentação específica para cada módulo;
* Criar diagramas de arquitetura e fluxo de boot.

Possíveis melhorias acadêmicas:

* Explicar o papel do Assembly no boot;
* Explicar o funcionamento do GRUB;
* Explicar o padrão Multiboot;
* Explicar como o C funciona em ambiente freestanding;
* Demonstrar a diferença entre aplicação comum e kernel;
* Demonstrar análise de binário sem código-fonte;
* Comparar conceitos do TuringOS com Linux/Unix.

---

## Documentação

A documentação completa do projeto está disponível em:

```text
docs/pdf/TuringOS_Plano_Desenvolvimento_Completo.pdf
```

Ela contém:

* Visão geral do projeto;
* Objetivos;
* Aderência aos requisitos da disciplina;
* Plano de execução;
* Roadmap;
* Melhorias por etapa;
* Riscos;
* Estratégia de commits;
* Melhorias futuras;
* Organização do Kanban;
* Guia de continuidade.

---

## Fluxo de desenvolvimento

Fluxo recomendado:

```bash
git switch main
git pull origin main
git switch -c feature/nome-da-funcionalidade
```

Após implementar:

```bash
git status
git add arquivos_alterados
git commit -m "tipo: descrição da mudança"
git push -u origin feature/nome-da-funcionalidade
```

Depois, abrir Pull Request no GitHub e fazer merge na `main`.

---

## Convenção de commits

Sugestões:

```text
feat: nova funcionalidade
fix: correção de erro
docs: alteração de documentação
chore: tarefa de manutenção
refactor: melhoria interna sem mudar comportamento
test: testes ou validações
build: mudanças no processo de build
```

Exemplos:

```text
feat: add VGA text mode driver
feat: add terminal abstraction
feat: add basic shell commands
docs: add reverse engineering guide
docs: update development plan
chore: update Makefile targets
```

---

## Limitações atuais

A versão atual ainda é simples e possui limitações importantes:

* Não há driver VGA modular;
* Não há terminal com cursor;
* Não há entrada de teclado;
* Não há shell interativo;
* Não há interrupções;
* Não há timer;
* Não há gerenciamento de memória;
* Não há sistema de arquivos;
* Não há modo usuário;
* Não há execução de programas externos.

Essas limitações são esperadas na versão `v0.1`. O projeto será evoluído gradualmente.

---

## Licença

Este projeto é educacional e pode ser distribuído conforme a licença definida no arquivo `LICENSE`.

---

## Autor

**Joseph Antony**

Projeto desenvolvido para fins acadêmicos na área de Interface Hardware/Software, Sistemas Operacionais e Programação de Baixo Nível.

GitHub: `thejosephantony`
