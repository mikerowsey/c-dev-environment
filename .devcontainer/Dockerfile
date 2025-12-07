FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \        # gcc, g++, make, etc.
    clang-format \           # formatter only
    cmake \
    ninja-build \
    gdb \
    git \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Dev container user expected by VS Code
RUN useradd -m vscode && \
    usermod -aG sudo vscode && \
    echo "vscode ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER vscode
WORKDIR /workspace
