#ifndef LIB54CLIGC_H
#define LIB54CLIGC_H
#include <stdint.h>
#include <stdio.h>

typedef struct lib54cligc_color_t {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} lib54cligc_color_t;

typedef struct lib54cligc_pixel_t {
    uint16_t x;
    uint16_t y;
    lib54cligc_color_t b;
    lib54cligc_color_t f;
} lib54cligc_pixel_t;

typedef struct lib54cligc_pixelmap_t {
    lib54cligc_pixel_t* p;
    uint32_t size;
    uint32_t index;
} lib54cligc_pixelmap_t;

typedef enum lib54cligc_error_t {
    LIB54CLIGC_SUCCESS = 0,
    LIB54CLIGC_ERROR_INIT_IOCTL = 1,
    LIB54CLIGC_ERROR_INIT_TCGETATTR = 2,
    LIB54CLIGC_ERROR_INIT_TCSETATTR = 3,
    LIB54CLIGC_ERROR_INIT_PMAP_ALLOCATION = 4,
    LIB54CLIGC_ERROR_PIXEL_OUT_OF_BOUNDS = 20,
    LIB54CLIGC_ERROR_PIXEL_MAP_INDEX = 21,
    LIB54CLIGC_ERROR_LOG_FILE = 30,
    LIB54CLIGC_ERROR_INVALID_POINTER = 35,
    LIB54CLIGC_ERROR_MEMORY_ALLOCATION = 36
} lib54cligc_error_t;

typedef enum lib54cligc_warning_t {
    LIB54CLIGC_POLL_KEY_NO_PRESSED = 10
} lib54cligc_warning_t;

void lib54cligc_cursor_show();
void lib54cligc_cursor_hide();
void lib54cligc_update_terminal();

int lib54cligc_quit(lib54cligc_pixelmap_t* pixel_map);
int lib54cligc_init(lib54cligc_pixelmap_t* pixel_map);
int lib54cligc_clear(lib54cligc_pixelmap_t* pmap);
int lib54cligc_poll_key(char* key, size_t read_size);
int lib54cligc_set_logfd(FILE* fd);
int lib54cligc_color_set(lib54cligc_color_t* color, uint8_t r, uint8_t g, uint8_t b);
int lib54cligc_color2esc(lib54cligc_color_t color, const char* layer, char* out, size_t out_s);
int lib54cligc_pixel_add(lib54cligc_pixelmap_t* pmap, uint16_t x, uint16_t y, lib54cligc_color_t bg, lib54cligc_color_t fg, char c);
int lib54cligc_pixel_add_double(lib54cligc_pixelmap_t* pmap, uint16_t x, uint16_t y, lib54cligc_color_t bg);

unsigned short lib54cligc_get_terminal_width();
unsigned short lib54cligc_get_terminal_height();

#endif
