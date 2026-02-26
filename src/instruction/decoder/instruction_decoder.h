#define REPEAT_2(...) \
    __VA_ARGS__, __VA_ARGS__
#define REPEAT_3(...) \
    REPEAT_2(__VA_ARGS__), __VA_ARGS__
#define REPEAT_4(...) \
    REPEAT_2(__VA_ARGS__), REPEAT_2(__VA_ARGS__)
#define REPEAT_6(...) \
    REPEAT_4(__VA_ARGS__), REPEAT_2(__VA_ARGS__)
#define REPEAT_8(...) \
    REPEAT_6(__VA_ARGS__), REPEAT_2(__VA_ARGS__)
#define REPEAT_10(...) \
    REPEAT_6(__VA_ARGS__), REPEAT_4(__VA_ARGS__)
#define REPEAT_12(...) \
    REPEAT_6(__VA_ARGS__), REPEAT_6(__VA_ARGS__)
#define REPEAT_16(...) \
    REPEAT_12(__VA_ARGS__), REPEAT_4(__VA_ARGS__)
#define REPEAT_18(...) \
    REPEAT_16(__VA_ARGS__), REPEAT_2(__VA_ARGS__)
#define REPEAT_24(...) \
    REPEAT_16(__VA_ARGS__), REPEAT_8(__VA_ARGS__)
#define REPEAT_27(...) \
    REPEAT_24(__VA_ARGS__), REPEAT_2(__VA_ARGS__), __VA_ARGS__

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
