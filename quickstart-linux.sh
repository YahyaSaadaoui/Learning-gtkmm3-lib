#!/bin/bash

# QUICK START GUIDE FOR LINUX

echo "========================================"
echo "GTKmm Domino - Linux Quick Start"
echo "========================================"
echo ""

DISTRO=""

if [ -f /etc/os-release ]; then
    . /etc/os-release
    DISTRO=$ID
fi

echo "Detected: $DISTRO"
echo ""

case "$DISTRO" in
    ubuntu|debian)
        echo "[1/3] Installing dependencies..."
        sudo apt update
        sudo apt install -y g++ make pkg-config libgtkmm-3.0-dev
        ;;
    fedora|rhel|centos)
        echo "[1/3] Installing dependencies..."
        sudo dnf install -y gcc-c++ make pkgconfig gtkmm30-devel
        ;;
    arch|manjaro)
        echo "[1/3] Installing dependencies..."
        sudo pacman -S --noconfirm base-devel gtkmm3
        ;;
    *)
        echo "Unsupported distro. Please install: g++, make, pkg-config, libgtkmm-3.0-dev"
        exit 1
        ;;
esac

echo "[2/3] Building application..."
make -f Makefile.linux

echo "[3/3] Done!"
echo ""
echo "Run demos:"
echo "  ./demo1   - Basic drawing"
echo "  ./demo2   - Interactive domino"
