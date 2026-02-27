struct InstructionSpec
{
    Mnemonic mnemonic;
};

typedef Instruction (*inst_decoder_t)(InstructionInput *instruction_input, DecodingContext *decoding_context, InstructionSpec decoder_function_args);

struct InstructionDecodeSpec
{
    inst_decoder_t decoder_function;
    InstructionSpec instruction_spec;
};

void InitializeInstructionDecodeSpecs();
Instruction DecodeInstruction(InstructionInput *instruction_input, DecodingContext *decoding_context);
