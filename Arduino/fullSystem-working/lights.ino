#define P1LP 2
#define P2LP 1
#define P3LP 0
//#define P4LP 3

Adafruit_NeoPixel P1L = Adafruit_NeoPixel(8, P1LP, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel P2L = Adafruit_NeoPixel(8, P2LP, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel P3L = Adafruit_NeoPixel(8, P3LP, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel P4L = Adafruit_NeoPixel(8, P4LP, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel * lightStrips[3] = {&P1L, &P2L, &P3L};


void lightsInit()
{
  for(int i=0; i<3; i++)
  {
    lightStrips[i]->begin();
    lightStrips[i]->show();
  }
}

void lightIdle(int strip)
{
    for(int j=0; j<8; j++)
    {
      lightStrips[strip]->setPixelColor(j, 0);
    }
    lightStrips[strip]->show();
}

void whiteBar(int strip, int mag)
{
  if(mag>255) mag = 255;
  if(mag<0) mag = 0;
  int pivot = mag / 32;
  for(int i=0; i<pivot; i++)
  {
    lightStrips[strip]->setPixelColor(i, 255, 255, 255);
  }
  mag &= 31;
  mag *= 8;
  mag += 7;
  lightStrips[strip]->setPixelColor(pivot, mag, mag, mag);
  lightStrips[strip]->show();
}

void blueBar(int strip, int mag)
{
  if(mag>255) mag = 255;
    if(mag<0) mag = 0;
  int pivot = mag / 32;
  for(int i=0; i<pivot; i++)
  {
    lightStrips[strip]->setPixelColor(i, 0, 0, 255);
  }
  mag &= 31;
  mag *= 8;
  mag += 7;
  lightStrips[strip]->setPixelColor(pivot, 0, 0, mag);
  lightStrips[strip]->show();
}

void redBar(int strip, int mag)
{
  if(mag>255) mag = 255;
    if(mag<0) mag = 0;
  int pivot = mag / 32;
  for(int i=0; i<pivot; i++)
  {
    lightStrips[strip]->setPixelColor(i, 255, 0, 0);
  }
  mag &= 31;
  mag *= 8;
  mag += 7;
  lightStrips[strip]->setPixelColor(pivot, mag, 0, 0);
  lightStrips[strip]->show();
}

void greenBar(int strip, int mag)
{
  if(mag>255) mag = 255;
    if(mag<0) mag = 0;
  int pivot = mag / 32;
  for(int i=0; i<pivot; i++)
  {
    lightStrips[strip]->setPixelColor(i, 0, 255, 0);
  }
  mag &= 31;
  mag *= 8;
  //mag += 7;
  lightStrips[strip]->setPixelColor(pivot, 0, mag, 0);
  lightStrips[strip]->show();
}
  
  
  

