# Makefile for ANSI Library
# For RC2014/RomWBW systems with CP/M compatibility
# Uses 8.3 filename conventions

# Compiler and tools
ZCC = zcc
TARGET = +cpm
CFLAGS = -SO3 -compiler=sccz80 
LDFLAGS = 
ASM = zcc
ASMFLAGS = +cpm

# Target executables (8.3 names)
TEST_NAME = ansitest

# Source files
C_SOURCES = ansi.c ansitest.c
HEADERS = ansi.h

# Object files
LIB_OBJECTS = ansi.o
TEST_OBJECTS = ansitest.o ansi.o

# Default target - build test program
all: $(TEST_NAME).com
	@echo "Compiled $(TEST_NAME).com successfully"

# Build the test program
$(TEST_NAME).com: $(TEST_OBJECTS)
	$(ZCC) $(TARGET) $(CFLAGS) $(LDFLAGS) -o $@ $(TEST_OBJECTS)

# Build library objects  
ansi.o: ansi.c ansi.h
	$(ZCC) $(TARGET) $(CFLAGS) -c ansi.c -o ansi.o

# Build test objects
ansitest.o: ansitest.c ansi.h
	$(ZCC) $(TARGET) $(CFLAGS) -c ansitest.c -o ansitest.o

# Clean build artifacts
clean:
	rm -f *.o *.com *.map *.lst
	echo "Cleaned build files"

# Library target (for use in other projects)
libansi.a: $(LIB_OBJECTS)
	ar rcs libansi.a $(LIB_OBJECTS)

# Install library headers and lib file
install: libansi.a
	@if [ -n "$(INSTALL_DIR)" ]; then \
		cp ansi.h $(INSTALL_DIR)/; \
		cp libansi.a $(INSTALL_DIR)/; \
		echo "Installed to $(INSTALL_DIR)"; \
	else \
		echo "Set INSTALL_DIR environment variable to install location"; \
	fi

# Test the program (requires RC2014/RomWBW environment)
test: $(TEST_NAME).com
	@echo "Testing $(TEST_NAME).com requires RC2014/RomWBW environment"
	@echo "Copy $(TEST_NAME).com to your RC2014 system and run it"

# Display help
help:
	@echo "ANSI Library - Available targets:"
	@echo "  all      - Build $(TEST_NAME).com (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  libansi.a - Build static library"
	@echo "  install  - Install library to INSTALL_DIR"
	@echo "  test     - Show testing instructions" 
	@echo "  help     - Show this help"
	@echo ""
	@echo "Requirements:"
	@echo "  - z88dk toolchain"
	@echo "  - RC2014 with RomWBW CP/M"
	@echo "  - ANSI-capable terminal"

.PHONY: all clean install test help
