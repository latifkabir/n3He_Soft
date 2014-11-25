#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#define ES_MAGIC 0xaa55f154

#define NCHAN 24

struct Sample 
{
    unsigned data[NCHAN];
};

int process(const char* rawname)
{
    FILE* fp_in = fopen(rawname, "r");
    if (fp_in == 0)
    {
	perror(rawname); exit(1);
    }

    Sample* sample = new Sample;

    for(int read_id=1; read_id<=10000; read_id++)
    {
	fread(sample->data, sizeof(unsigned), NCHAN, fp_in);

	if (sample->data[0] == ES_MAGIC)
	{

	    // std::cout<<std::setw(15) << std::hex << "sample#" << read_id << " ch#0:" << sample->data[0] << " ch#1:" << sample->data[1] << " ch#2:" << sample->data[2] << " ch#3:" << sample->data[3] << " ch#4:" << sample->data[4] << " ch#5:" << sample->data[5] << " ch#6:" << sample->data[6] << " ch#7:" << sample->data[7] << std::endl;
	    std::cout <<std::dec << "  sample#" << read_id << "  ch#0:" << sample->data[0] << "  ch#1:" << sample->data[1] << "  ch#2:" << sample->data[2] << "  ch#3:" << sample->data[3] << "  ch#4:" << sample->data[4] << "  ch#5:" << sample->data[5] << "  ch#6:" << sample->data[6] << "  ch#7:" << sample->data[7] << std::endl;
	}
    }


    return 0;
}
int main(int argc, const char* argv[])
{
    if (argc < 2) 
    {
	fprintf(stderr, "USAGE crc_validate RAWFILE\n");
	exit(1);
    }
    else
    {
	return process(argv[1]);
    }
}
