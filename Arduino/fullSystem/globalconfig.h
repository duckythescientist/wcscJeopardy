
#define CONFIGLEN 7

int numPlayers = 3;
int toBuzz = 4000;
int lockout = 1000;
int timeoutAnswer = 4000;
int settingFlags = 0x1F;
int hwControl = 1;
int timeoutAck = 50;

int configList[CONFIGLEN] = {numPlayers, toBuzz, lockout, timeoutAnswer, settingFlags, hwControl, timeoutAck};


int timeoutNoAnswer = 8000;
