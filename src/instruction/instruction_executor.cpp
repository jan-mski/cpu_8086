void ExecuteInstruction(Instruction *instruction)
{
    if (instruction->mnemonic == Mnemonic_MOV &&
        instruction->operands[0].type == OperandType_Register &&
        instruction->operands[1].type == OperandType_Immediate)
    {
        Register *register_ = &registers[instruction->operands[0].register_id];
        uint16_t immediate_value = instruction->operands[1].immediate_value;
        register_->SetValue(immediate_value);
    }
    else if (instruction->mnemonic == Mnemonic_MOV &&
        instruction->operands[0].type == OperandType_Register &&
        instruction->operands[1].type == OperandType_Register)
    {
        Register *dst_register = &registers[instruction->operands[0].register_id];
        Register *src_register = &registers[instruction->operands[1].register_id];
        dst_register->SetValue(src_register->GetValue());
    }
}