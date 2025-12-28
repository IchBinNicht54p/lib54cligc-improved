#include <string.h>
#include "lib54cligc.h"

int lib54cligc_g2d_pixel(lib54cligc_pixelmap_t* pmap, uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b){
    lib54cligc_color_t c;
    int status;

    if ((status = lib54cligc_color_set(&c, r, g, b)) != LIB54CLIGC_SUCCESS) return status;
    if ((status = lib54cligc_pixel_add_double(pmap, x, y, c)) != LIB54CLIGC_SUCCESS) return status;

    return LIB54CLIGC_SUCCESS;
}

void lib54cligc_g2d_rect(lib54cligc_pixelmap_t* pmap, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t r, uint8_t g, uint8_t b){
    for (uint16_t i = 0; i < w; i++){
        for (uint16_t j = 0; j < h; j++){
            lib54cligc_g2d_pixel(pmap, x + i, y + j, r, g, b);
        }
    }
};

int lib54cligc_g2d_text(lib54cligc_pixelmap_t* pmap, const char* txt, uint16_t x, uint16_t y, 
                        uint8_t r, uint8_t g, uint8_t b, uint8_t rb, uint8_t gb, uint8_t bb){
    lib54cligc_color_t c;
    lib54cligc_color_t bg;
    size_t l;
    
    int status;

    if ((status = lib54cligc_color_set(&c, r, g, b)) != LIB54CLIGC_SUCCESS) return status;
    if ((status = lib54cligc_color_set(&bg, rb, gb, bb)) != LIB54CLIGC_SUCCESS) return status;

    l = strlen(txt);

    for (size_t i = 0; i < l; i++){
        if ((status = lib54cligc_pixel_add(pmap, x + i, y, bg, c, txt[i])) != LIB54CLIGC_SUCCESS) return status;
    }

    return LIB54CLIGC_SUCCESS;
}
