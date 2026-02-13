#pragma once

void ReadNextBytesToIndex(uint8_t byte_index, OpDecodeData *decode_data);
void DecodeW(uint8_t w_shift, OpDecodeData *decode_data);
void DecodeD(uint8_t d_shift, OpDecodeData *decode_data);
void DecodeModRM(uint8_t mod_shift, uint8_t r_m_shift, OpDecodeData *decode_data);
void DecodeReg(uint8_t reg_byte_index, uint8_t reg_shift, OpDecodeData *decode_data);
void DecodeData(uint8_t data_byte_1_index, OpDecodeData *decode_data);
void DecodeAddr(OpDecodeData *decode_data);
uint8_t DecodeDisplacement(OpDecodeData *decode_data);

const uint8_t TRANSLATED_REG_MAX_LEN = 3;
const uint8_t TRANSLATED_R_M_MAX_LEN = 18;

void TranslateRM(char *r_m_str, const OpDecodeData *decode_data);
void TranslateReg(char *reg_str, const OpDecodeData *decode_data);
