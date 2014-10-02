//Program to show progress status bar of current run
//Author:Latiful Kabir
//Date: 9.29.14

#include<iostream>
#include<unistd.h>
using namespace std;

void printProgBar( int percent )
{
    std::string bar;

    for(int i = 0; i < 50; i++)
    {
	if( i < (percent/2))
	{
	    bar.replace(i,1,"=");
	}
	else if( i == (percent/2))
	{
	    bar.replace(i,1,">");
	}
	else
	{
	    bar.replace(i,1," ");
	}
    }

    std::cout<< "\r" "[" << bar << "] ";
    std::cout.width( 3 );
    std::cout<< percent << "%     " << std::flush;
}

/*
//Demo usage:
int main(void)
{
    printProgBar(10);
    sleep(3);
    printProgBar(20);
    sleep(3);
    printProgBar(40);
    sleep(3);
    printProgBar(60);
    sleep(3);
    printProgBar(80);
    sleep(3);
    printProgBar(100);

    return(0);
}

*/
