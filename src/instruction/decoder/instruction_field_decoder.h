#pragma once

#include "../instruction.h"
#include "../instruction_input.h"

void DecodeW(uint8_t w_shift, InstructionDecodingContext *decoding_context);
void DecodeD(uint8_t d_shift, InstructionDecodingContext *decoding_context);
void DecodeS(uint8_t s_shift, InstructionDecodingContext *decoding_context);
void DecodeModAndRM(const InstructionInput *instruction_input, uint8_t mod_shift, uint8_t r_m_shift, InstructionDecodingContext *decoding_context);
void DecodeReg(const InstructionInput *instruction_input, uint8_t reg_byte_index, uint8_t reg_shift, InstructionDecodingContext *decoding_context);
void DecodeData(const InstructionInput *instruction_input, uint8_t data_byte_1_index, InstructionDecodingContext *decoding_context);
void DecodeAddr(const InstructionInput *instruction_input, InstructionDecodingContext *decoding_context);
void DecodeArithmeticMnemonic(const InstructionInput *instruction_input, InstructionDecodingContext *decoding_context);
uint8_t DecodeDisplacement8Bit(const InstructionInput *instruction_input, uint8_t displacement_byte_1_index, InstructionDecodingContext *decoding_context);
uint8_t DecodeDisplacement16Bit(const InstructionInput *instruction_input, uint8_t displacement_byte_1_index, InstructionDecodingContext *decoding_context);
uint8_t DecodeDisplacement(const InstructionInput *instruction_input, InstructionDecodingContext *decoding_context);
