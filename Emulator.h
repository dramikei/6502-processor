class Emulator {
    CPU* cpu_ptr;
    enum AddressMode { accumulator, immediate, zero_page, absolute, indirect, indexed_by_X, indexed_by_Y, relative };
    AddressMode addressMode;
    public:
    Emulator(CPU &cpu_);
    void emulate();
    void setAddressMode(uint8_t addressMode);
};