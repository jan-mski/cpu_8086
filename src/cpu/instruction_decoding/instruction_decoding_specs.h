#ifndef CPU_INSTRUCTION_DECODING_SPECS_H
#define CPU_INSTRUCTION_DECODING_SPECS_H

namespace cpu::instruction_decoding::specs
{
    enum class FieldSpecType : uint8_t
    {
        None,

        D,
        S,
        V,
        W,
        MOD,
        RM,
        REG,
        SR,
        IP_INC_8,
        IP_INC_LO,
        IP_INC_HI,
        DATA_8,
        DATA_LO,
        DATA_HI,
        ADDR_LO,
        ADDR_HI,
        DISP_LO_HI,
        OpcodeExtension,
    };

    struct FieldSpec
    {
        FieldSpecType type;
        uint8_t bit_shift;
        uint8_t bit_mask;
        bool is_forced;
        uint8_t forced_value;
    };

    enum class OperandSpecType : uint8_t
    {
        None,

        Register,
        SegmentRegister,
        DataRegister,
        Accumulator,
        RegisterOrMemoryAddress,
        DirectMemoryAddress,
        Immediate,
        IPIncrement,
        ShiftRotateCount,
    };

    enum class InstructionSpecType : uint8_t
    {
        None,

        Regular,
        ExtendedOpcode,
    };

    struct InstructionFormatSpec
    {
        cpu::instruction::Mnemonic mnemonic;
        OperandSpecType operand_types[2];
    };

    const uint8_t BYTE_FIELDS_MAX_LEN = 3;

    struct InstructionSpecBody
    {
        FieldSpec byte_1[BYTE_FIELDS_MAX_LEN];
        FieldSpec byte_2[BYTE_FIELDS_MAX_LEN];
        FieldSpec byte_3456[BYTE_FIELDS_MAX_LEN];
        InstructionFormatSpec format;
    };

    struct InstructionSpec
    {
        InstructionSpecType type;
        InstructionSpecBody bodies[8];
    };
}

#include "instruction_decoding_specs.inl"

#endif // CPU_INSTRUCTION_DECODING_SPECS_H
