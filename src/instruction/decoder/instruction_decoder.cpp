#define D FIELD_TYPE_SPEC_D
#define S FIELD_TYPE_SPEC_S
#define W FIELD_TYPE_SPEC_W
#define MOD FIELD_TYPE_SPEC_MOD
#define RM FIELD_TYPE_SPEC_RM
#define REG FIELD_TYPE_SPEC_REG
#define SR FIELD_TYPE_SPEC_SR
#define DISP_8 FIELD_TYPE_SPEC_DISP_8
#define DISP FIELD_TYPE_SPEC_DISP
#define DATA FIELD_TYPE_SPEC_DATA
#define ADDR FIELD_TYPE_SPEC_ADDR
#define ARITHM_MNEMO FIELD_TYPE_SPEC_ARITHMETIC_MNEMO

#define D_FORCED(forced_value) {D, 0, 0, 1, forced_value}
#define W_FORCED(forced_value) {W, 0, 0, 1, forced_value}

#define REGISTER OPERAND_TYPE_SPEC_REGISTER
#define SEG_REGISTER OPERAND_TYPE_SPEC_SEGMENT_REGISTER
#define ACCUMULATOR OPERAND_TYPE_SPEC_ACCUMULATOR
#define REG_OR_MEM_ADDR OPERAND_TYPE_SPEC_REGISTER_OR_MEMORY_ADDRESS
#define IMMEDIATE OPERAND_TYPE_SPEC_IMMEDIATE
#define LABEL_DISP OPERAND_TYPE_SPEC_LABEL_LIKE_DISPLACEMENT
#define DIRECT_ADDR OPERAND_TYPE_SPEC_DIRECT_MEMORY_ADDRESS

