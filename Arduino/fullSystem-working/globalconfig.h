
#define CONFIGLEN 7

int numPlayers = 3;
int toBuzz = 3000;
int lockout = 750;
int timeoutAnswer = 4000;
int settingFlags = 0x1F;
int hwControl = 1;
int timeoutAck = 500;

int configList[CONFIGLEN] = {numPlayers, toBuzz, lockout, timeoutAnswer, settingFlags, hwControl, timeoutAck};

