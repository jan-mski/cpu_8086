const uint8_t INSTRUCTION_MAX_BYTES = 6;
const uint8_t REGISTER_NAMES_MAX_LEN = 2;

enum Register
{
    REGISTER_NONE,
    REGISTER_AL,
    REGISTER_AH,
    REGISTER_AX,
    REGISTER_BL,
    REGISTER_BH,
    REGISTER_BX,
    REGISTER_CL,
    REGISTER_CH,
    REGISTER_CX,
    REGISTER_DL,
    REGISTER_DH,
    REGISTER_DX,
    REGISTER_SP,
    REGISTER_BP,
    REGISTER_SI,
    REGISTER_DI,
    REGISTER_COUNT
};

enum OperandType
{
    OPERAND_NONE,
    OPERAND_REGISTER,
    OPERAND_MEMORY_ADDRESS,
    OPERAND_IMMEDIATE,
    OPERAND_LABEL_LIKE_DISPLACEMENT
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

struct InstructionDecodingContext
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

    const char *mnemonic;
    Operand operands[2];
};
