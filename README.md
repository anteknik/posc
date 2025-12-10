# Proyek Simulasi ATM

Aplikasi simulasi ATM berbasis Desktop (Win32 API) dengan fitur Login, Menu Interaktif, dan Suara.

## Prasyarat (Prerequisites)

Sebelum memulai, pastikan Anda telah menginstal tools berikut:

1.  **Visual Studio Code**: [Download disini](https://code.visualstudio.com/)
2.  **CMake**: [Download disini](https://cmake.org/download/)
3.  **Compiler C++**:
    *   **Windows**: MinGW-w64 (melalui MSYS2 atau installer standalone)
    *   **Linux**: GCC/G++
4.  **Ekstensi VS Code**:
    *   C/C++ (Microsoft)
    *   CMake Tools (Microsoft)

---

## Panduan Pengaturan (Setup Guide)

### 1. Windows (MinGW/GCC)

1.  **Install MinGW-w64**:
    *   Cara termudah adalah menggunakan MSYS2 ([hype link](https://www.msys2.org/)).
    *   Jalankan terminal MSYS2 dan ketik: `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake make`
2.  **Environment Variables**:
    *   Tambahkan path bin MinGW ke System PATH Windows (contoh: `C:\msys64\mingw64\bin`).
    *   Cek instalasi di terminal (PowerShell/CMD) dengan: `g++ --version` dan `cmake --version`.
3.  **Konfigurasi VS Code**:
    *   Buka folder proyek ini di VS Code.
    *   Install ekstensi **CMake Tools**.
    *   Buka Command Palette (`Ctrl+Shift+P`) -> ketik `CMake: Scan for Kits`.
    *   Pilih kit `GCC` atau `MinGW` yang terdeteksi.

### 2. Linux (Ubuntu/Debian)

1.  **Install Tools**:
    *   Buka terminal dan jalankan:
        ```bash
        sudo apt update
        sudo apt install build-essential cmake
        ```
2.  **Konfigurasi VS Code**:
    *   Buka folder proyek di VS Code.
    *   Install ekstensi **CMake Tools**.
    *   Ekstensi biasanya otomatis mendeteksi GCC sistem. Jika tidak, jalankan `CMake: Scan for Kits`.

---

## Cara Build dan Run

### Menggunakan VS Code (CMake Tools)
1.  Klik tombol **Build** di status bar bawah VS Code (atau `F7`).
2.  Klik tombol **Run/Play** di status bar bawah (atau `Shift+F5`).

### Menggunakan Terminal Manual

1.  Buat folder build:
    ```sh
    cmake -B build -S .
    ```
2.  Compile project:
    ```sh
    cmake --build build
    ```
3.  Jalankan aplikasi:
    *   **Windows**: `.\build\ProyekSaya.exe`
    *   **Linux**: `./build/ProyekSaya` (Catatan: Fitur GUI Win32 hanya bekerja di Windows atau via Wine)

## Struktur Project

*   `src/`: Kode implementasi (.cpp)
*   `library/`: Header files (.h)
*   `CMakeLists.txt`: Konfigurasi build system