enum FieldTypeSpec
{
    FIELD_TYPE_SPEC_NONE,

    FIELD_TYPE_SPEC_D,
    FIELD_TYPE_SPEC_S,
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
    FIELD_TYPE_SPEC_ARITHMETIC_MNEMO,
};

enum OperandTypeSpec
{
    OPERAND_TYPE_SPEC_NONE,

    OPERAND_TYPE_SPEC_REGISTER,
    OPERAND_TYPE_SPEC_SEGMENT_REGISTER,
    OPERAND_TYPE_SPEC_DATA_REGISTER,
    OPERAND_TYPE_SPEC_ACCUMULATOR,
    OPERAND_TYPE_SPEC_REGISTER_OR_MEMORY_ADDRESS,
    OPERAND_TYPE_SPEC_DIRECT_MEMORY_ADDRESS,
    OPERAND_TYPE_SPEC_IMMEDIATE,
    OPERAND_TYPE_SPEC_LABEL_LIKE_DISPLACEMENT
};

struct FieldSpec
{
    FieldTypeSpec type_spec;
    uint8_t byte_index;
    uint8_t bit_shift;
    bool is_forced;
    uint8_t forced_value;
};

struct InstructionSpec
{
    Mnemonic mnemonic;
    FieldSpec field_specs[7];
    OperandTypeSpec operand_type_specs[2];
};

typedef Instruction (*inst_decoder_t)(InstructionInput *instruction_input, DecodingContext *decoding_context, InstructionSpec decoder_function_args);

struct InstructionDecodeSpec
{
    inst_decoder_t decoder_function;
    InstructionSpec instruction_spec;
};

Instruction DecodeInstruction(InstructionInput *instruction_input, DecodingContext *decoding_context);
