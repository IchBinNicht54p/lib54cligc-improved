#include <stdio.h>
#include <unistd.h>
#include <lib54cligc_improved/lib54cligc.h>
#include <lib54cligc_improved/graphics_2d.h>
#include <lib54cligc_improved/escape_codes.h>

int handle_key(char key){
    if (key == 'q' || key == ESC_CONTROL_ETX){
        return 1;
    }

    return 0;
}

void draw(lib54cligc_pixelmap_t* pmap, int* run, int16_t* x, int16_t* y, int* vx, int* vy, unsigned short w, unsigned short h){
    char key;
    int key_pressed = lib54cligc_poll_key(&key, 1);

    if (key_pressed != LIB54CLIGC_POLL_KEY_NO_PRESSED){
        if (handle_key(key) != 0){
            *run = 0;
        }
    }

    *x += *vx;
    *y += *vy;

    if (*x >= (w / 2)){
        *vx = -1;
    } else if (*x <= 1){
        *vx = 1;
    }

    if (*y >= h){
        *vy = -1;
    } else if (*y <= 1){
        *vy = 1;
    }

    lib54cligc_g2d_pixel(pmap, *x, *y, 255, 0, 0);
}

int main(){
    lib54cligc_pixelmap_t pmap;
    FILE* ofd = fopen("log", "w");

    int fps = 60;
    int run = 1;
    int status;
    char keybuf;

    int16_t x = 10;
    int16_t y = 10;
    int vx = 1;
    int vy = 1;

    if ((status = lib54cligc_set_logfd(ofd)) != 0){
        printf("an error occoured while setting the logfd %d\n", status);

        return 1;
    }

    if ((status = lib54cligc_init(&pmap)) != 0){
        printf("an error occoured while initializing lib54cligc %d\n", status);

        return 1;
    }

    unsigned short w = lib54cligc_get_terminal_width();
    unsigned short h = lib54cligc_get_terminal_height();

    while (run){
        lib54cligc_clear(&pmap);
        draw(&pmap, &run, &x, &y, &vx, &vy, w, h);
        lib54cligc_update_terminal();

        usleep(1000000 / fps);
    }

    lib54cligc_quit(&pmap);
    fclose(ofd);

    return 0;
}
