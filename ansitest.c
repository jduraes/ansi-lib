#include "ansi.h"

// putchar is provided by ansi.c
extern int putchar(int c);

// Simple print functions without stdio
void printStr(char *str) {
    while (*str) {
        putchar(*str++);
    }
}

void printChar(char ch) {
    putchar(ch);
}

void printNum(int num) {
    if (num >= 10) {
        printChar('0' + (num / 10));
    }
    printChar('0' + (num % 10));
}

void waitForKey(void) {
    printStr("Press any key to continue...");
    // Simple wait loop - replace with actual CP/M key input
    int i;
    for (i = 0; i < 50000; i++) {
        // Wait loop
    }
    printStr("\r\n");
}

void testBasicAnsi(void) {
    printStr("\r\n=== Basic ANSI Test ===\r\n");
    
    // Test clear screen
    printStr("Testing clear screen...\r\n");
    waitForKey();
    ansi_clear_screen();
    ansi_home_cursor();
    
    printStr("Screen cleared! Testing colors...\r\n\r\n");
    
    // Test colors
    ansi_set_fg_color(ANSI_RED);
    printStr("RED TEXT ");
    ansi_set_fg_color(ANSI_GREEN);
    printStr("GREEN TEXT ");
    ansi_set_fg_color(ANSI_BLUE);
    printStr("BLUE TEXT ");
    ansi_set_fg_color(ANSI_YELLOW);
    printStr("YELLOW TEXT\r\n");
    ansi_reset_colors();
    
    printStr("\r\nColors reset. ");
}

void testCursorMovement(void) {
    printStr("\r\n=== Cursor Movement Test ===\r\n");
    
    printStr("Moving cursor to position 10,5...\r\n");
    waitForKey();
    
    ansi_goto_xy(10, 5);
    printStr("*** HERE I AM! ***");
    
    ansi_goto_xy(1, 8);
    printStr("Back to left margin, line 8");
    
    ansi_goto_xy(1, 10);
    printStr("Testing cursor movements:");
    
    ansi_goto_xy(5, 11);
    printStr("-> Right 5");
    
    ansi_goto_xy(1, 12);
    printStr("Done with cursor test.");
}

void testBoxDrawing(void) {
    printStr("\r\n=== Box Drawing Test ===\r\n");
    waitForKey();
    
    ansi_clear_screen();
    ansi_home_cursor();
    
    // Draw a simple box using ANSI positioning
    ansi_goto_xy(10, 3);
    printStr("+----------+");
    ansi_goto_xy(10, 4);
    printStr("|   BOX    |");
    ansi_goto_xy(10, 5);
    printStr("|  TEST    |");
    ansi_goto_xy(10, 6);
    printStr("+----------+");
    
    ansi_goto_xy(1, 8);
    printStr("Box drawn using ANSI positioning");
    
    ansi_goto_xy(1, 10);
}

void testAnsiDetection(void) {
    printStr("=== ANSI Detection Test ===\r\n\r\n");
    
    printStr("Current capability: ");
    switch (g_ansi_capability) {
        case ANSI_UNKNOWN:
            printStr("UNKNOWN");
            break;
        case ANSI_NOT_SUPPORTED:
            printStr("NOT SUPPORTED");
            break;
        case ANSI_SUPPORTED:
            printStr("SUPPORTED");
            break;
        case ANSI_FULL_SUPPORT:
            printStr("FULL SUPPORT");
            break;
        default:
            printStr("INVALID");
            break;
    }
    printStr("\r\n\r\n");
    
    printStr("Running detection...\r\n");
    ansi_capability_t result = ansi_detect_capability();
    
    printStr("Detection result: ");
    switch (result) {
        case ANSI_NOT_SUPPORTED:
            printStr("NOT SUPPORTED");
            break;
        case ANSI_SUPPORTED:
            printStr("SUPPORTED");
            break;
        case ANSI_FULL_SUPPORT:
            printStr("FULL SUPPORT");
            break;
        default:
            printStr("UNKNOWN");
            break;
    }
    printStr("\r\n\r\n");
}

int main(void) {
    printStr("ANSI Library Test Program v0.1.1\r\n");
    printStr("For RC2014 with RomWBW CP/M\r\n");
    printStr("==============================\r\n\r\n");
    
    // Test detection first
    testAnsiDetection();
    
    // Only run visual tests if ANSI seems supported
    if (g_ansi_capability >= ANSI_SUPPORTED) {
        printStr("ANSI appears supported - running visual tests...\r\n");
        waitForKey();
        
        testBasicAnsi();
        waitForKey();
        
        testCursorMovement();
        waitForKey();
        
        testBoxDrawing();
        
        printStr("All ANSI tests completed!\r\n");
    } else {
        printStr("ANSI not detected - skipping visual tests\r\n");
        printStr("Your terminal may not support ANSI escape codes.\r\n");
    }
    
    printStr("\r\nTest program finished. Goodbye!\r\n");
    return 0;
}
