void printConfig()
{
  Serial.print("C0");
  for(int i=0; i<CONFIGLEN; i++)
  {
    Serial.print(" ");
    Serial.print(configList[i]);
  }
  Serial.println();
}


void getConfig() //assumes C1 has already been read
{
  int configListBuf[CONFIGLEN];
  //todo: error checking
  for(int i=0; i<CONFIGLEN; i++)
  {
    configListBuf[i] = Serial.parseInt();
  }
  //todo: validate with error checking
  for(int i=0; i<CONFIGLEN; i++)
  {
    configList[i] = configListBuf[i];
  }
  clearSerial();
  SENDACK;
}
