#include <iostream>
#include "CPU.h"
#include "Emulator.h"

int main(int argc, char **argv) {
    CPU cpu = CPU();
    Emulator emulator = Emulator(&cpu);
    cpu.memory[0] = 10;
    cpu.memory[1] = 20;
    while(true) {
        emulator.emulate();
        break; //temperory
    }
    return 0;
}