#ifndef INSTRUCTION_DECODING_SPECS_H
#define INSTRUCTION_DECODING_SPECS_H

namespace instruction_decoding::specs
{
    enum FieldSpecType : U8
    {
        FieldSpecType_None,

        FieldSpecType_D,
        FieldSpecType_S,
        FieldSpecType_V,
        FieldSpecType_W,
        FieldSpecType_MOD,
        FieldSpecType_RM,
        FieldSpecType_REG,
        FieldSpecType_SR,
        FieldSpecType_IP_INC_8,
        FieldSpecType_IP_INC_LO,
        FieldSpecType_IP_INC_HI,
        FieldSpecType_DATA_8,
        FieldSpecType_DATA_LO,
        FieldSpecType_DATA_HI,
        FieldSpecType_ADDR_LO,
        FieldSpecType_ADDR_HI,
        FieldSpecType_DISP_LO_HI,
        FieldSpecType_OpcodeExtension,
    };

    struct FieldSpec
    {
        FieldSpecType type;
        U8 bit_shift;
        U8 bit_mask;
        bool is_forced;
        U8 forced_value;
    };

    enum OperandSpecType : U8
    {
        OperandSpecType_None,

        OperandSpecType_Register,
        OperandSpecType_SegmentRegister,
        OperandSpecType_DataRegister,
        OperandSpecType_Accumulator,
        OperandSpecType_RegisterOrMemoryAddress,
        OperandSpecType_MemoryAddress,
        OperandSpecType_DirectMemoryAddress,
        OperandSpecType_Immediate,
        OperandSpecType_IPIncrement,
        OperandSpecType_ShiftRotateCount,
    };

    enum InstructionSpecType : U8
    {
        InstructionSpecType_None,

        InstructionSpecType_Regular,
        InstructionSpecType_ExtendedOpcode,
    };

    struct InstructionFormatSpec
    {
        instruction::Mnemonic mnemonic;
        OperandSpecType operand_types[instruction::OPERANDS_MAX_LEN];
    };

    const U8 BYTE_FIELDS_MAX_LEN = 3;

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

#endif // INSTRUCTION_DECODING_SPECS_H
