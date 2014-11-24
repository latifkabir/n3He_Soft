
//Default DAQ & Run configuration (Default run length, run number, DAQ module)
#define RUN_LENGTH 100e6 
#define SHORT_RUN_LENGTH 20e6 
#define RUN_NUMBER 0 
#define MODULE 21 


//Data file name and directory path : On Picard Only
#define OLD_FILE "/home/daq/DATA/data_file-%d"
#define NEW_FILE "/home/daq/DATA/run%ddata_file-%d"
#define LAST_RUN "/home/daq/n3He_DAQ/bin/LastRun.txt"
#define RUN_LIST "/home/daq/n3He_DAQ/bin/RunList.txt"
#define CONFIG_SH "/home/daq/n3He_DAQ/bin/config.sh %d"
#define SH_SCRIPT "/home/daq/n3He_DAQ/bin/config.sh"

#define SLEEP_TIME 5

//DAQ Ports and IPs
#define DAQ21 21
#define DAQ22 22
#define DAQ23 23
#define DAQ24 24
#define DAQ26 26
#define DAQ30 30
#define DAQ_PORT1 "4210"
#define DAQ_PORT2 "4220"
#define DAQ21_IP "192.168.0.21" 
#define DAQ22_IP "192.168.0.22" 
#define DAQ23_IP "192.168.0.23" 
#define DAQ24_IP "192.168.0.24" 
#define DAQ26_IP "192.168.0.26" 
#define DAQ30_IP "192.168.0.30" 


//Default DAQ Config
#define n3He_EVENT 650
#define n3He_RATE 50
#define n3He_NACC 16  //Right now nacc(16,16)
#define CONT_NACC 16  //Right now nacc(16,16)
#define CONT_RATE 50 




//Data file name and directory path: For Developer's Computer Only
//#define OLD_FILE "../data/data_file-%d"
//#define NEW_FILE "../data/run%ddata_file-%d"
//#define LAST_RUN "LastRun.txt"
//#define RUN_LIST "RunList.txt"
//#define CONFIG_SH "./config.sh %d"
//#define SH_SCRIPT "./config.sh"


//#define DAQ21_IP "127.0.0.1" 

