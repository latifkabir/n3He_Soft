//Generate current time
//Author: latiful Kabir
//Date: 03.02.15

#include<time.h>
#include<stdlib.h>
#include<stdio.h>

void CurrentTime(char *strname,int strlen)
{
	time_t time_now;
	time(&time_now);
	struct tm my_time;
	localtime_r (&time_now,&my_time);
	snprintf(strname,strlen,"%04d-%02d-%02d-%02d-%02d-%02d",my_time.tm_year+1900,my_time.tm_mon+1,my_time.tm_mday,my_time.tm_hour,my_time.tm_min,my_time.tm_sec);
}
