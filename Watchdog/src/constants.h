#define TRANS_COMMAND "/home/daq/Watchdog/bin/transferFile.sh %d %d"
#define STATUS_COMMAND "/home/daq/Watchdog/bin/upStatus.sh >> /dev/null"
#define ALERT_COMMAND "/home/daq/Watchdog/bin/textAlert.sh \"%s\" >>/dev/null"
#define PING_COMMAND "/home/daq/Watchdog/bin/pingip.sh >> /dev/null"
#define WATCHDOG_PATH "/home/daq/Watchdog/bin/"
#define DAQ_STATUS_TXT "/home/daq/Watchdog/bin/daqStatus.txt"
#define MAG_TEMP_TXT "/home/daq/Watchdog/bin/magTemp.txt"
#define LAST_TRANS_TXT "/home/daq/Watchdog/bin/lastTrans.txt"
#define TXT_ALERT_SH "/home/daq/Watchdog/bin/textAlert.sh"
#define FILE_TRANS_SH "/home/daq/Watchdog/bin/transferFile.sh"
#define UP_STATUS_SH "/home/daq/Watchdog/bin/upStatus.sh"
#define PING_IP_SH "/home/daq/Watchdog/bin/pingip.sh"













//Input from DAQ progrem: last processed run number & trigger status.
//daqStatus.txt ---if trigger is active (trigger status) and last processed run number.
//magTemp.txt -- Instant values of magnetic filed and temperatures.
//lastTransferred.txt -- Last successfully transferred run.
//Scripts list:textAlert.sh,transferFile.sh,upStatus.sh,pingip.sh
