namespace instruction_execution::core
{
    namespace mem = ::memory;
    namespace cpu = ::cpu;
    namespace ins = ::instruction;
    namespace exe_ops = ::instruction_execution::ops;
    namespace exe_res = ::instruction_execution::resolution;

    void UpdateFlags(ExecutionResultValue instruction_result,
                     cpu::CpuState* cpu_state,
                     cpu::Flags flags)
    {
        cpu::Flags computed_flags = 0;
        if ((flags & cpu::FlagId_ZF) && instruction_result == 0)
        {
            computed_flags |= cpu::FlagId_ZF;
        }
        if ((flags & cpu::FlagId_SF) && instruction_result & 0x8000)
        {
            computed_flags |= cpu::FlagId_SF;
        }
        cpu_state->flags = (cpu_state->flags & ~flags) | computed_flags;
    }

    ins::Operand CreateOperandImmediate(U16 immediate_value)
    {
        return {
            .type            = ins::OperandType_Immediate,
            .immediate_value = immediate_value
        };
    }

    ins::Operand CreateOperandStack()
    {
        return {
            .type           = ins::OperandType_MemoryAddress,
            .memory_address = { .register_ids = { cpu::Register16BitId_SP } }
        };
    }

    ins::Operand CreateOperandSP()
    {
        return {
            .type               = ins::OperandType_Register16Bit,
            .register_16_bit_id = cpu::Register16BitId_SP
        };
    }

    ins::Operand CreateOperandIP()
    {
        return {
            .type               = ins::OperandType_Register16Bit,
            .register_16_bit_id = cpu::Register16BitId_IP
        };
    }

    ExecutionResult Execute(exe_ops::Op op,
                            ins::Operand* operands,
                            bool is_wide,
                            bool do_set_result,
                            cpu::CpuState* cpu_state,
                            mem::Memory* memory)
    {
        exe_res::ResolvedInstruction resolved_instruction =
                exe_res::ResolveInstruction(operands, 2, is_wide, cpu_state);
        ExecutionResult result = { .resolved_ea = resolved_instruction.resolved_ea };
        result.value = op(&resolved_instruction, cpu_state, memory);

        if (do_set_result)
        {
            exe_res::SetResolvedOperandValue(
                &resolved_instruction.operands[0],
                resolved_instruction.is_wide,
                result.value,
                cpu_state,
                memory);
        }

        return result;
    }

    ExecutionResult Execute(exe_ops::Op op,
                            ins::Instruction* instruction,
                            bool do_set_result,
                            cpu::CpuState* cpu_state,
                            mem::Memory* memory)
    {
        return Execute(
            op,
            instruction->operands,
            instruction->is_wide,
            do_set_result,
            cpu_state,
            memory);
    }

    ExecutionResult ExecuteShift(exe_ops::Op op,
                                 ins::Instruction* instruction,
                                 bool do_set_result,
                                 cpu::CpuState* cpu_state,
                                 mem::Memory* memory)
    {
        ExecutionResult result = Execute(op, instruction, do_set_result, cpu_state, memory);
        result.shift_count = instruction->operands[1].immediate_value;

        return result;
    }

    ExecutionResult ExecuteJump(ins::Instruction* instruction,
                                cpu::CpuState* cpu_state,
                                mem::Memory* memory,
                                bool condition)
    {
        ExecutionResult result = {};

        if (condition)
        {
            ins::Operand operands[] = { CreateOperandIP(), instruction->operands[0] };
            result = Execute(exe_ops::add, operands, instruction->is_wide, true, cpu_state, memory);

            result.did_branch_jump = true;
        }

        return result;
    }

    ExecutionResult ExecuteJump(ins::Instruction* instruction,
                                cpu::CpuState* cpu_state,
                                mem::Memory* memory)
    {
        ins::Operand operands[] = { CreateOperandIP(), instruction->operands[0] };
        exe_ops::Op op = instruction->operands[0].type == ins::OperandType_IPIncrement ? exe_ops::add : exe_ops::noop;

        return Execute(op, operands, instruction->is_wide, true, cpu_state, memory);
    }

    ExecutionResult ExecuteStoreOnStack(ins::Operand source_operand,
                                        bool is_wide,
                                        cpu::CpuState* cpu_state,
                                        mem::Memory* memory)
    {
        ins::Operand operands[] = { CreateOperandStack(), source_operand };

        return Execute(exe_ops::noop, operands, is_wide, true, cpu_state, memory);
    }

    ExecutionResult ExecuteLoadFromStack(ins::Operand destination_operand,
                                         bool is_wide,
                                         cpu::CpuState* cpu_state,
                                         mem::Memory* memory)
    {
        ins::Operand operands[] = { destination_operand, CreateOperandStack() };

        return Execute(exe_ops::noop, operands, is_wide, true, cpu_state, memory);
    }

