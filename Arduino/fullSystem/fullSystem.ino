/*
  Hacker Jeopardy System
  Sean Murphy
  2014-02-22
  seantaylormurphy@gmail.com
*/



#define DEBUG_ON 0
//#define byte unsigned char


#include <util/delay.h>
#include <Adafruit_NeoPixel.h>
#include "hardware.h"
#include "globalconfig.h"
#include "switches.h"
#include "sound.h"

#define DEBUG(x) if(DEBUG_ON) Serial.println(x)
#define SENDACK Serial.println('A')
#define RETRIES 1
#define SERIALDELAY _delay_us(1000.0)

void verify(void (*func)(void) );

void setup()
{
    MCUCR|= (1<<JTD);
  MCUCR|= (1<<JTD);
  //yes, disable JTAG twice
  hwInit();
  Serial.begin(115200);
}


void loop()
{
  if(lockout)
  {
    long currTime = millis();
    for(int i=0; i<3; i++)
    {
      if(!(playerListSwitches[i] & PINSW))
      {
        lockoutBits |= playerListSwitches[i]; //disable buzz-in
        lastEarlyLockout[i] = currTime;
      }
    }
  }
        
  parseSerial();
}






  
  

    

