namespace text_output
{
    namespace cpu = ::cpu;
    namespace ins = ::instruction;
    namespace cyc = ::cycle_estimation;

    const char* GetRegisterName(cpu::Register8BitId register_id)
    {
        const char* register_names[] = {
            0,
            "al", "ah", "bl", "bh", "cl", "ch", "dl", "dh"
        };

        static_assert(
            cpu::Register8BitId_Count == ARRAY_SIZE(register_names),
            "Number of register id enums and strings must be equal");

        return register_names[register_id];
    }

    const char* GetRegisterName(cpu::Register16BitId register_id)
    {
        const char* register_names[] = {
            0,
            "ax", "bx", "cx", "dx", "sp", "bp", "si", "di",
            "es", "cs", "ss", "ds",
            "ip"
        };

        static_assert(
            cpu::Register16BitId_Count == ARRAY_SIZE(register_names),
            "Number of register id enums and strings must be equal");

        return register_names[register_id];
    }

    const char* GetMnemonicString(ins::Mnemonic mnemonic)
    {
        const char* mnemonic_strings[] = {
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
            ins::Mnemonic_Count == ARRAY_SIZE(mnemonic_strings),
            "Number of mnemonic enums and strings must be equal");

        return mnemonic_strings[mnemonic];
    }

    const char* GetMemoryAddressQualifierString(U8 operand_size_bytes)
    {
        const char* memory_address_qualifier_strings[] = {
            0,
            "byte", "word",
        };

        return memory_address_qualifier_strings[operand_size_bytes];
    }

    U8 BuildAsmString(ins::Instruction* instruction,
                      char* asm_string,
                      bool do_terminate)
    {
        U8 string_idx = sprintf(asm_string, "%s", GetMnemonicString(instruction->mnemonic));

        for (size_t operand_idx = 0; operand_idx < ARRAY_SIZE(instruction->operands); ++operand_idx)
        {
            ins::Operand* operand = &instruction->operands[operand_idx];

            if (operand->type == ins::OperandType_None)
            {
                continue;
            }

            string_idx += sprintf(asm_string + string_idx, operand_idx == 0 ? " " : ", ");

            switch (operand->type)
            {
                case ins::OperandType_None:
                {
                    break;
                } break;
                case ins::OperandType_Register8Bit:
                {
                    string_idx += sprintf(
                        asm_string + string_idx,
                        "%s",
                        GetRegisterName(operand->register_8_bit_id));
                } break;
                case ins::OperandType_Register16Bit:
                {
                    string_idx += sprintf(
                        asm_string + string_idx,
                        "%s",
                        GetRegisterName(operand->register_16_bit_id));
                } break;
                case ins::OperandType_MemoryAddress:
                {
                    ins::MemoryAddress* memory_address = &operand->memory_address;
                    if (!memory_address->is_operand_size_implicit)
                    {
                        string_idx += sprintf(
                            asm_string + string_idx,
                            "%s ",
                            GetMemoryAddressQualifierString(instruction->is_wide ? 2 : 1));
                    }

                    bool is_any_register_used = false;
                    for (U8 register_idx = 0; register_idx < ARRAY_SIZE(memory_address->register_ids); ++register_idx)
                    {
                        const char* register_name = GetRegisterName(memory_address->register_ids[register_idx]);
                        if (!register_name)
                        {
                            break;
                        }
                        is_any_register_used = true;
                        string_idx += sprintf(
                            asm_string + string_idx,
                            register_idx == 0 ? "[%s" : " + %s",
                            register_name);
                    }
                    if (is_any_register_used && memory_address->displacement != 0)
                    {
                        string_idx += sprintf(
                            asm_string + string_idx,
                            memory_address->displacement > 0 ? " + %i]" : " - %i]",
                            abs(memory_address->displacement));
                    }
                    else if (memory_address->displacement == 0)
                    {
                        string_idx += sprintf(asm_string + string_idx, "%s", "]");
                    }
                    else
                    {
                        string_idx += sprintf(asm_string + string_idx, "[%i]", memory_address->displacement);
                    }
                } break;
                case ins::OperandType_Immediate:
                {
                    string_idx += sprintf(asm_string + string_idx, "%u", operand->immediate_value);
                } break;
                case ins::OperandType_IPIncrement:
                {
                    U8 num_instruction_bytes = 2;
                    I32 ip_increment = num_instruction_bytes + operand->ip_increment;

                    // NOTE: `$0` doesn't work with nasm, so have to use dummy arithmetic
                    if (ip_increment == 0)
                    {
                        string_idx += sprintf(
                            asm_string + string_idx,
                            "($+2) + %i",
                            operand->ip_increment);
                    }
                    else
                    {
                        string_idx += sprintf(
                            asm_string + string_idx,
                            ip_increment > 0 ? "$+%i" : "$%i",
                            ip_increment);
                    }
                } break;
            }
        }

        if (do_terminate)
        {
            sprintf(asm_string + string_idx, "%s", "\0");
        }

        return string_idx;
    }

    void PrintAsmString(FILE* output_stream,
                        ins::Instruction* instruction)
    {
        char asm_string[64];
        BuildAsmString(instruction, asm_string, true);
        fprintf(output_stream, "%s\n", asm_string);
    }

