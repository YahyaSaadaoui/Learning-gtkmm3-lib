# GTKmm Domino Drawing Application

A GTK+ GUI application demonstrating Cairo graphics with interactive domino drawing.

## System Requirements

- C++17 compiler
- GTKmm 3.0 development libraries
- pkg-config
- GNU Make

## Installation by Platform

### Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install -y g++ make pkg-config libgtkmm-3.0-dev
```

Then build with:
```bash
make -f Makefile.linux
```

### Linux (Fedora/RHEL/CentOS)

```bash
sudo dnf install -y gcc-c++ make pkgconfig gtkmm30-devel
```

Then build with:
```bash
make -f Makefile.linux
```

### macOS (Homebrew)

```bash
brew install gtkmm3 pkg-config
```

Then build with:
```bash
make -f Makefile.macos
```

### Windows (MSYS2)

1. Install [MSYS2](https://www.msys2.org/)
2. Open MSYS2 terminal and run:

```bash
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-gtkmm3 make
```

Then build with:
```bash
make -f Makefile.windows
```

## Building

Choose the appropriate Makefile for your system:

```bash
make -f Makefile.linux      # Linux
make -f Makefile.macos      # macOS
make -f Makefile.windows    # Windows (MSYS2)
```

Or use the default Makefile (auto-detects Linux):
```bash
make
```

## Running

After building, run either demo:

```bash
./demo1      # Basic drawing demo
./demo2      # Interactive domino demo
```

## Features

- **demo1**: Basic Cairo drawing demonstrations
  - Lines, rectangles, circles
  - Text rendering
  - Toggle rectangle display

- **demo2**: Interactive domino manipulation
  - Draggable domino piece
  - Click-to-rotate functionality
  - Multiple drawing primitives

## Cleaning Up

Remove compiled binaries:

```bash
make clean
```

## Troubleshooting

### pkg-config not found
Ensure pkg-config is installed for your platform (see Installation section)

### GTKmm development files missing
Install the -dev or -devel package for your distribution

### Compilation errors on macOS
Try: `brew reinstall gtkmm3 --with-dev`

### Windows builds fail
Ensure you're using MSYS2 MinGW terminal, not CMD or PowerShell
