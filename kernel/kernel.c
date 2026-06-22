/*
 * TuringOS - kernel.c
 * Kernel mínimo em C.
 *
 * Esta primeira versão escreve diretamente na memória de vídeo VGA.
 */

#define VGA_MEMORY ((volatile unsigned short*)0xB8000)
#define VGA_COLOR_WHITE_ON_BLACK 0x0F

static unsigned short vga_entry(char character, unsigned char color) {
    return (unsigned short) character | (unsigned short) color << 8;
}

static void kernel_clear_screen(void) {
    for (int i = 0; i < 80 * 25; i++) {
        VGA_MEMORY[i] = vga_entry(' ', VGA_COLOR_WHITE_ON_BLACK);
    }
}

static void kernel_write_string(const char* text) {
    int i = 0;

    while (text[i] != '\0') {
        VGA_MEMORY[i] = vga_entry(text[i], VGA_COLOR_WHITE_ON_BLACK);
        i++;
    }
}

void kernel_main(void) {
    kernel_clear_screen();
    kernel_write_string("TuringOS v0.1 - Kernel loaded successfully.");
}
