#include <iostream>
#include "CPU.h"
#include "Emulator.h"

int main(int argc, char **argv) {
    CPU cpu = CPU();
    Emulator emulator = Emulator(cpu);
    while(true) {
        emulator.emulate();
    }
    return 0;
}