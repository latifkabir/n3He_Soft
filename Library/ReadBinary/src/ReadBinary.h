#include"Constants.h"

struct Pattern
{
    int data[NCHAN];
};

class ReadBinary
{
public:
    FILE *ptr_myfile;
    const char* myfile;
    Pattern *dataPattern=new Pattern;
    int fStatus;
    size_t GetFileSize();
    int GetValue(int channel,long position);
    ReadBinary(const char* filename);
    ~ReadBinary();
};
