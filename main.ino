#include <Adafruit_NeoPixel.h>;
#include <IRremote.h>

const int LedPin = 3;
const int NumLed = 10;
const int IrPin = 11;

long int val;
int brightness = 255;


Adafruit_NeoPixel strip(NumLed, LedPin);

IRrecv irrecv(IrPin);
decode_results results;

uint32_t white = strip.Color(239, 235, 216);

uint32_t red0 = strip.Color(255, 0, 0);
uint32_t red1 = strip.Color(255, 35, 0);
uint32_t red2 = strip.Color(255, 50, 0);
uint32_t red3 = strip.Color(255, 75, 0);
uint32_t red4 = strip.Color(255, 150, 0);


uint32_t green0 = strip.Color(0, 255, 0);
uint32_t green1 = strip.Color(0, 255, 40);
uint32_t green2 = strip.Color(80, 255, 80);
uint32_t green3 = strip.Color(0, 255, 80);
uint32_t green4 = strip.Color(0, 255, 150);

uint32_t blue0 = strip.Color(0, 0, 255);
uint32_t blue1 = strip.Color(40, 0, 255);
uint32_t blue2 = strip.Color(100, 0, 255);
uint32_t blue3 = strip.Color(170, 0, 255);
uint32_t blue4 = strip.Color(255, 0, 255);

void setup() {

  strip.begin();
  strip.fill(white);
  strip.show();

  irrecv.enableIRIn();

  Serial.begin(9600);

}

void loop() {

  if (irrecv.decode(&results)) {
    
    val = results.value;
    irrecv.resume();

    if (val == 16187647 && brightness < 255) {
      brightness += 20;
    }

    if (val == 16220287 && brightness > 20) {
      brightness -= 20;
    }

    switch(val) {

      case 16195807:
      strip.fill(red0);
      break;

      case 16191727:
      strip.fill(red1);
      break;

      case 16199887:
      strip.fill(red2);
      break;

      case 16189687:
      strip.fill(red3);
      break;

      case 16197847:
      strip.fill(red4);
      break;

      case 16228447:
      strip.fill(green0);
      break;

      case 16224367:
      strip.fill(green1);
      break;

      case 16232527:
      strip.fill(green2);
      break;
      
      case 16222327:
      strip.fill(green3);
      break;

      case 16230487:
      strip.fill(green4);
      break;

      case 16212127:
      strip.fill(blue0);
      break;

      case 16208047:
      strip.fill(blue1);
      break;

      case 16216207:
      strip.fill(blue2);
      break;

      case 16206007:
      strip.fill(blue3);
      break;

      case 16214167:
      strip.fill(blue4);
      break;

      case 16244767:
      strip.fill(white);
      break;

    }

  }

  strip.setBrightness(brightness);
  strip.show();

  delay(100);
  Serial.println(val);

}
