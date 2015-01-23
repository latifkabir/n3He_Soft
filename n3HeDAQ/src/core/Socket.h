//The Socket Class Structure 
//Author: Latiful Kabir
//Base Socket code contributed by: David Blyth
//Date:08.15.14
//Version:1.0



//Note!!!: To enable non-static data member you must compile with -std=c++11 flag



#include<netdb.h>
#include<unistd.h>
#include<fstream>


using namespace std;

class Socket
{
private:
    const char *SERVER_NAME; //IP address for the socket
    const char *PORT;       //Port number of the socket
    int daq;               //DAQ module number
    char *filename=new char[200];

    addrinfo hints;
    addrinfo* servInfo;

    ofstream data;


public:
    int s;
    int bufferSize=0x100000;
    char *buffer = new char[bufferSize]; //Requires c++11
    ssize_t retVal;
    ssize_t retChunk;
    ssize_t totRet;
    int nout;

    Socket(const char *ip,const char *port,int module);
    ~Socket();
    int CheckStatus();
    ssize_t ReadData(int tSize,int fSize);
    void WriteData();
    int WriteToSocket(const char *txt);
    size_t GetFileSize();
 
};

