# Base image using Ubuntu 20.04 LTS for long-term support
FROM ubuntu:20.04

# Set the non-interactive timezone to avoid geographical queries during setup
ENV DEBIAN_FRONTEND=noninteractive

# Install essential packages including the build essential for C/C++ (GCC, G++, Make),
# GDB for debugging, and common utilities like git.

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    gdb \
    git \
    cmake \
    tree \
    nano \
    locales \
    vim && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Set the locale to avoid any locale issues during the build
RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8


# Create a non-root user 'devuser' with sudo access for Yocto builds
RUN useradd -m devuser && \
    echo "devuser:devuser" | chpasswd && \
    usermod -aG sudo devuser

# Set the default working directory where your C/C++ project would reside
WORKDIR /workspace

# Switch to your non-root user to avoid using root for builds
USER devuser

# Default command to keep the container running
CMD ["/bin/bash"]
