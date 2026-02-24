#define _CRT_SECURE_NO_WARNINGS

const char *REGISTER_NAMES[] = {
    0,
    "al",
    "ah",
    "ax",
    "bl",
    "bh",
    "bx",
    "cl",
    "ch",
    "cx",
    "dl",
    "dh",
    "dx",
    "sp",
    "bp",
    "si",
    "di"
};

const char *MNEMONIC_STRINGS[] = {
    0,
    "mov",
    "add",
    "sub",
    "cmp",
    "jo",
    "jno",
    "jb",
    "jnb",
    "je",
    "jne",
    "jbe",
    "jnbe",
    "js",
    "jns",
    "jp",
    "jnp",
    "jl",
    "jnl",
    "jle",
    "jnle",
    "loopnz",
    "loopz",
    "loop",
    "jcxz"
};

const char *GetRegisterName(Register register_)
{
    static_assert(REGISTER_COUNT == ARRAY_SIZE(REGISTER_NAMES), "REGISTER_COUNT and size of REGISTER_NAMES must be equal");
    return REGISTER_NAMES[register_];
}

const char *GetMnemonicString(Mnemonic mnemonic)
{
    static_assert(MNEMONIC_COUNT == ARRAY_SIZE(MNEMONIC_STRINGS), "MNEMONIC_COUNT and size of MNEMONIC_NAMES must be equal");
    return MNEMONIC_STRINGS[mnemonic];
}

void PrintInstructionString(FILE *output_stream, DecodingContext *decoding_context)
{
    fprintf(output_stream, "%s", GetMnemonicString(decoding_context->mnemonic));

    for (size_t operand_idx = 0; operand_idx < ARRAY_SIZE(decoding_context->operands); ++operand_idx)
    {
        Operand *operand = &decoding_context->operands[operand_idx];
        fprintf(output_stream, operand_idx == 0 ? " " : ", ");

        switch (operand->type)
        {
            case OPERAND_NONE:
            {
                break;
            } break;
            case OPERAND_REGISTER:
            {
                fprintf(output_stream, "%s", GetRegisterName(operand->register_));
            } break;
            case OPERAND_MEMORY_ADDRESS:
            {
                MemoryAddress *memory_address = &operand->memory_address;
                if (memory_address->qualifier)
                {
                    fprintf(output_stream, "%s", memory_address->qualifier);
                }
                if (memory_address->direct)
                {
                    fprintf(output_stream, "[%i]", memory_address->displacement);
                }
                else
                {
                    for (size_t register_idx = 0; register_idx < REGISTER_NAMES_MAX_LEN; ++register_idx)
                    {
                        const char *register_name = GetRegisterName(memory_address->registers[register_idx]);
                        if (!register_name)
                        {
                            break;
                        }
                        fprintf(output_stream, register_idx == 0 ? "[%s" : " + %s", register_name);
                    }
                    fprintf(output_stream, " + %i]", memory_address->displacement);
                }
            } break;
            case OPERAND_IMMEDIATE:
            {
                fprintf(output_stream, "%u", operand->immediate_value);
            } break;
            case OPERAND_LABEL_LIKE_DISPLACEMENT:
            {
                fprintf(output_stream, "($+2) + %i", operand->label_like_displacement);
            } break;
        }
    }

    fprintf(output_stream, "\n");
}
