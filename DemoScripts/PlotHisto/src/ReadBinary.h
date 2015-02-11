//A stand alone class for reading and analyzing binary file
//Author: Latiful Kabir
//Date: 6/11/14

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
