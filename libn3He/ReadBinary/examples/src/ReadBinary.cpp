#include<iostream>
#include<cstdio>
#include"ReadBinary.h"

using namespace std;

ReadBinary::ReadBinary(const char* filename)
{
  
     ptr_myfile=fopen(filename,"rb");
}

ReadBinary::~ReadBinary()
{
 fclose(ptr_myfile);
}

int ReadBinary::GetValue(int channel,long point)
{

    struct rec
    {
	int my_data[64];
    };

    long counter=point;
    struct rec my_record;
    int value;

    if (!ptr_myfile)
    {
	cout<<"Unable to open file!"<<endl;
	return 1;
    }
    

    fseek(ptr_myfile,sizeof(struct rec)*counter,SEEK_SET);
    fread(&my_record,sizeof(struct rec),1,ptr_myfile);
    // printf("%d   %d\n",counter,my_record.my_data[0]);
    value=my_record.my_data[channel];

    // fclose(ptr_myfile);

    return (value);
}


  
