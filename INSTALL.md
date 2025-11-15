# INSTALLATION & BUILD GUIDE

## Quick Reference

| Platform | Command |
|----------|---------|
| **Linux** | `bash quickstart-linux.sh` or `make -f Makefile.linux` |
| **macOS** | `brew install gtkmm3 && make -f Makefile.macos` |
| **Windows** | MSYS2: `bash build.sh` |
| **Auto-detect** | `make` (detects OS automatically) |

---

## Detailed Installation

### Linux (Ubuntu/Debian)

```bash
# Install dependencies
sudo apt update
sudo apt install -y g++ make pkg-config libgtkmm-3.0-dev

# Build
make -f Makefile.linux

# Run
./demo1
./demo2
```

### Linux (Fedora/RHEL/CentOS)

```bash
# Install dependencies
sudo dnf install -y gcc-c++ make pkgconfig gtkmm30-devel

# Build
make -f Makefile.linux

# Run
./demo1
./demo2
```

### Linux (Arch/Manjaro)

```bash
# Install dependencies
sudo pacman -S --noconfirm base-devel gtkmm3

# Build
make -f Makefile.linux

# Run
./demo1
./demo2
```

### macOS (Homebrew)

```bash
# Install Homebrew (if not already installed)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install gtkmm3 pkg-config

# Build
make -f Makefile.macos

# Run
./demo1
./demo2
```

### Windows (MSYS2 Required)

1. Install [MSYS2](https://www.msys2.org/)

2. Open MSYS2 MinGW terminal and run:

```bash
# Automatic setup
bash build.sh

# OR manual steps:
pacman -S --noconfirm mingw-w64-x86_64-toolchain mingw-w64-x86_64-gtkmm3 make
make -f Makefile.windows
demo1.exe
demo2.exe
```

---

## Using Auto-Detection Makefile

If you just want to use `make` without specifying a platform:

```bash
# Automatically detects your OS
make

# Clean
make clean
```

This will use:
- `g++` on Linux
- `clang++` on macOS
- `g++` on Windows (MSYS2)

---

## Platform-Specific Makefiles

If auto-detection doesn't work, use platform-specific versions:

- **Makefile.linux** - For all Linux distributions
- **Makefile.macos** - Optimized for macOS with clang++
- **Makefile.windows** - For Windows MSYS2 MinGW

---

## Build Scripts

### Automatic Platform Detection

**Unix/Linux/macOS:**
```bash
bash build.sh
```
Automatically detects your OS and installs dependencies + builds.

**Windows (MSYS2):**
```bash
bash build.sh
# OR
build.bat
```

---

## Troubleshooting

### "pkg-config not found"
Install pkg-config:
- Ubuntu: `sudo apt install pkg-config`
- macOS: `brew install pkg-config`
- Fedora: `sudo dnf install pkgconfig`

### "gtkmm-3.0 not found"
Install GTKmm development files:
- Ubuntu: `sudo apt install libgtkmm-3.0-dev`
- Fedora: `sudo dnf install gtkmm30-devel`
- macOS: `brew install gtkmm3`

### "g++: command not found"
Install build tools:
- Ubuntu: `sudo apt install build-essential`
- Fedora: `sudo dnf install gcc-c++`
- macOS: `xcode-select --install`

### Windows: "make: command not found"
- Must use MSYS2 MinGW terminal (not CMD.exe)
- Install make: `pacman -S make`

### Compilation errors on macOS
```bash
brew reinstall gtkmm3
brew reinstall pkg-config
```

---

## After Building

Both executables are built in the same directory:

```bash
./demo1      # Basic Cairo drawing demo
./demo2      # Interactive domino application
```

To clean up binaries:
```bash
make clean
```

---

## Supported Configurations

✅ **Tested & Working:**
- Ubuntu 20.04 LTS, 22.04 LTS
- Fedora 35+
- Arch Linux
- macOS 10.15+
- Windows 10/11 (MSYS2)

⚠️ **Should Work:**
- Debian 10+
- CentOS 7+
- AlmaLinux 8+
- Other MSYS2 configurations

---

## Next Steps

Once built, run the applications:

1. **demo1** - Display basic Cairo graphics
2. **demo2** - Interactive domino drawing with mouse controls