InstructionSpec INSTRUCTION_SPECS[256] = {
    /* 00000000 */ {MNEMONIC_ADD, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 00000001 */ {MNEMONIC_ADD, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 00000010 */ {MNEMONIC_ADD, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 00000011 */ {MNEMONIC_ADD, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 00000100 */ {MNEMONIC_ADD, {{W, 0, 0}, {DATA}}, {ACCUMULATOR, IMMEDIATE}},
    /* 00000101 */ {MNEMONIC_ADD, {{W, 0, 0}, {DATA}}, {ACCUMULATOR, IMMEDIATE}},
    /* 00000110 */ {MNEMONIC_PUSH, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00000111 */ {MNEMONIC_POP, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00001000 */ {},
    /* 00001001 */ {},
    /* 00001010 */ {},
    /* 00001011 */ {},
    /* 00001100 */ {},
    /* 00001101 */ {},
    /* 00001110 */ {MNEMONIC_PUSH, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00001111 */ {MNEMONIC_POP, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00010000 */ {},
    /* 00010001 */ {},
    /* 00010010 */ {},
    /* 00010011 */ {},
    /* 00010100 */ {},
    /* 00010101 */ {},
    /* 00010110 */ {MNEMONIC_PUSH, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00010111 */ {MNEMONIC_POP, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00011000 */ {MNEMONIC_PUSH, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00011001 */ {MNEMONIC_PUSH, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00011010 */ {MNEMONIC_PUSH, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00011011 */ {MNEMONIC_PUSH, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00011100 */ {MNEMONIC_PUSH, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00011101 */ {MNEMONIC_PUSH, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00011110 */ {MNEMONIC_PUSH, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00011111 */ {MNEMONIC_POP, {{SR, 0, 3}}, {SEG_REGISTER}},
    /* 00100000 */ {},
    /* 00100001 */ {},
    /* 00100010 */ {},
    /* 00100011 */ {},
    /* 00100100 */ {},
    /* 00100101 */ {},
    /* 00100110 */ {},
    /* 00100111 */ {},
    /* 00101000 */ {MNEMONIC_SUB, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 00101001 */ {MNEMONIC_SUB, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 00101010 */ {MNEMONIC_SUB, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 00101011 */ {MNEMONIC_SUB, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 00101100 */ {MNEMONIC_SUB, {{W, 0, 0}, {DATA}}, {ACCUMULATOR, IMMEDIATE}},
    /* 00101101 */ {MNEMONIC_SUB, {{W, 0, 0}, {DATA}}, {ACCUMULATOR, IMMEDIATE}},
    /* 00101110 */ {},
    /* 00101111 */ {},
    /* 00110000 */ {},
    /* 00110001 */ {},
    /* 00110010 */ {},
    /* 00110011 */ {},
    /* 00110100 */ {},
    /* 00110101 */ {},
    /* 00110110 */ {},
    /* 00110111 */ {},
    /* 00111000 */ {MNEMONIC_CMP, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 00111001 */ {MNEMONIC_CMP, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 00111010 */ {MNEMONIC_CMP, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 00111011 */ {MNEMONIC_CMP, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 00111100 */ {MNEMONIC_CMP, {{W, 0, 0}, {DATA}}, {ACCUMULATOR, IMMEDIATE}},
    /* 00111101 */ {MNEMONIC_CMP, {{W, 0, 0}, {DATA}}, {ACCUMULATOR, IMMEDIATE}},
    /* 00111110 */ {},
    /* 00111111 */ {},
    /* 01000000 */ {},
    /* 01000001 */ {},
    /* 01000010 */ {},
    /* 01000011 */ {},
    /* 01000100 */ {},
    /* 01000101 */ {},
    /* 01000110 */ {},
    /* 01000111 */ {},
    /* 01001000 */ {},
    /* 01001001 */ {},
    /* 01001010 */ {},
    /* 01001011 */ {},
    /* 01001100 */ {},
    /* 01001101 */ {},
    /* 01001110 */ {},
    /* 01001111 */ {},
    /* 01010000 */ {MNEMONIC_PUSH, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01010001 */ {MNEMONIC_PUSH, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01010010 */ {MNEMONIC_PUSH, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01010011 */ {MNEMONIC_PUSH, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01010100 */ {MNEMONIC_PUSH, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01010101 */ {MNEMONIC_PUSH, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01010110 */ {MNEMONIC_PUSH, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01010111 */ {MNEMONIC_PUSH, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01011000 */ {MNEMONIC_POP, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01011001 */ {MNEMONIC_POP, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01011010 */ {MNEMONIC_POP, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01011011 */ {MNEMONIC_POP, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01011100 */ {MNEMONIC_POP, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01011101 */ {MNEMONIC_POP, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01011110 */ {MNEMONIC_POP, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01011111 */ {MNEMONIC_POP, {W_FORCED(1), {REG, 0, 0}}, {REGISTER}},
    /* 01100000 */ {},
    /* 01100001 */ {},
    /* 01100010 */ {},
    /* 01100011 */ {},
    /* 01100100 */ {},
    /* 01100101 */ {},
    /* 01100110 */ {},
    /* 01100111 */ {},
    /* 01101000 */ {},
    /* 01101001 */ {},
    /* 01101010 */ {},
    /* 01101011 */ {},
    /* 01101100 */ {},
    /* 01101101 */ {},
    /* 01101110 */ {},
    /* 01101111 */ {},
    /* 01110000 */ {MNEMONIC_JO, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01110001 */ {MNEMONIC_JNO, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01110010 */ {MNEMONIC_JB_JNAE, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01110011 */ {MNEMONIC_JNB_JAE, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01110100 */ {MNEMONIC_JE_JZ, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01110101 */ {MNEMONIC_JNE_JNZ, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01110110 */ {MNEMONIC_JBE_JNA, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01110111 */ {MNEMONIC_JNBE_JA, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01111000 */ {MNEMONIC_JS, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01111001 */ {MNEMONIC_JNS, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01111010 */ {MNEMONIC_JP_JPE, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01111011 */ {MNEMONIC_JNP_JPO, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01111100 */ {MNEMONIC_JL_JNGE, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01111101 */ {MNEMONIC_JNL_JGE, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01111110 */ {MNEMONIC_JLE_JNG, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 01111111 */ {MNEMONIC_JNLE_JG, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 10000000 */ {MNEMONIC_NONE, {{S, 0, 1}, {ARITHM_MNEMO}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {DISP}, {DATA}}, {REG_OR_MEM_ADDR, IMMEDIATE}},
    /* 10000001 */ {MNEMONIC_NONE, {{S, 0, 1}, {ARITHM_MNEMO}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {DISP}, {DATA}}, {REG_OR_MEM_ADDR, IMMEDIATE}},
    /* 10000010 */ {MNEMONIC_NONE, {{S, 0, 1}, {ARITHM_MNEMO}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {DISP}, {DATA}}, {REG_OR_MEM_ADDR, IMMEDIATE}},
    /* 10000011 */ {MNEMONIC_NONE, {{S, 0, 1}, {ARITHM_MNEMO}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {DISP}, {DATA}}, {REG_OR_MEM_ADDR, IMMEDIATE}},
    /* 10000100 */ {},
    /* 10000101 */ {},
    /* 10000110 */ {MNEMONIC_XCHG, {D_FORCED(1), {W, 0, 0}, {MOD, 1, 6}, {REG, 1, 3}, {RM, 1, 0}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 10000111 */ {MNEMONIC_XCHG, {D_FORCED(1), {W, 0, 0}, {MOD, 1, 6}, {REG, 1, 3}, {RM, 1, 0}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 10001000 */ {MNEMONIC_MOV, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 10001001 */ {MNEMONIC_MOV, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 10001010 */ {MNEMONIC_MOV, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 10001011 */ {MNEMONIC_MOV, {{D, 0, 1}, {W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {REG, 1, 3}, {DISP}}, {REG_OR_MEM_ADDR, REG_OR_MEM_ADDR}},
    /* 10001100 */ {},
    /* 10001101 */ {},
    /* 10001110 */ {},
    /* 10001111 */ {MNEMONIC_POP, {W_FORCED(1), {MOD, 1, 6}, {RM, 1, 0}, {DISP}}, {REG_OR_MEM_ADDR}},
    /* 10010000 */ {MNEMONIC_XCHG, {W_FORCED(1), {REG, 0, 0}}, {REGISTER, ACCUMULATOR}},
    /* 10010001 */ {MNEMONIC_XCHG, {W_FORCED(1), {REG, 0, 0}}, {REGISTER, ACCUMULATOR}},
    /* 10010010 */ {MNEMONIC_XCHG, {W_FORCED(1), {REG, 0, 0}}, {REGISTER, ACCUMULATOR}},
    /* 10010011 */ {MNEMONIC_XCHG, {W_FORCED(1), {REG, 0, 0}}, {REGISTER, ACCUMULATOR}},
    /* 10010100 */ {MNEMONIC_XCHG, {W_FORCED(1), {REG, 0, 0}}, {REGISTER, ACCUMULATOR}},
    /* 10010101 */ {MNEMONIC_XCHG, {W_FORCED(1), {REG, 0, 0}}, {REGISTER, ACCUMULATOR}},
    /* 10010110 */ {MNEMONIC_XCHG, {W_FORCED(1), {REG, 0, 0}}, {REGISTER, ACCUMULATOR}},
    /* 10010111 */ {MNEMONIC_XCHG, {W_FORCED(1), {REG, 0, 0}}, {REGISTER, ACCUMULATOR}},
    /* 10011000 */ {},
    /* 10011001 */ {},
    /* 10011010 */ {},
    /* 10011011 */ {},
    /* 10011100 */ {},
    /* 10011101 */ {},
    /* 10011110 */ {},
    /* 10011111 */ {},
    /* 10100000 */ {MNEMONIC_MOV, {{W, 0, 0}, {ADDR}}, {ACCUMULATOR, DIRECT_ADDR}},
    /* 10100001 */ {MNEMONIC_MOV, {{W, 0, 0}, {ADDR}}, {ACCUMULATOR, DIRECT_ADDR}},
    /* 10100010 */ {MNEMONIC_MOV, {{W, 0, 0}, {ADDR}}, {DIRECT_ADDR, ACCUMULATOR}},
    /* 10100011 */ {MNEMONIC_MOV, {{W, 0, 0}, {ADDR}}, {DIRECT_ADDR, ACCUMULATOR}},
    /* 10100100 */ {},
    /* 10100101 */ {},
    /* 10100110 */ {},
    /* 10100111 */ {},
    /* 10101000 */ {},
    /* 10101001 */ {},
    /* 10101010 */ {},
    /* 10101011 */ {},
    /* 10101100 */ {},
    /* 10101101 */ {},
    /* 10101110 */ {},
    /* 10101111 */ {},
    /* 10110000 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10110001 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10110010 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10110011 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10110100 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10110101 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10110110 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10110111 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10111000 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10111001 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10111010 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10111011 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10111100 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10111101 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10111110 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 10111111 */ {MNEMONIC_MOV, {{W, 0, 3}, {REG, 0, 0}, {DATA}}, {REGISTER, IMMEDIATE}},
    /* 11000000 */ {},
    /* 11000001 */ {},
    /* 11000010 */ {},
    /* 11000011 */ {},
    /* 11000100 */ {},
    /* 11000101 */ {},
    /* 11000110 */ {MNEMONIC_MOV, {{W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {DISP}, {DATA}}, {REG_OR_MEM_ADDR, IMMEDIATE}},
    /* 11000111 */ {MNEMONIC_MOV, {{W, 0, 0}, {MOD, 1, 6}, {RM, 1, 0}, {DISP}, {DATA}}, {REG_OR_MEM_ADDR, IMMEDIATE}},
    /* 11001000 */ {},
    /* 11001001 */ {},
    /* 11001010 */ {},
    /* 11001011 */ {},
    /* 11001100 */ {},
    /* 11001101 */ {},
    /* 11001110 */ {},
    /* 11001111 */ {},
    /* 11010000 */ {},
    /* 11010001 */ {},
    /* 11010010 */ {},
    /* 11010011 */ {},
    /* 11010100 */ {},
    /* 11010101 */ {},
    /* 11010110 */ {},
    /* 11010111 */ {},
    /* 11011000 */ {},
    /* 11011001 */ {},
    /* 11011010 */ {},
    /* 11011011 */ {},
    /* 11011100 */ {},
    /* 11011101 */ {},
    /* 11011110 */ {},
    /* 11011111 */ {},
    /* 11100000 */ {MNEMONIC_LOOPNZ_LOOPNE, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 11100001 */ {MNEMONIC_LOOPZ_LOOPE, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 11100010 */ {MNEMONIC_LOOP, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 11100011 */ {MNEMONIC_JCXZ, {{DISP_8, 1}}, {LABEL_DISP}},
    /* 11100100 */ {},
    /* 11100101 */ {},
    /* 11100110 */ {},
    /* 11100111 */ {},
    /* 11101000 */ {},
    /* 11101001 */ {},
    /* 11101010 */ {},
    /* 11101011 */ {},
    /* 11101100 */ {},
    /* 11101101 */ {},
    /* 11101110 */ {},
    /* 11101111 */ {},
    /* 11110000 */ {},
    /* 11110001 */ {},
    /* 11110010 */ {},
    /* 11110011 */ {},
    /* 11110100 */ {},
    /* 11110101 */ {},
    /* 11110110 */ {},
    /* 11110111 */ {},
    /* 11111000 */ {},
    /* 11111001 */ {},
    /* 11111010 */ {},
    /* 11111011 */ {},
    /* 11111100 */ {},
    /* 11111101 */ {},
    /* 11111110 */ {},
    /* 11111111 */ {MNEMONIC_PUSH, {W_FORCED(1), {MOD, 1, 6}, {RM, 1, 0}, {DISP}}, {REG_OR_MEM_ADDR}},
};

Mnemonic SIGNED_ARITHMETIC_MNEMONICS[] = {
    MNEMONIC_ADD,
    MNEMONIC_NONE,
    MNEMONIC_NONE, // "adc" - unsupported
    MNEMONIC_NONE, // "sbb" - unsupported
    MNEMONIC_NONE,
    MNEMONIC_SUB,
    MNEMONIC_NONE,
    MNEMONIC_CMP
};

Instruction DecodeInstruction(InstructionInput *instruction_input,
                              DecodingContext *decoding_context,
                              InstructionSpec *instruction_spec)
{
    Instruction instruction = {instruction_spec->mnemonic};

    for (uint8_t i = 0; i < ARRAY_SIZE(instruction_spec->field_specs); ++i)
    {
        FieldSpec field_spec = instruction_spec->field_specs[i];

        if (field_spec.type_spec == FIELD_TYPE_SPEC_NONE)
        {
            break;
        }

        switch (field_spec.type_spec)
        {
            case FIELD_TYPE_SPEC_NONE:
            {

            } break;
            case FIELD_TYPE_SPEC_D:
            {
                DecodeD(field_spec, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_S:
            {
                DecodeS(field_spec, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_W:
            {
                DecodeW(field_spec, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_MOD:
            {
                DecodeMod(instruction_input, field_spec.bit_shift, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_RM:
            {
                DecodeRM(instruction_input, field_spec.bit_shift, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_REG:
            {
                DecodeReg(instruction_input, field_spec.byte_index, field_spec.bit_shift, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_SR:
            {
                DecodeSR(instruction_input, field_spec.byte_index, field_spec.bit_shift, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_DISP_8:
            {
                DecodeDisplacement8Bit(instruction_input, field_spec.byte_index, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_DISP:
            {
                DecodeDisplacement(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_DATA:
            {
                DecodeData(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_ADDR:
            {
                DecodeAddr(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_ARITHMETIC_MNEMO:
            {
                DecodeArithmeticMnemonic(instruction_input, decoding_context);
                instruction.mnemonic = SIGNED_ARITHMETIC_MNEMONICS[decoding_context->common_mnemonic];
            } break;
        }
    }

    if ((instruction_spec->operand_type_specs[0] == OPERAND_TYPE_SPEC_REGISTER_OR_MEMORY_ADDRESS &&
        instruction_spec->operand_type_specs[1] == OPERAND_TYPE_SPEC_REGISTER_OR_MEMORY_ADDRESS))
    {
        DecodeOperandsRegisterOrMemoryAndEither(&instruction, decoding_context);

        return instruction;
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(instruction_spec->operand_type_specs); ++i)
    {
        OperandTypeSpec operand_type_spec = instruction_spec->operand_type_specs[i];

        if (operand_type_spec == OPERAND_TYPE_SPEC_NONE)
        {
            break;
        }

        switch (operand_type_spec)
        {
            case OPERAND_TYPE_SPEC_NONE:
            {

            } break;
            case OPERAND_TYPE_SPEC_REGISTER:
            {
                DecodeOperandRegister(&instruction.operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_SEGMENT_REGISTER:
            {
                DecodeOperandSegmentRegister(&instruction.operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_REGISTER_OR_MEMORY_ADDRESS:
            {
                DecodeOperandRegisterOrMemoryAddress(&instruction.operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_DIRECT_MEMORY_ADDRESS:
            {
                DecodeOperandDirectAddress(&instruction.operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_ACCUMULATOR:
            {
                DecodeOperandAccumulator(&instruction.operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_IMMEDIATE:
            {
                DecodeOperandImmediate(&instruction.operands[1], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_LABEL_LIKE_DISPLACEMENT:
            {
                DecodeOperandLabelLikeDisplacement(&instruction.operands[0], decoding_context);
            } break;
        }
    }

    return instruction;
}

Instruction DecodeInstruction(InstructionInput *instruction_input,
                              DecodingContext *decoding_context)
{
    InstructionSpec instruction_spec = INSTRUCTION_SPECS[decoding_context->bytes[0]];

    return DecodeInstruction(instruction_input, decoding_context, &instruction_spec);
}
