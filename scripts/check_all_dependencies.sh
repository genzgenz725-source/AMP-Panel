#!/bin/bash

packages=(
    "pipewire"
    "chromium"
    "pipewire-alsa"
    "pipewire-pulse"
    "guitarix"
    "libpipewire"
    "gcc"
)

detect_pm() {
    if command -v pacman &> /dev/null; then
        echo "pacman"
    elif command -v apt &> /dev/null; then
        echo "apt"
    elif command -v dnf &> /dev/null; then
        echo "dnf"
    elif command -v yum &> /dev/null; then
        echo "yum"
    elif command -v zypper &> /dev/null; then
        echo "zypper"
    elif command -v apk &> /dev/null; then
        echo "apk"
    else
        echo "unknown"
    fi
}

check_package() {
    local pkg=$1
    local pm=$2
    
    case $pm in
        pacman)
            pacman -Q "$pkg" &> /dev/null
            ;;
        apt)
            dpkg -l "$pkg" &> /dev/null
            ;;
        dnf|yum)
            rpm -q "$pkg" &> /dev/null
            ;;
        zypper)
            rpm -q "$pkg" &> /dev/null
            ;;
        apk)
            apk info "$pkg" &> /dev/null
            ;;
        *)
            return 1
            ;;
    esac
}

PM=$(detect_pm)

if [ "$PM" = "unknown" ]; then
    echo "cant detect package manager"
    exit 1
fi

echo "========================="

for pkg in "${packages[@]}"; do
    if check_package "$pkg" "$PM"; then
        echo "$pkg - OK"
    else
        echo "$pkg - do not downloaded"
    fi
done

echo "========================="