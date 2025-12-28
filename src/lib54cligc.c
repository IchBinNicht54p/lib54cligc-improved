#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "escape_codes.h"
#include "lib54cligc.h"

FILE* logfd;

struct termios terminal_flags;
struct termios terminal_flags_new;
struct winsize terminal_size_local;

unsigned short lib54cligc_get_terminal_width(){
    return terminal_size_local.ws_col;
}

unsigned short lib54cligc_get_terminal_height(){
    return terminal_size_local.ws_row;
}

int lib54cligc_color2esc(lib54cligc_color_t color, const char* layer, char* o, size_t os){
    if (!o || os < 1){
        fprintf(logfd, "color: converting (%u, %u, %u) into escape code failed, invalid pointer\n", color.r, color.g, color.b);
        fflush(logfd);

        return LIB54CLIGC_ERROR_INVALID_POINTER;
    }

    snprintf(o, os, "%s%s%u;%u;%um", ESC_CSI, layer, color.r, color.g, color.b);

    return LIB54CLIGC_SUCCESS;
};

int lib54cligc_set_logfd(FILE* fd){
    if (fd == NULL){
        return LIB54CLIGC_ERROR_LOG_FILE;
    }

    logfd = fd;

    return LIB54CLIGC_SUCCESS;
}

int lib54cligc_color_set(lib54cligc_color_t *color, uint8_t r, uint8_t g, uint8_t b){
    if (!logfd){
        return LIB54CLIGC_ERROR_LOG_FILE;
    }

    if (!color){
        fprintf(logfd, "color: init of color (%u, %u, %u) failed, invalid pointer\n", color->r, color->g, color->b);
        fflush(logfd);

        return LIB54CLIGC_ERROR_INVALID_POINTER;
    }

    color->r = r;
    color->g = g;
    color->b = b;

    return LIB54CLIGC_SUCCESS;
}

int lib54cligc_pixel_add(lib54cligc_pixelmap_t* pmap, uint16_t x, uint16_t y, lib54cligc_color_t bg, lib54cligc_color_t fg, char c){
    if (!logfd){
        return LIB54CLIGC_ERROR_LOG_FILE;
    }

    if (!pmap){
        fprintf(logfd, "pixel: failed to add pixel at %d %d, invalid pmap pointer\n", x, y);
        fflush(logfd);

        return LIB54CLIGC_ERROR_INVALID_POINTER;
    }

    if (x == 0 || x > terminal_size_local.ws_col || y == 0 || y > terminal_size_local.ws_row){
        fprintf(logfd, "pixel: failed to add pixel at %d %d, pixel position out of bounds\n", x, y);
        fflush(logfd);

        return LIB54CLIGC_ERROR_PIXEL_OUT_OF_BOUNDS;
    }

    if (pmap->index > UINT16_MAX - 1){
        fprintf(logfd, "pixel: failed to add pixel at %d %d, max pixel index reached %d\n", x, y, pmap->index);
        fflush(logfd);

        return LIB54CLIGC_ERROR_PIXEL_MAP_INDEX;
    }

    pmap->p[pmap->index].x = x;
    pmap->p[pmap->index].y = y;
    pmap->p[pmap->index].b = bg;
    pmap->p[pmap->index].f = fg;
    pmap->index += 1;

    char bg_esc[32];
    char fg_esc[32];
    int status;

    if ((status = lib54cligc_color2esc(bg, ESC_SGR_COLOR_BG_24_BIT, bg_esc, sizeof(bg_esc))) != LIB54CLIGC_SUCCESS){
        fprintf(logfd, "pixel: failed to add pixel at %d %d, color2esc for bg failed\n", x, y);
        fflush(logfd);

        return status;
    }

    if ((status = lib54cligc_color2esc(fg, ESC_SGR_COLOR_FG_24_BIT, fg_esc, sizeof(fg_esc))) != LIB54CLIGC_SUCCESS){
        fprintf(logfd, "pixel: failed to add pixel at %d %d, color2esc for fg failed\n", x, y);
        fflush(logfd);

        return status;
    }

    printf("%s%d;%d%c%s%s%c", ESC_CSI, y, x, ESC_CUP, bg_esc, fg_esc, c);

    return LIB54CLIGC_SUCCESS;
}

int lib54cligc_clear(lib54cligc_pixelmap_t* pmap){
    if (!logfd){
        return LIB54CLIGC_ERROR_LOG_FILE;
    }

    if (!pmap){
        fprintf(logfd, "pixel: failed to clear, invalid pmap pointer\n");
        fflush(logfd);

        return LIB54CLIGC_ERROR_INVALID_POINTER;
    }

    for (int i = 0; i < pmap->index; i++){
        printf("%s%d;%d%c%s%cm ", ESC_CSI, pmap->p[i].y, pmap->p[i].x, ESC_CUP, ESC_CSI, ESC_SGR_RESET);
        printf("%s;%c", ESC_CSI, ESC_CUP);

        pmap->p[i].x = 0;
        pmap->p[i].y = 0;
    }

    pmap->index = 0;

    return LIB54CLIGC_SUCCESS;
}

