FROM ubuntu:24.04

# Install build tools and dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    git curl \
    clang make lldb \
    libpcre2-dev libreadline-dev \
    # python3 \
    # python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Set workdir
WORKDIR /lita

# Copy the project files
COPY . .

RUN make .bin/lita-test
RUN make .bin/lita-dev

# Default command: run the REPL
CMD ["make"]
