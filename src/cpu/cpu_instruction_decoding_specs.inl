#define T_REGULAR InstructionSpecType::Regular
#define T_EXTENDED InstructionSpecType::ExtendedOpcode

#define D(bit_shift) {FieldSpecType::D, bit_shift, 0b1}
#define S(bit_shift) {FieldSpecType::S, bit_shift, 0b1}
#define V(bit_shift) {FieldSpecType::V, bit_shift, 0b1}
#define W(bit_shift) {FieldSpecType::W, bit_shift, 0b1}
#define D_FORCED(forced_value) {FieldSpecType::D, 0, 0b1, true, forced_value}
#define W_FORCED(forced_value) {FieldSpecType::W, 0, 0b1, true, forced_value}
#define MOD(bit_shift) {FieldSpecType::MOD, bit_shift, 0b11}
#define RM(bit_shift) {FieldSpecType::RM, bit_shift, 0b111}
#define REG(bit_shift) {FieldSpecType::REG, bit_shift, 0b111}
#define SR(bit_shift) {FieldSpecType::SR, bit_shift, 0b11}
#define OPCODE_EXT(bit_shift) {FieldSpecType::OpcodeExtension, bit_shift, 0b111}
#define IGNORED_8() {FieldSpecType::DATA_8}
#define DISP_8() {FieldSpecType::DISP_8}
#define DISP() {FieldSpecType::DISP}
#define DATA_8() {FieldSpecType::DATA_8}
#define DATA_LO() {FieldSpecType::DATA_LO}
#define DATA_HI() {FieldSpecType::DATA_HI}
#define ADDR_LO() {FieldSpecType::ADDR_LO}
#define ADDR_HI() {FieldSpecType::ADDR_HI}

#define O_REG OperandSpecType::Register
#define O_SEG_REG OperandSpecType::SegmentRegister
#define O_DATA_REG OperandSpecType::DataRegister
#define O_ACC OperandSpecType::Accumulator
#define O_REG_OR_MEM OperandSpecType::RegisterOrMemoryAddress
#define O_IMM OperandSpecType::Immediate
#define O_LABEL_DISP OperandSpecType::LabelLikeDisplacement
#define O_DIRECT_ADDR OperandSpecType::DirectMemoryAddress
#define O_SHIFT_CNT OperandSpecType::ShiftRotateCount

#define OPCODE_EXT_BYTE {MOD(6), OPCODE_EXT(3), RM(0)}

namespace cpu::instruction_decoding::specs
{
    using cpu::instruction::Mnemonic;
    using cpu::instruction_decoding::fields::BYTE_FIELDS_MAX_LEN;
    using cpu::instruction_decoding::fields::FieldSpec;
    using cpu::instruction_decoding::fields::FieldSpecType;
    using cpu::instruction_decoding::operands::OperandSpecType;

    inline FieldSpec OPCODE_EXT_BYTE_FIELDS[BYTE_FIELDS_MAX_LEN] = OPCODE_EXT_BYTE;

