#ifndef LIB54CLIGC_GRAPHICS_2D
#define LIB54CLIGC_GRAPHICS_2D
#include "lib54cligc.h"

int lib54cligc_g2d_pixel(lib54cligc_pixelmap_t* pmap, uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);

void lib54cligc_g2d_rect(lib54cligc_pixelmap_t* pmap, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t r, uint8_t g, uint8_t b);

#endif
