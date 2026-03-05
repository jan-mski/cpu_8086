#define ARRAY_SIZE(array) ((sizeof(array) / sizeof(array[0])))

enum Register : uint8_t
{
    Register_None,

    Register_AL,
    Register_AH,
    Register_AX,
    Register_BL,
    Register_BH,
    Register_BX,
    Register_CL,
    Register_CH,
    Register_CX,
    Register_DL,
    Register_DH,
    Register_DX,
    Register_SP,
    Register_BP,
    Register_SI,
    Register_DI,

    Register_ES,
    Register_CS,
    Register_SS,
    Register_DS,

    Register_Count
};

void DecodeInstructions(FILE *output_stream, FILE *input_stream);
