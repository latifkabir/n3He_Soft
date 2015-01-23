//The Socket Class Definition 
//Author: Latiful Kabir
//Base Socket code contributed by: David Blyth
//Date:08.15.14
//Version:1.0

#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<unistd.h>
#include<iostream>
#include<fstream>
#include <sys/stat.h>
#include"Socket.h"
#include"Constants.h"

using namespace std;


//Constructor for Socket
Socket::Socket(const char *ip,const char *port,int module)
{
    SERVER_NAME=ip;
    PORT=port;
    daq=module;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = AF_UNSPEC;

    //Generate file name for corresponding DAQ module
    sprintf(filename,OLD_FILE,daq);
    data.open(filename,ofstream::binary);
}

//Destructor for Socket
Socket::~Socket()
{
    close(s);   //Close the socket
    data.close();  //Close the data file
    delete []buffer;  //Deallowcate buffer memory
    delete []filename;  //Deallowcate char array
}


//Create Socket and check status
int Socket::CheckStatus()
{

	int status = getaddrinfo( SERVER_NAME, PORT, &hints, &servInfo);
	if (status != 0) {
		cerr << "getaddrinfo error: " << gai_strerror(status) << endl;
		return 1;
	}

	s = socket(servInfo->ai_family, servInfo->ai_socktype,
			servInfo->ai_protocol);
	if(s < 0) {
		cerr << "Socket acquisition failed" << endl;
		return 1;
	}

	status = connect(s, servInfo->ai_addr, servInfo->ai_addrlen);
	if(status < 0) {
	    //cerr << "Connection failed" << endl;
		return 1;
	}

	return(0);
}

//Read Chunk of data to buffer
ssize_t Socket::ReadData(int tSize,int fSize)
{
    if((tSize+bufferSize)<fSize)
	retChunk=read(s,buffer,bufferSize);
    else
	retChunk=read(s,buffer,(fSize-tSize)); //resquest only remaining chunk at the end of file.

    return retChunk;
}


//Write data to the file from the buffer
void Socket::WriteData()
{
    data.write(buffer, retVal);	
   // cout.write(buffer, retVal); //Uncomment this if you want to dump to screen/file.
}

int Socket::WriteToSocket(const char *txt)
{
    string str=txt;
    nout=write(s, str.c_str(), str.length());
    return(0);
}

size_t Socket::GetFileSize()
{
    const string fname = string(filename);
    struct stat st;
    if(stat(fname.c_str(), &st) != 0) 
    {
        return 0;
    }
    return st.st_size;   
}
