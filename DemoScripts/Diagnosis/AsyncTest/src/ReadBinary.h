//A stand alone class for reading and analyzing binary file
//Author: Latiful Kabir
//Date: 6/11/14

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
