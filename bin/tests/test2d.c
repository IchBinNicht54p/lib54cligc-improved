#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lib54cligc_improved/lib54cligc.h>
#include <lib54cligc_improved/graphics_2d.h>
#include <lib54cligc_improved/escape_codes.h>

#define KEY_READ_AMOUNT 3

uint16_t x = 20;
uint16_t y = 20;

int handle_key(char* key, size_t n){
    if (key[0] == 'q' || key[0] == ESC_CONTROL_ETX){
        return 1;
    }

    if (key[0] == ESC_CONTROL_ESC && key[1] == '['){
        switch (key[2]){
            case ESC_CUB:
                x -= 5;
                
                break;
            case ESC_CUF:
                x += 5;
                
                break;
            case ESC_CUU:
                y -= 5;

                break;
            case ESC_CUD:
                y += 5;

                break;
        }
    }

    return 0;
}


int main(){
    lib54cligc_pixelmap_t pmap;
    FILE* ofd = fopen("log", "w");

    int fps = 60;
    int run = 1;
    int status;
    char* key = malloc(2);

    if ((status = lib54cligc_set_logfd(ofd)) != 0){
        printf("an error occoured while setting the logfd %d\n", status);

        return 1;
    }

    if ((status = lib54cligc_init(&pmap)) != 0){
        printf("an error occoured while initializing lib54cligc %d\n", status);

        return 1;
    }

    while (1){ 
        int key_pressed = lib54cligc_poll_key(key, KEY_READ_AMOUNT);

        if (key_pressed != LIB54CLIGC_POLL_KEY_NO_PRESSED){
            if (handle_key(key, key_pressed) != 0){
                break;
            }
        }

        lib54cligc_clear(&pmap);

        lib54cligc_g2d_rect(&pmap, x, y, 20, 10, 0, 255, 0);

        lib54cligc_update_terminal();
        usleep(1000000 / fps);
    }

    lib54cligc_quit(&pmap);
    fclose(ofd);
    free(key);

    return 0;
}
