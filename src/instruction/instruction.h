const uint8_t INSTRUCTION_MAX_BYTES = 6;
const uint8_t REGISTER_NAMES_MAX_LEN = 2;

enum OperandType
{
    OPERAND_NONE,
    OPERAND_REGISTER,
    OPERAND_MEMORY_ADDRESS,
    OPERAND_IMMEDIATE,
    OPERAND_LABEL_LIKE_DISPLACEMENT
};

enum Mnemonic
{
    MNEMONIC_NONE,

    MNEMONIC_MOV,
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

struct MemoryAddress
{
    bool direct;
    const char *qualifier;
    Register *registers;
    int32_t displacement;
};

struct Operand
{
    OperandType type;
    Register register_;
    MemoryAddress memory_address;
    uint16_t immediate_value;
    int32_t label_like_displacement;
};

struct DecodingContext
{
    uint8_t bytes[INSTRUCTION_MAX_BYTES];
    uint8_t num_bytes_read;
    bool w;                          // 1 bit
    bool d;                          // 1 bit
    bool s;                          // 1 bit
    uint8_t mod;                     // 2 bits
    uint8_t reg;                     // 3 bits
    uint8_t r_m;                     // 3 bits
    uint8_t common_mnemonic;         // 3 bits
    uint16_t data;                   // 8/16 bits
    uint16_t addr;                   // 8/16 bits
    int32_t displacement;            // 8/16 bits

    Mnemonic mnemonic;
    Operand operands[2];
};
