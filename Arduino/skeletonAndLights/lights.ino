#define P1LP 0
#define P2LP 0
#define P3LP 0
#define P4LP 0

Adafruit_NeoPixel P1L = Adafruit_NeoPixel(8, P1LP, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel P2L = Adafruit_NeoPixel(8, P2LP, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel P3L = Adafruit_NeoPixel(8, P3LP, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel P4L = Adafruit_NeoPixel(8, P4LP, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel * lightStrips[4] = {&P1L, &P2L, &P3L, &P4L};


void lightsInit()
{
  for(int i=0; i<4; i++)
  {
  lightStrips[i]->show();
  }
}

void whiteBar(int strip, int mag)
{
  if(mag>255) mag = 255;
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
  
  
  

