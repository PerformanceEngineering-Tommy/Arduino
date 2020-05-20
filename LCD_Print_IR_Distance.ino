/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 22
 * LCD Enable pin to digital pin 23
 * LCD D4 pin to digital pin 27
 * LCD D5 pin to digital pin 26
 * LCD D6 pin to digital pin 25
 * LCD D7 pin to digital pin 24
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

int sensorPin = A1; // select the input pin for the IR Distance Sensor
int sensorValue = 0;
int sensorVoltage = 0;  // variable to store the value coming from the sensor
int distance = 0;
int sensorResolution = 0;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 22, en = 23, d4 = 27, d5 = 26, d6 = 25, d7 = 24;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("IR Distance Test");
      delay(1000);
      analogReadResolution(sensorResolution);
}

void loop() {

    // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  sensorVoltage = (sensorValue/(sensorResolution/3.3));
  distance = (sensorVoltage*0.00355556) + 100;
  // stop the program for for <sensorValue> milliseconds:
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  // print the number of seconds since reset:
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print("cm");
      lcd.setCursor(0, 1);
          lcd.print("Voltage");
    lcd.print(sensorVoltage);
    lcd.print(" V");
          delay(250);
          
          
}
