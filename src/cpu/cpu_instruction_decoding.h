namespace cpu::instruction_decoding::context
{
    struct DecodingContext
    {
        uint8_t bytes[6];
        uint8_t num_bytes_read;
        bool d;                    // 1 bit
        bool s;                    // 1 bit
        bool v;                    // 1 bit
        bool w;                    // 1 bit
        bool is_w_forced;
        uint8_t mod;               // 2 bits
        uint8_t sr;                // 2 bits
        uint8_t reg;               // 3 bits
        uint8_t r_m;               // 3 bits
        uint8_t opcode_extension;  // 3 bits
        uint16_t data;             // 8 || 16 bits
        uint16_t addr;             // 8 || 16 bits
        int32_t displacement;      // 8 || 16 bits
    };

    void ReadNextInstructionByte(DecodingContext *decoding_context,
                                 uint16_t instruction_pointer_value,
                                 memory::Memory *memory);
}

namespace cpu::instruction_decoding::fields
{
    const uint8_t BYTE_FIELDS_MAX_LEN = 3;

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
        DISP_8,
        DISP_LO_HI,
        DATA_8,
        DATA_LO,
        DATA_HI,
        ADDR_LO,
        ADDR_HI,
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

    void DecodeByteFields(FieldSpec *byte_field_specs,
                          uint8_t byte_idx,
                          context::DecodingContext *decoding_context,
                          memory::Memory *memory);
}

namespace cpu::instruction_decoding::operands
{
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
        LabelLikeDisplacement,
        ShiftRotateCount,
    };

    void DecodeOperands(cpu::instruction::Instruction *instruction,
                        OperandSpecType *operand_types,
                        uint8_t num_operands,
                        context::DecodingContext *decoding_context);
}

namespace cpu::instruction_decoding::specs
{
    enum class InstructionSpecType : uint8_t
    {
        None,

        Regular,
        ExtendedOpcode,
    };

    struct InstructionFormatSpec
    {
        cpu::instruction::Mnemonic mnemonic;
        operands::OperandSpecType operand_types[2];
    };

    struct InstructionSpecBody
    {
        fields::FieldSpec byte_1[fields::BYTE_FIELDS_MAX_LEN];
        fields::FieldSpec byte_2[fields::BYTE_FIELDS_MAX_LEN];
        fields::FieldSpec byte_3456[fields::BYTE_FIELDS_MAX_LEN];
        InstructionFormatSpec format;
    };

    struct InstructionSpec
    {
        InstructionSpecType type;
        InstructionSpecBody bodies[8];
    };
}

namespace cpu::instruction_decoding::core {
    cpu::instruction::Instruction DecodeInstruction(context::DecodingContext *decoding_context,
                                                    cpu::core::CpuState *cpu_state,
                                                    memory::Memory *memory);
}
