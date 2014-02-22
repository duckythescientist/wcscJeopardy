
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
  while(((currTime + toBuzz) > millis()) && !Serial.available() && !(response = (PINSW & responseMask)^responseMask))
  {
    whiteBar(currAnswer-1, 255 - ((millis() - currTime) * 255 / toBuzz));
  }
  DEBUG("check about response");
  if(!Serial.available() && !response)
  {
    verify(sendTimeoutNoResponse);
    while(!Serial.available() && !(response = (PINSW & responseMask)^responseMask))
    {}; //wait for actual response
  }
  Serial.read(); //expect 'R'
  SERIALDELAY;
  int correctness = Serial.available() ? Serial.parseInt() : (response & SWYES);
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
  int buzzedIn = 0;
  long currTime = millis();
  while((currTime + timeoutAnswer > millis()) && !(buzzedIn = (PINSW & currMask) ^ currMask))
  {}
  int whoBuzzed = 0;
  DEBUG("buzzedIn");
  DEBUG(buzzedIn);
  switch(buzzedIn)
  {
    case P1SW:
      whoBuzzed = 1;
      break;
    case P2SW:
      whoBuzzed = 2;
      break;
    case P3SW:
      whoBuzzed = 3;
      break;
  }
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
  if(getResponse())
  {
    //successful answer
    //
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


