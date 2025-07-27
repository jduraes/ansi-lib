#include "ansi.h"

// Simple putchar implementation for CP/M
int putchar(int c) {
    __asm
        ld c, 2
        ld e, l    ; Parameter is in L, not A
        call 5
    __endasm;
    return c;
}

// Helper function to print a number as decimal
void print_num(int num) {
    if (num >= 10) {
        print_num(num / 10);
    }
    putchar('0' + (num % 10));
}

ansi_capability_t g_ansi_capability = ANSI_UNKNOWN;

// Send ANSI escape code for Device Attributes (DA) and read response
int ansi_test_device_attributes(void) {
    // Send DA escape code: ESC [ c
    putchar(27);  // ESC
    putchar('[');
    putchar('c');
    
    // Implement response reading (stub)
    // Normally, read from serial or input buffer and check for expected response
    return 0;  // Return 0 indicating stub (replace with actual check)
}

// Send ANSI escape code for Cursor Position Report (CPR) and read response
int ansi_test_cursor_position_report(void) {
    // Send CPR escape code: ESC [ 6 n
    putchar(27);  // ESC
    putchar('[');
    putchar('6');
    putchar('n');
    
    // Implement response reading (stub)
    // Normally, read from serial or input buffer and check for expected response
    return 0;  // Return 0 indicating stub (replace with actual check)
}

ansi_capability_t ansi_detect_capability(void) {
    // Try DA detection first
    if (ansi_test_device_attributes() == 0) {
        g_ansi_capability = ANSI_SUPPORTED;
        return g_ansi_capability;
    }
    
    // Fallback to CPR detection
    if (ansi_test_cursor_position_report() == 0) {
        g_ansi_capability = ANSI_SUPPORTED;
        return g_ansi_capability;
    }
    
    // If neither worked, assume not supported
    g_ansi_capability = ANSI_NOT_SUPPORTED;
    return g_ansi_capability;
}

void ansi_clear_screen(void) {
    putchar(27);  // ESC
    putchar('[');
    putchar('2');
    putchar('J');
}

void ansi_home_cursor(void) {
    putchar(27);
    putchar('[');
    putchar('H');
}

void ansi_goto_xy(int x, int y) {
    putchar(27);  // ESC
    putchar('[');
    print_num(y);
    putchar(';');
    print_num(x);
    putchar('H');
}

void ansi_clear_line(void) {
    putchar(27);
    putchar('[');
    putchar('K');
}

void ansi_clear_to_eol(void) {
    putchar(27);
    putchar('[');
    putchar('K');
}

void ansi_set_fg_color(ansi_color_t color) {
    putchar(27);  // ESC
    putchar('[');
    putchar('3');
    putchar('0' + (color % 10));
    putchar('m');
}

void ansi_set_bg_color(ansi_color_t color) {
    putchar(27);  // ESC
    putchar('[');
    putchar('4');
    putchar('0' + (color % 10));
    putchar('m');
}

void ansi_reset_colors(void) {
    putchar(27);  // ESC
    putchar('[');
    putchar('3');
    putchar('9');
    putchar(';');
    putchar('4');
    putchar('9');
    putchar('m');
}

