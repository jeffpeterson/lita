#!/bin/bash
# Validation script to test copilot environment setup

set -e

echo "=== Lita Copilot Environment Validation ==="
echo ""

echo "1. Checking system dependencies..."
clang --version | head -1
make --version | head -1
pkg-config --version

echo ""
echo "2. Checking project dependencies..."
pkg-config --exists libpcre2-8 && echo "✓ PCRE2 available" || echo "✗ PCRE2 missing"

echo ""
echo "3. Testing compilation of core dependencies..."
echo '#define PCRE2_CODE_UNIT_WIDTH 8' > validation_test.c
echo '#include <stdio.h>' >> validation_test.c
echo '#include <pcre2.h>' >> validation_test.c
echo 'int main() { printf("PCRE2 test successful\\n"); return 0; }' >> validation_test.c

clang -Isrc $(pkg-config --cflags --libs libpcre2-8) validation_test.c -o validation_test
./validation_test
rm -f validation_test validation_test.c

echo ""
echo "4. Testing project build system..."
mkdir -p _build .bin
chmod +x build-linux.sh

# Try to build a few key object files
echo "Building core object files..."
./build-linux.sh _build/lita/common.o
./build-linux.sh _build/lita/pcre2_test.o
./build-linux.sh _build/lita/xxhash_test.o

echo ""
echo "✓ Environment validation completed successfully!"
echo ""
echo "You can now use:"
echo "  ./build-linux.sh          # Build the project"
echo "  ./build-linux.sh clean    # Clean build artifacts"
echo "  make clean                # Alternative clean command"