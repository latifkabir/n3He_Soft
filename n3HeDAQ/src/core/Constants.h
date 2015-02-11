//Default DAQ & Run configuration (Default run length, run number, DAQ module)
#define RUN_LENGTH 240e6 
#define SHORT_RUN_LENGTH 20e6 
#define RUN_NUMBER 0 
#define MODULE 21 


//Data file name and directory path : On Picard Only
#define OLD_FILE "/home/daq/DATA/data-%d"
#define NEW_FILE "/home/daq/DATA/run-%ddata-%d"
#define LAST_RUN "/home/daq/n3HeDAQ/bin/LastRun.txt"
#define RUN_LIST "/home/daq/n3HeDAQ/bin/RunList.txt"
#define CONFIG_SH "/home/daq/n3HeDAQ/bin/config.sh %d"
#define SH_SCRIPT "/home/daq/n3HeDAQ/bin/config.sh"

#define SLEEP_TIME 5

//DAQ Ports and IPs
#define DAQ21 21
#define DAQ22 22
#define DAQ23 23
#define DAQ24 24
#define DAQ26 26
#define DAQ30 30
#define DAQTEMP 300
#define DAQ_PORT1 "4210"
#define DAQ_PORT2 "4220"
#define DAQ21_IP "192.168.0.21" 
#define DAQ22_IP "192.168.0.22" 
#define DAQ23_IP "192.168.0.23" 
#define DAQ24_IP "192.168.0.24" 
#define DAQ26_IP "192.168.0.26" 
#define DAQ30_IP "192.168.0.30" 


//Default DAQ Config
#define n3He_EVENT 830
#define n3He_RATE 50
#define n3He_NACC 16  //Right now nacc(16,16)
#define CONT_NACC 16  //Right now nacc(16,16)
#define CONT_RATE 50 

#define DIRTY_EVENT 1660
#define DIRTY_NACC 1
#define DIRTY_RES 0

//Adjustrment for Dirty DAQ run length
#define DIRTY_FACTOR 5.416666667 

//Process Dirty DAQ data
#define NCHAN_BEFORE 8  //Number of Channels before process
#define NCHAN_AFTER 2   //Number of Channels after process


//Data file name and directory path: For Developer's Computer Only
//#define OLD_FILE "../data/data-%d"
//#define NEW_FILE "../data/run-%ddata-%d"
//#define LAST_RUN "LastRun.txt"
//#define RUN_LIST "RunList.txt"
//#define CONFIG_SH "./config.sh %d"
//#define SH_SCRIPT "./config.sh"


//#define DAQ21_IP "127.0.0.1" 



//With Event Length 830 and Averaging 16, there will be 1 header + 49 Sample/tbin, i.e. total 50 samples per T0
//(Including Header).
