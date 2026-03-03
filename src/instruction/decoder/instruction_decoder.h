const uint8_t BYTE_FIELDS_MAX_LEN = 3;

enum InstructionTypeSpec : uint8_t
{
    INSTRUCTION_TYPE_NONE,

    INSTRUCTION_TYPE_REGULAR,
    INSTRUCTION_TYPE_EXTENDED_OPCODE
};

enum FieldTypeSpec : uint8_t
{
    FIELD_TYPE_SPEC_NONE,

    FIELD_TYPE_SPEC_D,
    FIELD_TYPE_SPEC_S,
    FIELD_TYPE_SPEC_V,
    FIELD_TYPE_SPEC_W,
    FIELD_TYPE_SPEC_MOD,
    FIELD_TYPE_SPEC_RM,
    FIELD_TYPE_SPEC_REG,
    FIELD_TYPE_SPEC_SR,
    FIELD_TYPE_SPEC_DISP_8,
    FIELD_TYPE_SPEC_DISP,
    FIELD_TYPE_SPEC_DATA_8,
    FIELD_TYPE_SPEC_DATA,
    FIELD_TYPE_SPEC_ADDR,
    FIELD_TYPE_SPEC_OPCODE_EXTENSION,
};

enum OperandTypeSpec : uint8_t
{
    OPERAND_TYPE_SPEC_NONE,

    OPERAND_TYPE_SPEC_REGISTER,
    OPERAND_TYPE_SPEC_SEGMENT_REGISTER,
    OPERAND_TYPE_SPEC_DATA_REGISTER,
    OPERAND_TYPE_SPEC_ACCUMULATOR,
    OPERAND_TYPE_SPEC_REGISTER_OR_MEMORY_ADDRESS,
    OPERAND_TYPE_SPEC_DIRECT_MEMORY_ADDRESS,
    OPERAND_TYPE_SPEC_IMMEDIATE,
    OPERAND_TYPE_SPEC_LABEL_LIKE_DISPLACEMENT,
    OPERAND_TYPE_SPEC_SHIFT_ROTATE_COUNT
};

struct FieldSpec
{
    FieldTypeSpec type;
    uint8_t bit_shift;
    bool is_forced;
    uint8_t forced_value;
};

struct InstructionFormatSpec
{
    Mnemonic mnemonic;
    OperandTypeSpec operand_types[2];
};

struct InstructionSpecBody
{
    FieldSpec byte_1[BYTE_FIELDS_MAX_LEN];
    FieldSpec byte_2[BYTE_FIELDS_MAX_LEN];
    FieldSpec byte_3456[BYTE_FIELDS_MAX_LEN];
    InstructionFormatSpec format;
};

struct InstructionSpec
{
    InstructionTypeSpec type;
    InstructionSpecBody bodies[8];
};

typedef Instruction (*inst_decoder_t)(InstructionInput *instruction_input, DecodingContext *decoding_context, InstructionSpec decoder_function_args);

Instruction DecodeInstruction(InstructionInput *instruction_input, DecodingContext *decoding_context);
