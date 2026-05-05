#ifndef CYCLE_ESTIMATION_H
#define CYCLE_ESTIMATION_H

namespace cycle_estimation
{
    struct ExecutionEstimate
    {
        U8 num_cycles;
        U8 num_raw_cycles;
        U8 num_odd_address_cycles;
        U8 num_ea_cycles;
    };

    struct CycleCountEstimate
    {
        U32 total_num_cycles;
        ExecutionEstimate latest;
    };

    void UpdateCycleEstimate(CycleCountEstimate* current_estimate,
                             instruction::Instruction* instruction,
                             instruction_execution::core::ExecutionResult execution_result);
}

#endif //CYCLE_ESTIMATION_H
