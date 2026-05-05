#ifndef INSTRUCTION_EXECUTION_CORE_H
#define INSTRUCTION_EXECUTION_CORE_H

namespace instruction_execution::core
{
    typedef U16 ExecutionResultValue;

    struct ExecutionResult
    {
        ExecutionResultValue value;
        U8 shift_count;
        memory::Address resolved_ea;
        bool did_branch_jump;
    };

    ExecutionResult ExecuteInstruction(
        instruction::Instruction* instruction,
        cpu::CpuState* cpu_state,
        memory::Memory* memory);
}

#endif // INSTRUCTION_EXECUTION_CORE_H
