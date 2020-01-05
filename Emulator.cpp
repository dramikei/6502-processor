#include <iostream>
#include "CPU.h"
#include "Emulator.h"

Emulator::Emulator(CPU &cpu_) {
    std::cout << "Initialising Emulator" << std::endl;
    cpu_ptr = &cpu_;
}

void Emulator::emulate() {
    //TODO
}
