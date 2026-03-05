#define T_REGULAR InstructionSpecType_Regular
#define T_EXTENDED InstructionSpecType_ExtendedOpcode

#define D(bit_shift) {FieldSpecType_D, bit_shift, 0b1}
#define S(bit_shift) {FieldSpecType_S, bit_shift, 0b1}
#define V(bit_shift) {FieldSpecType_V, bit_shift, 0b1}
#define W(bit_shift) {FieldSpecType_W, bit_shift, 0b1}
#define D_FORCED(forced_value) {FieldSpecType_D, 0, 0b1, true, forced_value}
#define W_FORCED(forced_value) {FieldSpecType_W, 0, 0b1, true, forced_value}
#define MOD(bit_shift) {FieldSpecType_MOD, bit_shift, 0b11}
#define RM(bit_shift) {FieldSpecType_RM, bit_shift, 0b111}
#define REG(bit_shift) {FieldSpecType_REG, bit_shift, 0b111}
#define SR(bit_shift) {FieldSpecType_SR, bit_shift, 0b11}
#define OPCODE_EXT(bit_shift) {FieldSpecType_OpcodeExtension, bit_shift, 0b111}
#define IGNORED_8() {FieldSpecType_DATA_8}
#define DISP_8() {FieldSpecType_DISP_8}
#define DISP() {FieldSpecType_DISP}
#define DATA_8() {FieldSpecType_DATA_8}
#define DATA_LO() {FieldSpecType_DATA_LO}
#define DATA_HI() {FieldSpecType_DATA_HI}
#define ADDR_LO() {FieldSpecType_ADDR_LO}
#define ADDR_HI() {FieldSpecType_ADDR_HI}

#define O_REG OperandSpecType_Register
#define O_SEG_REG OperandSpecType_SegmentRegister
#define O_DATA_REG OperandSpecType_DataRegister
#define O_ACC OperandSpecType_Accumulator
#define O_REG_OR_MEM OperandSpecType_RegisterOrMemoryAddress
#define O_IMM OperandSpecType_Immediate
#define O_LABEL_DISP OperandSpecType_LabelLikeDisplacement
#define O_DIRECT_ADDR OperandSpecType_DirectMemoryAddress
#define O_SHIFT_CNT OperandSpecType_ShiftRotateCount

#define OPCODE_EXT_BYTE {MOD(6), OPCODE_EXT(3), RM(0)}

FieldSpec OPCODE_EXT_BYTE_FIELDS[BYTE_FIELDS_MAX_LEN] = OPCODE_EXT_BYTE;

