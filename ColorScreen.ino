/**************************************************************************
  This is a library for several Adafruit displays based on ST77* drivers.
  Works with the Adafruit 1.8" TFT Breakout w/SD card
    ----> http://www.adafruit.com/products/358
  The 1.8" TFT shield
    ----> https://www.adafruit.com/product/802
  The 1.44" TFT breakout
    ----> https://www.adafruit.com/product/2088
  as well as Adafruit raw 1.8" TFT display
    ----> http://www.adafruit.com/products/618
  Check out the links above for our tutorials and wiring diagrams.
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional).
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **************************************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include "CustomGraphics.h"

#define ST7735_BLACK   0x0000
#define ST7735_GRAY    0x8410
#define ST7735_WHITE   0xFFFF
#define ST7735_RED     0xF800
#define ST7735_ORANGE  0xFA60
#define ST7735_YELLOW  0xFFE0 
#define ST7735_LIME    0x07FF
#define ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_AQUA    0x04FF
#define ST7735_BLUE    0x001F
#define ST7735_MAGENTA 0xF81F
#define ST7735_PINK    0xF8FF

#ifdef ADAFRUIT_HALLOWING
  #define TFT_CS        39 // Hallowing display control pins: chip select
  #define TFT_RST       37 // Display reset
  #define TFT_DC        38 // Display data/command select
  #define TFT_BACKLIGHT  7 // Display backlight pin
#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8
#endif

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.

// For 1.44" and 1.8" TFT with ST7735 (including HalloWing) use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// For 1.54" TFT with ST7789:
//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// OPTION 2 lets you interface the display using ANY TWO or THREE PINS,
// tradeoff being that performance is not as fast as hardware SPI above.
//#define TFT_MOSI 11  // Data out
//#define TFT_SCLK 13  // Clock out
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

float p = 3.1415926;
int images[7];



void setup(void) 
{
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));

#ifdef ADAFRUIT_HALLOWING
  // HalloWing is a special case. It uses a ST7735R display just like the
  // breakout board, but the orientation and backlight control are different.
  tft.initR(INITR_HALLOWING);        // Initialize HalloWing-oriented screen
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH); // Backlight on

  Serial.println(F("Hallowing"));
  
#else
  // Use this initializer if using a 1.8" TFT screen:
  //tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab

  // OR use this initializer (uncomment) if using a 1.44" TFT:
  tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab

  // OR use this initializer (uncomment) if using a 0.96" 180x60 TFT:
  //tft.initR(INITR_MINI160x80);  // Init ST7735S mini display

  // OR use this initializer (uncomment) if using a 1.54" 240x240 TFT:
  //tft.init(240, 240);           // Init ST7789 240x240
  Serial.println(F("Not Hallowing"));
#endif  
  tft.setRotation(2);
  
  randomSeed(analogRead(0));
  //initialize images array;
  for(int i = 0; i < 7; i++)
  {
    images[i] = i;
  }
}

void loop() 
{
  
  int randTiming = random(5000,10000);

  //randomize the array;
  for(int i = 0; i < 7; i++)
  {
    int r = random(7);
    int temp = images[i];
    images[i] = images[r];
    images[r] = temp;
  }

  DrawRainbow();
  Serial.println("Reset");
  delay(randTiming);

  for(int i = 0; i < 7; i++)
  {
    DrawImage(images[i], randTiming);
    Serial.println(images[i]);
  }
  
}


void DrawImage(int index, int timing)
{
   switch(index) 
  {
    case 0:
    tft.fillScreen(ST7735_AQUA);
    DrawBMP(Mamimi, 128, 128, 0, 0, ST77XX_BLACK);
    delay(timing);
    break;

    case 1:
    tft.fillScreen(ST77XX_BLACK);
    DrawBMP(FLCL, 128, 64, 0, 0, ST7735_ORANGE);
    DrawBMP(NaotaVert, 64, 128, 30, 40, ST7735_ORANGE);
    delay(timing);
    break;

    case 2:
    tft.fillScreen(ST7735_YELLOW);
    DrawBMP(P, 128, 128, 0, 0, ST77XX_BLACK);
    delay(timing);
    break;

    case 3:
    tft.fillScreen(ST77XX_BLACK);
    DrawBMP(NeverKnowsBest, 128, 64, 0, 35, ST7735_WHITE);
    delay(timing);
    break;

    case 4:
    tft.fillScreen(ST7735_YELLOW);
    DrawBMP(CantiSymbol, 128, 128, 0, 0, ST7735_RED);
    delay(timing);
    break;   
    
    case 5:
    tft.fillScreen(ST7735_MAGENTA);
    DrawBMP(Ninamori, 128, 128, 0, 0, ST7735_BLACK);
    delay(timing);
    break;

    case 6:
    tft.fillScreen(ST7735_ORANGE);
    DrawBMP(Climax, 128, 128, 0, 0, ST7735_BLACK);
    delay(timing);
    break;   
  }  
}

void DrawRainbow()
{
  tft.fillRect(0,0,16,128,ST7735_WHITE);
  tft.fillRect(16,0,16,128,ST7735_YELLOW);
  tft.fillRect(32,0,16,128,ST7735_AQUA);
  tft.fillRect(48,0,16,128,ST7735_GREEN);
  tft.fillRect(64,0,16,128,ST7735_PINK);
  tft.fillRect(80,0,16,128,ST7735_RED);
  tft.fillRect(96,0,16,128,ST7735_BLUE);
  tft.fillRect(112,0,16,128,ST7735_WHITE);
}
/////////////////////////////////////////////////////////////////////////////
////////////////////////scrolling functions//////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void ScrollUp(const uint8_t image[], int imageWidth, int imageHeight, int scrollWidth, int scrollHeight, int delayTime)
{
  for(int i = scrollHeight; i >= scrollHeight - imageHeight; i-=5)
  {
    tft.drawBitmap(scrollWidth, i, image, imageWidth, imageHeight, ST77XX_WHITE);
    delay(5);
    tft.drawBitmap(scrollWidth, i, image, imageWidth, imageHeight, ST77XX_BLACK);
    
    //tft.fillRect(0, 0, 128, 64, ST77XX_BLACK);
    
    //delay(1000);
    
    //tft.drawBitmap(scrollWidth, i-1, image, imageWidth, imageHeight, ST77XX_BLACK);
    //display.display();
    //tft.fillScreen(ST77XX_BLACK);
    //delay(delayTime);
  }
}

void DrawBMP(const uint8_t image[], int imageWidth, int imageHeight, int xPos, int yPos, uint16_t color)
{
  tft.drawBitmap(xPos, yPos, image, imageWidth, imageHeight, color);
}
