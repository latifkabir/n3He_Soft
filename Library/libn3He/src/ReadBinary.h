//A stand alone class for reading and analyzing binary file
//Author: Latiful Kabir
//Date: 6/11/14

#include <stdio.h>
#include"Constants.h"

#define NCHAN 1  //Pretent that our data files have just one channel

struct Pattern
{
    int data[NCHAN];
};

class ReadBinary
{
public:
    FILE *ptr_myfile;
    const char* myfile;
    Pattern *dataPattern;
    int fStatus;
    size_t GetFileSize();
    int GetValue(int channel,long position);
    ReadBinary(const char* filename);
    ~ReadBinary();
};
