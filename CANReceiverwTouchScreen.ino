// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_FT6206.h>

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

#define STMPE_CS 8
Adafruit_FT6206 ts = Adafruit_FT6206();
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

boolean RecordOn = false;

#define FRAME_X 0  
#define FRAME_Y 10
#define FRAME_W 100
#define FRAME_H 50

#define CANRead_X 20
#define CANRead_Y 60
#define CANRead_W 100
#define CANRead_H 50 

#define CANWrite_X CANRead_X
#define CANWrite_Y (CANRead_Y + 60)
#define CANWrite_W FRAME_W
#define CANWrite_H FRAME_H

void CANReadBtn()
{ 
  tft.fillRect(CANRead_X, CANRead_Y, CANRead_W, CANRead_H, ILI9341_RED);
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(50, 0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.println("Reading CAN Bus");
  tft.drawRect(CANRead_X, CANRead_Y, CANRead_W, CANRead_H, ILI9341_BLUE);
  tft.setCursor(CANRead_X + 110 , CANRead_Y + (CANRead_H/2));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("Back");
}

void CANWriteBtn()
{
  tft.fillRect(CANWrite_X, CANWrite_Y, CANWrite_W, CANWrite_H, ILI9341_GREEN);

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
  }
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1);   
  tft.setCursor(50, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  tft.println("CAN Bus Test");
  
  tft.drawRect(CANRead_X, CANRead_Y, CANRead_W, CANRead_H, ILI9341_BLUE);
  tft.setCursor(CANRead_X + 110 , CANRead_Y + (CANRead_H/2));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("CAN Read");
  tft.drawRect(CANWrite_X, CANWrite_Y, CANWrite_W, CANWrite_H, ILI9341_BLUE);
  tft.setCursor(CANWrite_X + 110 , CANWrite_Y + (CANWrite_H/2));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("CAN Write");
}

void loop() {

   // See if there's any  touch data for us
  if (ts.touched())
  {   
    // Retrieve a point  
    TS_Point p = ts.getPoint(); 
    Serial.println(p); 
    // Scale using the calibration #'s
    // and rotate coordinate system
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
    int y = tft.height() - p.x;
    int x = p.y;

    if((x > CANRead_X) && (x < (CANRead_X + CANRead_W))) {
      if ((y > CANRead_Y) && (y <= (CANRead_Y + CANRead_H))) {
      Serial.println("Red btn hit"); 
      CANReadBtn();
      }
    }
    
    if((x > CANWrite_X) && (x < (CANWrite_X + CANWrite_W))) {
       if ((y > CANWrite_Y) && (y <= (CANWrite_Y + CANWrite_H))){
       Serial.println("Red btn hit"); 
        CANWriteBtn();
       }
    }
  }
}
