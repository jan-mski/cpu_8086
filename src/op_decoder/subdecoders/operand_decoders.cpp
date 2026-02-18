#include "../decoder.h"
#include "subdecoders.h"

void DecodeOperandsRegisterOrMemoryAndEither(OpDecodeData *decode_data)
{
    char reg_str[REG_OR_MEM_BUFFER_MAX_LEN];
    DecodeRegister(reg_str, decode_data);

    char r_m_str[REG_OR_MEM_BUFFER_MAX_LEN];
    DecodeRegisterOrMemoryAddress(r_m_str, decode_data);

    if (decode_data->d == 0)
    {
        snprintf(decode_data->left_operand, OPERAND_MAX_LEN, "%s", r_m_str);
        snprintf(decode_data->right_operand, OPERAND_MAX_LEN, "%s", reg_str);
    }
    else
    {
        snprintf(decode_data->left_operand, OPERAND_MAX_LEN, "%s", reg_str);
        snprintf(decode_data->right_operand, OPERAND_MAX_LEN, "%s", r_m_str);
    }
    decode_data->num_operands = 2;
}

void DecodeOperandsRegisterOrMemoryAndImmediate(OpDecodeData *decode_data)
{
    char r_m_str[REG_OR_MEM_BUFFER_MAX_LEN];
    const bool is_register = DecodeRegisterOrMemoryAddress(r_m_str, decode_data);

    snprintf(decode_data->right_operand, OPERAND_MAX_LEN, "%u", decode_data->data);
    if (is_register)
    {
        snprintf(decode_data->left_operand, OPERAND_MAX_LEN, "%s", r_m_str);
    } else
    {
        const char *qualifier = decode_data->w == 0 ? "byte" : "word";
        snprintf(decode_data->left_operand, OPERAND_MAX_LEN, "%s %s", qualifier, r_m_str);
    }
    decode_data->num_operands = 2;
}

void DecodeOperandsRegisterAndImmediate(OpDecodeData *decode_data)
{
    char reg_str[REG_OR_MEM_BUFFER_MAX_LEN];
    DecodeRegister(reg_str, decode_data);

    snprintf(decode_data->left_operand, OPERAND_MAX_LEN, "%s", reg_str);
    snprintf(decode_data->right_operand, OPERAND_MAX_LEN, "%u", decode_data->data);
    decode_data->num_operands = 2;
}

void DecodeOperandsAccumulatorAndMemory(OpDecodeData * decode_data)
{
    snprintf(decode_data->left_operand, OPERAND_MAX_LEN, "ax");
    snprintf(decode_data->right_operand, OPERAND_MAX_LEN, "[%u]", decode_data->addr);
    decode_data->num_operands = 2;
}

void DecodeOperandsMemoryAndAccumulator(OpDecodeData * decode_data)
{
    snprintf(decode_data->left_operand, OPERAND_MAX_LEN, "[%u]", decode_data->addr);
    snprintf(decode_data->right_operand, OPERAND_MAX_LEN, "ax");
    decode_data->num_operands = 2;
}

void DecodeOperandsAccumulatorAndImmediate(OpDecodeData * decode_data)
{
    snprintf(decode_data->left_operand, OPERAND_MAX_LEN, decode_data->w == 0 ? "al" : "ax");
    snprintf(decode_data->right_operand, OPERAND_MAX_LEN, "%u", decode_data->data);
    decode_data->num_operands = 2;
}

void DecodeOperandsReturnFromCall(OpDecodeData *decode_data)
{
    snprintf(decode_data->left_operand, OPERAND_MAX_LEN, "($+2) + %i", decode_data->displacement);
    decode_data->num_operands = 1;
}