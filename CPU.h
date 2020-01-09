#include <iostream>
#define RAM_SIZE 0xffff

class CPU {
public:
    //Various registers of 6502;
    uint8_t a,x,y;
    uint8_t n,v,b,d,i,z,c; //Processor Status flag bits;
    uint16_t sp;
    uint16_t pc;
    uint8_t memory[RAM_SIZE];


    //Constructor
    CPU();
};