    ExecutionResult ExecuteInstruction(ins::Instruction* instruction,
                                       cpu::CpuState* cpu_state,
                                       mem::Memory* memory)
    {
        ExecutionResult result = {};

        switch (instruction->mnemonic)
        {
            case ins::Mnemonic_MOV:
            {
                result = Execute(exe_ops::noop, instruction, true, cpu_state, memory);
            } break;
            case ins::Mnemonic_ADD:
            {
                result = Execute(exe_ops::add, instruction, true, cpu_state, memory);
                UpdateFlags(result.value, cpu_state, cpu::FlagId_ZF | cpu::FlagId_SF);
            } break;
            case ins::Mnemonic_INC:
            {
                ins::Operand operands[] = { instruction->operands[0], CreateOperandImmediate(1) };
                result = Execute(exe_ops::add, operands, instruction->is_wide, true, cpu_state, memory);
                UpdateFlags(result.value, cpu_state, cpu::FlagId_ZF | cpu::FlagId_SF);
            }
            case ins::Mnemonic_SUB:
            {
                result = Execute(exe_ops::subtract, instruction, true, cpu_state, memory);
                UpdateFlags(result.value, cpu_state, cpu::FlagId_ZF | cpu::FlagId_SF);
            } break;
            case ins::Mnemonic_DEC:
            {
                ins::Operand operands[] = { instruction->operands[0], CreateOperandImmediate(1) };
                result = Execute(exe_ops::subtract, operands, instruction->is_wide, true, cpu_state, memory);
                UpdateFlags(result.value, cpu_state, cpu::FlagId_ZF | cpu::FlagId_SF);
            } break;
            case ins::Mnemonic_CMP:
            {
                result = Execute(
                    exe_ops::subtract,
                    instruction->operands,
                    instruction->is_wide,
                    false,
                    cpu_state,
                    memory);
                UpdateFlags(result.value, cpu_state, cpu::FlagId_ZF | cpu::FlagId_SF);
            } break;
            case ins::Mnemonic_NOT:
            {
                result = Execute(exe_ops::bitwise_not, instruction, true, cpu_state, memory);
                UpdateFlags(result.value, cpu_state, cpu::FlagId_ZF | cpu::FlagId_SF);
            } break;
            case ins::Mnemonic_AND:
            {
                result = Execute(
                    exe_ops::bitwise_and,
                    instruction->operands,
                    instruction->is_wide,
                    true,
                    cpu_state,
                    memory);
                UpdateFlags(result.value, cpu_state, cpu::FlagId_ZF | cpu::FlagId_SF);
            } break;
            case ins::Mnemonic_OR:
            {
                result = Execute(exe_ops::bitwise_or, instruction, true, cpu_state, memory);
                UpdateFlags(result.value, cpu_state, cpu::FlagId_ZF | cpu::FlagId_SF);
            } break;
            case ins::Mnemonic_XOR:
            {
                result = Execute(exe_ops::bitwise_xor, instruction, true, cpu_state, memory);
                UpdateFlags(result.value, cpu_state, cpu::FlagId_ZF | cpu::FlagId_SF);
            } break;
            case ins::Mnemonic_TEST:
            {
                result = Execute(exe_ops::bitwise_and, instruction, false, cpu_state, memory);
                UpdateFlags(result.value, cpu_state, cpu::FlagId_ZF | cpu::FlagId_SF);
            } break;
            case ins::Mnemonic_SHL_SAL:
            {
                result = ExecuteShift(exe_ops::bitwise_shl, instruction, true, cpu_state, memory);
                UpdateFlags(result.value, cpu_state, cpu::FlagId_ZF | cpu::FlagId_SF);
            } break;
            case ins::Mnemonic_SHR:
            {
                result = ExecuteShift(exe_ops::bitwise_shr, instruction, true, cpu_state, memory);
                UpdateFlags(result.value, cpu_state, cpu::FlagId_ZF | cpu::FlagId_SF);
            } break;
            case ins::Mnemonic_SAR:
            {
                result = ExecuteShift(exe_ops::bitwise_sar, instruction, true, cpu_state, memory);
                UpdateFlags(result.value, cpu_state, cpu::FlagId_ZF | cpu::FlagId_SF);
            } break;
            case ins::Mnemonic_JNE_JNZ:
            {
                result = ExecuteJump(instruction, cpu_state, memory, !(cpu_state->flags & cpu::FlagId_ZF));
            } break;
            case ins::Mnemonic_JMP:
            {
                result = ExecuteJump(instruction, cpu_state, memory);
            } break;
            case ins::Mnemonic_PUSH:
            {
                cpu::DecrementSP(cpu_state);
                result = ExecuteStoreOnStack(instruction->operands[0], instruction->is_wide, cpu_state, memory);
            } break;
            case ins::Mnemonic_POP:
            {
                result = ExecuteLoadFromStack(instruction->operands[0], instruction->is_wide, cpu_state, memory);
                cpu::IncrementSP(cpu_state);
            } break;
            case ins::Mnemonic_LEA:
            {
                memory::Address resolved_ea = exe_res::ResolveEffectiveAddress(
                    &instruction->operands[1].memory_address,
                    cpu_state);
                ins::Operand operands[] = { instruction->operands[0], CreateOperandImmediate((U16) resolved_ea) };
                result = Execute(exe_ops::noop, operands, instruction->is_wide, true, cpu_state, memory);
            } break;
            case ins::Mnemonic_CALL:
            {
                cpu::DecrementSP(cpu_state);
                ExecuteStoreOnStack(CreateOperandIP(), instruction->is_wide, cpu_state, memory);
                result = ExecuteJump(instruction, cpu_state, memory);
            } break;
            case ins::Mnemonic_RET:
            {
                result = ExecuteLoadFromStack(CreateOperandIP(), instruction->is_wide, cpu_state, memory);
                cpu::IncrementSP(cpu_state);
            } break;
            default:
            {
            } break;
        }

        return result;
    }
}
