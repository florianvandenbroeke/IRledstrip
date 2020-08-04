#include <Adafruit_NeoPixel.h>;
#include <IRremote.h>

// Variable declaration
const int LedPin = 3;
const int NumLed = 10;
const int IrPin = 11;

long int val;
long int vorige;
long int firstPixel;
long int hue = 0;
int brightness = 255;
int color = 1;
int led = 0;

// Initialisation of IR receiver and ledstrip
Adafruit_NeoPixel strip(NumLed, LedPin);

IRrecv irrecv(IrPin);
decode_results results;

// Definition of preset colors
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

// array for easy acces to predefined colors
uint32_t colorBook[] = {strip.Color(239, 235, 216), strip.Color(255, 0, 0), strip.Color(255, 35, 0), strip.Color(255, 50, 0), strip.Color(255, 75, 0), 
strip.Color(255, 150, 0), strip.Color(0, 255, 0), strip.Color(0, 255, 40), strip.Color(80, 255, 80), strip.Color(0, 255, 80), strip.Color(0, 255, 150),
strip.Color(0, 0, 255), strip.Color(40, 0, 255), strip.Color(100, 0, 255), strip.Color(170, 0, 255), strip.Color(255, 0, 255)};

void setup() {

  strip.begin();
  strip.fill(white); // turning on sets led strip to white
  strip.show();

  irrecv.enableIRIn();

  Serial.begin(9600);

}

void loop() {

  if (irrecv.decode(&results)) {

    // store IR value, ignore repitions of the previous key (- value)
    vorige = val;
    val = results.value;
    if (val == -1)
    val = vorige;
    
    irrecv.resume();

    // brightness controls
    if (val == 16187647 && brightness < 255) {
      brightness += 20;
    }

    if (val == 16220287 && brightness > 20) {
      brightness -= 20;
    }

    // on/off controls
    if (val == 16203967) {
      brightness = 0;
    }

    if (val == 16236607) {
      strip.fill(white);
      brightness = 255;
    }

    // static color controls
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

  // animation controls
  switch (val) {

    case 16240687:
    randomLed(0);
    break;

    case 16246807:
    rainbow(20);
    break;

    case 16248847:
    colorwipe(100);
    break;

    case 16238647:
    fade(100);
    break;
    
  }

  strip.setBrightness(brightness); // set brightness for each cycle
  strip.show(); // apply color changes for each cycle

  delay(100);
  Serial.println(val); // serial commmunication for debugging

}

/* each animation function advances one "frame" in the animation when called
 *  this enables to interrupt the animation anywhere in the cycle */

// random animation: sets a random pixel to a random color of the color book
void randomLed(int wait) {

  int led = rand() % NumLed;
  int color = rand() % 16;

  strip.setPixelColor(led, colorBook[color]);

  delay(wait);
  
}

// rainbow animation: shifts rainbow over the ledstrip
void rainbow(int wait) {
  
  firstPixel %= 65536;

  for(int i = 0; i < NumLed; i ++) {
    int hue = firstPixel + (i * 65536L / NumLed);
    strip.setPixelColor(i, strip.ColorHSV(hue));
    }

  firstPixel += 256;

  delay(wait);
  
}

// colorwipe animation: fills ledstrip pixel per pixel with a random color
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

// fade animation: fades complete ledstrip through all colors
void fade(int wait) {

  hue % 65536;

  strip.fill(strip.ColorHSV(hue));
  hue += 256;
  delay(wait);
  
}
