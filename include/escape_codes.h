/** LIB54CLIGC ESCAPE CODE SEQUENCES
 * ------------------------------------------------------
 * SOURCE: https://en.wikipedia.org/wiki/ANSI_escape_code
 * ------------------------------------------------------
**/

#ifndef LIB54CLIGC_ESCAPE_CODES_H
#define LIB54CLIGC_ESCAPE_CODES_H

#define ESC_CONTROL_ETX '\x03' // CTRL + C
#define ESC_CONTROL_BEL '\x07'
#define ESC_CONTROL_BS '\x08'
#define ESC_CONTROL_HT '\x09'
#define ESC_CONTROL_CR '\x0d'
#define ESC_CONTROL_ESC '\x1b'
#define ESC_CSI "\033["
#define ESC_HVP 'f'
#define ESC_SGR 'm'
#define ESC_CUU 'A'
#define ESC_CUD 'B'
#define ESC_CUF 'C'
#define ESC_CUB 'D'
#define ESC_CNL 'E'
#define ESC_CPL 'F'
#define ESC_CHA 'G'
#define ESC_CUP 'H'
#define ESC_ED 'J'
#define ESC_EL 'K'
#define ESC_SU 'S'
#define ESC_SD 'T'
#define ESC_SCP 's'
#define ESC_RCP 's'
#define ESC_CS "?25h" // DECTCEM: Shows the cursor
#define ESC_CH "?25l" // DECTCEM: Hides the cursor
#define ESC_SGR_RESET '0'
#define ESC_SGR_BOLD '1'
#define ESC_SGR_FAINT '2'
#define ESC_SGR_ITALIC '3'
#define ESC_SGR_UNDERLINE '4'
#define ESC_SGR_SLOW_BLINK '5'
#define ESC_SGR_RAPID_BLINK '6'
#define ESC_SGR_INVERT '7'
#define ESC_SGR_CONCEAL '8'
#define ESC_SGR_STRIKE '9'
#define ESC_SGR_FONT_DEFAULT "10"
#define ESC_SGR_FONT_FRAKTUR "20"
#define ESC_SGR_DOUBLE_UNDERLINE "21"
#define ESC_SGR_NORMAL_INTENSITY "22"
#define ESC_SGR_NOT_BLINKING "25"
#define ESC_SGR_COLOR_FG_BLACK "30"
#define ESC_SGR_COLOR_FG_RED "31"
#define ESC_SGR_COLOR_FG_GREEN "32"
#define ESC_SGR_COLOR_FG_YELLOW "33"
#define ESC_SGR_COLOR_FG_BLUE "34"
#define ESC_SGR_COLOR_FG_MAGENTA "35"
#define ESC_SGR_COLOR_FG_CYAN "36"
#define ESC_SGR_COLOR_FG_WHITE "37"
#define ESC_SGR_COLOR_FG_BRIGHT_BLACK "90"
#define ESC_SGR_COLOR_FG_BRIGHT_RED "91"
#define ESC_SGR_COLOR_FG_BRIGHT_GREEN "92"
#define ESC_SGR_COLOR_FG_BRIGHT_YELLOW "93"
#define ESC_SGR_COLOR_FG_BRIGHT_BLUE "94"
#define ESC_SGR_COLOR_FG_BRIGHT_MAGENTA "95"
#define ESC_SGR_COLOR_FG_BRIGHT_CYAN "96"
#define ESC_SGR_COLOR_FG_BRIGHT_WHITE "97"
#define ESC_SGR_COLOR_BG_BLACK "40"
#define ESC_SGR_COLOR_BG_RED "41"
#define ESC_SGR_COLOR_BG_GREEN "42"
#define ESC_SGR_COLOR_BG_YELLOW "43"
#define ESC_SGR_COLOR_BG_BLUE "44"
#define ESC_SGR_COLOR_BG_MAGENTA "45"
#define ESC_SGR_COLOR_BG_CYAN "46"
#define ESC_SGR_COLOR_BG_WHITE "47"
#define ESC_SGR_COLOR_BG_BRIGHT_BLACK "100"
#define ESC_SGR_COLOR_BG_BRIGHT_RED "101"
#define ESC_SGR_COLOR_BG_BRIGHT_GREEN "102"
#define ESC_SGR_COLOR_BG_BRIGHT_YELLOW "103"
#define ESC_SGR_COLOR_BG_BRIGHT_BLUE "104"
#define ESC_SGR_COLOR_BG_BRIGHT_MAGENTA "105"
#define ESC_SGR_COLOR_BG_BRIGHT_CYAN "106"
#define ESC_SGR_COLOR_BG_BRIGHT_WHITE "107"
#define ESC_SGR_COLOR_FG_24_BIT "38;2;"
#define ESC_SGR_COLOR_BG_24_BIT "48;2;"

/** depreciated **/

#define ESCAPE_CODE_CONTROL_LF "\x0a"
#define ESCAPE_CODE_CONTROL_FF "\x0c"

#endif
