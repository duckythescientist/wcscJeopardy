
void sendBuzzIn()
{
  Serial.print("S ");
  Serial.println(currAnswer); //global
}

int getResponse()//0:no right answer yet,  1:right answer
{
  long currTime = millis();
  while(currTime + toBuzz > millis() && !Serial.available());
  if(!Serial.available())
  {
    verify(sendTimeoutNoResponse);
    return 0;
  }
  SERIALDELAY;
  int correctness = Serial.parseInt();
  SENDACK;
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
  //DDRSW &= ~switchesMask;
  //PORTSW |= switchesMask;
}

void clearAnswers()
{
  currAnswer = 0;
  currMask = switchesMask;
}

void getBuzzers()
{
  clearAnswers();
  //something about lights and sounds
  while(currMask)
  {
  int buzzedIn = 0;
  long currTime = millis();
  while(currTime + timeoutAnswer > millis() && (buzzedIn = (PINSW & currMask) ^ currMask))
  {}
  int whoBuzzed = 0;
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
    case P4SW:
      whoBuzzed = 4;
      break;
  }
  if(!whoBuzzed)
  {
    verify(sendTimeoutNoBuzz);
    return;
  }
  DEBUG("Buzz in:");
  DEBUG(whoBuzzed);
  currAnswer = whoBuzzed;
  currMask &= ~(playerListSwitches[whoBuzzed]);
  verify(sendBuzzIn);
  if(getResponse())
  {
    return;
  }
  //else, keep looking for answers
  }
}


