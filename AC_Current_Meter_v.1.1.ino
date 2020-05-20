#include <SPI.h>
#include <LiquidCrystal.h>
#include <Adafruit_RGBLCDShield.h>

int sensor1 = A0;    // select the input pin for the potentiometer
int sensor2 = A1;    // select the input pin for the potentiometer
int sensor3 = A2;    // select the input pin for the potentiometer

int sensor1Value = 0;  // variable to store the value coming from the sensor
int sensor2Value = 0;  // variable to store the value coming from the sensor
int sensor3Value = 0;  // variable to store the value coming from the sensor

void setup() {
  // put your setup code here, to run once:
// These #defines make it easy to set the backlight color
#define OFF 0x0
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7 

uint8_t buttons = lcd.readButtons();
}

void loop() {
  // put your main code here, to run repeatedly:



  if (buttons) {
    if (buttons & BUTTON_UP) {
      lcd.setBacklight(RED);
    }
    if (buttons & BUTTON_DOWN) {
      lcd.setBacklight(YELLOW);
    }
    if (buttons & BUTTON_LEFT) {
      lcd.setBacklight(GREEN);
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.setBacklight(TEAL);
    }
    if (buttons & BUTTON_SELECT) {
      lcd.setBacklight(VIOLET);
    }
  }
}
