#ifndef LIB54CLIGC_GRAPHICS_WIDGETS_H
#define LIB54CLIGC_GRAPHICS_WIDGETS_H
#include <stdint.h>
#include "lib54cligc.h"

typedef struct fps_counter_t {
    long long tnow;
    long long tsec;
    int fps;
    int dfps;
    char* tfps;
} lib54cligc_fps_counter_t;

int lib54cligc_widget_fps_counter_init(lib54cligc_fps_counter_t* counter);

void lib54cligc_widget_fps_counter_update(lib54cligc_fps_counter_t* counter);
void lib54cligc_widget_fps_counter_display(lib54cligc_pixelmap_t* pmap, lib54cligc_fps_counter_t* counter, uint16_t x, uint16_t y, 
                                           uint8_t r, uint8_t g, uint8_t b);

#endif
