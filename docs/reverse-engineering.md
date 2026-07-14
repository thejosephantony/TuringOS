# Engenharia Reversa do Binário do TuringOS

## Objetivo

Registrar a análise estática do binário `build/turingos.bin` utilizando ferramentas de inspeção ELF.

## Identificação

O comando `file build/turingos.bin` identifica o artefato como um executável ELF de 32 bits para a arquitetura Intel 80386.

## Cabeçalho ELF

O comando `readelf -h build/turingos.bin` permite identificar:

- formato ELF32;
- arquitetura x86;
- tipo executável;
- endereço de entrada;
- quantidade de seções;
- quantidade de segmentos.

O endereço de entrada observado foi `0x10101e`.

## Seções

O comando `readelf -SW build/turingos.bin` mostrou as principais seções:

- `.multiboot`;
- `.text`;
- `.rodata`;
- `.data`;
- `.bss`.

A seção `.multiboot` contém o cabeçalho utilizado pelo carregador. A seção `.text` contém instruções executáveis. `.rodata` contém constantes. `.data` e `.bss` armazenam dados graváveis.

## Segmentos e permissões

O comando `readelf -lW build/turingos.bin` identificou dois segmentos LOAD:

- segmento `R E` contendo `.multiboot`, `.text` e `.rodata`;
- segmento `RW` contendo `.data` e `.bss`.

Nenhum segmento LOAD possui permissões `RWE`.

Isso comprova a separação entre regiões executáveis e graváveis.

## Símbolos

O comando `nm -n build/turingos.bin` permite localizar:

- rotina de entrada;
- `kernel_main`;
- terminal;
- shell;
- teclado;
- timer;
- handlers de interrupção;
- biblioteca interna.

## Desmontagem

O comando `objdump -d -M intel build/turingos.bin` converte as instruções de máquina em Assembly Intel.

Foram analisadas especialmente as funções `start` e `kernel_main`.

## Strings

O comando `strings build/turingos.bin` recupera textos do banner, nomes de comandos e mensagens internas do kernel.

## Representação hexadecimal

O comando `hexdump -C build/turingos.bin` mostrou que os primeiros bytes são `7f 45 4c 46`, assinatura padrão de arquivos ELF.

## Resultado

A engenharia reversa confirmou:

- binário ELF32;
- arquitetura Intel 80386;
- entrada em `0x10101e`;
- separação de código e dados;
- ausência de segmento RWE;
- presença de símbolos;
- presença de strings internas;
- possibilidade de desmontagem do kernel.
