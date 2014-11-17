#include <stdio.h>
#include <vector>
#include <stdlib.h>

// #define ES_MAGIC 0xaa55f155
#define ES_MAGIC 0xaa55f154

//#define NCHAN 32
#define NCHAN 24

struct Sample {
	unsigned data[NCHAN];
};

int pulsenum;
std::vector <Sample*> pulse;

typedef std::vector<Sample*>::iterator IT;

bool is_es(Sample* es)
{
	return 
		es->data[0] == ES_MAGIC &&
		es->data[1] == ES_MAGIC &&
		es->data[2] == ES_MAGIC &&
		es->data[3] == ES_MAGIC &&
		es->data[8] == ES_MAGIC &&
		es->data[9] == ES_MAGIC &&
		es->data[10] == ES_MAGIC &&
		es->data[11] == ES_MAGIC &&
		es->data[16] == ES_MAGIC &&
		es->data[17] == ES_MAGIC &&
		es->data[18] == ES_MAGIC &&
		es->data[19] == ES_MAGIC;
}
int processPulse(const char* rawname, Sample* es)
{
	char pname[80];	
	sprintf(pname, "%s.%05d", rawname, ++pulsenum);
	FILE *fp = fopen(pname, "w");
	if (fp == 0){
		perror(pname); exit(1);
	}
	for (IT it = pulse.begin(); it != pulse.end(); ++it){
		fwrite((*it)->data, sizeof(unsigned), NCHAN, fp);
		delete [] (*it);
	}
	fclose(fp);

	char chkcmd[128];
	sprintf(chkcmd, "./cksum %s", pname);
	FILE *pp = popen(chkcmd, "r");
	if (pp == 0){
		perror(chkcmd); exit(1);
	}
	char report[80];
	fgets(report, 80, pp);
	pclose(pp);

/*	fprintf(stdout, "%12d %12d %12d %12d %s", 
		es->data[4], es->data[5], es->data[6], es->data[7], report);
*/
	unsigned comp_crc;
	sscanf(report, "crc: %x", &comp_crc);
	fprintf(stdout, "%12d %08x %08x %s %s", 
		es->data[4], es->data[5], es->data[7], 
			comp_crc==es->data[5]&& comp_crc==es->data[7]? "GOOD": "BAD", report);

	pulse.clear();
	return 0;
}
int process(const char* rawname)
{
	FILE* fp_in = fopen(rawname, "r");
	if (fp_in == 0){
		perror(rawname); exit(1);
	}
	Sample* sample = new Sample;
	enum STATE { LOOK_FIRST_ES, LOOK_SECOND_ES } state = LOOK_FIRST_ES;

	while(fread(sample->data, sizeof(unsigned), NCHAN, fp_in) == NCHAN){
		switch(state){
		case LOOK_FIRST_ES:
			if (is_es(sample)){
				state = LOOK_SECOND_ES;
				break;
			}
		case LOOK_SECOND_ES:
			if (is_es(sample)){
				processPulse(rawname, sample);
			}else{
				pulse.push_back(sample);
				sample = new Sample;
			}
		}
	}
	return 0;
}
int main(int argc, const char* argv[])
{
	if (argc < 2) {
		fprintf(stderr, "USAGE crc_validate RAWFILE\n");
		exit(1);
	}else{
		return process(argv[1]);
	}
}
