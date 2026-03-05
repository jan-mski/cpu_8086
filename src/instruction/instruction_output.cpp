#define _CRT_SECURE_NO_WARNINGS

const char *GetRegisterName(Register register_)
{
    const char *register_names[] = {
        0,
        "al", "ah", "ax", "bl", "bh", "bx", "cl", "ch", "cx", "dl",
        "dh", "dx", "sp", "bp", "si", "di", "es", "cs", "ss", "ds"
    };

    static_assert(Register_Count == ARRAY_SIZE(register_names),
        "Register_COUNT and size of Register_NAMES must be equal");

    return register_names[register_];
}

const char *GetMnemonicString(Mnemonic mnemonic)
{
    const char *mnemonic_strings[] = {
        0,
        "mov", "push", "pop", "xchg", "in", "out", "xlat", "lea", "lds", "les", "lahf", "sahf", "pushf", "popf", "add",
        "adc", "inc", "aaa", "daa", "sub", "sbb", "dec", "neg", "cmp", "aas", "das", "mul", "imul", "aam", "div", "idiv",
        "aad", "cbw", "cwd", "not", "shl", "shr", "sar", "rol", "ror", "rcl", "rcr", "and", "test", "or", "xor", "rep",
        "movsb", "movsw", "cmpsb", "cmpsw", "scasb", "scasw", "lodsb", "lodsw", "stosb", "stosw", "call", "jmp", "ret",
        "jo", "jno", "jb", "jnb", "je", "jne", "jbe", "jnbe", "js", "jns", "jp", "jnp", "jl", "jnl", "jle", "jnle",
        "loopnz", "loopz", "loop", "jcxz", "int", "int3", "into", "iret", "clc", "cmc", "stc", "cld", "std", "cli",
        "sti", "hlt", "wait",
    };

    static_assert(Mnemonic_Count == ARRAY_SIZE(mnemonic_strings),
        "MNEMONIC_COUNT and size of MNEMONIC_NAMES must be equal");

    return mnemonic_strings[mnemonic];
}

const char *GetMemoryAddressQualifierString(MemoryAddressQualifier qualifier)
{
    const char *memory_address_qualifier_strings[] = {
        0,
        "byte", "word",
    };

    static_assert(MemoryAddressQualifier_Count == ARRAY_SIZE(memory_address_qualifier_strings),
        "MEM_ADDR_QUALIFIER_COUNT and size of MEMORY_ADDRESS_QUALIFIER_STRINGS must be equal");

    return memory_address_qualifier_strings[qualifier];
}

void PrintInstructionString(FILE *output_stream, Instruction *instruction)
{
    char asm_string[64];
    uint8_t asm_string_idx = sprintf(asm_string, "%s", GetMnemonicString(instruction->mnemonic));

    for (size_t operand_idx = 0; operand_idx < ARRAY_SIZE(instruction->operands); ++operand_idx)
    {
        Operand *operand = &instruction->operands[operand_idx];

        if (operand->type == OperandType_None)
        {
            continue;
        }

        asm_string_idx += sprintf(asm_string + asm_string_idx, operand_idx == 0 ? " " : ", ");

        switch (operand->type)
        {
            case OperandType_None:
            {
                break;
            } break;
            case OperandType_Register:
            {
                asm_string_idx += sprintf(asm_string + asm_string_idx, "%s", GetRegisterName(operand->register_));
            } break;
            case OperandType_MemoryAddress:
            {
                MemoryAddress *memory_address = &operand->memory_address;
                if (memory_address->qualifier != MemoryAddressQualifier_None)
                {
                    asm_string_idx += sprintf(asm_string + asm_string_idx, "%s ", GetMemoryAddressQualifierString(memory_address->qualifier));
                }
                if (memory_address->direct)
                {
                    asm_string_idx += sprintf(asm_string + asm_string_idx, "[%i]", memory_address->displacement);
                }
                else
                {
                    for (size_t register_idx = 0; register_idx < ARRAY_SIZE(memory_address->registers); ++register_idx)
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
            case OperandType_Immediate:
            {
                asm_string_idx += sprintf(asm_string + asm_string_idx, "%u", operand->immediate_value);
            } break;
            case OperandType_LabelLikeDisplacement:
            {
                asm_string_idx += sprintf(asm_string + asm_string_idx, "($+2) + %i", operand->label_like_displacement);
            } break;
        }
    }

    sprintf(asm_string + asm_string_idx, "\0");
    fprintf(output_stream, "%s\n", asm_string);
}
