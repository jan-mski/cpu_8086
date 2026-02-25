#define REPEAT_2(x) \
    x, x
#define REPEAT_4(x) \
    REPEAT_2(x), REPEAT_2(x)
#define REPEAT_6(x) \
    REPEAT_4(x), REPEAT_2(x)
#define REPEAT_8(x) \
    REPEAT_6(x), REPEAT_2(x)
#define REPEAT_10(x) \
    REPEAT_6(x), REPEAT_4(x)
#define REPEAT_12(x) \
    REPEAT_6(x), REPEAT_6(x)
#define REPEAT_16(x) \
    REPEAT_12(x), REPEAT_4(x)
#define REPEAT_18(x) \
    REPEAT_16(x), REPEAT_2(x)
#define REPEAT_20(x) \
    REPEAT_16(x), REPEAT_4(x)
#define REPEAT_24(x) \
    REPEAT_20(x), REPEAT_4(x)
#define REPEAT_27(x) \
    REPEAT_24(x), REPEAT_2(x), x
#define REPEAT_34(x) \
    REPEAT_20(x), REPEAT_12(x), REPEAT_2(x)
#define REPEAT_50(x) \
    REPEAT_20(x), REPEAT_20(x), REPEAT_10(x)

struct DecoderFunctionArgs
{
    Mnemonic mnemonic;
};

typedef Instruction (*inst_decoder_t)(InstructionInput *instruction_input, DecodingContext *decoding_context, DecoderFunctionArgs decoder_function_args);

struct InstructionDecodeSpec
{
    inst_decoder_t decoder_function;
    DecoderFunctionArgs decoder_function_args;
};

Instruction DecodeInstruction(InstructionInput *instruction_input, DecodingContext *decoding_context);
