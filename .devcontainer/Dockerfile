FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Core toolchain + debuggers + analysis tools + QoL utilities + zsh
RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    clang-tools \
    llvm \
    lldb \
    clang-format \
    cmake \
    ninja-build \
    gdb \
    valgrind \
    strace \
    lsof \
    vim \
    git \
    tmux \
    htop \
    curl \
    wget \
    zip \
    unzip \
    tree \
    pkg-config \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Dev container user with zsh as default shell
RUN useradd -m -s /bin/bash vscode && \
    usermod -aG sudo vscode && \
    echo "vscode ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER vscode
WORKDIR /workspace
