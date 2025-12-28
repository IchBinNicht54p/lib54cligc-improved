#include <stdio.h>
#include <unistd.h>
#include <lib54cligc_improved/lib54cligc.h>
#include <lib54cligc_improved/escape_codes.h>

int handle_key(char key){
    if (key == 'q' || key == ESC_CONTROL_ETX){
        return 1;
    }

    return 0;
}

void draw(int* run){
    char key;
    int key_pressed = lib54cligc_poll_key(&key, 1);

    if (key_pressed != LIB54CLIGC_POLL_KEY_NO_PRESSED){
        if (handle_key(key) != 0){
            *run = 0;
        }
    }
}

int main(){
    lib54cligc_pixelmap_t pmap;
    FILE* ofd = fopen("log", "w");

    int fps = 60;
    int run = 1;
    int status;
    char keybuf;

    if ((status = lib54cligc_set_logfd(ofd)) != 0){
        printf("an error occoured while setting the logfd %d\n", status);

        return 1;
    }

    if ((status = lib54cligc_init(&pmap)) != 0){
        printf("an error occoured while initializing lib54cligc %d\n", status);

        return 1;
    }

    lib54cligc_color_t color1;
    lib54cligc_color_t color2;

    if ((status = lib54cligc_color_set(&color1, 0, 0, 255)) != 0){
        printf("an error occoured while setting color1 %d\n", status);
        lib54cligc_quit(&pmap);

        return 1;
    }

    if ((status = lib54cligc_color_set(&color2, 255, 255, 255)) != 0){
        printf("an error occoured while setting color2 %d\n", status);
        lib54cligc_quit(&pmap);

        return 1;
    }

    if ((status = lib54cligc_pixel_add_double(&pmap, 20, 20, color1)) != 0){
        printf("an error occoured while adding a pixel %d\n", status);
        lib54cligc_quit(&pmap);

        return 1;
    }

    if ((status = lib54cligc_pixel_add_double(&pmap, 21, 20, color2)) != 0){
        printf("an error occoured while adding a pixel %d\n", status);
        lib54cligc_quit(&pmap);

        return 1;
    }

    while (run){
        draw(&run);
        lib54cligc_update_terminal();

        usleep(1000000 / fps);
    }

    lib54cligc_quit(&pmap);
    fclose(ofd);

    return 0;
}
