#define _CRT_SECURE_NO_WARNINGS

namespace cpu::text_output
{
    using cpu::state::CpuState;
    using cpu::state::RegisterId;
    using cpu::state::FlagId;
    using cpu::state::Register;
    using cpu::state::RegisterSlice;
    using cpu::state::GetRegisterValue;
    using cpu::instruction::Instruction;
    using cpu::instruction::Mnemonic;
    using cpu::instruction::Operand;
    using cpu::instruction::OperandType;
    using cpu::instruction::MemoryAddressQualifier;
    using cpu::instruction::MemoryAddress;

    const char *REGISTER_NAMES[] = {
        0,
        "al", "ah", "ax", "bl", "bh", "bx", "cl", "ch", "cx", "dl",
        "dh", "dx", "sp", "bp", "si", "di", "es", "cs", "ss", "ds"
    };

    const char *FLAG_NAMES[] = {
        0,
        "T", "D", "I", "O", "S", "Z", "A", "P", "C"
    };

    const char *GetRegisterName(RegisterId register_)
    {
        static_assert(
            RegisterId::RegisterId_Count == ARRAY_SIZE(REGISTER_NAMES),
            "Number of register id enums and strings must be equal");

        return REGISTER_NAMES[register_];
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
            ((uint8_t) Mnemonic::Count) == ARRAY_SIZE(mnemonic_strings),
            "Number of mnemonic enums and strings must be equal");

        return mnemonic_strings[(uint8_t) mnemonic];
    }

    const char *GetMemoryAddressQualifierString(MemoryAddressQualifier qualifier)
    {
        const char *memory_address_qualifier_strings[] = {
            0,
            "byte", "word",
        };

        static_assert(
            ((uint8_t) MemoryAddressQualifier::Count) == ARRAY_SIZE(memory_address_qualifier_strings),
            "Number of qualifier enums and strings must be equal");

        return memory_address_qualifier_strings[(uint8_t) qualifier];
    }

    uint8_t BuildAsmString(Instruction *instruction, char *asm_string, bool terminate)
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
                }
                break;
                case OperandType::Register:
                {
                    asm_string_idx += sprintf(asm_string + asm_string_idx, "%s", GetRegisterName(operand->register_id));
                }
                break;
                case OperandType::MemoryAddress:
                {
                    MemoryAddress *memory_address = &operand->memory_address;
                    if (memory_address->qualifier != MemoryAddressQualifier::None)
                    {
                        asm_string_idx += sprintf(
                            asm_string + asm_string_idx,
                            "%s ",
                            GetMemoryAddressQualifierString(memory_address->qualifier));
                    }
                    if (memory_address->direct)
                    {
                        asm_string_idx += sprintf(asm_string + asm_string_idx, "[%i]", memory_address->displacement);
                    } else
                    {
                        for (size_t register_idx = 0; register_idx < ARRAY_SIZE(memory_address->register_ids); ++register_idx)
                        {
                            const char *register_name = GetRegisterName(memory_address->register_ids[register_idx]);
                            if (!register_name)
                            {
                                break;
                            }
                            asm_string_idx += sprintf(
                                asm_string + asm_string_idx,
                                register_idx == 0 ? "[%s" : " + %s",
                                register_name);
                        }
                        asm_string_idx += sprintf(asm_string + asm_string_idx, " + %i]", memory_address->displacement);
                    }
                }
                break;
                case OperandType::Immediate:
                {
                    asm_string_idx += sprintf(asm_string + asm_string_idx, "%u", operand->immediate_value);
                }
                break;
                case OperandType::LabelLikeDisplacement:
                {
                    asm_string_idx += sprintf(
                        asm_string + asm_string_idx,
                        "($+2) + %i",
                        operand->label_like_displacement);
                }
                break;
            }
        }

        if (terminate)
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

    void PrintFinalCpuState(FILE *output_stream, CpuState *final_cpu_state)
    {
        static_assert(
            FlagId::FlagId_Count == ARRAY_SIZE(FLAG_NAMES),
            "Number of flag enums and strings must be equal");

        fprintf(output_stream, "%s", "\nFinal registers:\n");

        for (uint8_t i = 1; i < RegisterId::RegisterId_Count; ++i)
        {
            RegisterId register_id = (RegisterId) i;
            Register register_ = final_cpu_state->registers[register_id];

            if (register_.slice == RegisterSlice::RegisterSlice_Low || register_.slice == RegisterSlice::RegisterSlice_High)
            {
                continue;
            }

            uint16_t register_value = GetRegisterValue(final_cpu_state->registers, register_id);

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

        char flag_string[FlagId::FlagId_Count];
        uint8_t flag_string_idx = 0;

        for (uint8_t i = 1; i < FlagId::FlagId_Count; ++i)
        {
            if (final_cpu_state->flags[i])
            {
                flag_string_idx += sprintf(flag_string, "%s", FLAG_NAMES[i]);
            }
        }

        if (flag_string_idx != 0)
        {
            sprintf(flag_string + flag_string_idx, "%s", "\0");
            fprintf(output_stream, "   flags: %s\n\n", flag_string);
        }
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

        for (uint8_t i = 0; i < RegisterId::RegisterId_Count; ++i)
        {
            RegisterId register_id = (RegisterId) i;

            RegisterSlice register_slice = pre_execution_state->registers[register_id].slice;
            if (register_slice == RegisterSlice::RegisterSlice_Low || register_slice == RegisterSlice::RegisterSlice_High)
            {
                continue;
            }

            uint16_t pre_register_value = GetRegisterValue(pre_execution_state->registers, register_id);
            uint16_t post_register_value = GetRegisterValue(post_execution_state->registers, register_id);

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

        for (uint8_t i = 0; i < FlagId::FlagId_Count; ++i)
        {
            bool pre_flag_value = pre_execution_state->flags[i];
            bool post_flag_value = post_execution_state->flags[i];

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
}
