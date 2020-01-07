#include <iostream>
#include <tuple>
#include "CPU.h"
#include "Emulator.h"

Emulator::Emulator(CPU &cpu_) {
    std::cout << "Initialising Emulator" << std::endl;
    cpu_ptr = &cpu_;
}
void Emulator::emulate() {
    //TODO
    uint8_t *opcode = &cpu_ptr->memory[cpu_ptr->pc];
    // std::cout << std::get<0>(OPCODE_TABLE[0])<<std::endl;
    switch(*opcode) {

        default:
        std::cout << "Unimplemented opcode";
        exit(1);
    }


}
