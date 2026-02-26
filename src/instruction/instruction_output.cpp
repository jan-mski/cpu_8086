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
    "di",
    "es",
    "cs",
    "ss",
    "ds"
};

const char *MNEMONIC_STRINGS[] = {
    0,
    "mov",
    "push",
    "pop",
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

const char *MEMORY_ADDRESS_QUALIFIER_STRINGS[] = {
    0,
    "byte",
    "word",
};

const char *GetRegisterName(Register register_)
{
    static_assert(REGISTER_COUNT == ARRAY_SIZE(REGISTER_NAMES),
        "REGISTER_COUNT and size of REGISTER_NAMES must be equal");

    return REGISTER_NAMES[register_];
}

const char *GetMnemonicString(Mnemonic mnemonic)
{
    static_assert(MNEMONIC_COUNT == ARRAY_SIZE(MNEMONIC_STRINGS),
        "MNEMONIC_COUNT and size of MNEMONIC_NAMES must be equal");

    return MNEMONIC_STRINGS[mnemonic];
}

const char *GetMemoryAddressQualifierString(MemoryAddressQualifier qualifier)
{
    static_assert(MEMORY_ADDRESS_QUALIFIER_COUNT == ARRAY_SIZE(MEMORY_ADDRESS_QUALIFIER_STRINGS),
        "MEM_ADDR_QUALIFIER_COUNT and size of MEMORY_ADDRESS_QUALIFIER_STRINGS must be equal");

    return MEMORY_ADDRESS_QUALIFIER_STRINGS[qualifier];
}

void PrintInstructionString(FILE *output_stream, Instruction *instruction)
{
    char asm_string[64];
    uint8_t asm_string_idx = sprintf(asm_string, "%s", GetMnemonicString(instruction->mnemonic));

    for (size_t operand_idx = 0; operand_idx < ARRAY_SIZE(instruction->operands); ++operand_idx)
    {
        Operand *operand = &instruction->operands[operand_idx];
        asm_string_idx += sprintf(asm_string + asm_string_idx,
            (operand_idx == 0 && operand->type != OPERAND_TYPE_NONE) ? " " : ", ");

        switch (operand->type)
        {
            case OPERAND_TYPE_NONE:
            {
                break;
            } break;
            case OPERAND_TYPE_REGISTER:
            {
                asm_string_idx += sprintf(asm_string + asm_string_idx, "%s", GetRegisterName(operand->register_));
            } break;
            case OPERAND_TYPE_MEMORY_ADDRESS:
            {
                MemoryAddress *memory_address = &operand->memory_address;
                if (memory_address->qualifier)
                {
                    asm_string_idx += sprintf(asm_string + asm_string_idx, "%s ", GetMemoryAddressQualifierString(memory_address->qualifier));
                }
                if (memory_address->direct)
                {
                    asm_string_idx += sprintf(asm_string + asm_string_idx, "[%i]", memory_address->displacement);
                }
                else
                {
                    for (size_t register_idx = 0; register_idx < REGISTERS_MAX_LEN; ++register_idx)
                    {
                        const char *register_name = GetRegisterName(memory_address->registers[register_idx]);
                        if (!register_name)
                        {
                            break;
                        }
                        asm_string_idx += sprintf(asm_string + asm_string_idx, register_idx == 0 ? "[%s" : " + %s", register_name);
                    }
                    asm_string_idx += sprintf(asm_string + asm_string_idx, " + %i]", memory_address->displacement);
                }
            } break;
            case OPERAND_TYPE_IMMEDIATE:
            {
                asm_string_idx += sprintf(asm_string + asm_string_idx, "%u", operand->immediate_value);
            } break;
            case OPERAND_TYPE_LABEL_LIKE_DISPLACEMENT:
            {
                asm_string_idx += sprintf(asm_string + asm_string_idx, "($+2) + %i", operand->label_like_displacement);
            } break;
        }
    }

    sprintf(asm_string + asm_string_idx, "\0");
    fprintf(output_stream, "%s\n", asm_string);
}
