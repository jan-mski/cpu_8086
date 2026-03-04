#define T_REGULAR INSTRUCTION_TYPE_REGULAR
#define T_EXTENDED INSTRUCTION_TYPE_EXTENDED_OPCODE

#define D FIELD_TYPE_SPEC_D
#define S FIELD_TYPE_SPEC_S
#define V FIELD_TYPE_SPEC_V
#define W FIELD_TYPE_SPEC_W
#define MOD FIELD_TYPE_SPEC_MOD
#define RM FIELD_TYPE_SPEC_RM
#define REG FIELD_TYPE_SPEC_REG
#define SR FIELD_TYPE_SPEC_SR
#define DISP_8 FIELD_TYPE_SPEC_DISP_8
#define DISP FIELD_TYPE_SPEC_DISP
#define DATA_8 FIELD_TYPE_SPEC_DATA_8
#define IGNORED_8 FIELD_TYPE_SPEC_DATA_8
#define DATA FIELD_TYPE_SPEC_DATA
#define ADDR FIELD_TYPE_SPEC_ADDR

#define D_FORCED(forced_value) {D, 0, 1, forced_value}
#define W_FORCED(forced_value) {W, 0, 1, forced_value}

#define O_REG OPERAND_TYPE_SPEC_REGISTER
#define O_SEG_REG OPERAND_TYPE_SPEC_SEGMENT_REGISTER
#define O_DATA_REG OPERAND_TYPE_SPEC_DATA_REGISTER
#define O_ACC OPERAND_TYPE_SPEC_ACCUMULATOR
#define O_REG_OR_MEM OPERAND_TYPE_SPEC_REGISTER_OR_MEMORY_ADDRESS
#define O_IMM OPERAND_TYPE_SPEC_IMMEDIATE
#define O_LABEL_DISP OPERAND_TYPE_SPEC_LABEL_LIKE_DISPLACEMENT
#define O_DIRECT_ADDR OPERAND_TYPE_SPEC_DIRECT_MEMORY_ADDRESS
#define O_SHIFT_CNT OPERAND_TYPE_SPEC_SHIFT_ROTATE_COUNT

#define OPCODE_EXT_BYTE_FIELDS {{MOD, 6}, {FIELD_TYPE_SPEC_OPCODE_EXTENSION, 3}, {RM, 0}}

const uint8_t OPCODE_EXT_BYTE_INDEX = 1;

