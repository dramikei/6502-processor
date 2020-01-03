#include <iostream>

class CPU {
public:
    //Various registers of 6502.
    uint8_t a,x,y;
    uint16_t sp;
    uint16_t pc;
    // uint8_t memory[];


    //Constructor
    CPU();
};