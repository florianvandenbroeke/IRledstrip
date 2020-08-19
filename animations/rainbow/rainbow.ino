#include <Adafruit_NeoPixel.h>

const int ledPin = 3;
const int NumLed = 10;
long firstPixel = 0;

Adafruit_NeoPixel strip(NumLed, ledPin);

void setup() {

  strip.begin();
  strip.show();
  Serial.begin(9600);
  
}

void loop() {

  rainbow(100);
  strip.show();
  
}

void rainbow(int wait) {
  
  firstPixel %= 65536;

  for(int i = 0; i < NumLed; i ++) {
    int hue = firstPixel + (i * 65536L / NumLed);
    strip.setPixelColor(i, strip.ColorHSV(hue));
    }

  firstPixel += 256;

  delay(wait);
  
}