const InstructionSpec INSTRUCTION_SPECS[256] = {
    /* 00000000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_ADD, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00000001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_ADD, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00000010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_ADD, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00000011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_ADD, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00000100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_ADD, {O_ACC, O_IMM}}}}},
    /* 00000101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_ADD, {O_ACC, O_IMM}}}}},
    /* 00000110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{SR, 3}},           .byte_2 {},                                     .byte_3456 {},          .format {MNEMONIC_PUSH, {O_SEG_REG}}}}},
    /* 00000111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{SR, 3}},           .byte_2 {},                                     .byte_3456 {},          .format {MNEMONIC_POP, {O_SEG_REG}}}}},
    /* 00001000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_OR, {O_REG_OR_MEM, O_REG_OR_MEM}} }} },
    /* 00001001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_OR, {O_REG_OR_MEM, O_REG_OR_MEM}} }} },
    /* 00001010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_OR, {O_REG_OR_MEM, O_REG_OR_MEM}} }} },
    /* 00001011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_OR, {O_REG_OR_MEM, O_REG_OR_MEM}} }} },
    /* 00001100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_OR, {O_ACC, O_IMM}} }} },
    /* 00001101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_OR, {O_ACC, O_IMM}} }} },
    /* 00001110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{SR, 3}},           .byte_2 {},                                     .byte_3456 {},          .format {MNEMONIC_PUSH, {O_SEG_REG}}}}},
    /* 00001111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{SR, 3}},           .byte_2 {},                                     .byte_3456 {},          .format {MNEMONIC_POP, {O_SEG_REG}}}}},
    /* 00010000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_ADC, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00010001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_ADC, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00010010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_ADC, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00010011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_ADC, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00010100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_ADC, {O_ACC, O_IMM}}}}},
    /* 00010101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_ADC, {O_ACC, O_IMM}}}}},
    /* 00010110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{SR, 3}},           .byte_2 {},                                     .byte_3456 {},          .format {MNEMONIC_PUSH, {O_SEG_REG}}}}},
    /* 00010111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{SR, 3}},           .byte_2 {},                                     .byte_3456 {},          .format {MNEMONIC_POP, {O_SEG_REG}}}}},
    /* 00011000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_SBB, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00011001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_SBB, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00011010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_SBB, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00011011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_SBB, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00011100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_SBB, {O_ACC, O_IMM}}}}},
    /* 00011101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_SBB, {O_ACC, O_IMM}}}}},
    /* 00011110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{SR, 3}},           .byte_2 {},                                     .byte_3456 {},          .format {MNEMONIC_PUSH, {O_SEG_REG}}}}},
    /* 00011111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{SR, 3}},           .byte_2 {},                                     .byte_3456 {},          .format {MNEMONIC_POP, {O_SEG_REG}}}}},
    /* 00100000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_AND, {O_REG_OR_MEM, O_REG_OR_MEM}} }}},
    /* 00100001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_AND, {O_REG_OR_MEM, O_REG_OR_MEM}} }}},
    /* 00100010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_AND, {O_REG_OR_MEM, O_REG_OR_MEM}} }}},
    /* 00100011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_AND, {O_REG_OR_MEM, O_REG_OR_MEM}} }}},
    /* 00100100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_AND, {O_ACC, O_IMM}} }}},
    /* 00100101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_AND, {O_ACC, O_IMM}} }}},
    /* 00100110 */ {},
    /* 00100111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},                     .byte_2 {},                                     .byte_3456 {},          .format {MNEMONIC_DAA, {}} }} },
    /* 00101000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_SUB, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00101001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_SUB, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00101010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_SUB, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00101011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_SUB, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00101100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_SUB, {O_ACC, O_IMM}}}}},
    /* 00101101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_SUB, {O_ACC, O_IMM}}}}},
    /* 00101110 */ {},
    /* 00101111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},                     .byte_2 {},                                     .byte_3456 {},          .format {MNEMONIC_DAS, {}} }} },
    /* 00110000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_XOR, {O_REG_OR_MEM, O_REG_OR_MEM}} }} },
    /* 00110001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_XOR, {O_REG_OR_MEM, O_REG_OR_MEM}} }} },
    /* 00110010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_XOR, {O_REG_OR_MEM, O_REG_OR_MEM}} }} },
    /* 00110011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_XOR, {O_REG_OR_MEM, O_REG_OR_MEM}} }} },
    /* 00110100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_XOR, {O_ACC, O_IMM}} }} },
    /* 00110101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_XOR, {O_ACC, O_IMM}} }} },
    /* 00110110 */ {},
    /* 00110111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},                     .byte_2 {},                                     .byte_3456 {},          .format {MNEMONIC_AAA, {}} }} },
    /* 00111000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_CMP, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00111001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_CMP, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00111010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_CMP, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00111011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_CMP, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 00111100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_CMP, {O_ACC, O_IMM}}}}},
    /* 00111101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},            .byte_2 {{DATA}},                            .byte_3456 {},          .format {MNEMONIC_CMP, {O_ACC, O_IMM}}}}},
    /* 00111110 */ {},
    /* 00111111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},                            .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_AAS, {}} }} },
    /* 01000000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_INC, {O_REG}}}} },
    /* 01000001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_INC, {O_REG}}}} },
    /* 01000010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_INC, {O_REG}}}} },
    /* 01000011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_INC, {O_REG}}}} },
    /* 01000100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_INC, {O_REG}}}} },
    /* 01000101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_INC, {O_REG}}}} },
    /* 01000110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_INC, {O_REG}}}} },
    /* 01000111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_INC, {O_REG}}}} },
    /* 01001000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_DEC, {O_REG}}}} },
    /* 01001001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_DEC, {O_REG}}}} },
    /* 01001010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_DEC, {O_REG}}}} },
    /* 01001011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_DEC, {O_REG}}}} },
    /* 01001100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_DEC, {O_REG}}}} },
    /* 01001101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_DEC, {O_REG}}}} },
    /* 01001110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_DEC, {O_REG}}}} },
    /* 01001111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_DEC, {O_REG}}}} },
    /* 01010000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_PUSH, {O_REG}}}}},
    /* 01010001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_PUSH, {O_REG}}}}},
    /* 01010010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_PUSH, {O_REG}}}}},
    /* 01010011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_PUSH, {O_REG}}}}},
    /* 01010100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_PUSH, {O_REG}}}}},
    /* 01010101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_PUSH, {O_REG}}}}},
    /* 01010110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_PUSH, {O_REG}}}}},
    /* 01010111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_PUSH, {O_REG}}}}},
    /* 01011000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_POP, {O_REG}}}}},
    /* 01011001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_POP, {O_REG}}}}},
    /* 01011010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_POP, {O_REG}}}}},
    /* 01011011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_POP, {O_REG}}}}},
    /* 01011100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_POP, {O_REG}}}}},
    /* 01011101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_POP, {O_REG}}}}},
    /* 01011110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_POP, {O_REG}}}}},
    /* 01011111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_POP, {O_REG}}}}},
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
    /* 01110000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JO, {O_LABEL_DISP}}}}},
    /* 01110001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JNO, {O_LABEL_DISP}}}}},
    /* 01110010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JB_JNAE, {O_LABEL_DISP}}}}},
    /* 01110011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JNB_JAE, {O_LABEL_DISP}}}}},
    /* 01110100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JE_JZ, {O_LABEL_DISP}}}}},
    /* 01110101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JNE_JNZ, {O_LABEL_DISP}}}}},
    /* 01110110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JBE_JNA, {O_LABEL_DISP}}}}},
    /* 01110111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JNBE_JA, {O_LABEL_DISP}}}}},
    /* 01111000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JS, {O_LABEL_DISP}}}}},
    /* 01111001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JNS, {O_LABEL_DISP}}}}},
    /* 01111010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JP_JPE, {O_LABEL_DISP}}}}},
    /* 01111011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JNP_JPO, {O_LABEL_DISP}}}}},
    /* 01111100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JL_JNGE, {O_LABEL_DISP}}}}},
    /* 01111101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JNL_JGE, {O_LABEL_DISP}}}}},
    /* 01111110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JLE_JNG, {O_LABEL_DISP}}}}},
    /* 01111111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DISP_8, 1}}, .byte_3456 {},.format {MNEMONIC_JNLE_JG, {O_LABEL_DISP}}}}},
    /* 10000000 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_ADD, {O_REG_OR_MEM, O_IMM}}},
        /* 001 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_OR, {O_REG_OR_MEM, O_IMM}}},
        /* 010 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_ADC, {O_REG_OR_MEM, O_IMM}}},
        /* 011 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_SBB, {O_REG_OR_MEM, O_IMM}}},
        /* 100 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_AND, {O_REG_OR_MEM, O_IMM}}},
        /* 101 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_SUB, {O_REG_OR_MEM, O_IMM}}},
        /* 110 */ { .byte_1 {{W, 0}},            .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_XOR, {O_REG_OR_MEM, O_IMM}}},
        /* 111 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_CMP, {O_REG_OR_MEM, O_IMM}}},
    }},
    /* 10000001 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_ADD, {O_REG_OR_MEM, O_IMM}}},
        /* 001 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_OR, {O_REG_OR_MEM, O_IMM}}},
        /* 010 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_ADC, {O_REG_OR_MEM, O_IMM}}},
        /* 011 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_SBB, {O_REG_OR_MEM, O_IMM}}},
        /* 100 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_AND, {O_REG_OR_MEM, O_IMM}}},
        /* 101 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_SUB, {O_REG_OR_MEM, O_IMM}}},
        /* 110 */ { .byte_1 {{W, 0}},            .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_XOR, {O_REG_OR_MEM, O_IMM}}},
        /* 111 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_CMP, {O_REG_OR_MEM, O_IMM}}},
    }},
    /* 10000010 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_ADD, {O_REG_OR_MEM, O_IMM}}},
        /* 001 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_OR, {O_REG_OR_MEM, O_IMM}}},
        /* 010 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_ADC, {O_REG_OR_MEM, O_IMM}}},
        /* 011 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_SBB, {O_REG_OR_MEM, O_IMM}}},
        /* 100 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_AND, {O_REG_OR_MEM, O_IMM}}},
        /* 101 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_SUB, {O_REG_OR_MEM, O_IMM}}},
        /* 110 */ {},
        /* 111 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_CMP, {O_REG_OR_MEM, O_IMM}}},
    }},
    /* 10000011 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_ADD, {O_REG_OR_MEM, O_IMM}}},
        /* 001 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_OR, {O_REG_OR_MEM, O_IMM}}},
        /* 010 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_ADC, {O_REG_OR_MEM, O_IMM}}},
        /* 011 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_SBB, {O_REG_OR_MEM, O_IMM}}},
        /* 100 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_AND, {O_REG_OR_MEM, O_IMM}}},
        /* 101 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_SUB, {O_REG_OR_MEM, O_IMM}}},
        /* 110 */ {},
        /* 111 */ { .byte_1 {{S, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_CMP, {O_REG_OR_MEM, O_IMM}}},
    }},
    /* 10000100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}},        .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}},     .byte_3456 {{DISP}},            .format {MNEMONIC_TEST, {O_REG_OR_MEM, O_REG}} }}},
    /* 10000101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}},        .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}},     .byte_3456 {{DISP}},            .format {MNEMONIC_TEST, {O_REG_OR_MEM, O_REG}} }}},
    /* 10000110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {D_FORCED(1), {W, 0}},   .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}},     .byte_3456 {{DISP}},            .format {MNEMONIC_XCHG, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 10000111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {D_FORCED(1), {W, 0}},   .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}},     .byte_3456 {{DISP}},            .format {MNEMONIC_XCHG, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 10001000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}},        .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}},     .byte_3456 {{DISP}},            .format {MNEMONIC_MOV, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 10001001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}},        .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}},     .byte_3456 {{DISP}},            .format {MNEMONIC_MOV, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 10001010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}},        .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}},     .byte_3456 {{DISP}},            .format {MNEMONIC_MOV, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 10001011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{D, 1}, {W, 0}},        .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}},     .byte_3456 {{DISP}},            .format {MNEMONIC_MOV, {O_REG_OR_MEM, O_REG_OR_MEM}}}}},
    /* 10001100 */ {},
    /* 10001101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1)},              .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}},     .byte_3456 {{DISP}},            .format {MNEMONIC_LEA, {O_REG, O_REG_OR_MEM}}}}},
    /* 10001110 */ {},
    /* 10001111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1)},              .byte_2 {{MOD, 6}, {RM, 0}},                  .byte_3456 {{DISP}},            .format {MNEMONIC_POP, {O_REG_OR_MEM}}}}},
    /* 10010000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_XCHG, {O_REG, O_ACC}}}}},
    /* 10010001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_XCHG, {O_REG, O_ACC}}}}},
    /* 10010010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_XCHG, {O_REG, O_ACC}}}}},
    /* 10010011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_XCHG, {O_REG, O_ACC}}}}},
    /* 10010100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_XCHG, {O_REG, O_ACC}}}}},
    /* 10010101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_XCHG, {O_REG, O_ACC}}}}},
    /* 10010110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_XCHG, {O_REG, O_ACC}}}}},
    /* 10010111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1), {REG, 0}}, .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_XCHG, {O_REG, O_ACC}}}}},
    /* 10011000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},                            .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_CBW, {}} }} },
    /* 10011001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},                            .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_CWD, {}} }} },
    /* 10011010 */ {},
    /* 10011011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},                            .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_WAIT, {}} }} },
    /* 10011100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},                            .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_PUSHF, {}}}}},
    /* 10011101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},                            .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_POPF, {}}}}},
    /* 10011110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},                            .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_SAHF, {}}}}},
    /* 10011111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},                            .byte_2 {},                                         .byte_3456 {},                     .format {MNEMONIC_LAHF, {}}}}},
    /* 10100000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},                   .byte_2 {{ADDR}},                                .byte_3456 {},                     .format {MNEMONIC_MOV, {O_ACC, O_DIRECT_ADDR}}}}},
    /* 10100001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},                   .byte_2 {{ADDR}},                                .byte_3456 {},                     .format {MNEMONIC_MOV, {O_ACC, O_DIRECT_ADDR}}}}},
    /* 10100010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},                   .byte_2 {{ADDR}},                                .byte_3456 {},                     .format {MNEMONIC_MOV, {O_DIRECT_ADDR, O_ACC}}}}},
    /* 10100011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},                   .byte_2 {{ADDR}},                                .byte_3456 {},                     .format {MNEMONIC_MOV, {O_DIRECT_ADDR, O_ACC}}}}},
    /* 10100100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_MOVSB, {}} }}},
    /* 10100101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_MOVSW, {}} }}},
    /* 10100110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_CMPSB, {}} }}},
    /* 10100111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_CMPSW, {}} }}},
    /* 10101000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_TEST, {O_ACC, O_IMM}} }}},
    /* 10101001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_TEST, {O_ACC, O_IMM}} }}},
    /* 10101010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_STOSB, {}} }}},
    /* 10101011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_STOSW, {}} }}},
    /* 10101100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_LODSB, {}} }}},
    /* 10101101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_LODSW, {}} }}},
    /* 10101110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_SCASB, {}} }}},
    /* 10101111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_SCASW, {}} }}},
    /* 10110000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10110001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10110010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10110011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10110100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10110101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10110110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10110111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10111000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10111001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10111010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10111011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10111100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10111101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10111110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 10111111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 3}, {REG, 0}}, .byte_2 {{DATA}}, .byte_3456 {}, .format {MNEMONIC_MOV, {O_REG, O_IMM}}}}},
    /* 11000000 */ {},
    /* 11000001 */ {},
    /* 11000010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1)}, .byte_2 {{DATA}},                            .byte_3456 {},                     .format {MNEMONIC_RET, {O_IMM}}}}},
    /* 11000011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},               .byte_2 {},                                     .byte_3456 {},                     .format {MNEMONIC_RET, {}}}}},
    /* 11000100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1)}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}},            .format {MNEMONIC_LES, {O_REG, O_REG_OR_MEM}}}}},
    /* 11000101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {W_FORCED(1)}, .byte_2 {{MOD, 6}, {REG, 3}, {RM, 0}}, .byte_3456 {{DISP}},            .format {MNEMONIC_LDS, {O_REG, O_REG_OR_MEM}}}}},
    /* 11000110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},      .byte_2 {{MOD, 6}, {RM, 0}},              .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_MOV, {O_REG_OR_MEM, O_IMM}}}}},
    /* 11000111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}},      .byte_2 {{MOD, 6}, {RM, 0}},              .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_MOV, {O_REG_OR_MEM, O_IMM}}}}},
    /* 11001000 */ {},
    /* 11001001 */ {},
    /* 11001010 */ {},
    /* 11001011 */ {},
    /* 11001100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {},            .byte_3456 {}, .format {MNEMONIC_INT3, {}}}}},
    /* 11001101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{DATA_8}}, .byte_3456 {}, .format {MNEMONIC_INT, {O_IMM}}}}},
    /* 11001110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {},            .byte_3456 {}, .format {MNEMONIC_INTO, {}}}}},
    /* 11001111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {},            .byte_3456 {}, .format {MNEMONIC_IRET, {}}}}},
    /* 11010000 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_ROL, {O_REG_OR_MEM, O_SHIFT_CNT}}},
        /* 001 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_ROR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 010 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_RCL, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 011 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_RCR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 100 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_SHL_SAL, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 101 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_SHR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 110 */ {},
        /* 111 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_SAR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
    }},
    /* 11010001 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_ROL, {O_REG_OR_MEM, O_SHIFT_CNT}}},
        /* 001 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_ROR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 010 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_RCL, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 011 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_RCR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 100 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_SHL_SAL, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 101 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_SHR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 110 */ {},
        /* 111 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_SAR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
    }},
    /* 11010010 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_ROL, {O_REG_OR_MEM, O_SHIFT_CNT}}},
        /* 001 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_ROR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 010 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_RCL, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 011 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_RCR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 100 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_SHL_SAL, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 101 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_SHR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 110 */ {},
        /* 111 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_SAR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
    }},
    /* 11010011 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_ROL, {O_REG_OR_MEM, O_SHIFT_CNT}}},
        /* 001 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_ROR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 010 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_RCL, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 011 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_RCR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 100 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_SHL_SAL, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 101 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_SHR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
        /* 110 */ {},
        /* 111 */ { .byte_1 {{V, 1}, {W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_SAR, {O_REG_OR_MEM, O_SHIFT_CNT}} },
    }},
    /* 11010100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{IGNORED_8}}, .byte_3456 {}, .format {MNEMONIC_AAM, {}} }} },
    /* 11010101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {{IGNORED_8}}, .byte_3456 {}, .format {MNEMONIC_AAD, {}} }} },
    /* 11010110 */ {},
    /* 11010111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_XLAT, {}}}}},
    /* 11011000 */ {},
    /* 11011001 */ {},
    /* 11011010 */ {},
    /* 11011011 */ {},
    /* 11011100 */ {},
    /* 11011101 */ {},
    /* 11011110 */ {},
    /* 11011111 */ {},
    /* 11100000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},          .byte_2 {{DISP_8, 1}}, .byte_3456 {}, .format {MNEMONIC_LOOPNZ_LOOPNE, {O_LABEL_DISP}}}}},
    /* 11100001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},          .byte_2 {{DISP_8, 1}}, .byte_3456 {}, .format {MNEMONIC_LOOPZ_LOOPE, {O_LABEL_DISP}}}}},
    /* 11100010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},          .byte_2 {{DISP_8, 1}}, .byte_3456 {}, .format {MNEMONIC_LOOP, {O_LABEL_DISP}}}}},
    /* 11100011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {},          .byte_2 {{DISP_8, 1}}, .byte_3456 {}, .format {MNEMONIC_JCXZ, {O_LABEL_DISP}}}}},
    /* 11100100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}}, .byte_2 {{DATA_8}},    .byte_3456 {}, .format {MNEMONIC_IN, {O_ACC, O_IMM}}}}},
    /* 11100101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}}, .byte_2 {{DATA_8}},    .byte_3456 {}, .format {MNEMONIC_IN, {O_ACC, O_IMM}}}}},
    /* 11100110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}}, .byte_2 {{DATA_8}},    .byte_3456 {}, .format {MNEMONIC_OUT, {O_IMM, O_ACC}}}}},
    /* 11100111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}}, .byte_2 {{DATA_8}},    .byte_3456 {}, .format {MNEMONIC_OUT, {O_IMM, O_ACC}}}}},
    /* 11101000 */ {},
    /* 11101001 */ {},
    /* 11101010 */ {},
    /* 11101011 */ {},
    /* 11101100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_IN, {O_ACC, O_DATA_REG}}}}},
    /* 11101101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_IN, {O_ACC, O_DATA_REG}}}}},
    /* 11101110 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_OUT, {O_DATA_REG, O_ACC}}}}},
    /* 11101111 */ { .type = T_REGULAR, .bodies {{ .byte_1 {{W, 0}}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_OUT, {O_DATA_REG, O_ACC}}}}},
    /* 11110000 */ {},
    /* 11110001 */ {},
    /* 11110010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_REP, {}} }}},
    /* 11110011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_REP, {}} }}},
    /* 11110100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_HLT, {}} }} },
    /* 11110101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_CMC, {}} }} },
    /* 11110110 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_TEST, {O_REG_OR_MEM, O_IMM}}},
        /* 001 */ {},
        /* 010 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_NOT, {O_REG_OR_MEM}} },
        /* 011 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_NEG, {O_REG_OR_MEM}} },
        /* 100 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_MUL, {O_REG_OR_MEM}} },
        /* 101 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_IMUL, {O_REG_OR_MEM}} },
        /* 110 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_DIV, {O_REG_OR_MEM}} },
        /* 111 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_IDIV, {O_REG_OR_MEM}} },
    }},
    /* 11110111 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}, {DATA}}, .format {MNEMONIC_TEST, {O_REG_OR_MEM, O_IMM}}},
        /* 001 */ {},
        /* 010 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_NOT, {O_REG_OR_MEM}} },
        /* 011 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_NEG, {O_REG_OR_MEM}} },
        /* 100 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_MUL, {O_REG_OR_MEM}} },
        /* 101 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_IMUL, {O_REG_OR_MEM}} },
        /* 110 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_DIV, {O_REG_OR_MEM}} },
        /* 111 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_IDIV, {O_REG_OR_MEM}} },
    }},
    /* 11111000 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_CLC, {}} }} },
    /* 11111001 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_STC, {}} }} },
    /* 11111010 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_CLI, {}} }} },
    /* 11111011 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_STI, {}} }} },
    /* 11111100 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_CLD, {}} }} },
    /* 11111101 */ { .type = T_REGULAR, .bodies {{ .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {MNEMONIC_STD, {}} }} },
    /* 11111110 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_INC, {O_REG_OR_MEM}}},
        /* 001 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_DEC, {O_REG_OR_MEM}}},
        /* 010 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_CALL, {O_REG_OR_MEM}}},
        /* 011 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_CALL, {O_REG_OR_MEM}}},
        /* 100 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_JMP, {O_REG_OR_MEM}}},
        /* 101 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_JMP, {O_REG_OR_MEM}}},
        /* 110 */ { .byte_1 {W_FORCED(1)}, .byte_2 {{MOD, 6}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_PUSH, {O_REG_OR_MEM}}},
        /* 111 */ {},
    }},
    /* 11111111 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_INC, {O_REG_OR_MEM}}},
        /* 001 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_DEC, {O_REG_OR_MEM}}},
        /* 010 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_CALL, {O_REG_OR_MEM}}},
        /* 011 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_CALL, {O_REG_OR_MEM}}},
        /* 100 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_JMP, {O_REG_OR_MEM}}},
        /* 101 */ { .byte_1 {{W, 0}}, .byte_2 = OPCODE_EXT_BYTE_FIELDS, .byte_3456 {{DISP}}, .format {MNEMONIC_JMP, {O_REG_OR_MEM}}},
        /* 110 */ { .byte_1 {W_FORCED(1)}, .byte_2 {{MOD, 6}, {RM, 0}}, .byte_3456 {{DISP}}, .format {MNEMONIC_PUSH, {O_REG_OR_MEM}}},
        /* 111 */ {},
    }},
};

