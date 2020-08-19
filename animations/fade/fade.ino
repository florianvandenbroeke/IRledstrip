#include <Adafruit_NeoPixel.h>

const int ledPin = 3;
const int NumLed = 10;
long int hue = 0;

Adafruit_NeoPixel strip(NumLed, ledPin);

void setup() {

  strip.begin();
  strip.show();
  Serial.begin(9600);
  
}

void loop() {

  fade(100);
  strip.show();
  
}

void fade(int wait) {

  hue % 65536;

  strip.fill(strip.ColorHSV(hue));
  hue += 256;
  delay(wait);
  
}
