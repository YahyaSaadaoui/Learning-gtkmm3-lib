#!/bin/bash

# Cross-platform build setup script for GTKmm Domino Application

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${YELLOW}GTKmm Domino Application - Setup${NC}"
echo "=================================="

OS_TYPE=$(uname -s)

case "$OS_TYPE" in
    Linux*)
        echo -e "${GREEN}Linux detected${NC}"
        
        if command -v apt &> /dev/null; then
            echo -e "${YELLOW}Debian/Ubuntu system detected${NC}"
            echo "Installing dependencies..."
            sudo apt update
            sudo apt install -y g++ make pkg-config libgtkmm-3.0-dev
            echo -e "${GREEN}Dependencies installed${NC}"
            echo "Building with: make -f Makefile.linux"
            make -f Makefile.linux
            
        elif command -v dnf &> /dev/null; then
            echo -e "${YELLOW}Fedora/RHEL system detected${NC}"
            echo "Installing dependencies..."
            sudo dnf install -y gcc-c++ make pkgconfig gtkmm30-devel
            echo -e "${GREEN}Dependencies installed${NC}"
            echo "Building with: make -f Makefile.linux"
            make -f Makefile.linux
            
        elif command -v pacman &> /dev/null; then
            echo -e "${YELLOW}Arch Linux system detected${NC}"
            echo "Installing dependencies..."
            sudo pacman -S --noconfirm base-devel gtkmm3
            echo -e "${GREEN}Dependencies installed${NC}"
            echo "Building with: make -f Makefile.linux"
            make -f Makefile.linux
        else
            echo -e "${RED}Unknown Linux distribution${NC}"
            echo "Please install: g++, make, pkg-config, libgtkmm-3.0-dev"
            exit 1
        fi
        ;;
        
    Darwin*)
        echo -e "${GREEN}macOS detected${NC}"
        
        if ! command -v brew &> /dev/null; then
            echo -e "${RED}Homebrew not found. Install from: https://brew.sh${NC}"
            exit 1
        fi
        
        echo "Installing dependencies with Homebrew..."
        brew install gtkmm3 pkg-config
        echo -e "${GREEN}Dependencies installed${NC}"
        echo "Building with: make -f Makefile.macos"
        make -f Makefile.macos
        ;;
        
    MINGW*|MSYS*)
        echo -e "${GREEN}Windows (MSYS2) detected${NC}"
        echo "Installing dependencies..."
        pacman -S --noconfirm mingw-w64-x86_64-toolchain mingw-w64-x86_64-gtkmm3
        echo -e "${GREEN}Dependencies installed${NC}"
        echo "Building with: make -f Makefile.windows"
        make -f Makefile.windows
        ;;
        
    *)
        echo -e "${RED}Unsupported operating system: $OS_TYPE${NC}"
        exit 1
        ;;
esac

echo -e "${GREEN}Build complete!${NC}"
echo "Run:"
echo "  ./demo1   - for basic drawing demo"
echo "  ./demo2   - for interactive domino demo"
