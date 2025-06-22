#!/bin/bash
# Helper script for building lita with proper Linux library paths

export CFLAGS="-g -Isrc $(pkg-config --cflags libpcre2-8) $(pkg-config --libs libpcre2-8) -lreadline -Wall -Werror -Wno-error=unused-variable -Wno-unused-function -Wno-unused-command-line-argument"

echo "Building lita with Linux-specific configuration..."
echo "CFLAGS: $CFLAGS"
echo ""

exec make "$@"