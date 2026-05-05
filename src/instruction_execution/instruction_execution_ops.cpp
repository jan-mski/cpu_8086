namespace instruction_execution::ops
{
    namespace mem = ::memory;
    namespace cpu = ::cpu;
    namespace exe_res = ::instruction_execution::resolution;

    I32 GetValueA(exe_res::ResolvedInstruction* resolved_instruction,
                  cpu::CpuState* cpu_state,
                  mem::Memory* memory)
    {
        return exe_res::GetResolvedOperandValue(
            &resolved_instruction->operands[0],
            resolved_instruction->is_wide,
            cpu_state,
            memory);
    }

    I32 GetValueB(exe_res::ResolvedInstruction* resolved_instruction,
                  cpu::CpuState* cpu_state,
                  mem::Memory* memory)
    {
        return exe_res::GetResolvedOperandValue(
            &resolved_instruction->operands[1],
            resolved_instruction->is_wide,
            cpu_state,
            memory);
    }

    OpResult noop(exe_res::ResolvedInstruction* resolved_instruction,
                  cpu::CpuState* cpu_state,
                  mem::Memory* memory)
    {
        return GetValueB(resolved_instruction, cpu_state, memory);
    }

    OpResult add(exe_res::ResolvedInstruction* resolved_instruction,
                 cpu::CpuState* cpu_state,
                 mem::Memory* memory)
    {
        U16 a = GetValueA(resolved_instruction, cpu_state, memory);
        U16 b = GetValueB(resolved_instruction, cpu_state, memory);

        return a + b;
    }

    OpResult subtract(exe_res::ResolvedInstruction* resolved_instruction,
                      cpu::CpuState* cpu_state,
                      mem::Memory* memory)
    {
        U16 a = GetValueA(resolved_instruction, cpu_state, memory);
        U16 b = GetValueB(resolved_instruction, cpu_state, memory);

        return a - b;
    }

    OpResult bitwise_not(exe_res::ResolvedInstruction* resolved_instruction,
                         cpu::CpuState* cpu_state,
                         mem::Memory* memory)
    {
        U16 a = GetValueA(resolved_instruction, cpu_state, memory);

        return ~a;
    }

    OpResult bitwise_and(exe_res::ResolvedInstruction* resolved_instruction,
                         cpu::CpuState* cpu_state,
                         mem::Memory* memory)
    {
        U16 a = GetValueA(resolved_instruction, cpu_state, memory);
        U16 b = GetValueB(resolved_instruction, cpu_state, memory);

        return a & b;
    }

    OpResult bitwise_or(exe_res::ResolvedInstruction* resolved_instruction,
                        cpu::CpuState* cpu_state,
                        mem::Memory* memory)
    {
        U16 a = GetValueA(resolved_instruction, cpu_state, memory);
        U16 b = GetValueB(resolved_instruction, cpu_state, memory);

        return a | b;
    }

    OpResult bitwise_xor(exe_res::ResolvedInstruction* resolved_instruction,
                         cpu::CpuState* cpu_state,
                         mem::Memory* memory)
    {
        U16 a = GetValueA(resolved_instruction, cpu_state, memory);
        U16 b = GetValueB(resolved_instruction, cpu_state, memory);

        return a ^ b;
    }

    OpResult bitwise_shl(exe_res::ResolvedInstruction* resolved_instruction,
                         cpu::CpuState* cpu_state,
                         mem::Memory* memory)
    {
        U16 a = GetValueA(resolved_instruction, cpu_state, memory);
        U16 b = GetValueB(resolved_instruction, cpu_state, memory);

        return a << b;
    }

    OpResult bitwise_shr(exe_res::ResolvedInstruction* resolved_instruction,
                         cpu::CpuState* cpu_state,
                         mem::Memory* memory)
    {
        U16 a = GetValueA(resolved_instruction, cpu_state, memory);
        U16 b = GetValueB(resolved_instruction, cpu_state, memory);

        return a >> b;
    }

    OpResult bitwise_sar(exe_res::ResolvedInstruction* resolved_instruction,
                         cpu::CpuState* cpu_state,
                         mem::Memory* memory)
    {
        U16 result = 0;
        U16 a = GetValueA(resolved_instruction, cpu_state, memory);
        U16 b = GetValueB(resolved_instruction, cpu_state, memory);

        if (resolved_instruction->is_wide)
        {
            I16 a_signed = (I16) a;
            result = (U16) (a_signed >> b);
        }
        else
        {
            I8 a_signed = (I8) a;
            result = (U8) (a_signed >> b);
        }

        return result;
    }
}
