#define DDRSW DDRF
#define PORTSW PORTF
#define PINSW PINF

#define P1SW (1<<4)
#define P2SW (1<<1)
#define P3SW (1<<0)
//#define P4SW (1<<3)

#define SWAE (1<<5)
#define SWYES (1<<7)
#define SWNO (1<<6)

#define SWENPIN 13

byte playerListSwitches[] = {P1SW, P2SW, P3SW};

long lastEarlyLockout[] = {0,0,0};
byte lockoutBits = 0;

byte switchesMask = 0;
byte responseMask = SWYES | SWNO;

int currAnswer = 0;
int stillAlive[3];
byte currMask = 0;



