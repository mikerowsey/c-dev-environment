# **c-dev-environment**

Containerized C/C++ development environment for use with Visual Studio Code Dev Containers.  
Provides a consistent Linux toolchain, debuggers, memory analysis tools, and formatting rules for coursework and systems programming exercises.

This environment supports:

- GCC and Clang/LLVM
- CMake + Ninja
- gdb and lldb
- Valgrind
- Sanitizers (ASan + UBSan)
- clang-format (1TBS)
- vim (for CLI editing)
- Common CLI tools (curl, wget, zip, tree, pkg-config, etc.)
- VS Code-managed dotfiles
- zsh as the default shell

Designed to be cloned per project or reused as a template.

---

## **Prerequisites**

Install the following on your host machine:

- Docker Desktop  
- Visual Studio Code  
- VS Code extensions:
  - **Dev Containers**
  - **C/C++** (`ms-vscode.cpptools`)
  - **CMake Tools** (`ms-vscode.cmake-tools`)

Your host shell (macOS zsh) is not modified.

---

## **Getting Started**

### 1. Clone the starter

```sh
git clone <repo-url> my-project
cd my-project
```

### 2. Open in VS Code

```sh
code .
```

### 3. Reopen in Container

VS Code detects `.devcontainer/devcontainer.json`.

Choose:

> **Reopen in Container**

The environment builds and opens inside an isolated Linux VM.

---

# **Dotfiles Integration (VS Code Managed)**

This environment uses **VS Code’s Dotfiles feature** to apply your personal shell/editor configuration inside the container.  
Your macOS system remains unchanged.

### **Enable dotfiles in VS Code**

1. Open **Command Palette**  
   → `Preferences: Open Settings (JSON)`

2. Add:

```jsonc
"dotfiles.repository": "https://github.com/mikerowsey/dotfiles-basic.git",
"dotfiles.targetPath": "~/.dotfiles-basic",
"dotfiles.installCommand": "./bootstrap.sh"
```

3. Rebuild any container:

- Command Palette → **Dev Containers: Rebuild and Reopen in Container**

VS Code will:

- Clone your dotfiles into the container  
- Run `bootstrap.sh`  
- Apply `.bashrc`, `.zshrc` (if present), `.vimrc`, `.tmux.conf`, `.gitconfig`  

### **Why dotfiles are not baked into the Dockerfile**

- Docker builds are non-interactive  
- Your bootstrap script expects a user shell  
- Any dotfile error would abort the entire image  
- VS Code’s built-in mechanism is safer and automatic  

Using VS Code for dotfiles keeps the container clean and predictable.

---

## **Shell Behavior**

- Default shell inside container: **/usr/bin/zsh**
- User: **vscode**
- Dotfiles applied via VS Code (not Dockerfile)
- `vim`, `tmux`, and your prompt/aliases become available automatically

---

# **CMake Presets**

`CMakePresets.json` provides a consistent build matrix.

### Available Configure Presets

| Compiler | Debug | Release | Sanitizers |
|----------|--------|---------|------------|
| **GCC** | gcc-debug | gcc-release | gcc-asan-ubsan |
| **Clang** | clang-debug | clang-release | clang-asan-ubsan |

### Build Presets

Each configure preset has a corresponding `*-build` preset.

### CLI Usage

```sh
# Configure
cmake --preset=clang-debug

# Build
cmake --build --preset=clang-debug-build
```

Sanitizer builds:

```sh
cmake --preset=clang-asan-ubsan
cmake --build --preset=clang-asan-ubsan-build
```

---

# **Memory Tools**

## **Valgrind**

Run via:

```sh
valgrind ./your_program
```

More detail:

```sh
valgrind --leak-check=full --show-leak-kinds=all ./your_program
```

Detects:

- Leaks  
- Invalid reads/writes  
- Use-after-free  
- Double free  
- Uninitialized memory  
- Heap corruption  

## **Sanitizers (ASan + UBSan)**

Enabled by presets `*-asan-ubsan`.

Compile + run:

```sh
cmake --preset=clang-asan-ubsan
cmake --build --preset=clang-asan-ubsan-build
./build/clang-asan-ubsan/your_program
```

Sanitizers provide fast stack traces for undefined behavior and memory issues.

---

# **Debugging**

Inside the container, after building a Debug preset:

```sh
gdb ./your_program
```

or:

```sh
lldb ./your_program
```

The container is configured with:

```
--cap-add=SYS_PTRACE
--security-opt=seccomp=unconfined
```

So debugging and ptrace operations work normally.

---

# **Formatting**

`.clang-format` uses:

- One True Brace Style (1TBS)
- 4 spaces
- No column limit

VS Code formats automatically on save using **clang-format inside the container**.

---

# **Included Tools**

Installed via Dockerfile:

- gcc / g++
- clang / clang++
- llvm tools
- gdb, lldb
- valgrind
- strace, lsof
- cmake, ninja
- vim
- curl, wget, zip, unzip, tree, pkg-config
- zsh (default shell)

No additional setup on the host is required.

---

# **Typical Workflow**

1. Open project in VS Code  
2. **Reopen in Container**  
3. Choose a CMake preset:
   - `clang-debug` (default choice)
   - `clang-asan-ubsan` (find memory bugs)
4. Edit code in `src/`, headers in `include/`
5. Save → formatted automatically
6. Build:
   ```sh
   cmake --build --preset=clang-debug-build
   ```
7. Debug or analyze memory:
   ```sh
   valgrind ./app
   gdb ./app
   ```

The environment is consistent, isolated, and repeatable.