    U8 BuildExecutionTraceCycleString(cyc::CycleCountEstimate cycle_count_estimate,
                                      char* execution_trace)
    {
        U8 string_idx = 0;
        
        cyc::ExecutionEstimate latest_estimate = cycle_count_estimate.latest;

        if (cycle_count_estimate.total_num_cycles)
        {
            string_idx += sprintf(
                execution_trace + string_idx,
                " Clocks: +%u = %u",
                latest_estimate.num_cycles,
                cycle_count_estimate.total_num_cycles);

            if (latest_estimate.num_ea_cycles || latest_estimate.num_odd_address_cycles)
            {
                if (latest_estimate.num_ea_cycles > 0)
                {
                    string_idx += sprintf(
                        execution_trace + string_idx,
                        " (%u + %uea",
                        latest_estimate.num_raw_cycles,
                        latest_estimate.num_ea_cycles);
                }

                if (latest_estimate.num_odd_address_cycles > 0)
                {
                    string_idx += sprintf(
                        execution_trace + string_idx,
                        " + %uo",
                        latest_estimate.num_odd_address_cycles);
                }

                string_idx += sprintf(execution_trace + string_idx, "%s", ")");
            }

            string_idx += sprintf(execution_trace + string_idx, "%s", " |");
        }

        return string_idx;
    }

    U8 BuildExecutionTraceRegisterString(cpu::CpuState* pre_execution_state,
                                         cpu::CpuState* post_execution_state,
                                         char* execution_trace)
    {
        U8 string_idx = 0;

        for (U8 i = 0; i < (cpu::Register16BitId_Count); ++i)
        {
            cpu::Register16BitId register_id = (cpu::Register16BitId) i;

            if (register_id == cpu::Register16BitId_None || register_id == cpu::Register16BitId_IP)
            {
                continue;
            }

            U16 pre_register_value = cpu::GetRegisterValue(pre_execution_state, register_id);
            U16 post_register_value = cpu::GetRegisterValue(post_execution_state, register_id);

            if (pre_register_value != post_register_value)
            {
                string_idx += sprintf(
                    execution_trace + string_idx,
                    " %s:0x%x->0x%x",
                    GetRegisterName(register_id),
                    pre_register_value,
                    post_register_value);
                break;
            }
        }

        U16 pre_ip_value = cpu::GetRegisterValue(pre_execution_state, cpu::Register16BitId_IP);
        U16 post_ip_value = cpu::GetRegisterValue(post_execution_state, cpu::Register16BitId_IP);

        if (pre_ip_value != post_ip_value)
        {
            string_idx += sprintf(
                execution_trace + string_idx,
                " %s:0x%x->0x%x",
                GetRegisterName(cpu::Register16BitId_IP),
                pre_ip_value,
                post_ip_value);
        }

        return string_idx;
    }

    U8 BuildFlagString(cpu::Flags flags,
                       char* destination_string)
    {
        U8 string_idx = 0;

        if (flags & cpu::FlagId_SF)
        {
            string_idx += sprintf(destination_string + string_idx, "%s", "S");
        }
        if (flags & cpu::FlagId_ZF)
        {
            string_idx += sprintf(destination_string + string_idx, "%s", "Z");
        }

        return string_idx;
    }

    U8 BuildExecutionTraceFlagString(cpu::CpuState* pre_execution_state,
                                     cpu::CpuState* post_execution_state,
                                     char* execution_trace)
    {
        U8 string_idx = 0;

        if (pre_execution_state->flags != post_execution_state->flags)
        {
            string_idx += sprintf(execution_trace + string_idx, " flags:");
            string_idx += BuildFlagString(pre_execution_state->flags, execution_trace + string_idx);
            string_idx += sprintf(execution_trace + string_idx, "%s", "->");
            string_idx += BuildFlagString(post_execution_state->flags, execution_trace + string_idx);
        }

        return string_idx;
    }

    void PrintExecutionTrace(FILE* output_stream,
                             ins::Instruction* instruction,
                             cpu::CpuState* pre_execution_state,
                             cpu::CpuState* post_execution_state,
                             cyc::CycleCountEstimate cycle_count_estimate)
    {
        char execution_trace[128];
        U8 string_idx = 0;

        string_idx += BuildAsmString(instruction, execution_trace, false);
        string_idx += sprintf(execution_trace + string_idx, "%s", " ;");

        string_idx += BuildExecutionTraceCycleString(cycle_count_estimate, execution_trace + string_idx);

        string_idx += BuildExecutionTraceRegisterString(
            pre_execution_state,
            post_execution_state,
            execution_trace + string_idx);

        string_idx += BuildExecutionTraceFlagString(
            pre_execution_state,
            post_execution_state,
            execution_trace + string_idx);

        sprintf(execution_trace + string_idx, "%s", "\0");
        fprintf(output_stream, "%s\n", execution_trace);
    }

    void PrintFinalCpuState(FILE* output_stream,
                            cpu::CpuState* final_cpu_state)
    {
        fprintf(output_stream, "%s", "\nFinal registers:\n");

        for (U8 i = 0; i < (cpu::Register16BitId_Count); ++i)
        {
            cpu::Register16BitId register_id = (cpu::Register16BitId) i;
            U16 register_value = cpu::GetRegisterValue(final_cpu_state, register_id);

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

        if (final_cpu_state->flags)
        {
            char flag_string[cpu::FlagId_Count];
            U8 flag_string_idx = BuildFlagString(final_cpu_state->flags, flag_string);
            sprintf(flag_string + flag_string_idx, "%s", "\0");
            fprintf(output_stream, "   flags: %s\n", flag_string);
        }
    }
}
