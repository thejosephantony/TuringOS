#include "klib.h"

size_t kstrlen(const char* str) {
    size_t length = 0;

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

int kstrcmp(const char* first, const char* second) {
    size_t index = 0;

    while (
        first[index] != '\0' &&
        second[index] != '\0' &&
        first[index] == second[index]
    ) {
        index++;
    }

    return
        (int)(unsigned char)first[index] -
        (int)(unsigned char)second[index];
}

void* kmemset(void* destination, int value, size_t count) {
    unsigned char* bytes = (unsigned char*)destination;
    unsigned char byte = (unsigned char)value;

    for (size_t index = 0; index < count; index++) {
        bytes[index] = byte;
    }

    return destination;
}

void* kmemcpy(void* destination, const void* source, size_t count) {
    unsigned char* destination_bytes =
        (unsigned char*)destination;

    const unsigned char* source_bytes =
        (const unsigned char*)source;

    for (size_t index = 0; index < count; index++) {
        destination_bytes[index] = source_bytes[index];
    }

    return destination;
}

char* kutoa(uint32_t value, char* buffer, uint32_t base) {
    static const char digits[] = "0123456789ABCDEF";

    size_t length = 0;
    size_t left;
    size_t right;

    if (buffer == 0) {
        return 0;
    }

    if (base < 2 || base > 16) {
        buffer[0] = '\0';
        return buffer;
    }

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return buffer;
    }

    while (value > 0) {
        uint32_t remainder = value % base;

        buffer[length] = digits[remainder];
        length++;

        value /= base;
    }

    buffer[length] = '\0';

    /*
     * Os digitos foram gerados na ordem inversa.
     */
    left = 0;
    right = length - 1;

    while (left < right) {
        char temporary = buffer[left];

        buffer[left] = buffer[right];
        buffer[right] = temporary;

        left++;
        right--;
    }

    return buffer;
}
