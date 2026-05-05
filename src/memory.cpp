namespace memory
{
    U8 ReadByte(Memory* memory,
                Address byte_address)
    {
        byte_address = byte_address < MEMORY_SIZE ? byte_address : 0;

        return memory->bytes[byte_address];
    }

    U16 ReadWord(Memory* memory,
                 Address byte_1_address)
    {
        return (U16) ReadByte(memory, byte_1_address)
               | (U16) (ReadByte(memory, byte_1_address + 1) << 8);
    }

    void WriteByte(Memory* memory,
                   Address byte_address,
                   U8 byte_value)
    {
        byte_address = byte_address < MEMORY_SIZE ? byte_address : 0;
        memory->bytes[byte_address] = byte_value;
    }

    void WriteWord(Memory* memory,
                   Address byte_1_address,
                   U16 word_value)
    {
        WriteByte(memory, byte_1_address, (U8) word_value);
        WriteByte(memory, byte_1_address + 1, (U8) (word_value >> 8));
    }

    U16 LoadFileToMemory(Memory* memory,
                         const char* file_path)
    {
        FILE* file = fopen(file_path, "rb");

        if (file == nullptr)
        {
            fprintf(stderr, "Error reading file: %s\n", file_path);

            return 0;
        }

        size_t num_bytes_read = fread(memory->bytes, 1, MEMORY_SIZE, file);

        fclose(file);

        return num_bytes_read;
    }

    void SaveMemoryToFile(const char* file_path,
                          Memory* memory)
    {
        FILE* file = fopen(file_path, "wb");

        if (file == nullptr)
        {
            fprintf(stderr, "Error opening file for writing: %s\n", file_path);
            return;
        }

        fwrite(memory->bytes, 1, MEMORY_SIZE, file);

        fclose(file);
    }
}