void DecodeByteFields(FieldSpec *byte_field_specs,
                      size_t byte_field_specs_size,
                      uint8_t byte_index,
                      InstructionInput *instruction_input,
                      DecodingContext *decoding_context)
{
    for (uint8_t i = 0; i < byte_field_specs_size; ++i)
    {
        FieldSpec field_spec = byte_field_specs[i];

        if (field_spec.type == FIELD_TYPE_SPEC_NONE)
        {
            break;
        }

        switch (field_spec.type)
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
            case FIELD_TYPE_SPEC_V:
            {
                DecodeV(field_spec, decoding_context);
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
                DecodeReg(instruction_input, byte_index, field_spec.bit_shift, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_SR:
            {
                DecodeSR(instruction_input, byte_index, field_spec.bit_shift, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_DISP_8:
            {
                DecodeDisplacement8Bit(instruction_input, byte_index, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_DISP:
            {
                DecodeDisplacement(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_DATA_8:
            {
                DecodeData8Bit(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_DATA:
            {
                DecodeData(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_ADDR:
            {
                DecodeAddr(instruction_input, decoding_context);
            } break;
            case FIELD_TYPE_SPEC_OPCODE_EXTENSION:
            {
                DecodeOpcodeExtension(instruction_input, decoding_context);
            } break;
        }
    }
}

void DecodeOperands(Instruction *instruction, InstructionFormatSpec *instruction_format, DecodingContext *decoding_context)
{
    if ((instruction_format->operand_types[0] == OPERAND_TYPE_SPEC_REGISTER_OR_MEMORY_ADDRESS &&
         instruction_format->operand_types[1] == OPERAND_TYPE_SPEC_REGISTER_OR_MEMORY_ADDRESS))
    {
        DecodeOperandsRegisterOrMemoryAndEither(instruction, decoding_context);
        return;
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(instruction_format->operand_types); ++i)
    {
        OperandTypeSpec operand_type_spec = instruction_format->operand_types[i];

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
                DecodeOperandRegister(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_SEGMENT_REGISTER:
            {
                DecodeOperandSegmentRegister(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_DATA_REGISTER:
            {
                DecodeOperandDataRegister(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_REGISTER_OR_MEMORY_ADDRESS:
            {
                DecodeOperandRegisterOrMemoryAddress(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_DIRECT_MEMORY_ADDRESS:
            {
                DecodeOperandDirectAddress(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_ACCUMULATOR:
            {
                DecodeOperandAccumulator(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_IMMEDIATE:
            {
                DecodeOperandImmediate(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_LABEL_LIKE_DISPLACEMENT:
            {
                DecodeOperandLabelLikeDisplacement(&instruction->operands[i], decoding_context);
            } break;
            case OPERAND_TYPE_SPEC_SHIFT_ROTATE_COUNT:
            {
                DecodeOperandShiftRotateCount(&instruction->operands[i], decoding_context);
            } break;
        }
    }
}

void DecodeFirstByteFields(InstructionSpecBody *instruction_spec_body,
                           InstructionInput *instruction_input,
                           DecodingContext *decoding_context)
{
    DecodeByteFields(instruction_spec_body->byte_1, ARRAY_SIZE(instruction_spec_body->byte_1), 0,
                     instruction_input, decoding_context);
}

void DecodeSecondByteFields(
    InstructionSpecBody *instruction_spec_body,
    InstructionInput *instruction_input,
    DecodingContext *decoding_context)
{
    DecodeByteFields(instruction_spec_body->byte_2, ARRAY_SIZE(instruction_spec_body->byte_2), 1,
                     instruction_input, decoding_context);
}

void DecodeSubsequentByteFields(InstructionSpecBody *instruction_spec_body,
                                InstructionInput *instruction_input,
                                DecodingContext *decoding_context)
{
    DecodeByteFields(instruction_spec_body->byte_3456, ARRAY_SIZE(instruction_spec_body->byte_3456),
                     decoding_context->num_bytes_read, instruction_input, decoding_context);
}

Instruction DecodeInstruction(InstructionSpec *instruction_spec,
                              InstructionInput *instruction_input,
                              DecodingContext *decoding_context)
{
    Instruction instruction = {};
    Instruction *instruction_ptr = &instruction;
    InstructionSpecBody *instruction_spec_body = 0;

    switch (instruction_spec->type)
    {
        case INSTRUCTION_TYPE_NONE:
        {
            return instruction;
        } break;
        case INSTRUCTION_TYPE_REGULAR:
        {
            instruction_spec_body = &instruction_spec->bodies[0];
            DecodeFirstByteFields(instruction_spec_body, instruction_input, decoding_context);
            DecodeSecondByteFields(instruction_spec_body, instruction_input, decoding_context);
            DecodeSubsequentByteFields(instruction_spec_body, instruction_input, decoding_context);
        } break;
        case INSTRUCTION_TYPE_EXTENDED_OPCODE:
        {
            FieldSpec byte_field_specs[BYTE_FIELDS_MAX_LEN] = OPCODE_EXT_BYTE_FIELDS;
            ReadNextBytesToIndex(instruction_input, decoding_context, OPCODE_EXT_BYTE_INDEX);
            DecodeByteFields(byte_field_specs, BYTE_FIELDS_MAX_LEN, OPCODE_EXT_BYTE_INDEX, instruction_input,
                             decoding_context);

            instruction_spec_body = &instruction_spec->bodies[decoding_context->opcode_extension];
            DecodeFirstByteFields(instruction_spec_body, instruction_input, decoding_context);
            DecodeSubsequentByteFields(instruction_spec_body, instruction_input, decoding_context);

        } break;
    }

    DecodeOperands(instruction_ptr, &instruction_spec_body->format, decoding_context);
    instruction.mnemonic = instruction_spec_body->format.mnemonic;

    return instruction;
}

Instruction DecodeInstruction(InstructionInput *instruction_input, DecodingContext *decoding_context)
{
    InstructionSpec instruction_spec = INSTRUCTION_SPECS[decoding_context->bytes[0]];

    return DecodeInstruction(&instruction_spec, instruction_input, decoding_context);
}
