
class ReadBinary
{
public:
    FILE *ptr_myfile;
    const char* myfile;
    size_t GetFileSize();
    int GetValue(int channel,long point);
    ReadBinary(const char* filename);
    ~ReadBinary();
};
