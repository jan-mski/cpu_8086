#ifndef CPU_INSTRUCTION_H
#define CPU_INSTRUCTION_H

namespace cpu::instruction
{
    enum class Mnemonic : uint8_t
    {
        None,

        MOV,
        PUSH,
        POP,
        XCHG,
        IN,
        OUT,
        XLAT,
        LEA,
        LDS,
        LES,
        LAHF,
        SAHF,
        PUSHF,
        POPF,
        ADD,
        ADC,
        INC,
        AAA,
        DAA,
        SUB,
        SBB,
        DEC,
        NEG,
        CMP,
        AAS,
        DAS,
        MUL,
        IMUL,
        AAM,
        DIV,
        IDIV,
        AAD,
        CBW,
        CWD,
        NOT,
        SHL_SAL,
        SHR,
        SAR,
        ROL,
        ROR,
        RCL,
        RCR,
        AND,
        TEST,
        OR,
        XOR,
        REP,
        MOVSB,
        MOVSW,
        CMPSB,
        CMPSW,
        SCASB,
        SCASW,
        LODSB,
        LODSW,
        STOSB,
        STOSW,
        CALL,
        JMP,
        RET,
        JO,
        JNO,
        JB_JNAE,
        JNB_JAE,
        JE_JZ,
        JNE_JNZ,
        JBE_JNA,
        JNBE_JA,
        JS,
        JNS,
        JP_JPE,
        JNP_JPO,
        JL_JNGE,
        JNL_JGE,
        JLE_JNG,
        JNLE_JG,
        LOOPNZ_LOOPNE,
        LOOPZ_LOOPE,
        LOOP,
        JCXZ,
        INT,
        INT3,
        INTO,
        IRET,
        CLC,
        CMC,
        STC,
        CLD,
        STD,
        CLI,
        STI,
        HLT,
        WAIT,

        Count
    };

    struct MemoryAddress
    {
        bool is_operand_size_implicit;
        cpu::core::Register16BitId register_ids[2];
        int32_t displacement;
    };

    enum class OperandType : uint8_t
    {
        None,

        Register8Bit,
        Register16Bit,
        MemoryAddress,
        Immediate,
        IPIncrement
    };

    struct Operand
    {
        OperandType type;

        union
        {
            cpu::core::Register8BitId register_8_bit_id;
            cpu::core::Register16BitId register_16_bit_id;
            MemoryAddress memory_address;
            uint16_t immediate_value;
            int16_t ip_increment;
        };
    };

    struct Instruction
    {
        Mnemonic mnemonic;
        Operand operands[2];
        bool is_wide;
    };
}

#endif // CPU_INSTRUCTION_H
