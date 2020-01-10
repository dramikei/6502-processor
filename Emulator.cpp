#include <iostream>
#include <tuple>
#include "CPU.h"
#include "Emulator.h"

Emulator::Emulator(CPU *cpu_) {
    std::cout << "Initialising Emulator" << std::endl;
    cpu_ptr = cpu_;
}
void Emulator::emulate() {
    //TODO
    uint8_t *opcode = &cpu_ptr->memory[cpu_ptr->pc];
    std::cout<<opcode[1]<<"\n"; //cout not working?
    // std::cout<<std::get<0>(OPCODE_TABLE[opcode[1]])<<"\n";
    // std::cout<<std::get<1>(OPCODE_TABLE[opcode[1]])<<"\n";
    switch(std::get<0>(OPCODE_TABLE[*opcode])) {
        case ADC: {
            execute_adc(opcode);
            break;
        }
        case AND: {
            execute_and(opcode);
            break;
        }
        case ASL: {
            execute_asl(opcode);
            break;
        }
        case BCC: {
            execute_bcc(opcode);
            break;
        }
        case BCS: {
            execute_bcs(opcode);
            break;
        }
        case BEQ: {
            break;
        }
        case BIT: {
            break;
        }
        case BMI: {
            break;
        }
        case BNE: {
            break;
        }
        case BPL: {
            break;
        }
        case BRK: {
            break;
        }
        case BVC: {
            break;
        }
        case BVS: {
            break;
        }
        case CLC: {
            break;
        }
        case CLD: {
            break;
        }
        case CLI: {
            break;
        }
        case CLV: {
            break;
        }
        case CMP: {
            break;
        }
        case CPX: {
            break;
        }
        case CPY: {
            break;
        }
        case DEC: {
            break;
        }
        case DEX: {
            break;
        }
        case DEY: {
            break;
        }
        case EOR: {
            break;
        }
        case INC: {
            break;
        }
        case INX: {
            break;
        }
        case INY: {
            break;
        }
        case JMP: {
            break;
        }
        case JSR: {
            break;
        }
        case LDA: {
            break;
        }
        case LDX: {
            break;
        }
        case LDY: {
            break;
        }
        case LSR: {
            break;
        }
        case NOP: {
            break;
        }
        case ORA: {
            break;
        }
        case PHA: {
            break;
        }
        case PHP: {
            break;
        }
        case PLA: {
            break;
        }
        case PLP: {
            break;
        }
        case ROL: {
            break;
        }
        case ROR: {
            break;
        }
        case RTI: {
            break;
        }
        case RTS: {
            break;
        }
        case SBC: {
            break;
        }
        case SEC: {
            break;
        }
        case SED: {
            break;
        }
        case SEI: {
            break;
        }
        case STA: {
            break;
        }
        case STX: {
            break;
        }
        case STY: {
            break;
        }
        case TAX: {
            break;
        }
        case TAY: {
            break;
        }
        case TSX: {
            break;
        }
        case TXA: {
            break;
        }
        case TXS: {
            break;
        }
        case TYA: {
            break;
        }
        default:
            std::cout << "Unimplemented opcode";
            exit(1);
    }
    cpu_ptr->pc++;
}

void Emulator::execute_adc(uint8_t *opcode) {
    uint8_t data = dataFromAddressMode(opcode);
    int result = cpu_ptr->a + data + cpu_ptr->c;
    //TODO: call Setflags() function
    cpu_ptr->a = (result&0xff);
}

void Emulator::execute_and(uint8_t *opcode) {
    uint8_t data = dataFromAddressMode(opcode);
    int result = cpu_ptr->a & data;
    //TODO: call Setflags() function
    cpu_ptr->a = (result&0xff);
}

void Emulator::execute_asl(uint8_t *opcode) {
    
}

void Emulator::execute_bcc(uint8_t *opcode) {
    
}

void Emulator::execute_bcs(uint8_t *opcode) {
    
}

uint8_t Emulator::dataFromAddressMode(uint8_t *opcode) {
    uint8_t data;
    switch(fetchAddressingMode(opcode)) {

        case Immediate: {
            data = opcode[1];
            break;
        }
        case Accumulator: {
            data = cpu_ptr->a;
            break;
        }
        case Absolute: {
            data = cpu_ptr->memory[((opcode[2]<<8)|opcode[1])];
            break;
        }
        case AbsoluteX: {
            data = cpu_ptr->memory[((opcode[2]<<8)|opcode[1]) + cpu_ptr->x];
            break;
        }
        case AbsoluteY: {
            data = cpu_ptr->memory[((opcode[2]<<8)|opcode[1]) + cpu_ptr->y];
            break;
        }
        case ZeroPage: {
            if((opcode[1]) > 0xff) {
                std::cout<< "ERROR AT OPCODE: " << *opcode << " ZeroPage address more than 1 byte\n";
                exit(1);
            } else {
                data = cpu_ptr->memory[opcode[1]];
            }
            break;
        }
        case ZeroPageX: {
            if((opcode[1] + cpu_ptr->x) > 0xff) {
                std::cout<< "ERROR AT OPCODE: " << *opcode << " ZeroPage address more than 1 byte\n";
                exit(1);
            } else {
                data = cpu_ptr->memory[opcode[1] + cpu_ptr->x];
            }
            break;
        }
        case ZeroPageY: {
            if((opcode[1] + cpu_ptr->x) > 0xff) {
                std::cout<< "ERROR AT OPCODE: " << *opcode << " ZeroPage address more than 1 byte\n";
                exit(1);
            } else {
                data = cpu_ptr->memory[opcode[1] + cpu_ptr->y];
            }
            break;
        }
        case Indirect: {
            data = cpu_ptr->memory[cpu_ptr->memory[((opcode[2]<<8)|opcode[1])]];
            break;
        }
        case IndirectX: {
            data = cpu_ptr->memory[cpu_ptr->memory[((opcode[2]<<8)|opcode[1])+cpu_ptr->x]];
            break;
        }
        case IndirectY: {
            data = cpu_ptr->memory[cpu_ptr->memory[((opcode[2]<<8)|opcode[1])+cpu_ptr->y]];
            break;
        }
        case Relative: {
            // data = cpu_ptr->memory[cpu_ptr->pc+opcode[1]];
            break;
        }
    }
    return data;
}

Emulator::AddressMode Emulator::fetchAddressingMode(uint8_t *opcode) {
    return std::get<1>(OPCODE_TABLE[opcode[1]]);
}
