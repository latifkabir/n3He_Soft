//This program Processes data file to throw away unused channels.
//Author: Latiful Kabir
//Date: 01/19/15

#include <fstream>      //For std::ifstream, std::ofstream
#include <iostream>
#include <cstdio>
#include "ProcessData.h"
#include "Constants.h"

using namespace std;

int ProcessData(int run,int module,bool gui_mode) 
{

    char *file_old=new char[200];
    char *file_new=new char[200];

    sprintf(file_old,OLD_FILE,module);
    sprintf(file_new,NEW_FILE,run,module);

    ifstream inFile (file_old,ifstream::binary);
    ofstream outFile (file_new,ofstream::binary);

    if(!inFile)
    {
	if(!gui_mode)
	    cout<<"Input file does not exist !"<<endl;
	return -1;
    }

    // get size of file
    inFile.seekg (0,inFile.end);
    long fsize = inFile.tellg();  //Size of input file
    inFile.seekg (0);

    int sizeBefore=NCHAN_BEFORE*sizeof(unsigned); //Chunk Size Process
    int sizeAfter=NCHAN_AFTER*sizeof(unsigned); //Buffer or Chunk Size after process

    // allocate memory for file content
    char* buffer = new char[sizeAfter];

    for (int i=sizeBefore; i<=fsize; i+=sizeBefore) 
    {	
	inFile.seekg (i-sizeBefore);
	// read content of inFile
	inFile.read (buffer,sizeAfter);

	// write to outFile
	outFile.write (buffer,sizeAfter);
    }

    // release dynamically-allocated memory
    outFile.close();
    inFile.close();

    if(!gui_mode)
	cout<<"\n\n\t\tData file for DAQ "<<module<<" has been processed successfully"<<endl;

    delete[] buffer;
    delete[] file_old;
    delete[] file_new;

    return 1;
}
