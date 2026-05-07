namespace cycle_estimation
{
    namespace cpu = ::cpu;
    namespace ins = ::instruction;
    namespace mem = ::memory;
    namespace exe = ::instruction_execution::core;

    typedef bool (* OperandPredicate)(ins::Operand* operand);

    bool IsNone(ins::Operand* operand)
    {
        return operand->type == ins::OperandType_None;
    }

    bool IsAccumulator(ins::Operand* operand)
    {
        return operand->type == ins::OperandType_Register8Bit && operand->register_8_bit_id == cpu::Register8BitId_AL
               || operand->type == ins::OperandType_Register16Bit && operand->register_16_bit_id ==
               cpu::Register16BitId_AX;
    }

    bool IsMemory(ins::Operand* operand)
    {
        return operand->type == ins::OperandType_MemoryAddress;
    }

    bool IsRegister(ins::Operand* operand)
    {
        return operand->type == ins::OperandType_Register8Bit || operand->type == ins::OperandType_Register16Bit;
    }

    bool IsReg16(ins::Operand* operand_1)
    {
        return operand_1->type == ins::OperandType_Register16Bit;
    }

    bool IsReg8(ins::Operand* operand_1)
    {
        return operand_1->type == ins::OperandType_Register8Bit;
    }

    bool IsImmediate(ins::Operand* operand)
    {
        return operand->type == ins::OperandType_Immediate;
    }

    bool IsIPIncrement(ins::Operand* operand)
    {
        return operand->type == ins::OperandType_IPIncrement;
    }

    bool IsCLRegister(ins::Operand* operand)
    {
        return operand->type == ins::OperandType_Register8Bit && operand->register_8_bit_id == cpu::Register8BitId_CL;
    }

    bool IsSegmentRegister(ins::Operand* operand)
    {
        return operand->type == ins::OperandType_Register16Bit
               && (operand->register_16_bit_id == cpu::Register16BitId_ES
                   || operand->register_16_bit_id == cpu::Register16BitId_CS
                   || operand->register_16_bit_id == cpu::Register16BitId_SS
                   || operand->register_16_bit_id == cpu::Register16BitId_DS);
    }

    struct CycleEstimationSpec
    {
        OperandPredicate operand_1_predicate;
        OperandPredicate operand_2_predicate;
        U8 num_raw_cycles;
        U8 num_transfers;
        bool update_ea_cycles;
        I8 memory_operand_idx = -1;
        U8 shift_count_multiplier;
    };

    const U8 CYCLE_ESTIMATES_MAX_LEN = 16;

    const CycleEstimationSpec MOV_CYCLE_ESTIMATES[] = {
        { IsMemory, IsAccumulator, 10, 1, false, 0 },
        { IsAccumulator, IsMemory, 10, 1, false, 1 },
        { IsRegister, IsRegister, 2, 0, false, -1 },
        { IsRegister, IsMemory, 8, 1, true, 1 },
        { IsMemory, IsRegister, 9, 1, true, 0 },
        { IsRegister, IsImmediate, 4, 0, false },
        { IsMemory, IsImmediate, 10, 1, true, 0 },
        { IsSegmentRegister, IsRegister, 2, 0, false, -1 },
        { IsSegmentRegister, IsMemory, 8, 1, true, 1 },
        { IsRegister, IsSegmentRegister, 2, 0, false, -1 },
        { IsMemory, IsSegmentRegister, 9, 1, true, 0 },
    };

    const CycleEstimationSpec ADD_CYCLE_ESTIMATES[] = {
        { IsRegister, IsRegister, 3, 0, false, -1 },
        { IsRegister, IsMemory, 9, 1, true, 1 },
        { IsMemory, IsRegister, 16, 2, true, 0 },
        { IsRegister, IsImmediate, 4, 0, false, -1 },
        { IsMemory, IsImmediate, 17, 2, true, 0 },
        { IsAccumulator, IsImmediate, 4, 0, false, -1 },
    };

    const CycleEstimationSpec INC_CYCLE_ESTIMATES[] = {
        { IsReg16, IsNone, 2, 0, false, -1 },
        { IsReg8, IsNone, 3, 0, false, -1 },
        { IsMemory, IsNone, 15, 2, true, 0 },
    };

    const CycleEstimationSpec SUB_CYCLE_ESTIMATES[] = {
        { IsRegister, IsRegister, 3, 0, false, -1 },
        { IsRegister, IsMemory, 9, 1, true, 1 },
        { IsMemory, IsRegister, 16, 2, true, 0 },
        { IsAccumulator, IsImmediate, 4, 0, false, -1 },
        { IsRegister, IsImmediate, 4, 0, false, -1 },
        { IsMemory, IsImmediate, 17, 2, true, 0 },
    };

    const CycleEstimationSpec DEC_CYCLE_ESTIMATES[] = {
        { IsReg16, IsNone, 2, 0, false, -1 },
        { IsReg8, IsNone, 3, 0, false, -1 },
        { IsMemory, IsNone, 15, 2, true, 0 },
    };

    const CycleEstimationSpec CMP_CYCLE_ESTIMATES[] = {
        { IsRegister, IsRegister, 3, 0, false, -1 },
        { IsRegister, IsMemory, 9, 1, true, 1 },
        { IsMemory, IsRegister, 9, 1, true, 0 },
        { IsRegister, IsImmediate, 4, 0, false, -1 },
        { IsMemory, IsImmediate, 10, 1, true, 0 },
        { IsAccumulator, IsImmediate, 4, 0, false, -1 },
    };

    const CycleEstimationSpec NOT_CYCLE_ESTIMATES[] = {
        { IsRegister, IsNone, 3, 0, false, -1 },
        { IsMemory, IsNone, 16, 2, true, 0 },
    };

    const CycleEstimationSpec AND_CYCLE_ESTIMATES[] = {
        { IsRegister, IsRegister, 3, 0, false, -1 },
        { IsRegister, IsMemory, 9, 1, true, 1 },
        { IsMemory, IsRegister, 16, 2, true, 0 },
        { IsRegister, IsImmediate, 4, 0, false, -1 },
        { IsMemory, IsImmediate, 17, 2, true, 0 },
        { IsAccumulator, IsImmediate, 4, 0, false, -1 },
    };

    const CycleEstimationSpec OR_CYCLE_ESTIMATES[] = {
        { IsRegister, IsRegister, 3, 0, false, -1 },
        { IsRegister, IsMemory, 9, 1, true, 1 },
        { IsMemory, IsRegister, 16, 2, true, 0 },
        { IsAccumulator, IsImmediate, 4, 0, false, -1 },
        { IsRegister, IsImmediate, 4, 0, false, -1 },
        { IsMemory, IsImmediate, 17, 2, true, 0 },
    };

    const CycleEstimationSpec XOR_CYCLE_ESTIMATES[] = {
        { IsRegister, IsRegister, 3, 0, false, -1 },
        { IsRegister, IsMemory, 9, 1, true, 1 },
        { IsMemory, IsRegister, 16, 2, true, 0 },
        { IsAccumulator, IsImmediate, 4, 0, false, -1 },
        { IsRegister, IsImmediate, 4, 0, false, -1 },
        { IsMemory, IsImmediate, 17, 2, true, 0 },
    };

    const CycleEstimationSpec TEST_CYCLE_ESTIMATES[] = {
        { IsRegister, IsRegister, 3, 0, false, -1 },
        { IsRegister, IsMemory, 9, 1, true, 1 },
        { IsAccumulator, IsImmediate, 4, 0, false, -1 },
        { IsRegister, IsImmediate, 5, 0, false, -1 },
        { IsMemory, IsImmediate, 11, 0, true, 0 },
    };

    const CycleEstimationSpec SHR_CYCLE_ESTIMATES[] = {
        { IsRegister, IsImmediate, 2, 0, false, -1, 0 },
        { IsRegister, IsCLRegister, 8, 0, false, -1, 4 },
        { IsMemory, IsImmediate, 15, 2, true, -1, 0 },
        { IsMemory, IsCLRegister, 20, 2, true, -1, 4 },
    };

    const CycleEstimationSpec SHL_SAL_CYCLE_ESTIMATES[] = {
        { IsRegister, IsImmediate, 2, 0, false, -1, 0 },
        { IsRegister, IsCLRegister, 8, 0, false, -1, 4 },
        { IsMemory, IsImmediate, 15, 2, true, -1, 0 },
        { IsMemory, IsCLRegister, 20, 2, true, -1, 4 },
    };

    const CycleEstimationSpec SAR_CYCLE_ESTIMATES[] = {
        { IsRegister, IsImmediate, 2, 0, false, -1, 0 },
        { IsRegister, IsCLRegister, 8, 0, false, -1, 4 },
        { IsMemory, IsImmediate, 15, 2, true, -1, 0 },
        { IsMemory, IsCLRegister, 20, 2, true, -1, 4 },
    };

    const CycleEstimationSpec PUSH_CYCLE_ESTIMATES[] = {
        { IsRegister, IsNone, 11, 1, false, -1 },
        { IsSegmentRegister, IsNone, 10, 1, false, -1 },
        { IsMemory, IsNone, 16, 2, true, 0 },
    };

    const CycleEstimationSpec POP_CYCLE_ESTIMATES[] = {
        { IsRegister, IsNone, 8, 1, false, -1 },
        { IsSegmentRegister, IsNone, 8, 1, false, -1 },
        { IsMemory, IsNone, 17, 2, true, 0 },
    };

    const CycleEstimationSpec LEA_CYCLE_ESTIMATES[] = {
        { IsReg16, IsMemory, 2, 0, true, 1 },
    };

    const CycleEstimationSpec CONDITIONAL_JUMP_CYCLE_ESTIMATES[] = {
        { IsIPIncrement, IsNone, 4, 0, false, -1 },  // no jump
        { IsIPIncrement, IsNone, 16, 0, false, -1 }, // jump
    };

    const CycleEstimationSpec JMP_CYCLE_ESTIMATES[] = {
        { IsIPIncrement, IsNone, 15, 0, false, -1 },
        { IsReg16, IsNone, 11, 0, false, -1 },
        { IsMemory, IsNone, 18, 1, true, 0 },
    };

    const CycleEstimationSpec CALL_CYCLE_ESTIMATES[] = {
        { IsIPIncrement, IsNone, 19, 1, false, -1 },
        { IsMemory, IsNone, 21, 2, true, 0 },
        { IsReg16, IsNone, 16, 1, false, -1 },
    };

    const CycleEstimationSpec RET_CYCLE_ESTIMATES[] = {
        { IsNone, IsNone, 8, 1, false, -1 },
        { IsImmediate, IsNone, 12, 1, false, -1 },
    };

    U8 EstimateOddAddressCycles(mem::Address resolved_ea,
                                U8 num_transfers)
    {
        const U8 odd_address_multiple = 4;

        return resolved_ea % 2 != 0
                   ? num_transfers * odd_address_multiple
                   : 0;
    }

    U8 EstimateEACycles(ins::MemoryAddress* memory_address)
    {
        U8 ea_cycles = 0;

        U8 num_registers = 0;
        while (memory_address->register_ids[num_registers] != cpu::Register16BitId_None)
        {
            ++num_registers;
        }

        bool has_displacement = memory_address->displacement != 0;

        if (num_registers == 0)
        {
            ea_cycles = 6;
        }
        else if (num_registers == 1)
        {
            ea_cycles = has_displacement ? 9 : 5;
        }
        else if (num_registers == 2)
        {
            cpu::Register16BitId register_1_id = memory_address->register_ids[0];
            cpu::Register16BitId register_2_id = memory_address->register_ids[1];
            bool is_fast_pair = (register_1_id == cpu::Register16BitId_BP && register_2_id == cpu::Register16BitId_DI)
                                || (register_1_id == cpu::Register16BitId_BX && register_2_id ==
                                    cpu::Register16BitId_SI);

            ea_cycles = has_displacement
                            ? is_fast_pair
                                  ? 11
                                  : 12
                            : is_fast_pair
                                  ? 7
                                  : 8;
        }

        return ea_cycles;
    }

    ExecutionEstimate EstimateFromSpec(ins::Operand* operands,
                                       exe::ExecutionResult execution_result,
                                       const CycleEstimationSpec* spec)
    {
        ExecutionEstimate estimate = {};

        estimate.num_raw_cycles = spec->num_raw_cycles;

        if (spec->memory_operand_idx == 0 || spec->memory_operand_idx == 1)
        {
            estimate.num_odd_address_cycles = EstimateOddAddressCycles(
                execution_result.resolved_ea,
                spec->num_transfers);

            if (spec->update_ea_cycles)
            {
                estimate.num_ea_cycles += EstimateEACycles(&operands[spec->memory_operand_idx].memory_address);
            }
        }

        if (spec->shift_count_multiplier)
        {
            estimate.num_raw_cycles += spec->shift_count_multiplier * execution_result.shift_count;
        }

        estimate.num_cycles = estimate.num_raw_cycles + estimate.num_odd_address_cycles + estimate.num_ea_cycles;

        return estimate;
    }

    ExecutionEstimate Estimate(ins::Operand* operands,
                               exe::ExecutionResult execution_result,
                               const CycleEstimationSpec* specs)
    {
        ExecutionEstimate estimate = {};

        for (U8 i = 0; i < CYCLE_ESTIMATES_MAX_LEN; ++i)
        {
            CycleEstimationSpec spec = specs[i];

            // NOTE: A somewhat lazy implementation, in many cases we end up checking the same predicates multiple times
            if (spec.operand_1_predicate(&operands[0]) && spec.operand_2_predicate(&operands[1]))
            {
                estimate = EstimateFromSpec(operands, execution_result, &spec);
                break;
            }
        }

        return estimate;
    }

    ExecutionEstimate EstimateForConditionalJump(ins::Operand* operands,
                                                 exe::ExecutionResult execution_result)
    {
        const CycleEstimationSpec spec = execution_result.did_branch_jump
                                             ? CONDITIONAL_JUMP_CYCLE_ESTIMATES[1]
                                             : CONDITIONAL_JUMP_CYCLE_ESTIMATES[0];

        return EstimateFromSpec(operands, execution_result, &spec);
    }

    void UpdateCycleEstimate(CycleCountEstimate* current_estimate,
                             ins::Instruction* instruction,
                             exe::ExecutionResult execution_result)
    {
        ExecutionEstimate latest_estimate = {};

        switch (instruction->mnemonic)
        {
            case ins::Mnemonic_MOV:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, MOV_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_ADD:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, ADD_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_INC:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, INC_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_DEC:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, DEC_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_SHR:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, SHR_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_SHL_SAL:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, SHL_SAL_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_SAR:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, SAR_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_SUB:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, SUB_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_CMP:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, CMP_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_NOT:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, NOT_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_AND:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, AND_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_OR:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, OR_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_XOR:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, XOR_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_TEST:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, TEST_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_PUSH:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, PUSH_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_POP:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, POP_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_LEA:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, LEA_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_CALL:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, CALL_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_RET:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, RET_CYCLE_ESTIMATES);
            } break;
            case ins::Mnemonic_JNE_JNZ:
            {
                latest_estimate = EstimateForConditionalJump(instruction->operands, execution_result);
            } break;
            case ins::Mnemonic_JMP:
            {
                latest_estimate = Estimate(instruction->operands, execution_result, JMP_CYCLE_ESTIMATES);
            } break;
            default:
            {
            } break;
        }

        current_estimate->latest = latest_estimate;
        current_estimate->total_num_cycles += latest_estimate.num_cycles;
    }
}
