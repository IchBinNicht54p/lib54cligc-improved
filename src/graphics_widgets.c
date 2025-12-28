#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "graphics_2d.h"
#include "graphics_widgets.h"

int lib54cligc_widget_fps_counter_init(lib54cligc_fps_counter_t* counter){
    counter->tnow = time(NULL);
    counter->tsec = counter->tnow;
    counter->fps = 0;
    counter->tfps = malloc(10 + 1); // max 32 bit integer limit + null terminator

    if (!counter->tfps){
        return LIB54CLIGC_ERROR_MEMORY_ALLOCATION;
    }

    return LIB54CLIGC_SUCCESS;
}

void lib54cligc_widget_fps_counter_update(lib54cligc_fps_counter_t* counter){
    counter->tsec = time(NULL);

    if (counter->tsec - counter->tnow > 1){
        counter->tnow = counter->tsec;
        counter->dfps = counter->fps;
        counter->fps = 0;

        return;
    }

    counter->fps += 1;
}

void lib54cligc_widget_fps_counter_display(lib54cligc_pixelmap_t* pmap, lib54cligc_fps_counter_t* counter, uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b){
    sprintf(counter->tfps, "%d", counter->dfps);
    lib54cligc_g2d_text(pmap, counter->tfps, x, y, r, g, b, 0, 0, 0);
}
