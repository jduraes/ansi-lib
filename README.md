# ANSI Library for RC2014 / CP/M

A comprehensive ANSI escape sequence library for RC2014 systems running CP/M, designed to add colors, cursor control, and professional interfaces to terminal applications.

## Features

- ✅ **Full Color Support**: 16 colors (8 standard + 8 bright)
- ✅ **Cursor Control**: Positioning, movement, save/restore
- ✅ **Screen Management**: Clear screen, clear line, home cursor
- ✅ **ANSI Detection**: Automatic terminal capability detection
- ✅ **Box Drawing**: Simple ASCII box drawing functions
- ✅ **CP/M Compatible**: Works with ZPM3, CP/M 2.2, and compatible systems

## Version History

- **v0.1.2** - **MAJOR FIX**: Replaced custom putchar with stdio implementation
- **v0.1.1** - Added color fixes and improved test program
- **v0.1.0** - Initial release with basic ANSI functionality

## Quick Start

Include the library in your project:

```c
#include "ansi.h"
#include <stdio.h>  // Required for putchar

int main(void) {
    // Set red text
    ansi_set_fg_color(ANSI_RED);
    printf("Hello in red!\\r\\n");
    
    // Reset colors
    ansi_reset_colors();
    
    // Position cursor and draw a box
    ansi_goto_xy(10, 5);
    printf("+-------+");
    ansi_goto_xy(10, 6);
    printf("| BOX   |");
    ansi_goto_xy(10, 7);
    printf("+-------+");
    
    return 0;
}
```

## Available Colors

```c
// Standard colors (0-7)
ANSI_BLACK, ANSI_RED, ANSI_GREEN, ANSI_YELLOW
ANSI_BLUE, ANSI_MAGENTA, ANSI_CYAN, ANSI_WHITE

// Bright colors (8-15)  
ANSI_BRIGHT_BLACK, ANSI_BRIGHT_RED, ANSI_BRIGHT_GREEN, ANSI_BRIGHT_YELLOW
ANSI_BRIGHT_BLUE, ANSI_BRIGHT_MAGENTA, ANSI_BRIGHT_CYAN, ANSI_BRIGHT_WHITE
```

## Core Functions

### Color Functions
```c
void ansi_set_fg_color(ansi_color_t color);   // Set foreground color
void ansi_set_bg_color(ansi_color_t color);   // Set background color  
void ansi_reset_colors(void);                 // Reset to default colors
```

### Cursor Functions
```c
void ansi_goto_xy(int x, int y);             // Position cursor
void ansi_home_cursor(void);                 // Move to top-left
void ansi_save_cursor(void);                 // Save cursor position
void ansi_restore_cursor(void);              // Restore cursor position
```

### Screen Functions
```c
void ansi_clear_screen(void);                // Clear entire screen
void ansi_clear_line(void);                  // Clear current line
void ansi_clear_to_eol(void);               // Clear to end of line
```

### Detection Functions
```c
ansi_capability_t ansi_detect_capability(void);  // Detect ANSI support
```

## Building

Requires [z88dk](https://github.com/z88dk/z88dk) cross-compiler:

```bash
make                    # Build test program
make clean             # Clean build files
```

This produces `ANSITEST.COM` which demonstrates all library capabilities.

## Terminal Compatibility

Tested and working with:
- **Tera Term** (Windows)
- **PuTTY** (Windows/Linux)  
- **Any VT100/ANSI compatible terminal**

Make sure your terminal is configured for:
- **Terminal Type**: VT100 or VT102
- **Character Set**: ISO 8859-1 or ASCII
- **ANSI Colors**: Enabled

## Technical Notes

- Uses Z88DK's standard `putchar()` from `<stdio.h>`
- Generates standard ANSI escape sequences (ESC[...m)
- No timing dependencies - works on any speed system
- 8.3 filename convention for CP/M compatibility

## Example Output

The test program demonstrates:
- Colored text in RED, GREEN, BLUE, YELLOW
- Cursor positioning and movement
- Screen clearing and box drawing
- All features working together

## Integration

To use in your own projects:
1. Copy `ansi.c` and `ansi.h` to your project
2. Include `#include "ansi.h"` and `#include <stdio.h>`
3. Compile with z88dk: `zcc +cpm -create-app myprogram.c ansi.c`

## License

Open source - feel free to modify and distribute.

---

*Perfect for adding professional color interfaces to RC2014 CP/M applications!*
