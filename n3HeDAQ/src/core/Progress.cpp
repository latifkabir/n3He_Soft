//Program to show progress status bar of current run
//Author:Latiful Kabir
//Date: 9.29.14
#include <iostream> 
#include <string> 
#include <unistd.h> 
#include <ncurses.h> 
#include <sys/ioctl.h> 
#include <stdlib.h> 
       
using namespace std; 
              
void printProgBar(int percent)      // percent -> Percentage 
{ 
    string bar; 
    struct winsize uk; 
    if(ioctl(0,TIOCGWINSZ,&uk) != 0) 
    { 
	exit(1); 
    } 
    int wdt = uk.ws_col - 55; // create some space for the other text 
    if(wdt < 5) 
    { 
	wdt = 5;      // minimum width for progress bar 5 char 
    } 
       
    for(int i=0; i < wdt; i++) 
    { 
	if(i < (percent*wdt/100)) 
	{ 
	    bar.replace(i,1,"="); 
	} 
	else if(i == (percent*wdt/100))
	{ 
	    bar.replace(i,1,">"); 
	}
	else 
	{ 
	    bar.replace(i,1," "); 
	} 
    } 
    cout << "\r";          // go to the first character in terminal 
    cout<<"\t\t\t";
    cout << "[" << bar << "] ";     // progress bar        
    cout << percent << " %   ";      

    cout<< flush; 
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
