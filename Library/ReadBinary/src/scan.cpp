//This script can scan through binary data for specific channel.
//Latiful Kabir
// Date:05/05/2014


#include<iostream>
#include<fstream>
#include"ReadBinary.h"
#include"Constants.h"

using namespace std;

void scan(int ch=0,int start=0,int n=10)
{
   
  ReadBinary fa(DATA_FILE);
  int entries=(int)8*fa.GetFileSize()/(64*32);                
 
  if(entries==0)
  {
      cout<<"No data file or file is empty... Exiting!!!"<<endl;
  }
  else if(start>entries || n>entries)
  {
      cout<<"Requested entries exceed total number of entries. Exiting!!!"<<endl;
  }
  else
  {
      cout<<"Printing "<<n<<" entries starting from "<<start<<" for channel-"<<ch<<endl;

      for(int i=start;i<(start+n);i++)
      {
	  cout<<i<<"   "<<fa.GetValue(ch,i)<<endl;
      }
  }
   
}

int main(void)
{
    if(!fstream(DATA_FILE))
    {
	cout<<"No data file. Exiting !!!"<<endl;
	return -1;
    }
  
    int x,y,z;
    cout<<"Enter Channel number:"<<endl;
    cin>>x;
    cout<<"Enter the first entry number:"<<endl;
    cin>>y;
    cout<<"Enter how many entries to be printed:"<<endl;
    cin>>z;
    scan(x,y,z);
  
    return(0);
}
