void switchesInit()
{
  switchesMask = 0;
  for(int i=0; i<numPlayers; i++)
  {
    switchesMask |= playerListSwitches[i];
  }
  DEBUG(switchesMask);
  DDRSW &= ~switchesMask;
  PORTSW |= switchesMask;
}


