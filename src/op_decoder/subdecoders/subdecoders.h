#pragma once

// # Single fields
void ReadNextBytesToIndex(uint8_t byte_index, OpDecodeData *decode_data);
void DecodeW(uint8_t w_shift, OpDecodeData *decode_data);
void DecodeD(uint8_t d_shift, OpDecodeData *decode_data);
void DecodeS(uint8_t s_shift, OpDecodeData *decode_data);
void DecodeModRM(uint8_t mod_shift, uint8_t r_m_shift, OpDecodeData *decode_data);
void DecodeReg(uint8_t reg_byte_index, uint8_t reg_shift, OpDecodeData *decode_data);
void DecodeData(uint8_t data_byte_1_index, OpDecodeData *decode_data);
void DecodeAddr(OpDecodeData *decode_data);
void DecodeArithmeticMnemonic(OpDecodeData *decode_data);
uint8_t DecodeDisplacement(OpDecodeData *decode_data);

// # Field aggregates
void DecodeFieldsRegisterOrMemoryAndEither(OpDecodeData *decode_data);
void DecodeFieldsRegisterOrMemoryAndImmediate(OpDecodeData *decode_data);
void DecodeFieldsRegisterAndImmediate(OpDecodeData *decode_data);
void DecodeFieldsMemoryAndAccumulator(OpDecodeData *decode_data);
void DecodeFieldsAccumulatorAndImmediate(OpDecodeData *decode_data);

// # Memory/register
const uint8_t REG_OR_MEM_BUFFER_MAX_LEN = 18;

// # Register / address calculation
bool DecodeRegisterOrMemoryAddress(char *buffer, const OpDecodeData *decode_data);
void DecodeRegister(char *buffer, const OpDecodeData *decode_data);

// # Operands
void DecodeOperandsRegisterOrMemoryAndEither(OpDecodeData *decode_data);
void DecodeOperandsRegisterOrMemoryAndImmediate(OpDecodeData *decode_data);
void DecodeOperandsRegisterAndImmediate(OpDecodeData *decode_data);
void DecodeOperandsAccumulatorAndMemory(OpDecodeData *decode_data);
void DecodeOperandsMemoryAndAccumulator(OpDecodeData *decode_data);
void DecodeOperandsAccumulatorAndImmediate(OpDecodeData *decode_data);
