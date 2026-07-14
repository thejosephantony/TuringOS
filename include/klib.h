#ifndef KLIB_H
#define KLIB_H

#include <stddef.h>
#include <stdint.h>

/*
 * Funcoes de string.
 */
size_t kstrlen(const char* str);
int kstrcmp(const char* first, const char* second);

/*
 * Funcoes de memoria.
 *
 * kmemcpy pressupoe que as regioes nao se sobrepoem.
 */
void* kmemset(void* destination, int value, size_t count);
void* kmemcpy(void* destination, const void* source, size_t count);

/*
 * Converte um inteiro sem sinal para texto.
 *
 * Bases suportadas: 2 ate 16.
 * O buffer deve possuir espaco suficiente para o resultado
 * e para o caractere terminador '\0'.
 */
char* kutoa(uint32_t value, char* buffer, uint32_t base);

#endif
