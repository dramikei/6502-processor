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
    switch(std::get<0>(OPCODE_TABLE[*opcode])) {
        case ADC: {
            break;
        }
        case ASL: {
            break;
        }
        case BCC: {
            break;
        }
        case BCS: {
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


}
