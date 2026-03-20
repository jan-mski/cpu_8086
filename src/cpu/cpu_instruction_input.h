namespace cpu::instruction_input
{
    struct InstructionInput
    {
        FILE *stream;
    };

    size_t ReadByte(uint8_t *destination, InstructionInput *instruction_input);
}
