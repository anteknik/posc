# Win32 C++ ATM 

A simple ATM application for Windows, built using C++ and the native Win32 API.

## Features
- Basic arithmetic operations: Addition, Subtraction, Multiplication, Division.
- Native Windows GUI (no external UI frameworks required).
- Built with CMake and MinGW.

## Prerequisites
- **CMake**: Build system generator.
- **MinGW**: GCC compiler for Windows.

## Build Instructions

1.  Open a terminal in the project directory.
2.  Configure the project with CMake:
    ```bash
    cmake -G "MinGW Makefiles" .
    ```
3.  Build the executable:
    ```bash
    cmake --build .
    ```
    Automated Tests
    Run cmake --build . --clean-first to ensure the build system picks up the new paths.
    
    ```bash
    cmake --build . --clean-first
    ```

## Run Instructions

Run the compiled executable:

```bash
./menu.exe
```

ATM Application window will appear.
