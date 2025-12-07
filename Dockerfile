# Simple, stable C development environment
FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y \
        build-essential \
        gdb \
        valgrind \
        cmake \
        ninja-build \
        git \
        vim \
        less \
        curl \
        ca-certificates \
        pkg-config \
    && rm -rf /var/lib/apt/lists/*
RUN useradd -ms /bin/bash dev
USER dev
WORKDIR /home/dev
