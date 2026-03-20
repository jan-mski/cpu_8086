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

    enum class MemoryAddressQualifier : uint8_t
    {
        None,

        Byte,
        Word,

        Count
    };

    struct MemoryAddress
    {
        bool direct;
        MemoryAddressQualifier qualifier;
        cpu::state::RegisterId register_ids[2];
        int32_t displacement;
    };

    enum class OperandType : uint8_t
    {
        None,

        Register,
        MemoryAddress,
        Immediate,
        LabelLikeDisplacement
    };

    struct Operand
    {
        OperandType type;
        union
        {
            cpu::state::RegisterId register_id;
            MemoryAddress memory_address;
            uint16_t immediate_value;
            int32_t label_like_displacement;
        };
    };

    struct Instruction
    {
        Mnemonic mnemonic;
        Operand operands[2];
    };
}
