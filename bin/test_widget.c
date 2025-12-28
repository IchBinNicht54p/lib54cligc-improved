#include <stdio.h>
#include <unistd.h>
#include <lib54cligc_improved/lib54cligc.h>
#include <lib54cligc_improved/graphics_widgets.h>

int main(){
    FILE* ofd = fopen("log", "w");
    
    int status;
    char key;

    lib54cligc_pixelmap_t map;

    if ((status = lib54cligc_set_logfd(ofd)) != LIB54CLIGC_SUCCESS){
        printf("set logfd failed\n");

        return 1;
    }

    if ((status = lib54cligc_init(&map)) != LIB54CLIGC_SUCCESS){
        printf("init failed\n");

        return 1;
    }

    lib54cligc_fps_counter_t counter;

    if ((status = lib54cligc_widget_fps_counter_init(&counter)) != LIB54CLIGC_SUCCESS){
        printf("FPS counter init failed \n");

        return 1;
    }

    while (1){
        lib54cligc_widget_fps_counter_update(&counter);

        status = lib54cligc_poll_key(&key, 1);

        if (status != LIB54CLIGC_POLL_KEY_NO_PRESSED){
            break;
        }

        lib54cligc_clear(&map);

        lib54cligc_widget_fps_counter_display(&map, &counter, 2, 2, 255, 255, 255);

        lib54cligc_update_terminal();
    }

    lib54cligc_quit(&map);
    fclose(ofd);
}
