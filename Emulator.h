class Emulator {
    CPU* cpu_ptr;
    public:
    Emulator(CPU &cpu_);
    void emulate();
};