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

    sprintf(file_old,NEW_FILE,run,DAQTEMP);
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

    int sizeBefore=NCHAN_BEFORE*sizeof(unsigned); //Chunk Size before Process
    int sizeAfter=NCHAN_AFTER*sizeof(unsigned); //Buffer or Chunk Size after process
    int startPoint=5*sizeof(unsigned); //Offset for the first chunk

    // allocate memory for file content
    char* buffer = new char[sizeAfter];

    for (int i=startPoint; i<=fsize; i+=sizeBefore) 
    {	
	inFile.seekg (i);
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

    if(remove(file_old) == 0)
    {
	if(!gui_mode)
	    cout<<"\t\tTemporary file has been deleted"<<endl<<endl;
    }
    else
    {
	if(!gui_mode)
	    cout<<"\t\tError deleting temporary file"<<endl<<endl;
    }

    delete[] buffer;
    delete[] file_old;
    delete[] file_new;

    return 1;
}
