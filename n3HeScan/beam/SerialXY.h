//The SerialXY derived class with Serial as base class
//Author: Latiful Kabir
//Date:09.5.14
//Version:1.0

#include<fstream>
#include"Serial.h"

using namespace std;

class SerialXY : public Serial //Derived SerialXY class from Serial
{
public:
    char move_x[200];
    char move_y[200];
    ofstream BeamData;
    int sleep_time;
    void MoveXY(char axis,int increment);
    int GetPosition(char axis);
    void CurrentTime();
    SerialXY(const char *portName,int sspeed);
    ~SerialXY();
};

