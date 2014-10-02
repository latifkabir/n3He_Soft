//The Daq derived class with Socket as base class
//Author: Latiful Kabir
//Date:08.15.14
//Version:1.0



#include"Socket.h"

using namespace std;

class Daq : public Socket //Derived Daq class from Socket
{
public:
    int filesize;
    void SaveData(bool pStatus);
    Daq(const char *ip,const char *port,int module,int length);
    ~Daq();
};
