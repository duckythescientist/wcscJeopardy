

#define DEBUG_ON 0
#define DEBUG(x) if(DEBUG_ON) Serial.println(x)


#include <util/delay.h>
#include <Adafruit_NeoPixel.h>
#include "hardware.h"
#include "globalconfig.h"
#include "switches.h"

#define SENDACK Serial.println('A')
#define RETRIES 3
#define SERIALDELAY _delay_us(1000.0)

void verify(void (*func)(void) );

void setup()
{
  hwInit();
  Serial.begin(115200);
}


void loop()
{
  parseSerial();
}






  
  

    

