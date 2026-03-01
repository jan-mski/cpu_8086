const uint8_t INSTRUCTION_MAX_BYTES = 6;
const uint8_t REGISTERS_MAX_LEN = 2;

enum OperandType
{
    OPERAND_TYPE_NONE,

    OPERAND_TYPE_REGISTER,
    OPERAND_TYPE_MEMORY_ADDRESS,
    OPERAND_TYPE_IMMEDIATE,
    OPERAND_TYPE_LABEL_LIKE_DISPLACEMENT
};

enum Mnemonic
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
    MNEMONIC_SUB,
    MNEMONIC_CMP,
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

    MNEMONIC_COUNT
};

enum MemoryAddressQualifier
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
    bool w;                          // 1 bit
    bool d;                          // 1 bit
    bool s;                          // 1 bit
    uint8_t mod;                     // 2 bits
    uint8_t sr;                      // 2 bits
    uint8_t reg;                     // 3 bits
    uint8_t r_m;                     // 3 bits
    uint8_t common_mnemonic;         // 3 bits
    uint16_t data;                   // 8 || 16 bits
    uint16_t addr;                   // 8 || 16 bits
    int32_t displacement;            // 8 || 16 bits
};

struct Instruction
{
    Mnemonic mnemonic;
    Operand operands[2];
};