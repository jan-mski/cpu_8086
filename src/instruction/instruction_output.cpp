#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include "../instruction/instruction.h"
#include "instruction_output.h"

void PrintInstructionString(FILE *output_stream, const InstructionDecodingContext *decoding_context)
{
    fprintf(output_stream, "%s", decoding_context->mnemonic);

    for (size_t operand_idx = 0; operand_idx < ARRAY_SIZE(decoding_context->operands); ++operand_idx)
    {
        const Operand *operand = &decoding_context->operands[operand_idx];
        fprintf(output_stream, operand_idx == 0 ? " " : ", ");

        switch (operand->type)
        {
            case OPERAND_NONE:
            {
                break;
            } break;
            case OPERAND_REGISTER:
            {
                fprintf(output_stream, "%s", operand->register_name);
            } break;
            case OPERAND_MEMORY_ADDRESS:
            {
                const MemoryAddress *memory_address = &operand->memory_address;
                if (memory_address->qualifier)
                {
                    fprintf(output_stream, "%s", memory_address->qualifier);
                }
                if (memory_address->direct)
                {
                    fprintf(output_stream, "[%i]", memory_address->displacement);
                }
                else
                {
                    for (size_t register_idx = 0; register_idx < REGISTER_NAMES_MAX_LEN; ++register_idx)
                    {
                        const char *register_name = memory_address->register_names[register_idx];
                        if (!register_name)
                        {
                            break;
                        }
                        fprintf(output_stream, register_idx == 0 ? "[%s" : " + %s", register_name);
                    }
                    fprintf(output_stream, " + %i]", memory_address->displacement);
                }
            } break;
            case OPERAND_IMMEDIATE:
            {
                fprintf(output_stream, "%u", operand->immediate_value);
            } break;
            case OPERAND_LABEL_LIKE_DISPLACEMENT:
            {
                fprintf(output_stream, "($+2) + %i", operand->label_like_displacement);
            } break;
        }
    }

    fprintf(output_stream, "\n");
}
