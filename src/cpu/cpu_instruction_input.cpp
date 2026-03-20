namespace cpu::instruction_input
{
    size_t ReadByte(uint8_t *destination, InstructionInput *instruction_input)
    {
        if (!instruction_input->stream)
        {
            return 0;
        }

        return fread( destination, sizeof(uint8_t), 1, instruction_input->stream);
    }
}