const InstructionSpec INSTRUCTION_SPECS[256] = {
    /* 00000000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_ADD, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00000001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_ADD, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00000010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_ADD, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00000011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_ADD, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00000100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_ADD, {O_ACC, O_IMM}}
        }
    }},
    /* 00000101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_ADD, {O_ACC, O_IMM}}
        }
    }},
    /* 00000110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_PUSH, {O_SEG_REG}}
        }
    }},
    /* 00000111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_POP, {O_SEG_REG}}
        }
    }},
    /* 00001000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_OR, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00001001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_OR, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00001010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_OR, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00001011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_OR, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00001100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_OR, {O_ACC, O_IMM}}
        }
    }},
    /* 00001101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_OR, {O_ACC, O_IMM}}
        }
    }},
    /* 00001110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_PUSH, {O_SEG_REG}}
        }
    }},
    /* 00001111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_POP, {O_SEG_REG}}
        }
    }},
    /* 00010000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_ADC, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00010001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_ADC, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00010010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_ADC, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00010011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_ADC, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00010100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_ADC, {O_ACC, O_IMM}}
        }
    }},
    /* 00010101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_ADC, {O_ACC, O_IMM}}
        }
    }},
    /* 00010110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_PUSH, {O_SEG_REG}}
        }
    }},
    /* 00010111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_POP, {O_SEG_REG}}
        }
    }},
    /* 00011000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_SBB, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00011001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_SBB, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00011010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_SBB, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00011011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_SBB, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00011100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_SBB, {O_ACC, O_IMM}}
        }
    }},
    /* 00011101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_SBB, {O_ACC, O_IMM}}
        }
    }},
    /* 00011110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_PUSH, {O_SEG_REG}}
        }
    }},
    /* 00011111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_POP, {O_SEG_REG}}
        }
    }},
    /* 00100000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_AND, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00100001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_AND, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00100010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_AND, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00100011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_AND, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00100100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_AND, {O_ACC, O_IMM}}
        }
    }},
    /* 00100101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_AND, {O_ACC, O_IMM}}
        }
    }},
    /* 00100110 */ {

    },
    /* 00100111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_DAA, {}}
        }
    }},
    /* 00101000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_SUB, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00101001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_SUB, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00101010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_SUB, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00101011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_SUB, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00101100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_SUB, {O_ACC, O_IMM}}
        }
    }},
    /* 00101101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_SUB, {O_ACC, O_IMM}}
        }
    }},
    /* 00101110 */ {

    },
    /* 00101111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_DAS, {}}
        }
    }},
    /* 00110000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_XOR, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00110001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_XOR, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00110010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_XOR, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00110011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_XOR, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00110100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_XOR, {O_ACC, O_IMM}}
        }
    }},
    /* 00110101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_XOR, {O_ACC, O_IMM}}
        }
    }},
    /* 00110110 */ {

    },
    /* 00110111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_AAA, {}}
        }
    }},
    /* 00111000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_CMP, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00111001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_CMP, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00111010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_CMP, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00111011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_CMP, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 00111100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_CMP, {O_ACC, O_IMM}}
        }
    }},
    /* 00111101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_CMP, {O_ACC, O_IMM}}
        }
    }},
    /* 00111110 */ {

    },
    /* 00111111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_AAS, {}}
        }
    }},
    /* 01000000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_INC, {O_REG}}
        }
    }},
    /* 01000001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_INC, {O_REG}}
        }
    }},
    /* 01000010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_INC, {O_REG}}
        }
    }},
    /* 01000011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_INC, {O_REG}}
        }
    }},
    /* 01000100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_INC, {O_REG}}
        }
    }},
    /* 01000101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_INC, {O_REG}}
        }
    }},
    /* 01000110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_INC, {O_REG}}
        }
    }},
    /* 01000111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_INC, {O_REG}}
        }
    }},
    /* 01001000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_DEC, {O_REG}}
        }
    }},
    /* 01001001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_DEC, {O_REG}}
        }
    }},
    /* 01001010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_DEC, {O_REG}}
        }
    }},
    /* 01001011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_DEC, {O_REG}}
        }
    }},
    /* 01001100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_DEC, {O_REG}}
        }
    }},
    /* 01001101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_DEC, {O_REG}}
        }
    }},
    /* 01001110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_DEC, {O_REG}}
        }
    }},
    /* 01001111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_DEC, {O_REG}}
        }
    }},
    /* 01010000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_PUSH, {O_REG}}
        }
    }},
    /* 01010001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_PUSH, {O_REG}}
        }
    }},
    /* 01010010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_PUSH, {O_REG}}
        }
    }},
    /* 01010011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_PUSH, {O_REG}}
        }
    }},
    /* 01010100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_PUSH, {O_REG}}
        }
    }},
    /* 01010101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_PUSH, {O_REG}}
        }
    }},
    /* 01010110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_PUSH, {O_REG}}
        }
    }},
    /* 01010111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_PUSH, {O_REG}}
        }
    }},
    /* 01011000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_POP, {O_REG}}
        }
    }},
    /* 01011001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_POP, {O_REG}}
        }
    }},
    /* 01011010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_POP, {O_REG}}
        }
    }},
    /* 01011011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_POP, {O_REG}}
        }
    }},
    /* 01011100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_POP, {O_REG}}
        }
    }},
    /* 01011101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_POP, {O_REG}}
        }
    }},
    /* 01011110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_POP, {O_REG}}
        }
    }},
    /* 01011111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_POP, {O_REG}}
        }
    }},
    /* 01100000 */ {

    },
    /* 01100001 */ {

    },
    /* 01100010 */ {

    },
    /* 01100011 */ {

    },
    /* 01100100 */ {

    },
    /* 01100101 */ {

    },
    /* 01100110 */ {

    },
    /* 01100111 */ {

    },
    /* 01101000 */ {

    },
    /* 01101001 */ {

    },
    /* 01101010 */ {

    },
    /* 01101011 */ {

    },
    /* 01101100 */ {

    },
    /* 01101101 */ {

    },
    /* 01101110 */ {

    },
    /* 01101111 */ {

    },
    /* 01110000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JO, {O_LABEL_DISP}}
        }
    }},
    /* 01110001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JNO, {O_LABEL_DISP}}
        }
    }},
    /* 01110010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JB_JNAE, {O_LABEL_DISP}}
        }
    }},
    /* 01110011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JNB_JAE, {O_LABEL_DISP}}
        }
    }},
    /* 01110100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JE_JZ, {O_LABEL_DISP}}
        }
    }},
    /* 01110101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JNE_JNZ, {O_LABEL_DISP}}
        }
    }},
    /* 01110110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JBE_JNA, {O_LABEL_DISP}}
        }
    }},
    /* 01110111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JNBE_JA, {O_LABEL_DISP}}
        }
    }},
    /* 01111000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JS, {O_LABEL_DISP}}
        }
    }},
    /* 01111001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JNS, {O_LABEL_DISP}}
        }
    }},
    /* 01111010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JP_JPE, {O_LABEL_DISP}}
        }
    }},
    /* 01111011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JNP_JPO, {O_LABEL_DISP}}
        }
    }},
    /* 01111100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JL_JNGE, {O_LABEL_DISP}}
        }
    }},
    /* 01111101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JNL_JGE, {O_LABEL_DISP}}
        }
    }},
    /* 01111110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JLE_JNG, {O_LABEL_DISP}}
        }
    }},
    /* 01111111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic_JNLE_JG, {O_LABEL_DISP}}
        }
    }},
    /* 10000000 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_ADD, {O_REG_OR_MEM, O_IMM}}
        },
        /* 001 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_OR, {O_REG_OR_MEM, O_IMM}}
        },
        /* 010 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_ADC, {O_REG_OR_MEM, O_IMM}}
        },
        /* 011 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_SBB, {O_REG_OR_MEM, O_IMM}}
        },
        /* 100 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_AND, {O_REG_OR_MEM, O_IMM}}
        },
        /* 101 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_SUB, {O_REG_OR_MEM, O_IMM}}
        },
        /* 110 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_XOR, {O_REG_OR_MEM, O_IMM}}
        },
        /* 111 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_CMP, {O_REG_OR_MEM, O_IMM}}
        },
    }},
    /* 10000001 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_ADD, {O_REG_OR_MEM, O_IMM}}
        },
        /* 001 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_OR, {O_REG_OR_MEM, O_IMM}}
        },
        /* 010 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_ADC, {O_REG_OR_MEM, O_IMM}}
        },
        /* 011 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_SBB, {O_REG_OR_MEM, O_IMM}}
        },
        /* 100 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_AND, {O_REG_OR_MEM, O_IMM}}
        },
        /* 101 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_SUB, {O_REG_OR_MEM, O_IMM}}
        },
        /* 110 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_XOR, {O_REG_OR_MEM, O_IMM}}
        },
        /* 111 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_CMP, {O_REG_OR_MEM, O_IMM}}
        },
    }},
    /* 10000010 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_ADD, {O_REG_OR_MEM, O_IMM}}
        },
        /* 001 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_OR, {O_REG_OR_MEM, O_IMM}}
        },
        /* 010 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_ADC, {O_REG_OR_MEM, O_IMM}}
        },
        /* 011 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_SBB, {O_REG_OR_MEM, O_IMM}}
        },
        /* 100 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_AND, {O_REG_OR_MEM, O_IMM}}
        },
        /* 101 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_SUB, {O_REG_OR_MEM, O_IMM}}
        },
        /* 110 */ {

        },
        /* 111 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_CMP, {O_REG_OR_MEM, O_IMM}}
        },
    }},
    /* 10000011 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_ADD, {O_REG_OR_MEM, O_IMM}}
        },
        /* 001 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_OR, {O_REG_OR_MEM, O_IMM}}
        },
        /* 010 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_ADC, {O_REG_OR_MEM, O_IMM}}
        },
        /* 011 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_SBB, {O_REG_OR_MEM, O_IMM}}
        },
        /* 100 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_AND, {O_REG_OR_MEM, O_IMM}}
        },
        /* 101 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_SUB, {O_REG_OR_MEM, O_IMM}}
        },
        /* 110 */ {

        },
        /* 111 */ {
            .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_CMP, {O_REG_OR_MEM, O_IMM}}
        },
    }},
    /* 10000100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_TEST, {O_REG_OR_MEM, O_REG}}
        }
    }},
    /* 10000101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_TEST, {O_REG_OR_MEM, O_REG}}
        }
    }},
    /* 10000110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D_FORCED(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_XCHG, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 10000111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D_FORCED(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_XCHG, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 10001000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_MOV, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 10001001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_MOV, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 10001010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_MOV, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 10001011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_MOV, {O_REG_OR_MEM, O_REG_OR_MEM}}
        }
    }},
    /* 10001100 */ {

    },
    /* 10001101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_LEA, {O_REG, O_REG_OR_MEM}}
        }
    }},
    /* 10001110 */ {

    },
    /* 10001111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_POP, {O_REG_OR_MEM}}
        }
    }},
    /* 10010000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_XCHG, {O_REG, O_ACC}}
        }
    }},
    /* 10010001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_XCHG, {O_REG, O_ACC}}
        }
    }},
    /* 10010010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_XCHG, {O_REG, O_ACC}}
        }
    }},
    /* 10010011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_XCHG, {O_REG, O_ACC}}
        }
    }},
    /* 10010100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_XCHG, {O_REG, O_ACC}}
        }
    }},
    /* 10010101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_XCHG, {O_REG, O_ACC}}
        }
    }},
    /* 10010110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_XCHG, {O_REG, O_ACC}}
        }
    }},
    /* 10010111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_XCHG, {O_REG, O_ACC}}
        }
    }},
    /* 10011000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_CBW, {}}
        }
    }},
    /* 10011001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_CWD, {}}
        }
    }},
    /* 10011010 */ {

    },
    /* 10011011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_WAIT, {}}
        }
    }},
    /* 10011100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_PUSHF, {}}
        }
    }},
    /* 10011101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_POPF, {}}
        }
    }},
    /* 10011110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_SAHF, {}}
        }
    }},
    /* 10011111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_LAHF, {}}
        }
    }},
    /* 10100000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {ADDR_LO()}, .byte_3456 {ADDR_HI()}, .format {Mnemonic_MOV, {O_ACC, O_DIRECT_ADDR}}
        }
    }},
    /* 10100001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {ADDR_LO()}, .byte_3456 {ADDR_HI()}, .format {Mnemonic_MOV, {O_ACC, O_DIRECT_ADDR}}
        }
    }},
    /* 10100010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {ADDR_LO()}, .byte_3456 {ADDR_HI()}, .format {Mnemonic_MOV, {O_DIRECT_ADDR, O_ACC}}
        }
    }},
    /* 10100011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {ADDR_LO()}, .byte_3456 {ADDR_HI()}, .format {Mnemonic_MOV, {O_DIRECT_ADDR, O_ACC}}
        }
    }},
    /* 10100100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_MOVSB, {}}
        }
    }},
    /* 10100101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_MOVSW, {}}
        }
    }},
    /* 10100110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_CMPSB, {}}
        }
    }},
    /* 10100111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_CMPSW, {}}
        }
    }},
    /* 10101000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_TEST, {O_ACC, O_IMM}}
        }
    }},
    /* 10101001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_TEST, {O_ACC, O_IMM}}
        }
    }},
    /* 10101010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_STOSB, {}}
        }
    }},
    /* 10101011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_STOSW, {}}
        }
    }},
    /* 10101100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_LODSB, {}}
        }
    }},
    /* 10101101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_LODSW, {}}
        }
    }},
    /* 10101110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_SCASB, {}}
        }
    }},
    /* 10101111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_SCASW, {}}
        }
    }},
    /* 10110000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10110001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10110010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10110011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10110100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10110101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10110110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10110111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10111000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10111001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10111010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10111011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10111100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10111101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10111110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 10111111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_MOV, {O_REG, O_IMM}}
        }
    }},
    /* 11000000 */ {

    },
    /* 11000001 */ {

    },
    /* 11000010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic_RET, {O_IMM}}
        }
    }},
    /* 11000011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_RET, {}}
        }
    }},
    /* 11000100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_LES, {O_REG, O_REG_OR_MEM}}
        }
    }},
    /* 11000101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_LDS, {O_REG, O_REG_OR_MEM}}
        }
    }},
    /* 11000110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {MOD(6), RM(0)}, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_MOV, {O_REG_OR_MEM, O_IMM}}
        }
    }},
    /* 11000111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {MOD(6), RM(0)}, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_MOV, {O_REG_OR_MEM, O_IMM}}
        }
    }},
    /* 11001000 */ {

    },
    /* 11001001 */ {

    },
    /* 11001010 */ {

    },
    /* 11001011 */ {

    },
    /* 11001100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_INT3, {}}
        }
    }},
    /* 11001101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DATA_8()}, .byte_3456 {}, .format {Mnemonic_INT, {O_IMM}}
        }
    }},
    /* 11001110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_INTO, {}}
        }
    }},
    /* 11001111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_IRET, {}}
        }
    }},
    /* 11010000 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_ROL, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 001 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_ROR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 010 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_RCL, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 011 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_RCR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 100 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_SHL_SAL, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 101 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_SHR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 110 */ {

        },
        /* 111 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_SAR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
    }},
    /* 11010001 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_ROL, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 001 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_ROR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 010 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_RCL, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 011 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_RCR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 100 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_SHL_SAL, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 101 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_SHR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 110 */ {

        },
        /* 111 */
        {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_SAR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
    }},
    /* 11010010 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_ROL, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 001 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_ROR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 010 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_RCL, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 011 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_RCR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 100 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_SHL_SAL, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 101 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_SHR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 110 */ {

        },
        /* 111 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_SAR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
    }},
    /* 11010011 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_ROL, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 001 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_ROR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 010 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_RCL, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 011 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_RCR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 100 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_SHL_SAL, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 101 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_SHR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
        /* 110 */ {

        },
        /* 111 */ {
            .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_SAR, {O_REG_OR_MEM, O_SHIFT_CNT}}
        },
    }},
    /* 11010100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {IGNORED_8()}, .byte_3456 {}, .format {Mnemonic_AAM, {}}
        }
    }},
    /* 11010101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {IGNORED_8()}, .byte_3456 {}, .format {Mnemonic_AAD, {}}
        }
    }},
    /* 11010110 */ {

    },
    /* 11010111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_XLAT, {}}
        }
    }},
    /* 11011000 */ {

    },
    /* 11011001 */ {

    },
    /* 11011010 */ {

    },
    /* 11011011 */ {

    },
    /* 11011100 */ {

    },
    /* 11011101 */ {

    },
    /* 11011110 */ {

    },
    /* 11011111 */ {

    },
    /* 11100000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {}, .format {Mnemonic_LOOPNZ_LOOPNE, {O_LABEL_DISP}}
        }
    }},
    /* 11100001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {}, .format {Mnemonic_LOOPZ_LOOPE, {O_LABEL_DISP}}
        }
    }},
    /* 11100010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {}, .format {Mnemonic_LOOP, {O_LABEL_DISP}}
        }
    }},
    /* 11100011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {}, .format {Mnemonic_JCXZ, {O_LABEL_DISP}}
        }
    }},
    /* 11100100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_8()}, .byte_3456 {}, .format {Mnemonic_IN, {O_ACC, O_IMM}}
        }
    }},
    /* 11100101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_8()}, .byte_3456 {}, .format {Mnemonic_IN, {O_ACC, O_IMM}}
        }
    }},
    /* 11100110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_8()}, .byte_3456 {}, .format {Mnemonic_OUT, {O_IMM, O_ACC}}
        }
    }},
    /* 11100111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {DATA_8()}, .byte_3456 {}, .format {Mnemonic_OUT, {O_IMM, O_ACC}}
        }
    }},
    /* 11101000 */ {

    },
    /* 11101001 */ {

    },
    /* 11101010 */ {

    },
    /* 11101011 */ {

    },
    /* 11101100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_IN, {O_ACC, O_DATA_REG}}
        }
    }},
    /* 11101101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_IN, {O_ACC, O_DATA_REG}}
        }
    }},
    /* 11101110 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_OUT, {O_DATA_REG, O_ACC}}
        }
    }},
    /* 11101111 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {W(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_OUT, {O_DATA_REG, O_ACC}}
        }
    }},
    /* 11110000 */ {

    },
    /* 11110001 */ {

    },
    /* 11110010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_REP, {}}
        }
    }},
    /* 11110011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_REP, {}}
        }
    }},
    /* 11110100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_HLT, {}}
        }
    }},
    /* 11110101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_CMC, {}}
        }
    }},
    /* 11110110 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_TEST, {O_REG_OR_MEM, O_IMM}}
        },
        /* 001 */ {

        },
        /* 010 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_NOT, {O_REG_OR_MEM}}
        },
        /* 011 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_NEG, {O_REG_OR_MEM}}
        },
        /* 100 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_MUL, {O_REG_OR_MEM}}
        },
        /* 101 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_IMUL, {O_REG_OR_MEM}}
        },
        /* 110 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_DIV, {O_REG_OR_MEM}}
        },
        /* 111 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_IDIV, {O_REG_OR_MEM}}
        },
    }},
    /* 11110111 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic_TEST, {O_REG_OR_MEM, O_IMM}}
        },
        /* 001 */ {

        },
        /* 010 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_NOT, {O_REG_OR_MEM}}
        },
        /* 011 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_NEG, {O_REG_OR_MEM}}
        },
        /* 100 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_MUL, {O_REG_OR_MEM}}
        },
        /* 101 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_IMUL, {O_REG_OR_MEM}}
        },
        /* 110 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_DIV, {O_REG_OR_MEM}}
        },
        /* 111 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_IDIV, {O_REG_OR_MEM}}
        },
    }},
    /* 11111000 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_CLC, {}}
        }
    }},
    /* 11111001 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_STC, {}}
        }
    }},
    /* 11111010 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_CLI, {}}
        }
    }},
    /* 11111011 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_STI, {}}
        }
    }},
    /* 11111100 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_CLD, {}}
        }
    }},
    /* 11111101 */ { .type = T_REGULAR, .bodies {
        {
            .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic_STD, {}}
        }
    }},
    /* 11111110 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_INC, {O_REG_OR_MEM}}
        },
        /* 001 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_DEC, {O_REG_OR_MEM}}
        },
        /* 010 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_CALL, {O_REG_OR_MEM}}
        },
        /* 011 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_CALL, {O_REG_OR_MEM}}
        },
        /* 100 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_JMP, {O_REG_OR_MEM}}
        },
        /* 101 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_JMP, {O_REG_OR_MEM}}
        },
        /* 110 */ {
            .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_PUSH, {O_REG_OR_MEM}}
        },
        /* 111 */ {

        },
    }},
    /* 11111111 */ { .type = T_EXTENDED, .bodies {
        /* 000 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_INC, {O_REG_OR_MEM}}
        },
        /* 001 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_DEC, {O_REG_OR_MEM}}
        },
        /* 010 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_CALL, {O_REG_OR_MEM}}
        },
        /* 011 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_CALL, {O_REG_OR_MEM}}
        },
        /* 100 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_JMP, {O_REG_OR_MEM}}
        },
        /* 101 */ {
            .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic_JMP, {O_REG_OR_MEM}}
        },
        /* 110 */ {
            .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic_PUSH, {O_REG_OR_MEM}}
        },
        /* 111 */ {
        
        },
    }},
};

#undef T_REGULAR
#undef T_EXTENDED

#undef D
#undef S
#undef V
#undef W
#undef D_FORCED
#undef W_FORCED
#undef REG
#undef SR
#undef IGNORED_8
#undef DISP_8
#undef DISP
#undef DATA_8
#undef DATA_LO
#undef DATA_HI
#undef ADDR_LO
#undef ADDR_HI

#undef O_REG
#undef O_SEG_REG
#undef O_DATA_REG
#undef O_ACC
#undef O_REG_OR_MEM
#undef O_IMM
#undef O_LABEL_DISP
#undef O_DIRECT_ADDR
#undef O_SHIFT_CNT
