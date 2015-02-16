//A stand alone class for reading and analyzing binary file
//Author: Latiful Kabir
//Date: 6/11/14

#include<iostream>
#include<cstdio>
#include<string>
#include <sys/stat.h>
#include"ReadBinary.h"

using namespace std;

ReadBinary::ReadBinary(const char* filename)
{
    dataPattern=new Pattern;
    myfile=filename;
    ptr_myfile=fopen(filename,"rb");

    if (!ptr_myfile)
    {
	cout<<"Unable to open file!"<<endl;
	fStatus=0;
    }
    else
	fStatus=1;
    
}

ReadBinary::~ReadBinary()
{
    fclose(ptr_myfile);
    delete dataPattern;
}

size_t ReadBinary::GetFileSize()
{
    const string fname = string(myfile);
    struct stat st;
    if(stat(fname.c_str(), &st) != 0) 
    {
	return 0;
    }
    return st.st_size;
}

int ReadBinary::GetValue(int channel,long position)
{

    if(!fStatus)
	return -1;

    fseek(ptr_myfile,sizeof(struct Pattern)*position,SEEK_SET);
    fread(dataPattern,sizeof(struct Pattern),1,ptr_myfile);
    return (dataPattern->data[channel]);
}

