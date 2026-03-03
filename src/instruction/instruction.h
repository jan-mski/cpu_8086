const uint8_t INSTRUCTION_MAX_BYTES = 6;
const uint8_t REGISTERS_MAX_LEN = 2;

enum OperandType : uint8_t
{
    OPERAND_TYPE_NONE,

    OPERAND_TYPE_REGISTER,
    OPERAND_TYPE_MEMORY_ADDRESS,
    OPERAND_TYPE_IMMEDIATE,
    OPERAND_TYPE_LABEL_LIKE_DISPLACEMENT
};

enum Mnemonic : uint8_t
{
    MNEMONIC_NONE,

    MNEMONIC_MOV,
    MNEMONIC_PUSH,
    MNEMONIC_POP,
    MNEMONIC_XCHG,
    MNEMONIC_IN,
    MNEMONIC_OUT,
    MNEMONIC_XLAT,
    MNEMONIC_LEA,
    MNEMONIC_LDS,
    MNEMONIC_LES,
    MNEMONIC_LAHF,
    MNEMONIC_SAHF,
    MNEMONIC_PUSHF,
    MNEMONIC_POPF,
    MNEMONIC_ADD,
    MNEMONIC_ADC,
    MNEMONIC_INC,
    MNEMONIC_AAA,
    MNEMONIC_DAA,
    MNEMONIC_SUB,
    MNEMONIC_SBB,
    MNEMONIC_DEC,
    MNEMONIC_NEG,
    MNEMONIC_CMP,
    MNEMONIC_AAS,
    MNEMONIC_DAS,
    MNEMONIC_MUL,
    MNEMONIC_IMUL,
    MNEMONIC_AAM,
    MNEMONIC_DIV,
    MNEMONIC_IDIV,
    MNEMONIC_AAD,
    MNEMONIC_CBW,
    MNEMONIC_CWD,
    MNEMONIC_NOT,
    MNEMONIC_SHL_SAL,
    MNEMONIC_SHR,
    MNEMONIC_SAR,
    MNEMONIC_ROL,
    MNEMONIC_ROR,
    MNEMONIC_RCL,
    MNEMONIC_RCR,
    MNEMONIC_AND,
    MNEMONIC_TEST,
    MNEMONIC_OR,
    MNEMONIC_XOR,
    MNEMONIC_CALL,
    MNEMONIC_JMP,
    MNEMONIC_RET,
    MNEMONIC_JO,
    MNEMONIC_JNO,
    MNEMONIC_JB_JNAE,
    MNEMONIC_JNB_JAE,
    MNEMONIC_JE_JZ,
    MNEMONIC_JNE_JNZ,
    MNEMONIC_JBE_JNA,
    MNEMONIC_JNBE_JA,
    MNEMONIC_JS,
    MNEMONIC_JNS,
    MNEMONIC_JP_JPE,
    MNEMONIC_JNP_JPO,
    MNEMONIC_JL_JNGE,
    MNEMONIC_JNL_JGE,
    MNEMONIC_JLE_JNG,
    MNEMONIC_JNLE_JG,
    MNEMONIC_LOOPNZ_LOOPNE,
    MNEMONIC_LOOPZ_LOOPE,
    MNEMONIC_LOOP,
    MNEMONIC_JCXZ,
    MNEMONIC_CLC,
    MNEMONIC_CMC,
    MNEMONIC_STC,
    MNEMONIC_CLD,
    MNEMONIC_STD,
    MNEMONIC_CLI,
    MNEMONIC_STI,
    MNEMONIC_HLT,
    MNEMONIC_WAIT,

    MNEMONIC_COUNT
};

enum MemoryAddressQualifier : uint8_t
{
    MEMORY_ADDRESS_QUALIFIER_NONE,

    MEMORY_ADDRESS_QUALIFIER_BYTE,
    MEMORY_ADDRESS_QUALIFIER_WORD,

    MEMORY_ADDRESS_QUALIFIER_COUNT
};

struct MemoryAddress
{
    bool direct;
    MemoryAddressQualifier qualifier;
    Register registers[REGISTERS_MAX_LEN];
    int32_t displacement;
};

struct Operand
{
    OperandType type;
    union
    {
        Register register_;
        MemoryAddress memory_address;
        uint16_t immediate_value;
        int32_t label_like_displacement;
    };
};

struct DecodingContext
{
    uint8_t bytes[INSTRUCTION_MAX_BYTES];
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