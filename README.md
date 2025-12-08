# c-dev-environment

Containerized C development environment for use with Visual Studio Code Dev Containers.

This template provides a consistent Ubuntu-based toolchain for C coursework, systems programming, and small projects. It standardizes the compiler, build system, debugger, memory tools, and formatting rules so you can focus on the code instead of maintaining a local setup.

---

## What’s Included

Inside the container:

- **Compilers & tools**
  - GCC / G++
  - Clang / LLVM / `clang-tools`
  - CMake + Ninja
- **Debugging & analysis**
  - `gdb`
  - `lldb`
  - `valgrind`
  - Sanitizers (ASan + UBSan via CMake presets)
  - `strace`, `lsof`
- **Editor & CLI**
  - `vim`
  - `tmux`
  - `htop`
  - Standard utilities: `curl`, `wget`, `zip`, `unzip`, `tree`, `pkg-config`, `git`
- **Project wiring**
  - `CMakeLists.txt` with:
    - `PROJECT_NAME_FULL`
    - Library target: `${PROJECT_NAME_FULL}lib`
    - Executable target: `app`
  - `CMakePresets.json` for GCC/Clang in Debug/Release and sanitizer builds
  - Example `src/` and `include/` layout with a small library and main program

Base image: **Ubuntu 24.04**.  
Container user: **`vscode`**.

---

## Prerequisites (Host)

Install on macOS, Linux, or Windows (WSL2):

- Docker Desktop (or system Docker)
- Visual Studio Code
- VS Code extensions:
  - **Dev Containers**
  - **C/C++**
  - **CMake Tools**

Your host shell and dotfiles are not modified.

---

## Getting Started

### 1. Create a New Project from This Template

On GitHub:

1. Click **Use this template → Create a new repository**.
2. Name your project.
3. Clone it:

```bash
git clone <your-new-repo-url> my-c-project
cd my-c-project
```

### 2. Open the Project in VS Code

```bash
code .
```

VS Code will detect the Dev Container configuration.

### 3. Reopen in Container

Use the prompt or run **Dev Containers: Reopen in Container** from the Command Palette.

- VS Code builds the container using `.devcontainer/Dockerfile`.
- Container runs as user `vscode`.
- The post-create bootstrap runs automatically.

---

## Shell & Dotfiles Behavior

### Default Shell

The container uses **`/bin/bash`** as the default shell for the `vscode` user.

### Dotfiles Bootstrap

`postCreateCommand` automatically sets up your development shell:

```jsonc
"postCreateCommand": "set -ex; \
  if [ ! -d \"$HOME/.dotfiles-basic\" ]; then \
    git clone https://github.com/mikerowsey/dotfiles-basic.git \"$HOME/.dotfiles-basic\"; \
  fi; \
  cd \"$HOME/.dotfiles-basic\"; \
  chmod +x bootstrap.sh; \
  ./bootstrap.sh || echo 'bootstrap.sh failed (non-fatal)'; \
  true"
```

This:

1. Clones `dotfiles-basic` into `~/.dotfiles-basic`.
2. Runs `bootstrap.sh`, which symlinks:
   - `.bashrc`
   - `.vimrc`
   - `.tmux.conf`
   - `.gitconfig`

If the script fails, the environment still works.

Dotfiles are container-local—your host system is unchanged.

---

## Project Structure

The template includes a minimal but complete C project structure:

- `src/main.c` – example entry point
- `src/util.c` – example library code
- `include/util.h` – header for library utilities
- `CMakeLists.txt` – builds:
  - `${PROJECT_NAME_FULL}lib`
  - `app`

You can update the project name and targets directly in `CMakeLists.txt`.

---

## CMake Presets

`CMakePresets.json` includes:

### Configure Presets
- `gcc-debug`, `gcc-release`, `gcc-asan-ubsan`
- `clang-debug`, `clang-release`, `clang-asan-ubsan`

### Build Presets
- `gcc-debug-build`, `gcc-release-build`, `gcc-asan-ubsan-build`
- `clang-debug-build`, `clang-release-build`, `clang-asan-ubsan-build`

### Example Workflow

```bash
cmake --preset=clang-debug
cmake --build --preset=clang-debug-build
./build/clang-debug/app
```

Sanitizer workflow:

```bash
cmake --preset=clang-asan-ubsan
cmake --build --preset=clang-asan-ubsan-build
./build/clang-asan-ubsan/app
```

---

## Debugging

The container is configured with:

- `--cap-add=SYS_PTRACE`
- `--security-opt=seccomp=unconfined`

This allows normal use of gdb/lldb.

```bash
gdb ./build/clang-debug/app
# or
lldb ./build/clang-debug/app
```

---

## Memory Tools

### Valgrind

```bash
valgrind ./build/clang-debug/app
```

With detailed leak reporting:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./build/clang-debug/app
```

### Sanitizers (ASan + UBSan)

Enabled via the `*-asan-ubsan` presets.

---

## Formatting

A `.clang-format` file enforces:

- 1TBS brace style
- 4-space indentation
- No hard column limit

VS Code formatting configuration is included in `.devcontainer/devcontainer.json`.

Saving `.c` and `.h` files formats automatically.

---

## Typical Workflow

1. Open the repo in VS Code.
2. Reopen in Container.
3. Let dotfiles bootstrap.
4. Write code in `src/` and `include/`.
5. Save to auto-format.
6. Build with CMake presets.
7. Debug and run memory checks as needed.

This template is designed to be cloned per project or used as a reusable GitHub template for consistent C development environments.

---

