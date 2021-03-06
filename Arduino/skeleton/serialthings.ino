void clearSerial()
{
  while(Serial.available()>0)
  {
    Serial.read();
    //_delay_us(1000);
  }
}

void parseSerial()
{
  if(Serial.available())
  {
    char command = Serial.read();
    DEBUG("#SW");
    DEBUG(command);
    SERIALDELAY;
    char rw;
    switch(command)
    {
      case '\n': //junk
        break;
      case 'S': //I done goofed on the protocol. Interpret S and C as same
      case 'C':
        rw = Serial.read();
        SERIALDELAY;
        DEBUG("#rw");
        DEBUG(rw);
        if(rw == '1')
        {
          getConfig(); 
          hwInit(); //reinitialize because numPlayers et al. could change
        }
        else if(rw == '0')
        {
          verify(printConfig);//send the func pointer 
        }
        break;
      case 'E':
        //answer enable
        DEBUG("Ans En");
        getBuzzers();
        break;
     
    }
  }
}



void verify(void (*func)(void) )
{
  int count = 0;
  while(count < RETRIES)
  {
    long currTime = millis();
    func();
    int success = 0;
    while(currTime + timeoutAck > millis() && !success)
    {
      if(Serial.available())
      {
        if(Serial.find("A"))
        {
          success = 1;
          break;
        }
      }
    }
    if(success)
    {
      break;
    }
    count++;
  }
}
