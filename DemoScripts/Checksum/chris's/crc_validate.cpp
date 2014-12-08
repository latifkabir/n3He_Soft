// g++ crc_validate.cpp -o crc_validate && crc_validate kabir_data/data32

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include "crc32.c"
#include <iostream>
using namespace std;


// #define ES_MAGIC 0xaa55f155
#define ES_MAGIC 0xaa55f154
int NBANK1; // number of banks in first module
int NBANK2; // number of banks in second module
int NCHAN; // total number of channels

unsigned data[6*32]; // maximum banks=6
unsigned CRC1=0, CRC2=0;
int pulsenum;

bool is_es()
{
	for (int i=0;i<NBANK1+NBANK2;++i) {
		for (int j=0;j<4;++j) {
			if (data[8*i+j] != ES_MAGIC) return false;
		}
	}
	return true;
}

void append_CRC()
{
	CRC1 = crc32(CRC1, data, 32*NBANK1);
	if (NBANK2) {
	  CRC2 = crc32(CRC2, data+8*NBANK1, 32*NBANK2);
	}
}

void report_CRC()
{
	printf("%12d %08x %08x CRC1: %08x [%s]   ", 
	       data[4], data[5], data[7], CRC1,
	       CRC1==data[5]&& CRC1==data[7]? "GOOD": "BAD");
	if (NBANK2) {
	  printf("%08x %08x CRC2: %08x [%s]\n",
		 data[8*NBANK1+5], data[8*NBANK1+7], CRC2,
		 CRC2==data[8*NBANK1+5]&& CRC2==data[8*NBANK1+7]? "GOOD": "BAD");
	}
	else printf("\n");
}

int process(const char* rawname)
{
	FILE* fp_in = fopen(rawname, "r");
	if (fp_in == 0){
		perror(rawname); exit(1);
	}
	enum STATE { LOOK_FIRST_ES, LOOK_SECOND_ES } state = LOOK_FIRST_ES;

	while(fread(data, sizeof(unsigned), 8*(NBANK1+NBANK2), fp_in)
	      == 8*(NBANK1+NBANK2) ) {
		switch(state){
		case LOOK_FIRST_ES:
			if (is_es()){
				state = LOOK_SECOND_ES;
			}
			break;
		case LOOK_SECOND_ES:
			if (is_es()){
				report_CRC();
				CRC1=CRC2=0;
			}else{
				append_CRC();
			}
		}
	}
	return 0;
}
int main(int argc, const char* argv[])
{
	if (argc < 4) {
		fprintf(stderr, "USAGE: crc_validate NBANK1 NBANK2 RAWFILE\n");
		exit(1);
	}else{
		NBANK1=atoi(argv[1]);
		NBANK2=atoi(argv[2]);
		return process(argv[3]);
	}
}
