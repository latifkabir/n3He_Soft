//The Serial Class for serial communication
//Author: Latiful Kabir
//Version:0.0
//Date:08.27.14

#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <stdbool.h>
#include<string>
#include "Serial.h"

using namespace std;
typedef unsigned char byte;


Serial::Serial(const char *portName,int sspeed)
{
  serial_fd, file_fd = -1;
  serial_portname = portName;
  speed = sspeed;

}

//Open Serial Port and Check Status
int Serial::CheckStatus()
{
  

  switch (speed)
  {
    case 50: bspeed = B50; break;
    case 75: bspeed = B75; break;
    case 110: bspeed = B110; break;
    case 134: bspeed = B134; break;
    case 150: bspeed = B150; break;
    case 200: bspeed = B200; break;
    case 300: bspeed = B300; break;
    case 600: bspeed = B600; break;
    case 1200: bspeed = B1200; break;
    case 1800: bspeed = B1800; break;
    case 2400: bspeed = B2400; break;
    case 4800: bspeed = B4800; break;
    case 9600: bspeed = B9600; break;
    case 19200: bspeed = B19200; break;
    case 38400: bspeed = B38400; break;
    case 57600: bspeed = B57600; break;
    case 115200: bspeed = B115200; break;
    case 230400: bspeed = B230400; break;
    default:
	cout<<"Speed "<<speed<<" not supported\n";
      return 1;
  }

  // Open the port. NB. without O_NONBLOCK, this would wait until the
  // modem raises carrier detect.
  serial_fd = open(serial_portname, O_RDWR | O_NONBLOCK | O_NDELAY);
  if (serial_fd < 0)
  {
    fprintf(stderr,"Cannot open serial port '%s': %s\n",
            serial_portname,strerror(errno));
    return 1;
  }


  // Save the current terminal settings, so we can reset to them later on
  tcgetattr(serial_fd, &term);
  // Set the port speed as requested
  cfsetispeed(&term,bspeed);
  cfsetospeed(&term,bspeed);

  // Turn off canonical processing (line buffer, backspace etc)
  cfmakeraw(&term);
  // Turn of carrier detect (ie. make /dev/ttyd0 work like cuaa0
  term.c_cflag |= CLOCAL | CREAD;

  // And write the changes out so they take effect.
  tcsetattr(serial_fd, TCSANOW, &term);

  // Similarly, disable line buffering of the keyboard, but remember the old
  // settings to restore on exit
  tcgetattr(STDIN_FILENO, &term);


  FD_ZERO(&rd_map);
  fcntl(serial_fd,F_SETFL,FNDELAY);
 
}

Serial::~Serial()
{
    close(serial_fd);
}

int Serial::Write(const char *txt)
{
//  string name=txt;

    nout=write(serial_fd, txt, 1);      
//  nout=write(serial_fd, name.c_str(), name.length());      

      return(0);
}

int Serial::Read()
{
    nout = read(serial_fd,buf,256);
    return(buf[0]);
}

void Serial::Read(char *tmp)
{
    nout = read(serial_fd,buf,256);


    for(int p=0;p<48;p++)
	tmp[p]=buf[p];
}


