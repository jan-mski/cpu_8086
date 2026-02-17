#include "../decoder.h"
#include "subdecoders.h"

const char *REGISTER_NAMES_W0[] = {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"};
const char *REGISTER_NAMES_W1[] = {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"};
const char **REGISTER_NAMES[] = {REGISTER_NAMES_W0, REGISTER_NAMES_W1};
const char *ADDRESS_CALCULATION_BASES[] = {"bx + si", "bx + di", "bp + si", "bp + di", "si", "di", "bp", "bx"};

const char *ADDRESS_CALCULATION_REGISTERS_MOD_ZERO[][2] = {
    {"bx", "si"}, {"bx", "di"}, {"bp", "si"}, {"bp", "di"}, {"si"}, {"di"}, {}, {"bx"}
};
const char *ADDRESS_CALCULATION_REGISTERS_MOD_NON_ZERO[][2] = {
    {"bx", "si"}, {"bx", "di"}, {"bp", "si"}, {"bp", "di"}, {"si"}, {"di"}, {"bp"}, {"bx"}
};
const char *(*ADDRESS_CALCULATION_REGISTERS[])[2] = {
    ADDRESS_CALCULATION_REGISTERS_MOD_ZERO,
    ADDRESS_CALCULATION_REGISTERS_MOD_NON_ZERO,
    ADDRESS_CALCULATION_REGISTERS_MOD_NON_ZERO,
    ADDRESS_CALCULATION_REGISTERS_MOD_NON_ZERO
};

void CalculateAddressNoDisplacement(char *buffer, const OpDecodeData *decode_data)
{
    snprintf(buffer, REG_OR_MEM_BUFFER_MAX_LEN, "[%s]", ADDRESS_CALCULATION_BASES[decode_data->r_m]);
}

void GetDirectAddress(char *buffer, const OpDecodeData *decode_data)
{
    snprintf(buffer, REG_OR_MEM_BUFFER_MAX_LEN, "[%i]", decode_data->displacement);
}

void CalculateAddressWithDisplacement(char *buffer, const OpDecodeData *decode_data)
{
    snprintf(buffer, REG_OR_MEM_BUFFER_MAX_LEN, "[%s + %i]",
        ADDRESS_CALCULATION_BASES[decode_data->r_m], decode_data->displacement);
}

void GetRegisterName(char *buffer, const uint8_t w, const uint8_t reg)
{
    snprintf(buffer, REG_OR_MEM_BUFFER_MAX_LEN, "%s", REGISTER_NAMES[w][reg]);
}

bool DecodeRegisterOrMemoryAddress(char *buffer, const OpDecodeData *decode_data)
{
    switch (decode_data->mod)
    {
        case 0b00:
        {
            if (decode_data->r_m == 0b110)
            {
                GetDirectAddress(buffer, decode_data);
            } else
            {
                CalculateAddressNoDisplacement(buffer, decode_data);
            }
        } break;
        case 0b01:
        case 0b10:
        {
            CalculateAddressWithDisplacement(buffer, decode_data);
        } break;
        default:
        {
            GetRegisterName(buffer, decode_data->w, decode_data->r_m);
            return true;
        } break;
    }

    return false;
}

void DecodeRegister(char *buffer, const OpDecodeData *decode_data)
{
    GetRegisterName(buffer, decode_data->w, decode_data->reg);
}