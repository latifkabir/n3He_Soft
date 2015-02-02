// Program to read temperature from OMEGA CN606 & CN612 Series Temperature Monitor device
// Author: Latiful Kabir
// Date: 02/02/15

#include <iostream>
#include "Serial.h"
using namespace std;

int main()
{
    cout<<"Please wait while the temperature monitor is initialized ..."<<endl;
    Serial temp("/dev/ttyUSB0",4800);

    if(temp.CheckStatus()!=1)
    {
	cout<<"Reading the temperatures ..."<<endl;
	temp.Write("L");
	sleep(1);
	temp.Write("0"); //Passcode manually set to the device
	sleep(1);
	temp.Write("T");
	sleep(1);
	temp.Read();
    }
    return 0;
}
