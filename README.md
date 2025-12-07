# c-dev-environment

Containerized C/C++ development starter with:

- GCC and Clang/LLVM
- CMake + Ninja
- gdb and lldb
- Valgrind
- Clang sanitizers (ASan + UBSan via presets)
- clang-format (1TBS)
- Common CLI tools (git, curl, wget, zip, tree, vim, etc.)

Designed to be cloned per project and used with VS Code Dev Containers.

---

## Prerequisites

On the host (macOS, Linux, or Windows):

- Docker Desktop (or compatible Docker)
- Visual Studio Code
- VS Code extensions:
  - Dev Containers (Remote Containers)
  - C/C++ (`ms-vscode.cpptools`)
  - CMake Tools (`ms-vscode.cmake-tools`)

---

## Getting Started

1. **Use this repo as a template** (or clone it), e.g.:

   ```bash
   git clone <this-repo-url> my-project
   cd my-project


# GCC Debug
cmake --preset=gcc-debug
cmake --build --preset=gcc-debug-build

# GCC Release
cmake --preset=gcc-release
cmake --build --preset=gcc-release-build

# Clang Debug
cmake --preset=clang-debug
cmake --build --preset=clang-debug-build

# Clang Release
cmake --preset=clang-release
cmake --build --preset=clang-release-build

# Clang with ASan + UBSan
cmake --preset=clang-asan-ubsan
cmake --build --preset=clang-asan-ubsan-build
