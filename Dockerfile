FROM ubuntu:24.04

# Install build tools and dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    clang \
    make \
    git \
    curl \
    libpcre2-dev \
    libreadline-dev \
    # python3 \
    # python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Set workdir
WORKDIR /lita

# Copy the project files
COPY . .

# Build and test
RUN make test

# Default command: run the REPL
CMD ["make", "repl"]
