#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main ()
{
        string s("0x1C");
        unsigned long value;
        istringstream iss(s);
        iss >> hex >> value;
        cout << value << endl;
        return 0;
}
