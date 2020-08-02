#include <Adafruit_NeoPixel.h>

const int ledPin = 3;
const int NumLed = 10;

Adafruit_NeoPixel strip(NumLed, ledPin);

uint32_t colorBook[] = {strip.Color(239, 235, 216), strip.Color(255, 0, 0), strip.Color(255, 35, 0), strip.Color(255, 50, 0), strip.Color(255, 75, 0), 
strip.Color(255, 150, 0), strip.Color(0, 255, 0), strip.Color(0, 255, 40), strip.Color(80, 255, 80), strip.Color(0, 255, 80), strip.Color(0, 255, 150),
strip.Color(0, 0, 255), strip.Color(40, 0, 255), strip.Color(100, 0, 255), strip.Color(170, 0, 255), strip.Color(255, 0, 255)};
int led = 0;
int color = 1;

void setup() {

  strip.begin();
  strip.show();
  Serial.begin(9600);
  
}

void loop() {

  colorwipe(250);
  strip.show();
  
}

void colorwipe(int wait) {

    color %= 16;

    strip.setPixelColor(led, colorBook[color]);
    led++;

    if (led == NumLed) {
      
      color = rand() % 16;
      led = 0;
      
      }

    delay(wait);
  
}
