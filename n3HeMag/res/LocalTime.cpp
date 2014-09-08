//Program to get local time in desired format
//For details go to man page by doing: man ctime
//OR go to:http://man7.org/linux/man-pages/man3/ctime.3.html

#include<time.h>
#include<iostream>
#include<stdio.h>

using namespace std;

int main(void)
{
	time_t time_now;
	time(&time_now);
	struct tm my_time;
	localtime_r (&time_now,&my_time);
	int strlen=100;
	char strname[strlen];
	snprintf(strname,strlen,"%04d-%02d-%02d-%02d-%02d-%02d",my_time.tm_year+1900,my_time.tm_mon+1,my_time.tm_mday,my_time.tm_hour,my_time.tm_min,my_time.tm_sec);
	cout<<strname<<endl;
	return(0);
}
