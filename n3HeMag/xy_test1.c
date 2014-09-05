// grump -- a very simple serial port interface
//
// TODO:
// 1. atexit() handler to put the terminal back to normal
// 2. signal handler to ditto
// 3. consider mimicking mimicking miniterm.py's "exit" keybinding?
// 4. ditto for it's "obey a file"? do I ever want to use that?
//
// (miniterm.py says "Quit: Ctrl+] | Upload: Ctrl+U")

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
#ifndef linux
#include <sys/ttycom.h>
#endif
#include <stdbool.h>

typedef unsigned char byte;

static void print_usage()
{
  fprintf(stderr,
          "Usage: grump [-speed <speed>] [<serial device>]\n"
          "\n"
          "A very simple program for interacting over the serial port.\n"
          "\n"
          " <speed> defaults to 115200\n"
          " <serial device> defaults to /dev/ttyUSB0\n"
          "\n"
          "So, for instance:\n"
          "\n"
          " grump\n"
          " grump /dev/ttyUSB0\n"
          " grump /dev/ttyS0\n"
          "\n"
          "Beware that CTRL-C both sends CTRL-C and also breaks out of grump.\n"
          "Future versions of this software may try to do something more sensible.\n"
          );
}

int main(int argc, char **argv)
{
  int serial_fd, file_fd = -1;
  char *serial_portname = NULL;
  struct termios term, saved_term;
  fd_set rd_map;
  int speed = 300;
  int bspeed;

  int ii = 1;

  while (ii < argc)
  {
    if (argv[ii][0] == '-')
    {
      if (!strcmp("--help",argv[ii]) || !strcmp("-help",argv[ii]) ||
          !strcmp("-h",argv[ii]))
      {
        print_usage();
        return 0;
      }
      else if (!strcmp("-speed",argv[ii]))
      {
        speed = atoi(argv[ii+1]);
        ii++;
      }
      else
      {
        fprintf(stderr,"### grump: "
                "Unrecognised command line switch '%s'\n",argv[ii]);
        return 1;
      }
    }
    else
    {
      serial_portname = argv[ii];
    }
    ii++;
  }

  if (serial_portname == NULL)
    serial_portname = "/dev/ttyUSB0";

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
      printf("Speed %d not supported\n",speed);
      return 1;
  }

  /* Open the port. NB. without O_NONBLOCK, this would wait until the */
  /* modem raises carrier detect. */
  serial_fd = open(serial_portname, O_RDWR | O_NONBLOCK | O_NDELAY);
  if (serial_fd < 0)
  {
    fprintf(stderr,"Cannot open serial port '%s': %s\n",
            serial_portname,strerror(errno));
    return 1;
  }

  // Adjust the port settings. This is done by reading the current setings
  // into memory, making any desired change to that in-memory copy, then
  // writing them back into the terminal device so that all the changes come
  // into effect. See termios(4) man page for detail

  // Save the current terminal settings, so we can reset to them later on
  tcgetattr(serial_fd, &term);
  // Set the port speed as requested
  cfsetispeed(&term,bspeed);
  cfsetospeed(&term,bspeed);
  // Turn off canonical processing (line buffer, backspace etc)
  cfmakeraw(&term);
  // Turn of carrier detect (ie. make /dev/ttyd0 work like cuaa0
  term.c_cflag |= CLOCAL | CREAD;
#ifndef linux
  // Turn off RTS/CTS flow control (probably off anyhow, but make sure)
  term.c_cflag &= ~(CCTS_OFLOW | CRTS_IFLOW);
#endif
  // And write the changes out so they take effect.
  tcsetattr(serial_fd, TCSANOW, &term);

  // Similarly, disable line buffering of the keyboard, but remember the old
  // settings to restore on exit
  tcgetattr(STDIN_FILENO, &term);
  saved_term = term;
  cfmakeraw(&term);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);


  printf(">> grump ready (speed %d[%d])\r\n",speed,bspeed);
  FD_ZERO(&rd_map);
  fcntl(serial_fd,F_SETFL,FNDELAY);
  //usleep(200000);

  unsigned char buf[256];
  int nout;
  int i,j;


//0.send 0 to get response 80
      usleep(200000);
      printf("send 0\n");
      nout=write(serial_fd, "\000", 1);      
      usleep(200000);
      nout = read(serial_fd,buf,256);
      printf("bytes: %d\n",nout);
      printf(" %d: 0x%x\n",i,buf[0]);


//1.Send zero to get response 3
      usleep(300000);
      printf("send 0\n");
      nout=write(serial_fd, "\000", 1);
      usleep(200000);
      nout = read(serial_fd,buf,256);
      printf("bytes: %d\n",nout);
      printf(" %d: 0x%x\n",i,buf[0]);
      if (buf[0]==3) printf("Bingo!!! it's 3!!!");
 

//2.Send hex 99 for polled mode
      usleep(300000);
      printf("send 0\n");
      nout=write(serial_fd, "\231", 1);
      usleep(200000);
      nout = read(serial_fd,buf,256);
      printf("bytes: %d\n",nout);
      printf(" %d: 0x%x\n",i,buf[0]);
      if (buf[0]==3) printf("Bingo!!! it's 3!!!");
 
//Send bud rate
      usleep(300000);
      printf("send 0\n");
      nout=write(serial_fd, "\005", 1);
      usleep(200000);
      nout = read(serial_fd,buf,256);
      printf("bytes: %d\n",nout);
      printf(" %d: 0x%x\n",i,buf[0]);
      if (buf[0]==3) printf("Bingo!!! it's 3!!!");
      
//Send echo
      usleep(300000);
      printf("send 0\n");
      nout=write(serial_fd, "\000", 1);
      usleep(200000);
      nout = read(serial_fd,buf,256);
      printf("bytes: %d\n",nout);
      printf(" %d: 0x%x\n",i,buf[0]);
     


}
