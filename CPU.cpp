#include "CPU.h"
#include <iostream>

CPU::CPU() {
    std::cout << "Initialising CPU" << std::endl;
    a=0;
    x=0;
    y=0;
    sp = 0x100;
    pc = 0x0;
};