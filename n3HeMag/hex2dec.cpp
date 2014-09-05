//#include"conio.h"
#include<stdio.h>
#include<string.h>
#include<math.h>
int main()
{
    char hex[25];
    int i,j,num,len,counter=0;
    long int sum=0;  //value can cross range of int
    printf("\nEnter the hexadecimal number: ");
    gets(hex);
    //strupr(hex);  //so the program becomes independent of string case
    len=strlen(hex);
    for(i=len-1;i>=0;i--)
    {
       if(hex[i]>='0'&&hex[i]<='9')
          num=hex[i]-'0';     //the character is number in between 0 to 9
       else
       {
          if(hex[i]>='A'&&hex[i]<='F')
          num=hex[i]-55;      //the character is either a,b,c,d,e or f 
          else
          {
              printf("The Entered number is not hexadecimal number");
              //getch();// If the character is beyond 'f'
              return 1;
          }
       }
       sum=sum+pow(16,counter)*num;  //according to formula given by the link
       counter++;
    } 
    printf("Hexadecimal conversion of %s to decimal is %ld",hex,sum);
    return 0;
}
