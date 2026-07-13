ENTRY(start)

PHDRS
{
    text PT_LOAD FLAGS(5); /* leitura + execução */
    data PT_LOAD FLAGS(6); /* leitura + escrita */
}

SECTIONS
{
    /* O kernel será carregado a partir de 1 MiB. */
    . = 1M;

    /*
     * O cabeçalho Multiboot deve permanecer no início do binário
     * e dentro dos primeiros 8 KiB do arquivo.
     */
    .multiboot ALIGN(4) :
    {
        KEEP(*(.multiboot))
    } :text

    /* Código executável e dados somente para leitura. */
    .text ALIGN(4K) :
    {
        *(.text*)
    } :text

    .rodata ALIGN(4K) :
    {
        *(.rodata*)
    } :text

    /* Dados modificáveis e dados não inicializados. */
    .data ALIGN(4K) :
    {
        *(.data*)
    } :data

    .bss ALIGN(4K) :
    {
        *(COMMON)
        *(.bss*)
    } :data

    /*
     * Metadados desnecessários para o kernel freestanding.
     * .note.GNU-stack é utilizada durante o link, mas não precisa
     * permanecer no executável final.
     */
    /DISCARD/ :
    {
        *(.note.GNU-stack)
        *(.comment)
        *(.eh_frame)
    }
}
