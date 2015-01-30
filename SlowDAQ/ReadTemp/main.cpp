#include <iostream>
#include "Serial.h"
using namespace std;

int main()
{
    Serial temp("/dev/ttyUSB0",4800);

    if(temp.CheckStatus()!=1)
    {
	temp.Write("\114");
	sleep(3);
	temp.Write("\60");
	sleep(3);
	temp.Write("\124");
	sleep(1);
	temp.Read();
    }
    return 0;
}