int lib54cligc_pixel_add_double(lib54cligc_pixelmap_t* pmap, uint16_t x, uint16_t y, lib54cligc_color_t bg){
    if (!logfd){
        return LIB54CLIGC_ERROR_LOG_FILE;
    }

    int status;

    for (int i = 0; i < 2; i++){
        if ((status = lib54cligc_pixel_add(pmap, (x * 2) + i, y, bg, bg, 'O')) != LIB54CLIGC_SUCCESS){
            fprintf(logfd, "pixel: adding double pixel failed, pixel add function returned an error (%d)", status);

            return status;
        }
    }

    return LIB54CLIGC_SUCCESS;
};

int lib54cligc_poll_key(char* k, size_t s){
    ssize_t n = read(STDIN_FILENO, k, s);

    if (n < 1){
        return LIB54CLIGC_POLL_KEY_NO_PRESSED;
    }

    return LIB54CLIGC_SUCCESS;
}

int lib54cligc_init(lib54cligc_pixelmap_t* pmap){
    if (!logfd){
        return LIB54CLIGC_ERROR_LOG_FILE;
    }

    fprintf(logfd, "checking for valid tty...\n");

    int fd = STDIN_FILENO;

    if (!isatty(fd)){
        fprintf(logfd, "warning: STDIN is not a valid tty, using STDOUT\n");

        fd = STDOUT_FILENO;
    }

    fprintf(logfd, "checking terminal size...\n");

    if (ioctl(fd, TIOCGWINSZ, &terminal_size_local) < 0){
        fprintf(logfd, "error: ioctl failed, unable to check terminal size\n");

        return LIB54CLIGC_ERROR_INIT_IOCTL;
    }

    fprintf(logfd, "getting terminal flags\n");

    if (tcgetattr(STDIN_FILENO, &terminal_flags) < 0){
        fprintf(logfd, "error: tcgetattr failed, failed getting terminal flags\n");

        return LIB54CLIGC_ERROR_INIT_TCGETATTR;
    }

    terminal_flags_new = terminal_flags;
    terminal_flags_new.c_lflag &= ~(ICANON | ECHO | ISIG);
    terminal_flags_new.c_iflag &= ~(IXON | ICRNL);
    terminal_flags_new.c_cc[VMIN] = 0;
    terminal_flags_new.c_cc[VTIME] = 0;

    fprintf(logfd, "modified terminal flags, applying new terminal flags...\n");

    if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal_flags_new) < 0){
        fprintf(logfd, "error: failed to apply new terminal flags\n");

        return LIB54CLIGC_ERROR_INIT_TCSETATTR;
    }

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    size_t terminal_pixel_amount = terminal_size_local.ws_col * terminal_size_local.ws_row;
    pmap->p = malloc(terminal_pixel_amount * sizeof(lib54cligc_pixel_t));
    
    if (!pmap->p){
        fprintf(logfd, "error: failed to allocate %ld bytes for pixel map\n", terminal_pixel_amount * sizeof(lib54cligc_pixel_t));

        return LIB54CLIGC_ERROR_INIT_PMAP_ALLOCATION;
    }

    pmap->size = terminal_pixel_amount;
    pmap->index = 0;

    lib54cligc_cursor_hide();

    for (int i = 0; i < terminal_size_local.ws_row; i++){
        printf("\n");
    }

    printf("%s%c", ESC_CSI, ESC_CUP);
    fprintf(logfd, "\n\nlib54cligc has been initialized:\n\nterminal col: %d\nterminal row: %d\npixel map size: %ldB\n\n\n", terminal_size_local.ws_col, terminal_size_local.ws_row, terminal_pixel_amount * sizeof(lib54cligc_pixel_t));

    lib54cligc_update_terminal();
    fflush(logfd);

    return LIB54CLIGC_SUCCESS;
}

void lib54cligc_update_terminal(){
    fflush(stdout);
}

void lib54cligc_cursor_show(){
    printf("%s%s", ESC_CSI, ESC_CS);
    fprintf(logfd, "ansi: showing cursor\n");
}

void lib54cligc_cursor_hide(){
    printf("%s%s", ESC_CSI, ESC_CH);
    fprintf(logfd, "ansi: hiding cursor\n");
}

int lib54cligc_quit(lib54cligc_pixelmap_t* pmap){
    if (!pmap){
        fprintf(logfd, "quit: pmap is invalid when quitting\n");

        return LIB54CLIGC_ERROR_INVALID_POINTER;
    }

    lib54cligc_cursor_show();
    lib54cligc_clear(pmap);

    if (pmap->p){
        free(pmap->p);
    }

    pmap->size = 0;
    pmap->index = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal_flags) < 0){
        fprintf(logfd, "quit: failed to apply old terminal flags\n");

        return LIB54CLIGC_ERROR_INIT_TCSETATTR;
    }

    fprintf(logfd, "\n\nexiting lib54cligc\n");
    fflush(logfd);

    return LIB54CLIGC_SUCCESS;
}
