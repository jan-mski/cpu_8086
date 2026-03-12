enum Mnemonic : uint8_t
{
    Mnemonic_None,

    Mnemonic_MOV,
    Mnemonic_PUSH,
    Mnemonic_POP,
    Mnemonic_XCHG,
    Mnemonic_IN,
    Mnemonic_OUT,
    Mnemonic_XLAT,
    Mnemonic_LEA,
    Mnemonic_LDS,
    Mnemonic_LES,
    Mnemonic_LAHF,
    Mnemonic_SAHF,
    Mnemonic_PUSHF,
    Mnemonic_POPF,
    Mnemonic_ADD,
    Mnemonic_ADC,
    Mnemonic_INC,
    Mnemonic_AAA,
    Mnemonic_DAA,
    Mnemonic_SUB,
    Mnemonic_SBB,
    Mnemonic_DEC,
    Mnemonic_NEG,
    Mnemonic_CMP,
    Mnemonic_AAS,
    Mnemonic_DAS,
    Mnemonic_MUL,
    Mnemonic_IMUL,
    Mnemonic_AAM,
    Mnemonic_DIV,
    Mnemonic_IDIV,
    Mnemonic_AAD,
    Mnemonic_CBW,
    Mnemonic_CWD,
    Mnemonic_NOT,
    Mnemonic_SHL_SAL,
    Mnemonic_SHR,
    Mnemonic_SAR,
    Mnemonic_ROL,
    Mnemonic_ROR,
    Mnemonic_RCL,
    Mnemonic_RCR,
    Mnemonic_AND,
    Mnemonic_TEST,
    Mnemonic_OR,
    Mnemonic_XOR,
    Mnemonic_REP,
    Mnemonic_MOVSB,
    Mnemonic_MOVSW,
    Mnemonic_CMPSB,
    Mnemonic_CMPSW,
    Mnemonic_SCASB,
    Mnemonic_SCASW,
    Mnemonic_LODSB,
    Mnemonic_LODSW,
    Mnemonic_STOSB,
    Mnemonic_STOSW,
    Mnemonic_CALL,
    Mnemonic_JMP,
    Mnemonic_RET,
    Mnemonic_JO,
    Mnemonic_JNO,
    Mnemonic_JB_JNAE,
    Mnemonic_JNB_JAE,
    Mnemonic_JE_JZ,
    Mnemonic_JNE_JNZ,
    Mnemonic_JBE_JNA,
    Mnemonic_JNBE_JA,
    Mnemonic_JS,
    Mnemonic_JNS,
    Mnemonic_JP_JPE,
    Mnemonic_JNP_JPO,
    Mnemonic_JL_JNGE,
    Mnemonic_JNL_JGE,
    Mnemonic_JLE_JNG,
    Mnemonic_JNLE_JG,
    Mnemonic_LOOPNZ_LOOPNE,
    Mnemonic_LOOPZ_LOOPE,
    Mnemonic_LOOP,
    Mnemonic_JCXZ,
    Mnemonic_INT,
    Mnemonic_INT3,
    Mnemonic_INTO,
    Mnemonic_IRET,
    Mnemonic_CLC,
    Mnemonic_CMC,
    Mnemonic_STC,
    Mnemonic_CLD,
    Mnemonic_STD,
    Mnemonic_CLI,
    Mnemonic_STI,
    Mnemonic_HLT,
    Mnemonic_WAIT,

    Mnemonic_Count
};

enum MemoryAddressQualifier : uint8_t
{
    MemoryAddressQualifier_None,

    MemoryAddressQualifier_Byte,
    MemoryAddressQualifier_Word,

    MemoryAddressQualifier_Count
};

struct MemoryAddress
{
    bool direct;
    MemoryAddressQualifier qualifier;
    RegisterId register_ids[2];
    int32_t displacement;
};

enum OperandType : uint8_t
{
    OperandType_None,

    OperandType_Register,
    OperandType_MemoryAddress,
    OperandType_Immediate,
    OperandType_LabelLikeDisplacement
};

struct Operand
{
    OperandType type;
    union
    {
        RegisterId register_id;
        MemoryAddress memory_address;
        uint16_t immediate_value;
        int32_t label_like_displacement;
    };
};

struct DecodingContext
{
    uint8_t bytes[6];
    uint8_t num_bytes_read;
    bool d;                          // 1 bit
    bool s;                          // 1 bit
    bool v;                          // 1 bit
    bool w;                          // 1 bit
    uint8_t mod;                     // 2 bits
    uint8_t sr;                      // 2 bits
    uint8_t reg;                     // 3 bits
    uint8_t r_m;                     // 3 bits
    uint8_t opcode_extension;        // 3 bits
    uint16_t data;                   // 8 || 16 bits
    uint16_t addr;                   // 8 || 16 bits
    int32_t displacement;            // 8 || 16 bits
};

struct Instruction
{
    Mnemonic mnemonic;
    Operand operands[2];
};
