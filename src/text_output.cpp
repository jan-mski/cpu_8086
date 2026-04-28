namespace text_output
{
    using std::to_underlying;
    using cpu::core::CpuState;
    using cpu::core::Register8BitId;
    using cpu::core::Register16BitId;
    using cpu::core::FlagId;
    using cpu::instruction::Instruction;
    using cpu::instruction::Mnemonic;
    using cpu::instruction::Operand;
    using cpu::instruction::OperandType;
    using cpu::instruction::MemoryAddress;

    const char *FLAG_NAMES[] = {
        0,
        "T", "D", "I", "O", "S", "Z", "A", "P", "C"
    };

    const char *GetRegisterName(Register8BitId register_id)
    {
        const char *register_names[] = {
            0,
            "al", "ah", "bl", "bh", "cl", "ch", "dl", "dh"
        };

        static_assert(
            (to_underlying(Register8BitId::Count)) == ARRAY_SIZE(register_names),
            "Number of register id enums and strings must be equal");

        return register_names[to_underlying(register_id)];
    }

    const char *GetRegisterName(Register16BitId register_id)
    {
        const char *register_names[] = {
            0,
            "ax", "bx", "cx", "dx", "sp", "bp", "si", "di",
            "es", "cs", "ss", "ds",
            "ip"
        };

        static_assert(
            (to_underlying(Register16BitId::Count)) == ARRAY_SIZE(register_names),
            "Number of register id enums and strings must be equal");

        return register_names[to_underlying(register_id)];
    }

    const char *GetMnemonicString(Mnemonic mnemonic)
    {
        const char *mnemonic_strings[] = {
            0,
            "mov", "push", "pop", "xchg", "in", "out", "xlat", "lea", "lds", "les", "lahf", "sahf", "pushf", "popf",
            "add", "adc", "inc", "aaa", "daa", "sub", "sbb", "dec", "neg", "cmp", "aas", "das", "mul", "imul", "aam",
            "div", "idiv", "aad", "cbw", "cwd", "not", "shl", "shr", "sar", "rol", "ror", "rcl", "rcr", "and", "test",
            "or", "xor", "rep", "movsb", "movsw", "cmpsb", "cmpsw", "scasb", "scasw", "lodsb", "lodsw", "stosb",
            "stosw", "call", "jmp", "ret", "jo", "jno", "jb", "jnb", "je", "jne", "jbe", "jnbe", "js", "jns", "jp",
            "jnp", "jl", "jnl", "jle", "jnle", "loopnz", "loopz", "loop", "jcxz", "int", "int3", "into", "iret", "clc",
            "cmc", "stc", "cld", "std", "cli", "sti", "hlt", "wait",
        };

        static_assert(
            (to_underlying(Mnemonic::Count)) == ARRAY_SIZE(mnemonic_strings),
            "Number of mnemonic enums and strings must be equal");

        return mnemonic_strings[to_underlying(mnemonic)];
    }

    const char *GetMemoryAddressQualifierString(uint8_t operand_size_bytes)
    {
        const char *memory_address_qualifier_strings[] = {
            0,
            "byte", "word",
        };

        return memory_address_qualifier_strings[operand_size_bytes];
    }

    uint8_t BuildAsmString(Instruction *instruction, char *asm_string, bool do_terminate)
    {
        uint8_t asm_string_idx = sprintf(asm_string, "%s", GetMnemonicString(instruction->mnemonic));

        for (size_t operand_idx = 0; operand_idx < ARRAY_SIZE(instruction->operands); ++operand_idx)
        {
            Operand *operand = &instruction->operands[operand_idx];

            if (operand->type == OperandType::None)
            {
                continue;
            }

            asm_string_idx += sprintf(asm_string + asm_string_idx, operand_idx == 0 ? " " : ", ");

            switch (operand->type)
            {
                case OperandType::None:
                {
                    break;
                } break;
                case OperandType::Register8Bit:
                {
                    asm_string_idx += sprintf(
                        asm_string + asm_string_idx,
                        "%s",
                        GetRegisterName(operand->register_8_bit_id));
                } break;
                case OperandType::Register16Bit:
                {
                    asm_string_idx += sprintf(
                        asm_string + asm_string_idx,
                        "%s",
                        GetRegisterName(operand->register_16_bit_id));
                } break;
                case OperandType::MemoryAddress:
                {
                    MemoryAddress *memory_address = &operand->memory_address;
                    if (!memory_address->is_operand_size_implicit)
                    {
                        asm_string_idx += sprintf(
                            asm_string + asm_string_idx,
                            "%s ",
                            GetMemoryAddressQualifierString(instruction->is_wide ? 2 : 1));
                    }

                    bool is_any_register_used = false;
                    for (uint8_t register_idx = 0; register_idx < ARRAY_SIZE(memory_address->register_ids); ++register_idx)
                    {
                        const char *register_name = GetRegisterName(memory_address->register_ids[register_idx]);
                        if (!register_name)
                        {
                            break;
                        }
                        is_any_register_used = true;
                        asm_string_idx += sprintf(
                            asm_string + asm_string_idx,
                            register_idx == 0 ? "[%s" : " + %s",
                            register_name);
                    }
                    if (is_any_register_used && memory_address->displacement != 0)
                    {
                        asm_string_idx += sprintf(
                            asm_string + asm_string_idx,
                            memory_address->displacement > 0 ? " + %i]" : " - %i]",
                            abs(memory_address->displacement));
                    }
                    else if (memory_address->displacement == 0)
                    {
                        asm_string_idx += sprintf(asm_string + asm_string_idx, "%s", "]");
                    }
                    else
                    {
                        asm_string_idx += sprintf(asm_string + asm_string_idx, "[%i]", memory_address->displacement);
                    }
                } break;
                case OperandType::Immediate:
                {
                    asm_string_idx += sprintf(asm_string + asm_string_idx, "%u", operand->immediate_value);
                } break;
                case OperandType::IPIncrement:
                {
                    uint8_t num_instruction_bytes = 2;
                    int32_t ip_increment = num_instruction_bytes + operand->ip_increment;

                    // `$0` doesn't work with nasm, so have to use dummy arithmetic
                    if (ip_increment == 0)
                    {
                        asm_string_idx += sprintf(
                            asm_string + asm_string_idx,
                            "($+2) + %i",
                            operand->ip_increment);
                    }
                    else
                    {
                        asm_string_idx += sprintf(
                            asm_string + asm_string_idx,
                            ip_increment > 0 ? "$+%i" : "$%i",
                            ip_increment);
                    }
                } break;
            }
        }

        if (do_terminate)
        {
            sprintf(asm_string + asm_string_idx, "%s", "\0");
        }

        return asm_string_idx;
    }

    void PrintAsmString(FILE *output_stream, Instruction *instruction)
    {
        char asm_string[64];
        BuildAsmString(instruction, asm_string, true);
        fprintf(output_stream, "%s\n", asm_string);
    }

    void PrintExecutionTrace(FILE *output_stream,
                             Instruction *instruction,
                             CpuState *pre_execution_state,
                             CpuState *post_execution_state)
    {
        char execution_trace[128];
        uint8_t execution_trace_idx = 0;

        execution_trace_idx += BuildAsmString(instruction, execution_trace, false);
        execution_trace_idx += sprintf(execution_trace + execution_trace_idx, "%s", " ;");

        for (uint8_t i = 0; i < (to_underlying(Register16BitId::Count)); ++i)
        {
            Register16BitId register_id = (Register16BitId) i;

            if (register_id == Register16BitId::None || register_id == Register16BitId::IP)
            {
                continue;
            }

            uint16_t pre_register_value = pre_execution_state->GetRegisterValue(register_id);
            uint16_t post_register_value = post_execution_state->GetRegisterValue(register_id);

            if (pre_register_value != post_register_value)
            {
                execution_trace_idx += sprintf(
                    execution_trace + execution_trace_idx,
                    " %s:0x%x->0x%x",
                    GetRegisterName(register_id),
                    pre_register_value,
                    post_register_value);

                break;
            }
        }

        uint16_t pre_ip_value = pre_execution_state->GetRegisterValue(Register16BitId::IP);
        uint16_t post_ip_value = post_execution_state->GetRegisterValue(Register16BitId::IP);

        if (pre_ip_value != post_ip_value)
        {
            execution_trace_idx += sprintf(
                execution_trace + execution_trace_idx,
                " %s:0x%x->0x%x",
                GetRegisterName(Register16BitId::IP),
                pre_ip_value,
                post_ip_value);
        }

        for (uint8_t i = 0; i < (to_underlying(FlagId::Count)); ++i)
        {
            bool pre_flag_value = pre_execution_state->GetFlagValue((FlagId) i);
            bool post_flag_value = post_execution_state->GetFlagValue((FlagId) i);

            if (pre_flag_value != post_flag_value)
            {
                execution_trace_idx += sprintf(execution_trace + execution_trace_idx, " flags:");

                if (pre_flag_value)
                {
                    execution_trace_idx += sprintf(execution_trace + execution_trace_idx, "%s", FLAG_NAMES[i]);
                }

                execution_trace_idx += sprintf(execution_trace + execution_trace_idx, "%s", "->");

                if (post_flag_value)
                {
                    execution_trace_idx += sprintf(execution_trace + execution_trace_idx, "%s", FLAG_NAMES[i]);
                }

                break;
            }
        }

        sprintf(execution_trace + execution_trace_idx, "%s", "\0");
        fprintf(output_stream, "%s\n", execution_trace);
    }

    void PrintFinalCpuState(FILE *output_stream, CpuState *final_cpu_state)
    {
        static_assert(
            (to_underlying(FlagId::Count)) == ARRAY_SIZE(FLAG_NAMES),
            "Number of flag enums and strings must be equal");

        fprintf(output_stream, "%s", "\nFinal registers:\n");

        for (uint8_t i = 0; i < (to_underlying(Register16BitId::Count)); ++i)
        {
            Register16BitId register_id = (Register16BitId) i;
            uint16_t register_value = final_cpu_state->GetRegisterValue(register_id);

            if (register_value != 0)
            {
                fprintf(
                    output_stream,
                    "      %s: 0x%04x (%u)\n",
                    GetRegisterName(register_id),
                    register_value,
                    register_value);
            }
        }

        char flag_string[to_underlying(FlagId::Count)];
        uint8_t flag_string_idx = 0;

        for (uint8_t i = 1; i < (to_underlying(FlagId::Count)); ++i)
        {
            if (final_cpu_state->GetFlagValue((FlagId) i))
            {
                flag_string_idx += sprintf(flag_string, "%s", FLAG_NAMES[i]);
            }
        }

        if (flag_string_idx != 0)
        {
            sprintf(flag_string + flag_string_idx, "%s", "\0");
            fprintf(output_stream, "   flags: %s\n", flag_string);
        }
    }
}
