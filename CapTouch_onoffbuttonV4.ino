//This example implements a simple sliding On/Off button. The example
// demonstrates drawing and touch operations.
//
//Thanks to Adafruit forums member Asteroid for the original sketch!
//
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_FT6206.h>


// The FT6206 uses hardware I2C (SCL/SDA)
Adafruit_FT6206 ts = Adafruit_FT6206();

#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

boolean RecordOn = false;

#define FRAME_X 0
#define FRAME_Y 30
#define FRAME_W 90
#define FRAME_H 50

#define REDBUTTON_X FRAME_X
#define REDBUTTON_Y FRAME_Y
#define REDBUTTON_W (FRAME_W)
#define REDBUTTON_H FRAME_H

#define GREENBUTTON_X REDBUTTON_X
#define GREENBUTTON_Y (REDBUTTON_Y + 60)
#define GREENBUTTON_W FRAME_W
#define GREENBUTTON_H FRAME_H
//#define headerString "CAN BUS Tester"

void mainScreen()
{
    int screenWidth = tft.width();
    String headerString = "CAN BUS Tester";
    int headerLength = headerString.length();
    tft.fillScreen(ILI9341_BLACK);
    // origin = left,top landscape (USB left upper)
    tft.setRotation(1); 
    tft.setCursor((screenWidth/2) - (headerLength),0);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.println("CAN BUS Tester");
    //redBtn(); 
    tft.fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_RED);
    tft.drawRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_BLACK);
    tft.setCursor(REDBUTTON_X + 110 , REDBUTTON_Y + (REDBUTTON_H/2));
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("CAN Read");
    
    tft.fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, ILI9341_GREEN);
    tft.drawRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_BLACK);
    tft.setCursor(GREENBUTTON_X + 110 , GREENBUTTON_Y + (GREENBUTTON_H/2));
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("CAN Write");
    RecordOn = false;
}

void redBtn()
{ 
    Serial.println("Red Button Pressed."); 
    int screenWidth = tft.width();
    String headerString = "CAN BUS Tester";
    int headerLength = headerString.length();
    tft.fillScreen(ILI9341_BLACK);
    // origin = left,top landscape (USB left upper)
    tft.setRotation(1); 
    tft.setCursor((screenWidth/2) - (headerLength),0);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.println("CAN Read");

    tft.fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_RED);
    tft.drawRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_BLACK);
    tft.setCursor(REDBUTTON_X + 110 , REDBUTTON_Y + (REDBUTTON_H/2));
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("Begin CAN Read");

    tft.fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, ILI9341_GREEN);
    tft.drawRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_BLACK);
    tft.setCursor(GREENBUTTON_X + 110 , GREENBUTTON_Y + (GREENBUTTON_H/2));
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("End CAN Read");
    RecordOn = true;
    
}

void greenBtn()
{
    Serial.println("Red Button Pressed."); 
    int screenWidth = tft.height();
    String headerString = "CAN BUS Tester";
    int headerLength = headerString.length();
    tft.fillScreen(ILI9341_BLACK);
    // origin = left,top landscape (USB left upper)
    tft.setRotation(1); 
    tft.setCursor((screenWidth/2) - ((headerLength/2)),0);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.println("CAN Read");

    tft.fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_RED);
    tft.drawRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_BLACK);
    tft.setCursor(REDBUTTON_X + 110 , REDBUTTON_Y + (REDBUTTON_H/2));
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("Begin CAN Write");

    tft.fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, ILI9341_GREEN);
    tft.drawRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_BLACK);
    tft.setCursor(GREENBUTTON_X + 110 , GREENBUTTON_Y + (GREENBUTTON_H/2));
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("End CAN Write");
    RecordOn = true;
}

void setup(void)
{
  Serial.begin(9600);
  tft.begin();
  if (!ts.begin(40)) { 
    Serial.println("Unable to start touchscreen.");
  } 
  else { 
    Serial.println("Touchscreen started."); 
    mainScreen();
  }

}

void loop()
{
  // See if there's any  touch data for us
  if (ts.touched())
  {   
    // Retrieve a point  
    TS_Point p = ts.getPoint(); 
    // rotate coordinate system
    // flip it around to match the screen.
    p.x = map(p.x, 0, 240, 240, 0);
    p.y = map(p.y, 0, 320, 320, 0);
    int y = tft.height() - p.x;
    int x = p.y;

  if (RecordOn)
  {
      if((x > REDBUTTON_X) && (x < (REDBUTTON_X + REDBUTTON_W))) {
        if ((y > REDBUTTON_Y) && (y <= (REDBUTTON_Y + REDBUTTON_H))) {
          Serial.println("Red btn hit"); 
          mainScreen();
        }
      }
      if((x > GREENBUTTON_X) && (x < (GREENBUTTON_X + GREENBUTTON_W))) {
        if ((y > GREENBUTTON_Y) && (y <= (GREENBUTTON_Y + GREENBUTTON_H))) {
          Serial.println("Green btn hit"); 
           mainScreen();
        }
      }

  }
  else {
      if((x > REDBUTTON_X) && (x < (REDBUTTON_X + REDBUTTON_W))) {
        if ((y > REDBUTTON_Y) && (y <= (REDBUTTON_Y + REDBUTTON_H))) {
          Serial.println("Red btn hit"); 
          redBtn();
        }
      }
      if((x > GREENBUTTON_X) && (x < (GREENBUTTON_X + GREENBUTTON_W))) {
        if ((y > GREENBUTTON_Y) && (y <= (GREENBUTTON_Y + GREENBUTTON_H))) {
          Serial.println("Green btn hit"); 
          greenBtn();
           }

         }
   // Serial.println(RecordOn);
      }  
  }
}
