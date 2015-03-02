#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <stdbool.h>



class Serial
{
//private:
protected:
    int serial_fd, file_fd;
    const char *serial_portname;
    fd_set rd_map;
    int speed;
    int bspeed;
    struct termios term, saved_term;
    unsigned char buf[256];
    int nout;
    int i,j;

public:
    Serial(const char *portName,int sspeed);
    ~Serial();
    int CheckStatus();
    int Write(const char *txt);
    int Read();
    void Read(char *tmp);

};


