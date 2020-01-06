#include <iostream>
#include "CPU.h"
#include "Emulator.h"

Emulator::Emulator(CPU &cpu_) {
    std::cout << "Initialising Emulator" << std::endl;
    cpu_ptr = &cpu_;
}

void Emulator::setAddressMode(uint8_t addressMode) {
    if(addressMode == 0b000000) {
        addressMode = indirect;
    } else if(addressMode == 0b000001) {
        addressMode = zero_page;
    } else if(addressMode == 0b000010) {
        addressMode = immediate;
    } else if(addressMode == 0b000011) {
        addressMode = absolute;
    } else if(addressMode == 0b000100) {
        
    } else if(addressMode == 0b000101) {
        
    } else if(addressMode == 0b000110) {
        
    } else if(addressMode == 0b000111) {
        
    }

}

//addressMode:
// xxx000	(zero page,X)
// xxx001	zero page
// xxx010	#immediate
// xxx011	absolute
// xxx100	(zero page),Y
// xxx101	zero page,X
// xxx110	absolute,Y
// xxx111	absolute,X

void Emulator::emulate() {
    //TODO
    uint8_t *opcode = &cpu_ptr->memory[cpu_ptr->pc];
    uint8_t addressMode = (*opcode&0b00011100)>>2;
    setAddressMode(addressMode);
    switch(*opcode) {

        default:
        std::cout << "Unimplemented opcode";
        exit(1);
    }


}
