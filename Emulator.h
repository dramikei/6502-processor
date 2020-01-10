#include <vector>
#include <array>
#include <tuple>
class Emulator {
    CPU* cpu_ptr;
    enum Operation {
        ADC, AND, ASL, BCC,
        BCS, BEQ, BIT, BMI,
        BNE, BPL, BRK, BVC,
        BVS, CLC, CLD, CLI,
        CLV, CMP, CPX, CPY,
        DEC, DEX, DEY, EOR,
        INC, INX, INY, JMP,
        JSR, LDA, LDX, LDY,
        LSR, NOP, ORA, PHA,
        PHP, PLA, PLP, ROL,
        ROR, RTI, RTS, SBC,
        SEC, SED, SEI, STA,
        STX, STY, TAX, TAY,
        TSX, TXA, TXS, TYA,
        // "Extra" opcodes
        KIL,ISC,DCP,AXS,
        LAS,LAX,AHX,SAX,
        XAA,SHX,RRA,TAS,
        SHY,ARR,SRE,ALR,
        RLA,ANC,SLO,
    };

    //indexed indirect mode == IndirectX
    //indirect indexed addressing == IndirectY
    enum AddressMode {
        Immediate,
        ZeroPage,ZeroPageX,ZeroPageY,
        Absolute,AbsoluteX,AbsoluteY,
        Indirect,IndirectX,IndirectY,
        Relative,
        Accumulator,
        Implicit,
    };

    const AddressMode abs = Absolute;
    const AddressMode acc = Accumulator;
    const AddressMode imm = Immediate;
    const AddressMode imp = Implicit;
    const AddressMode izx = IndirectX;
    const AddressMode izy = IndirectY;
    const AddressMode zp  = ZeroPage;
    const AddressMode zpx = ZeroPageX;
    const AddressMode zpy = ZeroPageY;
    const AddressMode rel = Relative;
    const AddressMode abx = AbsoluteX;
    const AddressMode aby = AbsoluteY;
    const AddressMode ind = Indirect;
    
