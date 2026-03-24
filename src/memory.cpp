namespace memory
{
    void LoadFileToMemory(Memory *memory, const char *file_path)
    {
        FILE *file = fopen(file_path, "rb");

        if (file == nullptr)
        {
            fprintf(stderr, "Error reading file: %s\n", file_path);
            return;
        }
        
        size_t num_bytes_read = fread(memory->bytes, 1, MEMORY_SIZE, file);
        memory->num_bytes_used = num_bytes_read;

        fclose(file);
    }

    size_t ReadByte(uint8_t *destination, uint32_t address, Memory *memory)
    {
        if (address < memory->num_bytes_used)
        {
            *destination = memory->bytes[address];
            return 1;
        }

        return 0;
    }
}
