int playerLookup(byte swBit)
{
  if(swBit & P1SW) return 1;
  if(swBit & P2SW) return 2;
  if(swBit & P3SW) return 3;
  return 0;
}


void sendBuzzIn()
{
  Serial.print("S ");
  Serial.println(currAnswer); //global
}

int getResponse()//0:no right answer yet,  1:right answer
{
  DEBUG("getResponse");
  long currTime = millis();
  long nowTime;
  byte response;
  while(((currTime + timeoutAnswer) > millis()) 
    && !Serial.available() 
    && !(response = (PINSW & responseMask)^responseMask))
  {
    whiteBar(currAnswer-1, 255 - ((millis() - currTime) * 255 / toBuzz));
  }
  DEBUG("check about response");
  if(!Serial.available() && !response)
  {
    verify(sendTimeoutNoResponse);
    currTime = millis();
    int earlyExit = 0;
    while(!Serial.available() 
      && !(response = (PINSW & responseMask)^responseMask) 
      && !(earlyExit = ((currTime + timeoutNoAnswer)<millis()) || (PINSW & SWAE)^SWAE));
    {
    }; //wait a little bit for actual response
    if(earlyExit)
    {
      DEBUG("early exit");
      return 2;
    }
  }
  ; //expect 'R'
  SERIALDELAY;
  int correctness = Serial.available() ? Serial.read(), Serial.parseInt() : (response & SWYES);
  DEBUG("response");
  DEBUG(response);
  DEBUG("correctness");
  DEBUG(correctness);
  SENDACK;
  if(!correctness)
  {
    redBar(currAnswer-1, 255);
  }
  else
  {
    greenBar(currAnswer-1, 255);
  }
  return correctness;


}

void sendTimeoutNoBuzz()
{
  Serial.println("T 2"); //timeout after enable with no answer
}

void sendTimeoutNoResponse()
{
  Serial.println("T 1"); //timeout after enable with no answer
}



void switchesInit()
{
  switchesMask = 0;
  for(int i=0; i<numPlayers; i++)
  {
    switchesMask |= playerListSwitches[i];
  }
  DEBUG(switchesMask);
  DDRSW &= ~(switchesMask | responseMask | SWAE);
  PORTSW |= switchesMask | responseMask | SWAE;

  pinMode(SWENPIN, hwControl);
  digitalWrite(SWENPIN, 0);
}

void clearAnswers()
{
  currAnswer = 0;
  currMask = switchesMask;
  for(int i=0; i<3; i++)
  {
    stillAlive[i] = 1;
  }
}

void getBuzzers()
{
  clearAnswers();
  //something about lights and sounds
  for(int i=0; i<numPlayers; i++)
  {
    blueBar(i, 255);
  }
  while(currMask)
  {
    long currTime = millis();
    byte buzzedIn = 0;
    while((currTime + toBuzz > millis()) && !(buzzedIn = ((PINSW | lockoutBits) & currMask) ^ currMask))
    {
      if(lockoutBits)
      {
        for(int i=0; i<3; i++)
        {
          if((lastEarlyLockout[i] + lockout) < millis())
            lockoutBits &= ~(playerListSwitches[i]); //re-enable buzz-in capability
        }
      }
    }
    int whoBuzzed = 0;
    DEBUG("buzzedIn");
    DEBUG(buzzedIn);
    whoBuzzed = playerLookup(buzzedIn);
    if(!whoBuzzed)
    {
      for(int i=0; i<numPlayers; i++)
      {
        lightIdle(i);
      }
      verify(sendTimeoutNoBuzz);
      return;
    }
    DEBUG("Buzz in:");
    DEBUG(whoBuzzed);
    stillAlive[whoBuzzed-1] = 0;
    currAnswer = whoBuzzed;
    currMask &= ~(playerListSwitches[whoBuzzed-1]);
    DEBUG("currMask");
    DEBUG(currMask);
    for(int i=0; i<numPlayers; i++)
    {
      lightIdle(i);
    }

    verify(sendBuzzIn);
    int thisResponse = getResponse();
    if(thisResponse == 2)
    {
      //no input about response... timeout and reset for next question

      return;
    }
    if(thisResponse)
    {
      //successful response
      delay(2000);
      return;
    }
    //else, keep looking for answers
    for(int i=0; i<numPlayers; i++)
    {
      if(stillAlive[i])
        blueBar(i, 255);
    }
  }
}





