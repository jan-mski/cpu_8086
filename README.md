# Intel 8086 Simulator
A simulator of an 8086, implemented as part of Casey Muratori's course on performance-aware programming (https://www.computerenhance.com).

## What is implemented

### Registers
All 16-bit and 8-bit registers are implemented.

**Important:** 8-bit register access is implemented in a way that will only work on little-endian host machines (for simplicity).

### Memory management
Implemented in a simple way with no segmentation, unlike a real 8086.

### Instruction decoding
Almost all instructions, excluding:
- some variants of JMP, CALL, RET/RETF
- locks
- segment register overrides

### Instruction execution
Only the following are implemented: `MOV, ADD, INC, SUB, DEC, CMP, NOT, AND, OR, XOR, TEST, SHL_SAL, SHR, SAR, JNE_JNZ, JMP, PUSH, POP, LEA, CALL, RET` (possibly not all variants).

Check `tests/resources/print_8086.asm` for an example of what can be executed.

### Cycle count estimation
All instructions that can be executed have associated cycle count estimates as per the Intel 8086 manual.

## Build

### Powershell
```Powershell
# Clang:
mkdir build; clang++ -std=c++23 .\src\main.cpp -o .\build\cpu_8086.exe

# Cmake & Ninja:
cmake -B build -G Ninja
cmake --build .\build --target cpu_8086
```

### Bash/zsh
```bash
# Clang:
mkdir build && clang++ -std=c++23 ./src/main.cpp -o ./build/cpu_8086

# GCC:
mkdir build && g++ -std=c++23 ./src/main.cpp -o ./build/cpu_8086

# CMake & Ninja:
cmake -B build -G Ninja
cmake --build ./build --target cpu_8086
```

## Example usage

### Powershell

```Powershell
# Run the print_8086 assembly program
.\build\cpu_8086.exe .\tests\resources\print_8086 `
    --exec `
    --dump-memory `
    --print-final-state `
    --print-execution-trace `
    --print-cycle-count

# Read the memory content
$bytes = [System.IO.File]::ReadAllBytes("memory_dump.data")
[System.Text.Encoding]::ASCII.GetString($bytes[1024..($bytes.Length - 1)]) | Where-Object { $_ -ne 0 }
```

### Bash/zsh
```bash
# Run the print_8086 assembly program
./build/cpu_8086 ./tests/resources/print_8086 \
  --exec \
  --dump-memory \
  --print-final-state \
  --print-execution-trace \
  --print-cycle-count
  
# Read the memory content
tail -c +1024 memory_dump.data
```
