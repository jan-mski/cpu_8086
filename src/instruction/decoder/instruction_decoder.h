enum InstructionSpecType : uint8_t
{
    InstructionSpecType_None,

    InstructionSpecType_Regular,
    InstructionSpecType_ExtendedOpcode,
};

enum FieldSpecType : uint8_t
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
    FieldSpecType_DISP_8,
    FieldSpecType_DISP,
    FieldSpecType_DATA_8,
    FieldSpecType_DATA_LO,
    FieldSpecType_DATA_HI,
    FieldSpecType_ADDR_LO,
    FieldSpecType_ADDR_HI,
    FieldSpecType_OpcodeExtension,
};

enum OperandSpecType : uint8_t
{
    OperandSpecType_None,

    OperandSpecType_Register,
    OperandSpecType_SegmentRegister,
    OperandSpecType_DataRegister,
    OperandSpecType_Accumulator,
    OperandSpecType_RegisterOrMemoryAddress,
    OperandSpecType_DirectMemoryAddress,
    OperandSpecType_Immediate,
    OperandSpecType_LabelLikeDisplacement,
    OperandSpecType_ShiftRotateCount,
};

struct FieldSpec
{
    FieldSpecType type;
    uint8_t bit_shift;
    uint8_t bit_mask;
    bool is_forced;
    uint8_t forced_value;
};

struct InstructionFormatSpec
{
    Mnemonic mnemonic;
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

Instruction DecodeInstruction(InstructionInput *instruction_input, DecodingContext *decoding_context);
