#define DDRSW DDRB
#define PORTSW PORTB
#define PINSW PINB

#define P1SW (1<<0)
#define P2SW (1<<1)
#define P3SW (1<<2)
#define P4SW (1<<3)

#define SWAE (1<<4)
#define SWYES (1<<5)
#define SWNO (1<<6)

char playerListSwitches[] = {P1SW, P2SW, P3SW, P4SW};
char switchesMask = 0;
char responseMask = SWYES | SWNO;

int currAnswer = 0;
int currMask = 0;



