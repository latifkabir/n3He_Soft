#include <stdio.h>
#include <vector>
#include <stdlib.h>

#define ES_MAGIC 0xaa55f154

#define NCHAN 24

struct Sample {
    unsigned data[NCHAN];
};

int pulsenum;
std::vector <Sample*> pulse1,pulse2;

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
int processPulse(const char* rawname, Sample* es1, Sample* es2)
{
	char pname1[80];	
	char pname2[80];	
	sprintf(pname1, "%s.%05dM1", rawname, ++pulsenum);
	sprintf(pname2, "%s.%05dM2", rawname, ++pulsenum);
	FILE *fp1 = fopen(pname1, "w");
	FILE *fp2 = fopen(pname2, "w");
	if (fp1 == 0 || fp2==0){
		printf("Unable to Create File"); exit(1);
	}
	for (IT it = pulse1.begin(); it != pulse1.end(); ++it){
		fwrite((*it)->data, sizeof(unsigned), NCHAN, fp1);
		delete [] (*it);
	}
	for (IT it = pulse2.begin(); it != pulse2.end(); ++it){
		fwrite((*it)->data, sizeof(unsigned), NCHAN, fp2);
		delete [] (*it);
	}

	fclose(fp1);
	fclose(fp2);

	char chkcmd1[128];
	char chkcmd2[128];
	sprintf(chkcmd1, "./cksum %s", pname1);
	sprintf(chkcmd2, "./cksum %s", pname2);
	FILE *pp1 = popen(chkcmd1, "r");
	FILE *pp2 = popen(chkcmd2, "r");
	if (pp1 == 0 || pp2==0){
		printf("Unable to Open File"); exit(1);
	}
	char report1[80];
	char report2[80];
	fgets(report1, 80, pp1);
	fgets(report2, 80, pp2);
	pclose(pp1);
	pclose(pp2);

/*	fprintf(stdout, "%12d %12d %12d %12d %s", 
		es->data[4], es->data[5], es->data[6], es->data[7], report);
*/
	unsigned comp_crc1;
	unsigned comp_crc2;
	sscanf(report1, "crc: %x", &comp_crc1);
	sscanf(report2, "crc: %x", &comp_crc2);
	fprintf(stdout, "%12d %08x %08x %s %s", 
		es1->data[4], es1->data[5], es1->data[7], 
			comp_crc1==es1->data[5]&& comp_crc1==es1->data[7]? "GOOD": "BAD", report1);
	fprintf(stdout, "%12d %08x %08x %s %s", 
		es2->data[4], es2->data[5], es2->data[7], 
			comp_crc2==es2->data[5]&& comp_crc2==es2->data[7]? "GOOD": "BAD", report2);

	pulse1.clear();
	pulse2.clear();
	return 0;
}
int process(const char* rawname)
{
	FILE* fp_in = fopen(rawname, "r");
	if (fp_in == 0){
		perror(rawname); exit(1);
	}
	Sample* sample1 = new Sample;
	Sample* sample2 = new Sample;
	enum STATE { LOOK_FIRST_ES, LOOK_SECOND_ES } state = LOOK_FIRST_ES;

	while(fread(sample1->data, sizeof(unsigned), NCHAN, fp_in) == NCHAN && fread(sample2->data, sizeof(unsigned), NCHAN, fp_in) == NCHAN){
		switch(state){
		case LOOK_FIRST_ES:
			if (is_es(sample1)){
				state = LOOK_SECOND_ES;
				break;
			}
		case LOOK_SECOND_ES:
		    if (is_es(sample1) && is_es(sample2)){
			    processPulse(rawname, sample1,sample2);
			}else{
				pulse1.push_back(sample1);
				pulse2.push_back(sample2);
				sample1 = new Sample;
				sample2 = new Sample;
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
