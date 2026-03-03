#define ARRAY_SIZE(array) ((sizeof(array) / sizeof(array[0])))

enum Register : uint8_t
{
    REGISTER_NONE,

    REGISTER_AL,
    REGISTER_AH,
    REGISTER_AX,
    REGISTER_BL,
    REGISTER_BH,
    REGISTER_BX,
    REGISTER_CL,
    REGISTER_CH,
    REGISTER_CX,
    REGISTER_DL,
    REGISTER_DH,
    REGISTER_DX,
    REGISTER_SP,
    REGISTER_BP,
    REGISTER_SI,
    REGISTER_DI,

    REGISTER_ES,
    REGISTER_CS,
    REGISTER_SS,
    REGISTER_DS,

    REGISTER_COUNT
};

void DecodeInstructions(FILE *output_stream, FILE *input_stream);
