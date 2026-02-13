#include "../decoder.h"
#include "subdecoders.h"

typedef void (*r_m_translator_t)(char *r_m_str, const OpDecodeData *decode_data);

const char *REG_W0_TRANSLATIONS[] = {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"};
const char *REG_W1_TRANSLATIONS[] = {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"};
const char **REG_TRANSLATIONS[] = {REG_W0_TRANSLATIONS, REG_W1_TRANSLATIONS};
const char *R_M_TRANSLATIONS[] = {"bx + si", "bx + di", "bp + si", "bp + di", "si", "di", "bp", "bx"};

void TranslateRMMemModeNoDisplacement(char *r_m_str, const OpDecodeData *decode_data)
{
    snprintf(r_m_str, TRANSLATED_R_M_MAX_LEN, "[%s]", R_M_TRANSLATIONS[decode_data->r_m]);
}

void TranslateRMDirectAddress(char *r_m_str, const OpDecodeData *decode_data)
{
    snprintf(r_m_str, TRANSLATED_R_M_MAX_LEN, "[%u]", decode_data->displacement);
}

void TranslateRM8BitDisplacement(char *r_m_str, const OpDecodeData *decode_data)
{
    if (decode_data->displacement != 0)
    {
        snprintf(r_m_str, TRANSLATED_R_M_MAX_LEN, "[%s + %i]",
            R_M_TRANSLATIONS[decode_data->r_m], decode_data->displacement);
    }
    else
    {
        snprintf(r_m_str, TRANSLATED_R_M_MAX_LEN, "[%s]", R_M_TRANSLATIONS[decode_data->r_m]);
    }
}

void TranslateRM16BitDisplacement(char *r_m_str, const OpDecodeData *decode_data)
{
    if (decode_data->displacement != 0)
    {
        snprintf(r_m_str, TRANSLATED_R_M_MAX_LEN, "[%s + %i]",
            R_M_TRANSLATIONS[decode_data->r_m], decode_data->displacement);
    }
    else
    {
        snprintf(r_m_str, TRANSLATED_R_M_MAX_LEN, "[%s]", R_M_TRANSLATIONS[decode_data->r_m]);
    }
}

void TranslateRMRegModeNoDisplacement(char *r_m_str, const OpDecodeData *decode_data)
{
    snprintf(r_m_str, TRANSLATED_R_M_MAX_LEN, "%s", REG_TRANSLATIONS[decode_data->w][decode_data->r_m]);
}

// index: (mod << 3 | r_m), where mod is 2-bit long, r_m is 3-bit long, which makes a 5-bit long index
r_m_translator_t R_M_TRANSLATORS[32] = {
    REPEAT_6(TranslateRMMemModeNoDisplacement),  // 0b00000 - 0b00101
    TranslateRMDirectAddress,                    // 0b00110
    TranslateRMMemModeNoDisplacement,            // 0b00111
    REPEAT_8(TranslateRM8BitDisplacement),       // 0b01000 - 0b01111
    REPEAT_8(TranslateRM16BitDisplacement),      // 0b10000 - 0b10111
    REPEAT_8(TranslateRMRegModeNoDisplacement)   // 0b11000 - 0b11111
};

void TranslateRM(char *r_m_str, const OpDecodeData *decode_data)
{
    const uint8_t index = decode_data->mod << 3 | decode_data->r_m;
    const r_m_translator_t r_m_translator = R_M_TRANSLATORS[index];
    r_m_translator(r_m_str, decode_data);
}

void TranslateReg(char *reg_str, const OpDecodeData *decode_data)
{
    snprintf(reg_str, TRANSLATED_REG_MAX_LEN, "%s", REG_TRANSLATIONS[decode_data->w][decode_data->reg]);
}
