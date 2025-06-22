#!/bin/bash
# Helper script for building lita with proper Linux library paths

# Override the macOS-specific paths in the original Makefile
export CFLAGS="-g -Isrc $(pkg-config --cflags libpcre2-8) $(pkg-config --libs libpcre2-8) -lreadline -Wall -Werror -Wno-error=unused-variable -Wno-unused-function -Wno-unused-command-line-argument"

echo "Building lita with Linux-specific configuration..."
echo "CFLAGS: $CFLAGS"
echo ""

# Check if readline is available, warn if not
if ! pkg-config --exists readline 2>/dev/null && ! ls /usr/lib/*/libreadline.* >/dev/null 2>&1; then
    echo "Warning: readline library may not be available. Some features may not work."
    echo "Install with: sudo apt-get install libreadline-dev"
    echo ""
fi

exec make "$@"