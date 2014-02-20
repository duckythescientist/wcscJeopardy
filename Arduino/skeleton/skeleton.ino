#define DEBUG_ON 1
#define DEBUG(x) if(DEBUG_ON) Serial.println(x)


#include <util/delay.h>

#include "hardware.h"
#include "globalconfig.h"
#include "switches.h"

#define SENDACK Serial.println('A')
#define RETRIES 3

void verify(void (*func)(void) );

void setup()
{
  Serial.begin(115200);
}






void loop()
{
  
}






  
  

    

