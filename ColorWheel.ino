#include <Adafruit_NeoPixel.h>

#define NEOPIXELPIN 2
#define NUMPIXELS 16
#define SWITCHPIN 3


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

unsigned long ColorArray[16];
int PrevSwitchState;
int SwitchState;
unsigned long CurrentCycleTime;
int CurrentSwitchState;
bool PrellCheck = true;
unsigned long PrellCheckChangeTime = millis();
int DIM = 0;
unsigned long PrevPixelChangeTime = millis();
int NextPixel = 0;
int NextColor = 0;


void setup() {
  // put your setup code here, to run once:
  
  ColorArray[0] = strip.Color(0,0,0); // Black
  ColorArray[1] = strip.Color(255,255,255); // White
  ColorArray[2] = strip.Color(255,0,0); // Red
  ColorArray[3] = strip.Color(0,255,0); // Lime
  ColorArray[4] = strip.Color(0,0,255); // Blue
  ColorArray[5] = strip.Color(255,255,0); // Yellow
  ColorArray[6] = strip.Color(0,255,255); // Cyan
  ColorArray[7] = strip.Color(255,0,255); // Magenta
  ColorArray[8] = strip.Color(0,0,0); // Black
  ColorArray[9] = strip.Color(31,31,31); // White
  ColorArray[10] = strip.Color(31,0,0); // Red
  ColorArray[11] = strip.Color(0,31,0); // Lime
  ColorArray[12] = strip.Color(0,0,31); // Blue
  ColorArray[13] = strip.Color(31,31,0); // Yellow
  ColorArray[14] = strip.Color(0,31,31); // Cyan
  ColorArray[15] = strip.Color(31,0,31); // Magenta

  pinMode(SWITCHPIN, INPUT_PULLUP);
  PrevSwitchState = digitalRead(SWITCHPIN);
  SwitchState = PrevSwitchState;
  
  strip.begin();
  strip.show();
}


void loop() {
  // put your main code here, to run repeatedly:
  // record the value for the cycle variables
  CurrentCycleTime = millis(); // stores the timestamp on the beginning of every cycle
  CurrentSwitchState = digitalRead(SWITCHPIN); // status of the switch for every cycle

  if (CurrentSwitchState != SwitchState) {
    if (!PrellCheck) {
      PrevSwitchState = SwitchState;
      SwitchState = CurrentSwitchState;
      PrellCheck = true;
      PrellCheckChangeTime = CurrentCycleTime;
    }
    else if (CurrentCycleTime - PrellCheckChangeTime > 1000) {
      PrellCheck = false;
      PrellCheckChangeTime = CurrentCycleTime;
    }
  }

  if (SwitchState == LOW) {
    DIM = 8;
  }
  else {
    DIM = 0;
  }

  // changing the colors on the NeoPixel strip
  if (CurrentCycleTime - PrevPixelChangeTime > 100) {
    PrevPixelChangeTime = CurrentCycleTime;
    if (NextPixel <= NUMPIXELS) {
      strip.setPixelColor(NextPixel, ColorArray[NextColor + DIM]);
      strip.show();
      NextPixel++;
    }
    else {
      NextPixel = 0;
      if (NextColor++ > 6) {
        NextColor = 0;
      }
    }
  }
}