    const InstructionSpec INSTRUCTION_SPECS[256] = {
        /* 00000000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::ADD, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00000001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::ADD, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00000010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::ADD, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00000011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::ADD, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00000100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::ADD, {O_ACC, O_IMM}}
            }
        }},
        /* 00000101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::ADD, {O_ACC, O_IMM}}
            }
        }},
        /* 00000110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::PUSH, {O_SEG_REG}}
            }
        }},
        /* 00000111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::POP, {O_SEG_REG}}
            }
        }},
        /* 00001000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::OR, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00001001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::OR, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00001010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::OR, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00001011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::OR, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00001100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::OR, {O_ACC, O_IMM}}
            }
        }},
        /* 00001101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::OR, {O_ACC, O_IMM}}
            }
        }},
        /* 00001110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::PUSH, {O_SEG_REG}}
            }
        }},
        /* 00001111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::POP, {O_SEG_REG}}
            }
        }},
        /* 00010000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::ADC, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00010001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::ADC, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00010010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::ADC, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00010011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::ADC, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00010100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::ADC, {O_ACC, O_IMM}}
            }
        }},
        /* 00010101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::ADC, {O_ACC, O_IMM}}
            }
        }},
        /* 00010110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::PUSH, {O_SEG_REG}}
            }
        }},
        /* 00010111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::POP, {O_SEG_REG}}
            }
        }},
        /* 00011000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::SBB, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00011001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::SBB, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00011010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::SBB, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00011011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::SBB, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00011100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::SBB, {O_ACC, O_IMM}}
            }
        }},
        /* 00011101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::SBB, {O_ACC, O_IMM}}
            }
        }},
        /* 00011110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::PUSH, {O_SEG_REG}}
            }
        }},
        /* 00011111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {SR(3)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::POP, {O_SEG_REG}}
            }
        }},
        /* 00100000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::AND, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00100001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::AND, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00100010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::AND, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00100011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::AND, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00100100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::AND, {O_ACC, O_IMM}}
            }
        }},
        /* 00100101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::AND, {O_ACC, O_IMM}}
            }
        }},
        /* 00100110 */ {

        },
        /* 00100111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::DAA, {}}
            }
        }},
        /* 00101000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::SUB, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00101001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::SUB, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00101010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::SUB, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00101011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::SUB, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00101100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::SUB, {O_ACC, O_IMM}}
            }
        }},
        /* 00101101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::SUB, {O_ACC, O_IMM}}
            }
        }},
        /* 00101110 */ {

        },
        /* 00101111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::DAS, {}}
            }
        }},
        /* 00110000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::XOR, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00110001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::XOR, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00110010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::XOR, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00110011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::XOR, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00110100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::XOR, {O_ACC, O_IMM}}
            }
        }},
        /* 00110101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::XOR, {O_ACC, O_IMM}}
            }
        }},
        /* 00110110 */ {

        },
        /* 00110111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::AAA, {}}
            }
        }},
        /* 00111000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::CMP, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00111001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::CMP, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00111010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::CMP, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00111011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::CMP, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 00111100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::CMP, {O_ACC, O_IMM}}
            }
        }},
        /* 00111101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::CMP, {O_ACC, O_IMM}}
            }
        }},
        /* 00111110 */ {

        },
        /* 00111111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::AAS, {}}
            }
        }},
        /* 01000000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::INC, {O_REG}}
            }
        }},
        /* 01000001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::INC, {O_REG}}
            }
        }},
        /* 01000010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::INC, {O_REG}}
            }
        }},
        /* 01000011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::INC, {O_REG}}
            }
        }},
        /* 01000100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::INC, {O_REG}}
            }
        }},
        /* 01000101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::INC, {O_REG}}
            }
        }},
        /* 01000110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::INC, {O_REG}}
            }
        }},
        /* 01000111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::INC, {O_REG}}
            }
        }},
        /* 01001000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::DEC, {O_REG}}
            }
        }},
        /* 01001001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::DEC, {O_REG}}
            }
        }},
        /* 01001010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::DEC, {O_REG}}
            }
        }},
        /* 01001011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::DEC, {O_REG}}
            }
        }},
        /* 01001100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::DEC, {O_REG}}
            }
        }},
        /* 01001101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::DEC, {O_REG}}
            }
        }},
        /* 01001110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::DEC, {O_REG}}
            }
        }},
        /* 01001111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::DEC, {O_REG}}
            }
        }},
        /* 01010000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::PUSH, {O_REG}}
            }
        }},
        /* 01010001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::PUSH, {O_REG}}
            }
        }},
        /* 01010010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::PUSH, {O_REG}}
            }
        }},
        /* 01010011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::PUSH, {O_REG}}
            }
        }},
        /* 01010100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::PUSH, {O_REG}}
            }
        }},
        /* 01010101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::PUSH, {O_REG}}
            }
        }},
        /* 01010110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::PUSH, {O_REG}}
            }
        }},
        /* 01010111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::PUSH, {O_REG}}
            }
        }},
        /* 01011000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::POP, {O_REG}}
            }
        }},
        /* 01011001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::POP, {O_REG}}
            }
        }},
        /* 01011010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::POP, {O_REG}}
            }
        }},
        /* 01011011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::POP, {O_REG}}
            }
        }},
        /* 01011100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::POP, {O_REG}}
            }
        }},
        /* 01011101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::POP, {O_REG}}
            }
        }},
        /* 01011110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::POP, {O_REG}}
            }
        }},
        /* 01011111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::POP, {O_REG}}
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
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JO, {O_LABEL_DISP}}
            }
        }},
        /* 01110001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JNO, {O_LABEL_DISP}}
            }
        }},
        /* 01110010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JB_JNAE, {O_LABEL_DISP}}
            }
        }},
        /* 01110011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JNB_JAE, {O_LABEL_DISP}}
            }
        }},
        /* 01110100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JE_JZ, {O_LABEL_DISP}}
            }
        }},
        /* 01110101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JNE_JNZ, {O_LABEL_DISP}}
            }
        }},
        /* 01110110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JBE_JNA, {O_LABEL_DISP}}
            }
        }},
        /* 01110111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JNBE_JA, {O_LABEL_DISP}}
            }
        }},
        /* 01111000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JS, {O_LABEL_DISP}}
            }
        }},
        /* 01111001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JNS, {O_LABEL_DISP}}
            }
        }},
        /* 01111010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JP_JPE, {O_LABEL_DISP}}
            }
        }},
        /* 01111011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JNP_JPO, {O_LABEL_DISP}}
            }
        }},
        /* 01111100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JL_JNGE, {O_LABEL_DISP}}
            }
        }},
        /* 01111101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JNL_JGE, {O_LABEL_DISP}}
            }
        }},
        /* 01111110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JLE_JNG, {O_LABEL_DISP}}
            }
        }},
        /* 01111111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {},.format {Mnemonic::JNLE_JG, {O_LABEL_DISP}}
            }
        }},
        /* 10000000 */ { .type = T_EXTENDED, .bodies {
            /* 000 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::ADD, {O_REG_OR_MEM, O_IMM}}
            },
            /* 001 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::OR, {O_REG_OR_MEM, O_IMM}}
            },
            /* 010 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::ADC, {O_REG_OR_MEM, O_IMM}}
            },
            /* 011 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::SBB, {O_REG_OR_MEM, O_IMM}}
            },
            /* 100 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::AND, {O_REG_OR_MEM, O_IMM}}
            },
            /* 101 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::SUB, {O_REG_OR_MEM, O_IMM}}
            },
            /* 110 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::XOR, {O_REG_OR_MEM, O_IMM}}
            },
            /* 111 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::CMP, {O_REG_OR_MEM, O_IMM}}
            },
        }},
        /* 10000001 */ { .type = T_EXTENDED, .bodies {
            /* 000 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::ADD, {O_REG_OR_MEM, O_IMM}}
            },
            /* 001 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::OR, {O_REG_OR_MEM, O_IMM}}
            },
            /* 010 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::ADC, {O_REG_OR_MEM, O_IMM}}
            },
            /* 011 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::SBB, {O_REG_OR_MEM, O_IMM}}
            },
            /* 100 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::AND, {O_REG_OR_MEM, O_IMM}}
            },
            /* 101 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::SUB, {O_REG_OR_MEM, O_IMM}}
            },
            /* 110 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::XOR, {O_REG_OR_MEM, O_IMM}}
            },
            /* 111 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::CMP, {O_REG_OR_MEM, O_IMM}}
            },
        }},
        /* 10000010 */ { .type = T_EXTENDED, .bodies {
            /* 000 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::ADD, {O_REG_OR_MEM, O_IMM}}
            },
            /* 001 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::OR, {O_REG_OR_MEM, O_IMM}}
            },
            /* 010 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::ADC, {O_REG_OR_MEM, O_IMM}}
            },
            /* 011 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::SBB, {O_REG_OR_MEM, O_IMM}}
            },
            /* 100 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::AND, {O_REG_OR_MEM, O_IMM}}
            },
            /* 101 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::SUB, {O_REG_OR_MEM, O_IMM}}
            },
            /* 110 */ {

            },
            /* 111 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::CMP, {O_REG_OR_MEM, O_IMM}}
            },
        }},
        /* 10000011 */ { .type = T_EXTENDED, .bodies {
            /* 000 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::ADD, {O_REG_OR_MEM, O_IMM}}
            },
            /* 001 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::OR, {O_REG_OR_MEM, O_IMM}}
            },
            /* 010 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::ADC, {O_REG_OR_MEM, O_IMM}}
            },
            /* 011 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::SBB, {O_REG_OR_MEM, O_IMM}}
            },
            /* 100 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::AND, {O_REG_OR_MEM, O_IMM}}
            },
            /* 101 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::SUB, {O_REG_OR_MEM, O_IMM}}
            },
            /* 110 */ {

            },
            /* 111 */ {
                .byte_1 {S(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::CMP, {O_REG_OR_MEM, O_IMM}}
            },
        }},
        /* 10000100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::TEST, {O_REG_OR_MEM, O_REG}}
            }
        }},
        /* 10000101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::TEST, {O_REG_OR_MEM, O_REG}}
            }
        }},
        /* 10000110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D_FORCED(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::XCHG, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 10000111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D_FORCED(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::XCHG, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 10001000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::MOV, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 10001001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::MOV, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 10001010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::MOV, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 10001011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {D(1), W(0)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::MOV, {O_REG_OR_MEM, O_REG_OR_MEM}}
            }
        }},
        /* 10001100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), SR(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::MOV, {O_REG_OR_MEM, O_SEG_REG}}
            }
        }},
        /* 10001101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::LEA, {O_REG, O_REG_OR_MEM}}
            }
        }},
        /* 10001110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), SR(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::MOV, {O_SEG_REG, O_REG_OR_MEM}}
            }
        }},
        /* 10001111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::POP, {O_REG_OR_MEM}}
            }
        }},
        /* 10010000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::XCHG, {O_REG, O_ACC}}
            }
        }},
        /* 10010001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::XCHG, {O_REG, O_ACC}}
            }
        }},
        /* 10010010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::XCHG, {O_REG, O_ACC}}
            }
        }},
        /* 10010011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::XCHG, {O_REG, O_ACC}}
            }
        }},
        /* 10010100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::XCHG, {O_REG, O_ACC}}
            }
        }},
        /* 10010101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::XCHG, {O_REG, O_ACC}}
            }
        }},
        /* 10010110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::XCHG, {O_REG, O_ACC}}
            }
        }},
        /* 10010111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1), REG(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::XCHG, {O_REG, O_ACC}}
            }
        }},
        /* 10011000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::CBW, {}}
            }
        }},
        /* 10011001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::CWD, {}}
            }
        }},
        /* 10011010 */ {

        },
        /* 10011011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::WAIT, {}}
            }
        }},
        /* 10011100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::PUSHF, {}}
            }
        }},
        /* 10011101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::POPF, {}}
            }
        }},
        /* 10011110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::SAHF, {}}
            }
        }},
        /* 10011111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::LAHF, {}}
            }
        }},
        /* 10100000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {ADDR_LO()}, .byte_3456 {ADDR_HI()}, .format {Mnemonic::MOV, {O_ACC, O_DIRECT_ADDR}}
            }
        }},
        /* 10100001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {ADDR_LO()}, .byte_3456 {ADDR_HI()}, .format {Mnemonic::MOV, {O_ACC, O_DIRECT_ADDR}}
            }
        }},
        /* 10100010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {ADDR_LO()}, .byte_3456 {ADDR_HI()}, .format {Mnemonic::MOV, {O_DIRECT_ADDR, O_ACC}}
            }
        }},
        /* 10100011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {ADDR_LO()}, .byte_3456 {ADDR_HI()}, .format {Mnemonic::MOV, {O_DIRECT_ADDR, O_ACC}}
            }
        }},
        /* 10100100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::MOVSB, {}}
            }
        }},
        /* 10100101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::MOVSW, {}}
            }
        }},
        /* 10100110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::CMPSB, {}}
            }
        }},
        /* 10100111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::CMPSW, {}}
            }
        }},
        /* 10101000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::TEST, {O_ACC, O_IMM}}
            }
        }},
        /* 10101001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::TEST, {O_ACC, O_IMM}}
            }
        }},
        /* 10101010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::STOSB, {}}
            }
        }},
        /* 10101011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::STOSW, {}}
            }
        }},
        /* 10101100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::LODSB, {}}
            }
        }},
        /* 10101101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::LODSW, {}}
            }
        }},
        /* 10101110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::SCASB, {}}
            }
        }},
        /* 10101111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::SCASW, {}}
            }
        }},
        /* 10110000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10110001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10110010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10110011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10110100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10110101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10110110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10110111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10111000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10111001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10111010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10111011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10111100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10111101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10111110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 10111111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(3), REG(0)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::MOV, {O_REG, O_IMM}}
            }
        }},
        /* 11000000 */ {

        },
        /* 11000001 */ {

        },
        /* 11000010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1)}, .byte_2 {DATA_LO()}, .byte_3456 {DATA_HI()}, .format {Mnemonic::RET, {O_IMM}}
            }
        }},
        /* 11000011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::RET, {}}
            }
        }},
        /* 11000100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::LES, {O_REG, O_REG_OR_MEM}}
            }
        }},
        /* 11000101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), REG(3), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::LDS, {O_REG, O_REG_OR_MEM}}
            }
        }},
        /* 11000110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {MOD(6), RM(0)}, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::MOV, {O_REG_OR_MEM, O_IMM}}
            }
        }},
        /* 11000111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {MOD(6), RM(0)}, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::MOV, {O_REG_OR_MEM, O_IMM}}
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
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::INT3, {}}
            }
        }},
        /* 11001101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DATA_8()}, .byte_3456 {}, .format {Mnemonic::INT, {O_IMM}}
            }
        }},
        /* 11001110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::INTO, {}}
            }
        }},
        /* 11001111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::IRET, {}}
            }
        }},
        /* 11010000 */ { .type = T_EXTENDED, .bodies {
            /* 000 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::ROL, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 001 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::ROR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 010 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::RCL, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 011 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::RCR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 100 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::SHL_SAL, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 101 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::SHR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 110 */ {

            },
            /* 111 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::SAR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
        }},
        /* 11010001 */ { .type = T_EXTENDED, .bodies {
            /* 000 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::ROL, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 001 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::ROR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 010 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::RCL, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 011 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::RCR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 100 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::SHL_SAL, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 101 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::SHR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 110 */ {

            },
            /* 111 */
            {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::SAR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
        }},
        /* 11010010 */ { .type = T_EXTENDED, .bodies {
            /* 000 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::ROL, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 001 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::ROR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 010 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::RCL, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 011 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::RCR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 100 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::SHL_SAL, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 101 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::SHR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 110 */ {

            },
            /* 111 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::SAR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
        }},
        /* 11010011 */ { .type = T_EXTENDED, .bodies {
            /* 000 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::ROL, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 001 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::ROR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 010 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::RCL, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 011 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::RCR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 100 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::SHL_SAL, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 101 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::SHR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
            /* 110 */ {

            },
            /* 111 */ {
                .byte_1 {V(1), W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::SAR, {O_REG_OR_MEM, O_SHIFT_CNT}}
            },
        }},
        /* 11010100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {IGNORED_8()}, .byte_3456 {}, .format {Mnemonic::AAM, {}}
            }
        }},
        /* 11010101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {IGNORED_8()}, .byte_3456 {}, .format {Mnemonic::AAD, {}}
            }
        }},
        /* 11010110 */ {

        },
        /* 11010111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::XLAT, {}}
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
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {}, .format {Mnemonic::LOOPNZ_LOOPNE, {O_LABEL_DISP}}
            }
        }},
        /* 11100001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {}, .format {Mnemonic::LOOPZ_LOOPE, {O_LABEL_DISP}}
            }
        }},
        /* 11100010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {}, .format {Mnemonic::LOOP, {O_LABEL_DISP}}
            }
        }},
        /* 11100011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {DISP_8()}, .byte_3456 {}, .format {Mnemonic::JCXZ, {O_LABEL_DISP}}
            }
        }},
        /* 11100100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_8()}, .byte_3456 {}, .format {Mnemonic::IN, {O_ACC, O_IMM}}
            }
        }},
        /* 11100101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_8()}, .byte_3456 {}, .format {Mnemonic::IN, {O_ACC, O_IMM}}
            }
        }},
        /* 11100110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_8()}, .byte_3456 {}, .format {Mnemonic::OUT, {O_IMM, O_ACC}}
            }
        }},
        /* 11100111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {DATA_8()}, .byte_3456 {}, .format {Mnemonic::OUT, {O_IMM, O_ACC}}
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
                .byte_1 {W(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::IN, {O_ACC, O_DATA_REG}}
            }
        }},
        /* 11101101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::IN, {O_ACC, O_DATA_REG}}
            }
        }},
        /* 11101110 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::OUT, {O_DATA_REG, O_ACC}}
            }
        }},
        /* 11101111 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {W(0)}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::OUT, {O_DATA_REG, O_ACC}}
            }
        }},
        /* 11110000 */ {

        },
        /* 11110001 */ {

        },
        /* 11110010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::REP, {}}
            }
        }},
        /* 11110011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::REP, {}}
            }
        }},
        /* 11110100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::HLT, {}}
            }
        }},
        /* 11110101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::CMC, {}}
            }
        }},
        /* 11110110 */ { .type = T_EXTENDED, .bodies {
            /* 000 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::TEST, {O_REG_OR_MEM, O_IMM}}
            },
            /* 001 */ {

            },
            /* 010 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::NOT, {O_REG_OR_MEM}}
            },
            /* 011 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::NEG, {O_REG_OR_MEM}}
            },
            /* 100 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::MUL, {O_REG_OR_MEM}}
            },
            /* 101 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::IMUL, {O_REG_OR_MEM}}
            },
            /* 110 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::DIV, {O_REG_OR_MEM}}
            },
            /* 111 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::IDIV, {O_REG_OR_MEM}}
            },
        }},
        /* 11110111 */ { .type = T_EXTENDED, .bodies {
            /* 000 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP(), DATA_LO(), DATA_HI()}, .format {Mnemonic::TEST, {O_REG_OR_MEM, O_IMM}}
            },
            /* 001 */ {

            },
            /* 010 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::NOT, {O_REG_OR_MEM}}
            },
            /* 011 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::NEG, {O_REG_OR_MEM}}
            },
            /* 100 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::MUL, {O_REG_OR_MEM}}
            },
            /* 101 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::IMUL, {O_REG_OR_MEM}}
            },
            /* 110 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::DIV, {O_REG_OR_MEM}}
            },
            /* 111 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::IDIV, {O_REG_OR_MEM}}
            },
        }},
        /* 11111000 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::CLC, {}}
            }
        }},
        /* 11111001 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::STC, {}}
            }
        }},
        /* 11111010 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::CLI, {}}
            }
        }},
        /* 11111011 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::STI, {}}
            }
        }},
        /* 11111100 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::CLD, {}}
            }
        }},
        /* 11111101 */ { .type = T_REGULAR, .bodies {
            {
                .byte_1 {}, .byte_2 {}, .byte_3456 {}, .format {Mnemonic::STD, {}}
            }
        }},
        /* 11111110 */ { .type = T_EXTENDED, .bodies {
            /* 000 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::INC, {O_REG_OR_MEM}}
            },
            /* 001 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::DEC, {O_REG_OR_MEM}}
            },
            /* 010 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::CALL, {O_REG_OR_MEM}}
            },
            /* 011 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::CALL, {O_REG_OR_MEM}}
            },
            /* 100 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::JMP, {O_REG_OR_MEM}}
            },
            /* 101 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::JMP, {O_REG_OR_MEM}}
            },
            /* 110 */ {
                .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::PUSH, {O_REG_OR_MEM}}
            },
            /* 111 */ {

            },
        }},
        /* 11111111 */ { .type = T_EXTENDED, .bodies {
            /* 000 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::INC, {O_REG_OR_MEM}}
            },
            /* 001 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::DEC, {O_REG_OR_MEM}}
            },
            /* 010 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::CALL, {O_REG_OR_MEM}}
            },
            /* 011 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::CALL, {O_REG_OR_MEM}}
            },
            /* 100 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::JMP, {O_REG_OR_MEM}}
            },
            /* 101 */ {
                .byte_1 {W(0)}, .byte_2 = OPCODE_EXT_BYTE, .byte_3456 {DISP()}, .format {Mnemonic::JMP, {O_REG_OR_MEM}}
            },
            /* 110 */ {
                .byte_1 {W_FORCED(1)}, .byte_2 {MOD(6), RM(0)}, .byte_3456 {DISP()}, .format {Mnemonic::PUSH, {O_REG_OR_MEM}}
            },
            /* 111 */ {

            },
        }},
    };
}

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