    std::array<std::tuple<Operation,AddressMode,uint8_t,uint8_t>, 256> OPCODE_TABLE = {
        std::make_tuple(BRK, imp, 7, 0), // x0
        std::make_tuple(ORA, izx, 6, 0), // x1
        std::make_tuple(KIL, imp, 0, 0), // x2
        std::make_tuple(SLO, izx, 8, 0), // x3
        std::make_tuple(NOP, zp,  3, 0), // x4
        std::make_tuple(ORA, zp,  3, 0), // x5
        std::make_tuple(ASL, zp,  5, 0), // x6
        std::make_tuple(SLO, zp,  5, 0), // x7
        std::make_tuple(PHP, imp, 3, 0), // x8
        std::make_tuple(ORA, imm, 2, 0), // x9
        std::make_tuple(ASL, acc, 2, 0), // xA
        std::make_tuple(ANC, imm, 2, 0), // xB
        std::make_tuple(NOP, abs, 4, 0), // xC
        std::make_tuple(ORA, abs, 4, 0), // xD
        std::make_tuple(ASL, abs, 6, 0), // xE
        std::make_tuple(SLO, abs, 6, 0), // xF
        // 1x
        std::make_tuple(BPL, rel, 2, 1), // x0
        std::make_tuple(ORA, izy, 5, 1), // x1
        std::make_tuple(KIL, imp, 0, 0), // x2
        std::make_tuple(SLO, izy, 8, 0), // x3
        std::make_tuple(NOP, zpx, 4, 0), // x4
        std::make_tuple(ORA, zpx, 4, 0), // x5
        std::make_tuple(ASL, zpx, 6, 0), // x6
        std::make_tuple(SLO, zpx, 6, 0), // x7
        std::make_tuple(CLC, imp, 2, 0), // x8
        std::make_tuple(ORA, aby, 4, 1), // x9
        std::make_tuple(NOP, imp, 2, 0), // xA
        std::make_tuple(SLO, aby, 7, 0), // xB
        std::make_tuple(NOP, abx, 4, 1), // xC
        std::make_tuple(ORA, abx, 4, 1), // xD
        std::make_tuple(ASL, abx, 7, 0), // xE
        std::make_tuple(SLO, abx, 7, 0), // xF
        // 2x
        std::make_tuple(JSR, abs, 6, 0), // x0
        std::make_tuple(AND, izx, 6, 0), // x1
        std::make_tuple(KIL, imp, 0, 0), // x2
        std::make_tuple(RLA, izx, 8, 0), // x3
        std::make_tuple(BIT, zp,  3, 0), // x4
        std::make_tuple(AND, zp,  3, 0), // x5
        std::make_tuple(ROL, zp,  5, 0), // x6
        std::make_tuple(RLA, zp,  5, 0), // x7
        std::make_tuple(PLP, imp, 4, 0), // x8
        std::make_tuple(AND, imm, 2, 0), // x9
        std::make_tuple(ROL, acc, 2, 0), // xA
        std::make_tuple(ANC, imm, 2, 0), // xB
        std::make_tuple(BIT, abs, 4, 0), // xC
        std::make_tuple(AND, abs, 4, 0), // xD
        std::make_tuple(ROL, abs, 6, 0), // xE
        std::make_tuple(RLA, abs, 6, 0), // xF
        // 3x
        std::make_tuple(BMI, rel, 2, 1), // x0
        std::make_tuple(AND, izy, 5, 1), // x1
        std::make_tuple(KIL, imp, 0, 0), // x2
        std::make_tuple(RLA, izy, 8, 0), // x3
        std::make_tuple(NOP, zpx, 4, 0), // x4
        std::make_tuple(AND, zpx, 4, 0), // x5
        std::make_tuple(ROL, zpx, 6, 0), // x6
        std::make_tuple(RLA, zpx, 6, 0), // x7
        std::make_tuple(SEC, imp, 2, 0), // x8
        std::make_tuple(AND, aby, 4, 1), // x9
        std::make_tuple(NOP, imp, 2, 0), // xA
        std::make_tuple(RLA, aby, 7, 0), // xB
        std::make_tuple(NOP, abx, 4, 1), // xC
        std::make_tuple(AND, abx, 4, 1), // xD
        std::make_tuple(ROL, abx, 7, 0), // xE
        std::make_tuple(RLA, abx, 7, 0), // xF
        // 4x
        std::make_tuple(RTI, imp, 6, 0), // x0
        std::make_tuple(EOR, izx, 6, 0), // x1
        std::make_tuple(KIL, imp, 0, 0), // x2
        std::make_tuple(SRE, izx, 8, 0), // x3
        std::make_tuple(NOP, zp,  3, 0), // x4
        std::make_tuple(EOR, zp,  3, 0), // x5
        std::make_tuple(LSR, zp,  5, 0), // x6
        std::make_tuple(SRE, zp,  5, 0), // x7
        std::make_tuple(PHA, imp, 3, 0), // x8
        std::make_tuple(EOR, imm, 2, 0), // x9
        std::make_tuple(LSR, imp, 2, 0), // xA
        std::make_tuple(ALR, imm, 2, 0), // xB
        std::make_tuple(JMP, abs, 3, 0), // xC
        std::make_tuple(EOR, abs, 4, 0), // xD
        std::make_tuple(LSR, abs, 6, 0), // xE
        std::make_tuple(SRE, abs, 6, 0), // xF
        // 5x
        std::make_tuple(BVC, rel, 2, 1), // x0
        std::make_tuple(EOR, izy, 5, 1), // x1
        std::make_tuple(KIL, imp, 0, 0), // x2
        std::make_tuple(SRE, izy, 8, 0), // x3
        std::make_tuple(NOP, zpx, 4, 0), // x4
        std::make_tuple(EOR, zpx, 4, 0), // x5
        std::make_tuple(LSR, zpx, 6, 0), // x6
        std::make_tuple(SRE, zpx, 6, 0), // x7
        std::make_tuple(CLI, imp, 2, 0), // x8
        std::make_tuple(EOR, aby, 4, 1), // x9
        std::make_tuple(NOP, imp, 2, 0), // xA
        std::make_tuple(SRE, aby, 7, 0), // xB
        std::make_tuple(NOP, abx, 4, 1), // xC
        std::make_tuple(EOR, abx, 4, 1), // xD
        std::make_tuple(LSR, abx, 7, 0), // xE
        std::make_tuple(SRE, abx, 7, 0), // xF
        // 6x
        std::make_tuple(RTS, imp, 6, 0), // x0
        std::make_tuple(ADC, izx, 6, 0), // x1
        std::make_tuple(KIL, imp, 0, 0), // x2
        std::make_tuple(RRA, izx, 8, 0), // x3
        std::make_tuple(NOP, zp,  3, 0), // x4
        std::make_tuple(ADC, zp,  3, 0), // x5
        std::make_tuple(ROR, zp,  5, 0), // x6
        std::make_tuple(RRA, zp,  5, 0), // x7
        std::make_tuple(PLA, imp, 4, 0), // x8
        std::make_tuple(ADC, imm, 2, 0), // x9
        std::make_tuple(ROR, imp, 2, 0), // xA
        std::make_tuple(ARR, imm, 2, 0), // xB
        std::make_tuple(JMP, ind, 5, 0), // xC
        std::make_tuple(ADC, abs, 4, 0), // xD
        std::make_tuple(ROR, abs, 6, 0), // xE
        std::make_tuple(RRA, abs, 6, 0), // xF
        // 7x
        std::make_tuple(BVS, rel, 2, 1), // x0
        std::make_tuple(ADC, izy, 5, 1), // x1
        std::make_tuple(KIL, imp, 0, 0), // x2
        std::make_tuple(RRA, izy, 8, 0), // x3
        std::make_tuple(NOP, zpx, 4, 0), // x4
        std::make_tuple(ADC, zpx, 4, 0), // x5
        std::make_tuple(ROR, zpx, 6, 0), // x6
        std::make_tuple(RRA, zpx, 6, 0), // x7
        std::make_tuple(SEI, imp, 2, 0), // x8
        std::make_tuple(ADC, aby, 4, 1), // x9
        std::make_tuple(NOP, imp, 2, 0), // xA
        std::make_tuple(RRA, aby, 7, 0), // xB
        std::make_tuple(NOP, abx, 4, 1), // xC
        std::make_tuple(ADC, abx, 4, 1), // xD
        std::make_tuple(ROR, abx, 7, 0), // xE
        std::make_tuple(RRA, abx, 7, 0), // xF
        // 8x
        std::make_tuple(NOP, imm, 2, 0), // x0
        std::make_tuple(STA, izx, 6, 0), // x1
        std::make_tuple(NOP, imm, 2, 0), // x2
        std::make_tuple(SAX, izx, 6, 0), // x3
        std::make_tuple(STY, zp,  3, 0), // x4
        std::make_tuple(STA, zp,  3, 0), // x5
        std::make_tuple(STX, zp,  3, 0), // x6
        std::make_tuple(SAX, zp,  3, 0), // x7
        std::make_tuple(DEY, imp, 2, 0), // x8
        std::make_tuple(NOP, imm, 2, 0), // x9
        std::make_tuple(TXA, imp, 2, 0), // xA
        std::make_tuple(XAA, imm, 2, 1), // xB
        std::make_tuple(STY, abs, 4, 0), // xC
        std::make_tuple(STA, abs, 4, 0), // xD
        std::make_tuple(STX, abs, 4, 0), // xE
        std::make_tuple(SAX, abs, 4, 0), // xF
        // 9x
        std::make_tuple(BCC, rel, 2, 1), // x0
        std::make_tuple(STA, izy, 6, 0), // x1
        std::make_tuple(KIL, imp, 0, 0), // x2
        std::make_tuple(AHX, izy, 6, 0), // x3
        std::make_tuple(STY, zpx, 4, 0), // x4
        std::make_tuple(STA, zpx, 4, 0), // x5
       std::make_tuple (STX, zpy, 4, 0), // x6
        std::make_tuple(SAX, zpy, 4, 0), // x7
        std::make_tuple(TYA, imp, 2, 0), // x8
        std::make_tuple(STA, aby, 5, 0), // x9
        std::make_tuple(TXS, imp, 2, 0), // xA
        std::make_tuple(TAS, aby, 5, 0), // xB
        std::make_tuple(SHY, abx, 5, 0), // xC
        std::make_tuple(STA, abx, 5, 0), // xD
        std::make_tuple(SHX, aby, 5, 0), // xE
        std::make_tuple(AHX, aby, 5, 0), // xF
        // Ax
        std::make_tuple(LDY, imm, 2, 0), // x0
        std::make_tuple(LDA, izx, 6, 0), // x1
        std::make_tuple(LDX, imm, 2, 0), // x2
        std::make_tuple(LAX, izx, 6, 0), // x3
        std::make_tuple(LDY, zp,  3, 0), // x4
        std::make_tuple(LDA, zp,  3, 0), // x5
        std::make_tuple(LDX, zp,  3, 0), // x6
        std::make_tuple(LAX, zp,  3, 0), // x7
        std::make_tuple(TAY, imp, 2, 0), // x8
        std::make_tuple(LDA, imm, 2, 0), // x9
        std::make_tuple(TAX, imp, 2, 0), // xA
        std::make_tuple(LAX, imm, 2, 0), // xB
        std::make_tuple(LDY, abs, 4, 0), // xC
        std::make_tuple(LDA, abs, 4, 0), // xD
        std::make_tuple(LDX, abs, 4, 0), // xE
        std::make_tuple(LAX, abs, 4, 0), // xF
        // Bx
        std::make_tuple(BCS, rel, 2, 1), // x0
        std::make_tuple(LDA, izy, 5, 1), // x1
        std::make_tuple(KIL, imp, 0, 0), // x2
        std::make_tuple(LAX, izy, 5, 1), // x3
        std::make_tuple(LDY, zpx, 4, 0), // x4
        std::make_tuple(LDA, zpx, 4, 0), // x5
        std::make_tuple(LDX, zpy, 4, 0), // x6
        std::make_tuple(LAX, zpy, 4, 0), // x7
        std::make_tuple(CLV, imp, 2, 0), // x8
        std::make_tuple(LDA, aby, 4, 1), // x9
        std::make_tuple(TSX, imp, 2, 0), // xA
        std::make_tuple(LAS, aby, 4, 1), // xB
        std::make_tuple(LDY, abx, 4, 1), // xC
        std::make_tuple(LDA, abx, 4, 1), // xD
        std::make_tuple(LDX, aby, 4, 1), // xE
        std::make_tuple(LAX, aby, 4, 1), // xF
        // Cx
        std::make_tuple(CPY, imm, 2, 0), // x0
        std::make_tuple(CMP, izx, 6, 0), // x1
        std::make_tuple(NOP, imm, 2, 0), // x2
        std::make_tuple(DCP, izx, 8, 0), // x3
        std::make_tuple(CPY, zp,  3, 0), // x4
        std::make_tuple(CMP, zp,  3, 0), // x5
        std::make_tuple(DEC, zp,  5, 0), // x6
        std::make_tuple(DCP, zp,  5, 0), // x7
        std::make_tuple(INY, imp, 2, 0), // x8
        std::make_tuple(CMP, imm, 2, 0), // x9
        std::make_tuple(DEX, imp, 2, 0), // xA
        std::make_tuple(AXS, imm, 2, 0), // xB
        std::make_tuple(CPY, abs, 4, 0), // xC
        std::make_tuple(CMP, abs, 4, 0), // xD
        std::make_tuple(DEC, abs, 6, 0), // xE
        std::make_tuple(DCP, abs, 6, 0), // xF
        // Dx
        std::make_tuple(BNE, rel, 2, 1), // x0
        std::make_tuple(CMP, izy, 5, 1), // x1
        std::make_tuple(KIL, imp, 0, 0), // x2
        std::make_tuple(DCP, izy, 8, 0), // x3
        std::make_tuple(NOP, zpx, 4, 0), // x4
        std::make_tuple(CMP, zpx, 4, 0), // x5
        std::make_tuple(DEC, zpx, 6, 0), // x6
        std::make_tuple(DCP, zpx, 6, 0), // x7
        std::make_tuple(CLD, imp, 2, 0), // x8
        std::make_tuple(CMP, aby, 4, 1), // x9
        std::make_tuple(NOP, imp, 2, 0), // xA
        std::make_tuple(DCP, aby, 7, 0), // xB
        std::make_tuple(NOP, abx, 4, 1), // xC
        std::make_tuple(CMP, abx, 4, 1), // xD
        std::make_tuple(DEC, abx, 7, 0), // xE
        std::make_tuple(DCP, abx, 7, 0), // xF
        // Ex
        std::make_tuple(CPX, imm, 2, 0), // x0
        std::make_tuple(SBC, izx, 6, 0), // x1
        std::make_tuple(NOP, imm, 2, 0), // x2
        std::make_tuple(ISC, izx, 8, 0), // x3
        std::make_tuple(CPX, zp,  3, 0), // x4
        std::make_tuple(SBC, zp,  3, 0), // x5
        std::make_tuple(INC, zp,  5, 0), // x6
        std::make_tuple(ISC, zp,  5, 0), // x7
        std::make_tuple(INX, imp, 2, 0), // x8
        std::make_tuple(SBC, imm, 2, 0), // x9
        std::make_tuple(NOP, imp, 2, 0), // xA
        std::make_tuple(SBC, imm, 2, 0), // xB
        std::make_tuple(CPX, abs, 4, 0), // xC
        std::make_tuple(SBC, abs, 4, 0), // xD
        std::make_tuple(INC, abs, 6, 0), // xE
        std::make_tuple(ISC, abs, 6, 0), // xF
        // Fx
        std::make_tuple(BEQ, rel, 2, 1), // x0
        std::make_tuple(SBC, izy, 5, 1), // x1
        std::make_tuple(KIL, imp, 0, 0), // x2
        std::make_tuple(ISC, izy, 8, 0), // x3
        std::make_tuple(NOP, zpx, 4, 0), // x4
        std::make_tuple(SBC, zpx, 4, 0), // x5
        std::make_tuple(INC, zpx, 6, 0), // x6
        std::make_tuple(ISC, zpx, 6, 0), // x7
        std::make_tuple(SED, imp, 2, 0), // x8
        std::make_tuple(SBC, aby, 4, 1), // x9
        std::make_tuple(NOP, imp, 2, 0), // xA
        std::make_tuple(ISC, aby, 7, 0), // xB
        std::make_tuple(NOP, abx, 4, 1), // xC
        std::make_tuple(SBC, abx, 4, 1), // xD
        std::make_tuple(INC, abx, 7, 0), // xE
        std::make_tuple(ISC, abx, 7, 0), // xF
        };
    AddressMode addressMode;
    public:
    Emulator(CPU *cpu_);
    void emulate();
    void execute_adc(uint8_t *opcode);
    void execute_and(uint8_t *opcode);
    void execute_asl(uint8_t *opcode);
    void execute_bcs(uint8_t *opcode);
    void execute_bcc(uint8_t *opcode);
    AddressMode fetchAddressingMode(uint8_t *opcode);
    uint8_t dataFromAddressMode(uint8_t *opcode)
};