//The FluxGate derived class with Serial as base class
//Author: Latiful Kabir
//Date:09.5.14
//Version:1.0

#include"Serial.h"

using namespace std;

class FluxGate : public Serial //Derived FluxGate class from Serial
{
public:
    int ReadFG(int ch);
    void WriteFG(int ch);
    FluxGate(const char *portName,int sspeed);
    ~FluxGate();
};
