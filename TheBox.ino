#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM !!!"
#endif


//////////////////////////////////////////////////////
#include <iostream>
#include <string>
using namespace std;

#include <Arduino.h>
#include "epd_driver.h" //from LilyGo
#include "firasans.h"
#include "opensans12b.h" //see instructions on where to source and place this file
#include "trigrams.h" //see instructions on where to source and place this file
//#include "pins.h"
int cursor_y = 60;

      int32_t blockX;
      int32_t blockY;
      uint8_t blockColor;

uint8_t *framebuffer = NULL;
int vref = 1100;
int cursor_x = 20;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////PRINTER
//#include "Adafruit_Thermal.h" //CRITICAL edit this file to increase the heat of the printer. My settings: setHeatConfig(uint8_t dots=4, uint8_t time=255, uint8_t interval=255)
////Print Library MIT License, attribute to Limor Fried
//Adafruit_Thermal printer(&Serial1);

//#include "SoftwareSerial.h"
//const byte rxPin = 15;
//const byte txPin = 16;
//SoftwareSerial mySerial(rxPin,txPin);
//Pos_Printer printer(&mySerial); //edit the cpp and h file where necessary to set heat settings : dots=4, time = 255, interval = 255
#include "Pos_Printer.h"
Pos_Printer printer(&Serial0); //edit the cpp and h file where necessary to set heat settings : dots=4, time = 255, interval = 255
int PRINTIT = 1; //print iterations for certain tasks

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////SD CARD
//#include <FS.h>
//#include <SPI.h>
#include <SdFat.h>

#define SD_MISO    (16)
#define SD_MOSI    (15)
#define SD_SCLK    (11)
#define SD_CS      (42)

//#define GPIO_MISO  (45)
//#define GPIO_MOSI  (10)
//#define GPIO_SCLK  (48)
//#define GPIO_CS    (39)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////BUTTON CONTROL
#include "ClickButton.h" ////////give credit to this guy
const int buttons = 1;
//const int buttonPin1 = 21;
#define BUTTON_2  21
int state = 0 ;
int countdown = 0;

//CUSTOM TIMER
int period = 90000; //https://www.norwegiancreations.com/2017/09/arduino-tutorial-using-millis-instead-of-delay/
unsigned long time_now = 0;
//time_now = millis();
//while(millis() < time_now + period)

ClickButton button[1] = 
{
  ClickButton (BUTTON_2, LOW,CLICKBTN_PULLUP),
  };


#include <bootloader_random.h> //necessary for true random number generator - brings in entropy from WIFI, but shuts off after random numbers are generated
#include <Bitcoin.h> //MIT License, attribute to Stepan Snigerev
#include <PSBT.h> //MIT License, attribute to Stepan Snigerev
#include <qrcoderm.h> //CRITICAL see instructions for renaming files here or QR code will not work https://github.com/ricmoo/QRCode/issues/35#issuecomment-1179311130
//qrcode MIT license, attribute to Richard Moore and Project Nayuki


String finalString;
String psbtString;
PSBT psbt;
HDPrivateKey root;
HDPublicKey pub;
PrivateKey pk;
PublicKey pubk;
bool no_wallet_created_so_far = true;
String pkstr = "", pkwif = "", pubkstr = "";
const char* PRIVATE;
const char* PUBLIC;
const char* PHR;
const char* PHRS;

const char* P1;
const char* P2;
const char* P3;
const char* P4;

String PB1;
String PB2;
String PB3;
String PB4;
String finger;
const char* fing;
String BWxpub;

const char* PBL1;
const char* PBL2;
const char* PBL3;
const char* PBL4;
const char* XXPUB;
const char* XXPUBS;

const char* PBL4_PAGE;
const char* XPUB_PAGE;
const char* PRIV_PAGE;
const char* PRIV_PAGE2;
int stringlength = 0;
String displaystring ="";
String displaystring2 ="";

String pu1;
String pu2;
String pu3;
String pu4;
String phra;
String phrase;
String ROOOT;
String pubx;

String walletamount = "\n\n LEFTOVER IN WALLET ->\n0.00";
String transaction = "";

int RAND1;
int RANDO;

String NUMER[] = {"0","1","2","3","4","5","7","8","9"};
String ALPHA[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
String OTPLine = "";
String TRICODES [1199] = {"AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0","AAA\0"};
#define ARRAY_SIZE 1200
int THAT [ARRAY_SIZE] {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int SORTED [ARRAY_SIZE] {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int RANKED [ARRAY_SIZE] {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int sort_desc(const void *cmp1, const void *cmp2) {
  int a = *((int *)cmp1);
  int b = *((int *)cmp2);
  return (b - a); // Return a negative value if a < b, zero if a == b, and a positive value if a > b
}



void PRINTPUB()
{QRCode qrcode;
uint8_t qrVersion = 10; 
uint8_t qrErrorLevel = ECC_MEDIUM;
byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, PBL4);
uint8_t scale=3;
int buffer_size = calc_buffer_size(&qrcode, scale);
int width = ((qrcode.version * 5 + 7) * scale);
uint8_t pixels[buffer_size];
buffer_qr(&qrcode, pixels, scale);
printer.feed(1);
printer.printBitmap(width, width, pixels);}

void PRINTXPUB()
{QRCode qrcode;
uint8_t qrVersion = 10; 
uint8_t qrErrorLevel = ECC_MEDIUM;
byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, XXPUB);
uint8_t scale=3;
int buffer_size = calc_buffer_size(&qrcode, scale);
int width = ((qrcode.version * 5 + 7) * scale);
uint8_t pixels[buffer_size];
buffer_qr(&qrcode, pixels, scale);
printer.feed(1);
printer.printBitmap(width, width, pixels);}

void PRINTPRIV()
{QRCode qrcode;
uint8_t qrVersion = 10; 
uint8_t qrErrorLevel = ECC_MEDIUM;
byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, PRIVATE);
uint8_t scale=3;
int buffer_size = calc_buffer_size(&qrcode, scale);
int width = ((qrcode.version * 5 + 7) * scale);
uint8_t pixels[buffer_size];
buffer_qr(&qrcode, pixels, scale);
printer.feed(1);
printer.printBitmap(width, width, pixels);}

void PRINTLEARN()
{
QRCode qrcode;
uint8_t qrVersion = 10; 
uint8_t qrErrorLevel = ECC_MEDIUM;
byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];  
qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, "https://youtu.be/beu0riqB3gY?si=gKE_gT5IRNOJrgqL");
uint8_t scale=3;
int buffer_size = calc_buffer_size(&qrcode, scale);
int width = ((qrcode.version * 5 + 7) * scale);
uint8_t pixels[buffer_size];
buffer_qr(&qrcode, pixels, scale);
printer.feed(1);
printer.printBitmap(width, width, pixels);}


void reset_buffer()
{framebuffer = NULL;framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);}


void TRIGRAMDECODE()
{
reset_buffer();epd_poweron();epd_clear();cursor_x = 400; cursor_y = 280; write_string((GFXfont *)&FiraSans, "PRINTING\nTRIGRAMS", &cursor_x, &cursor_y, NULL);epd_poweroff();
printer.println("\n++++++++ DECODE +++++++++");
printer.println("ZZZ END LINE"); delay(1000);
time_now = millis();
for(int i=0;i<1199;i++)
  { 
    if(TRICODES[i][0]=='A'){THAT[i]+=(26*10000);}
    if(TRICODES[i][0]=='B'){THAT[i]+=(25*10000);}
    if(TRICODES[i][0]=='C'){THAT[i]+=(24*10000);}
    if(TRICODES[i][0]=='D'){THAT[i]+=(23*10000);}
    if(TRICODES[i][0]=='E'){THAT[i]+=(22*10000);}
    if(TRICODES[i][0]=='F'){THAT[i]+=(21*10000);}
    if(TRICODES[i][0]=='G'){THAT[i]+=(20*10000);}
    if(TRICODES[i][0]=='H'){THAT[i]+=(19*10000);}
    if(TRICODES[i][0]=='I'){THAT[i]+=(18*10000);}
    if(TRICODES[i][0]=='J'){THAT[i]+=(17*10000);}
    if(TRICODES[i][0]=='K'){THAT[i]+=(16*10000);}
    if(TRICODES[i][0]=='L'){THAT[i]+=(15*10000);}
    if(TRICODES[i][0]=='M'){THAT[i]+=(14*10000);}
    if(TRICODES[i][0]=='N'){THAT[i]+=(13*10000);}
    if(TRICODES[i][0]=='O'){THAT[i]+=(12*10000);}
    if(TRICODES[i][0]=='P'){THAT[i]+=(11*10000);}
    if(TRICODES[i][0]=='Q'){THAT[i]+=(10*10000);}
    if(TRICODES[i][0]=='R'){THAT[i]+=(9*10000);}
    if(TRICODES[i][0]=='S'){THAT[i]+=(8*10000);}
    if(TRICODES[i][0]=='T'){THAT[i]+=(7*10000);}
    if(TRICODES[i][0]=='U'){THAT[i]+=(6*10000);}
    if(TRICODES[i][0]=='V'){THAT[i]+=(5*10000);}
    if(TRICODES[i][0]=='W'){THAT[i]+=(4*10000);}
    if(TRICODES[i][0]=='X'){THAT[i]+=(3*10000);}
    if(TRICODES[i][0]=='Y'){THAT[i]+=(2*10000);}
    if(TRICODES[i][0]=='Z'){THAT[i]+=(1*10000);}
  }

for(int i=0;i<1199;i++)
  {
    if(TRICODES[i][1]=='A'){THAT[i]+=(26*100);}
    if(TRICODES[i][1]=='B'){THAT[i]+=(25*100);}
    if(TRICODES[i][1]=='C'){THAT[i]+=(24*100);}
    if(TRICODES[i][1]=='D'){THAT[i]+=(23*100);}
    if(TRICODES[i][1]=='E'){THAT[i]+=(22*100);}
    if(TRICODES[i][1]=='F'){THAT[i]+=(21*100);}
    if(TRICODES[i][1]=='G'){THAT[i]+=(20*100);}
    if(TRICODES[i][1]=='H'){THAT[i]+=(19*100);}
    if(TRICODES[i][1]=='I'){THAT[i]+=(18*100);}
    if(TRICODES[i][1]=='J'){THAT[i]+=(17*100);}
    if(TRICODES[i][1]=='K'){THAT[i]+=(16*100);}
    if(TRICODES[i][1]=='L'){THAT[i]+=(15*100);}
    if(TRICODES[i][1]=='M'){THAT[i]+=(14*100);}
    if(TRICODES[i][1]=='N'){THAT[i]+=(13*100);}
    if(TRICODES[i][1]=='O'){THAT[i]+=(12*100);}
    if(TRICODES[i][1]=='P'){THAT[i]+=(11*100);}
    if(TRICODES[i][1]=='Q'){THAT[i]+=(10*100);}
    if(TRICODES[i][1]=='R'){THAT[i]+=(9*100);}
    if(TRICODES[i][1]=='S'){THAT[i]+=(8*100);}
    if(TRICODES[i][1]=='T'){THAT[i]+=(7*100);}
    if(TRICODES[i][1]=='U'){THAT[i]+=(6*100);}
    if(TRICODES[i][1]=='V'){THAT[i]+=(5*100);}
    if(TRICODES[i][1]=='W'){THAT[i]+=(4*100);}
    if(TRICODES[i][1]=='X'){THAT[i]+=(3*100);}
    if(TRICODES[i][1]=='Y'){THAT[i]+=(2*100);}
    if(TRICODES[i][1]=='Z'){THAT[i]+=(1*100);}
  }

  for(int i=0;i<1199;i++)
  {
    if(TRICODES[i][2]=='A'){THAT[i]+=25;}
    if(TRICODES[i][2]=='B'){THAT[i]+=24;}
    if(TRICODES[i][2]=='C'){THAT[i]+=23;}
    if(TRICODES[i][2]=='D'){THAT[i]+=22;}
    if(TRICODES[i][2]=='E'){THAT[i]+=21;}
    if(TRICODES[i][2]=='F'){THAT[i]+=20;}
    if(TRICODES[i][2]=='G'){THAT[i]+=19;}
    if(TRICODES[i][2]=='H'){THAT[i]+=18;}
    if(TRICODES[i][2]=='I'){THAT[i]+=17;}
    if(TRICODES[i][2]=='J'){THAT[i]+=16;}
    if(TRICODES[i][2]=='K'){THAT[i]+=15;}
    if(TRICODES[i][2]=='L'){THAT[i]+=14;}
    if(TRICODES[i][2]=='M'){THAT[i]+=13;}
    if(TRICODES[i][2]=='N'){THAT[i]+=12;}
    if(TRICODES[i][2]=='O'){THAT[i]+=11;}
    if(TRICODES[i][2]=='P'){THAT[i]+=10;}
    if(TRICODES[i][2]=='Q'){THAT[i]+=9;}
    if(TRICODES[i][2]=='R'){THAT[i]+=8;}
    if(TRICODES[i][2]=='S'){THAT[i]+=7;}
    if(TRICODES[i][2]=='T'){THAT[i]+=6;}
    if(TRICODES[i][2]=='U'){THAT[i]+=5;}
    if(TRICODES[i][2]=='V'){THAT[i]+=4;}
    if(TRICODES[i][2]=='W'){THAT[i]+=3;}
    if(TRICODES[i][2]=='X'){THAT[i]+=2;}
    if(TRICODES[i][2]=='Y'){THAT[i]+=1;}
    if(TRICODES[i][2]=='Z'){THAT[i]+=0;}
  }

time_now = millis();
//RANK
  for (int i = 0; i < 1199; i++) 
      {SORTED[i] = THAT[i];}
  qsort(SORTED, 1199, sizeof(int), sort_desc);


    for (int i = 0; i < 1199; i++) {
      for (int j = 0; j <1199; j++) {
        if (THAT[i] == SORTED[j]) {
          RANKED[j] = i; // store position of match
        }
      }
    }
  
for (int i=0;i<50;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=50;i<100;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=100;i<150;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=150;i<200;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=200;i<250;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=250;i<300;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=300;i<350;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=350;i<400;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=400;i<450;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=450;i<500;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=500;i<550;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=550;i<600;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=600;i<650;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=650;i<700;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=700;i<750;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=750;i<800;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=800;i<850;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=850;i<900;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=900;i<950;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=950;i<1000;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=1000;i<1050;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=1050;i<1100;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=1100;i<1150;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
for (int i=1150;i<1199;i++){OTPLine+=TRICODES[RANKED[i]];OTPLine+=" ";strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[RANKED[i]])));OTPLine += buffer;OTPLine+="\n";printer.print(OTPLine);OTPLine="";}delay(2000);
printer.println("\n+++++++++++++++++++++++++++++\n\n"); 
delay(10000);
ESP.restart();
} 


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TRIGRAMENCODE() 
{

reset_buffer(); epd_poweron(); epd_clear();cursor_x =40; cursor_y = 140; write_string((GFXfont *)&FiraSans, "Prepare Up to 2 New Paper Rolls\n\nInsert New Roll and Click Button\nfor Encode Trigram List ", &cursor_x, &cursor_y, NULL);epd_poweroff();
time_now = millis();
while (millis() < time_now + period)
{
button[0].Update();
if(button[0].clicks == 1){time_now = millis();break;}
}
time_now = millis();
  
int i=0;
int j=0;
bootloader_random_enable();
  for (i=0; i < 100; i++)
    {
        OTPLine="";
        j = random(0,26); //1 
        OTPLine += ALPHA[j];
        j = random(0,26); //2
        OTPLine += ALPHA[j];
        j = random(0,26); //3
        OTPLine += ALPHA[j]; 
            if (OTPLine = "ZZZ") //ZZZ is reserved
              {OTPLine="";
                j = random(0,26); //1 
                OTPLine += ALPHA[j];
                j = random(0,26); //2
                OTPLine += ALPHA[j];
                j = random(0,26); //3
                OTPLine += ALPHA[j];
              }
            OTPLine +="\0";
              int ind = -1;
              for (int k=0;k<1199;k++)
              {
              ind = TRICODES[k].indexOf(OTPLine);
              if (ind!=-1){i--;break;}//if (ind!=-1){OTPLine=""; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j];}
              }
            TRICODES[i]=OTPLine;
      }

time_now = millis();
//epd_poweron(); cursor_x =100; cursor_y = 240; write_string((GFXfont *)&FiraSans, "-", &cursor_x, &cursor_y, NULL);epd_poweroff();

  for (i=100; i < 200; i++)
    {
        OTPLine="";
        j = random(0,26); //1 
        OTPLine += ALPHA[j];
        j = random(0,26); //2
        OTPLine += ALPHA[j];
        j = random(0,26); //3
        OTPLine += ALPHA[j]; 
            if (OTPLine = "ZZZ") //ZZZ is reserved
              {OTPLine="";
                j = random(0,26); //1 
                OTPLine += ALPHA[j];
                j = random(0,26); //2
                OTPLine += ALPHA[j];
                j = random(0,26); //3
                OTPLine += ALPHA[j];
              }
            OTPLine +="\0";
              int ind = -1;
              for (int k=0;k<1199;k++)
              {
              ind = TRICODES[k].indexOf(OTPLine);
              if (ind!=-1){i--;break;}//if (ind!=-1){OTPLine=""; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j];}
              }
            TRICODES[i]=OTPLine;

      }
      
time_now = millis();
//epd_poweron(); cursor_x =160; cursor_y = 240; write_string((GFXfont *)&FiraSans, "-", &cursor_x, &cursor_y, NULL);epd_poweroff();


  for (i=200; i < 300; i++)
    {
        OTPLine="";
        j = random(0,26); //1 
        OTPLine += ALPHA[j];
        j = random(0,26); //2
        OTPLine += ALPHA[j];
        j = random(0,26); //3
        OTPLine += ALPHA[j]; 
            if (OTPLine = "ZZZ") //ZZZ is reserved
              {OTPLine="";
                j = random(0,26); //1 
                OTPLine += ALPHA[j];
                j = random(0,26); //2
                OTPLine += ALPHA[j];
                j = random(0,26); //3
                OTPLine += ALPHA[j];
              }
            OTPLine +="\0";
              int ind = -1;
              for (int k=0;k<1199;k++)
              {
              ind = TRICODES[k].indexOf(OTPLine);
              if (ind!=-1){i--;break;}//if (ind!=-1){OTPLine=""; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j];}
              }
            TRICODES[i]=OTPLine;

      }
time_now = millis(); 
//epd_poweron(); cursor_x =200; cursor_y = 240; write_string((GFXfont *)&FiraSans, "-", &cursor_x, &cursor_y, NULL);epd_poweroff();


  for (i=300; i < 400; i++)
    {
        OTPLine="";
        j = random(0,26); //1 
        OTPLine += ALPHA[j];
        j = random(0,26); //2
        OTPLine += ALPHA[j];
        j = random(0,26); //3
        OTPLine += ALPHA[j]; 
            if (OTPLine = "ZZZ") //ZZZ is reserved
              {OTPLine="";
                j = random(0,26); //1 
                OTPLine += ALPHA[j];
                j = random(0,26); //2
                OTPLine += ALPHA[j];
                j = random(0,26); //3
                OTPLine += ALPHA[j];
              }
            OTPLine +="\0";
              int ind = -1;
              for (int k=0;k<1199;k++)
              {
              ind = TRICODES[k].indexOf(OTPLine);
              if (ind!=-1){i--;break;}//if (ind!=-1){OTPLine=""; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j];}
              }
            TRICODES[i]=OTPLine;

      }

time_now = millis();
//epd_poweron(); cursor_x =260; cursor_y = 240; write_string((GFXfont *)&FiraSans, "-", &cursor_x, &cursor_y, NULL);epd_poweroff();


  for (i=400; i < 500; i++)
    {
        OTPLine="";
        j = random(0,26); //1 
        OTPLine += ALPHA[j];
        j = random(0,26); //2
        OTPLine += ALPHA[j];
        j = random(0,26); //3
        OTPLine += ALPHA[j]; 
            if (OTPLine = "ZZZ") //ZZZ is reserved
              {OTPLine="";
                j = random(0,26); //1 
                OTPLine += ALPHA[j];
                j = random(0,26); //2
                OTPLine += ALPHA[j];
                j = random(0,26); //3
                OTPLine += ALPHA[j];
              }
            OTPLine +="\0";
              int ind = -1;
              for (int k=0;k<1199;k++)
              {
              ind = TRICODES[k].indexOf(OTPLine);
              if (ind!=-1){i--;break;}//if (ind!=-1){OTPLine=""; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j];}
              }
            TRICODES[i]=OTPLine;

      }
time_now = millis();
//epd_poweron(); cursor_x =340; cursor_y = 240; write_string((GFXfont *)&FiraSans, "-", &cursor_x, &cursor_y, NULL);epd_poweroff();


  for (i=500; i < 600; i++)
    {
        OTPLine="";
        j = random(0,26); //1 
        OTPLine += ALPHA[j];
        j = random(0,26); //2
        OTPLine += ALPHA[j];
        j = random(0,26); //3
        OTPLine += ALPHA[j]; 
            if (OTPLine = "ZZZ") //ZZZ is reserved
              {OTPLine="";
                j = random(0,26); //1 
                OTPLine += ALPHA[j];
                j = random(0,26); //2
                OTPLine += ALPHA[j];
                j = random(0,26); //3
                OTPLine += ALPHA[j];
              }
            OTPLine +="\0";
              int ind = -1;
              for (int k=0;k<1199;k++)
              {
              ind = TRICODES[k].indexOf(OTPLine);
              if (ind!=-1){i--;break;}//if (ind!=-1){OTPLine=""; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j];}
              }
            TRICODES[i]=OTPLine;

      }
time_now = millis();
//epd_poweron(); cursor_x =400; cursor_y = 240; write_string((GFXfont *)&FiraSans, "-", &cursor_x, &cursor_y, NULL);epd_poweroff();


  for (i=600; i < 700; i++)
    {
        OTPLine="";
        j = random(0,26); //1 
        OTPLine += ALPHA[j];
        j = random(0,26); //2
        OTPLine += ALPHA[j];
        j = random(0,26); //3
        OTPLine += ALPHA[j]; 
            if (OTPLine = "ZZZ") //ZZZ is reserved
              {OTPLine="";
                j = random(0,26); //1 
                OTPLine += ALPHA[j];
                j = random(0,26); //2
                OTPLine += ALPHA[j];
                j = random(0,26); //3
                OTPLine += ALPHA[j];
              }
            OTPLine +="\0";
              int ind = -1;
              for (int k=0;k<1199;k++)
              {
              ind = TRICODES[k].indexOf(OTPLine);
              if (ind!=-1){i--;break;}//if (ind!=-1){OTPLine=""; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j];}
              }
            TRICODES[i]=OTPLine;

      }
time_now = millis();
//epd_poweron(); cursor_x =460; cursor_y = 240; write_string((GFXfont *)&FiraSans, "-", &cursor_x, &cursor_y, NULL);epd_poweroff();


  for (i=700; i < 800; i++)
    {
        OTPLine="";
        j = random(0,26); //1 
        OTPLine += ALPHA[j];
        j = random(0,26); //2
        OTPLine += ALPHA[j];
        j = random(0,26); //3
        OTPLine += ALPHA[j]; 
            if (OTPLine = "ZZZ") //ZZZ is reserved
              {OTPLine="";
                j = random(0,26); //1 
                OTPLine += ALPHA[j];
                j = random(0,26); //2
                OTPLine += ALPHA[j];
                j = random(0,26); //3
                OTPLine += ALPHA[j];
              }
            OTPLine +="\0";
              int ind = -1;
              for (int k=0;k<1199;k++)
              {
              ind = TRICODES[k].indexOf(OTPLine);
              if (ind!=-1){i--;break;}//if (ind!=-1){OTPLine=""; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j];}
              }
            TRICODES[i]=OTPLine;

      }

time_now = millis(); 
//epd_poweron(); cursor_x =520; cursor_y = 240; write_string((GFXfont *)&FiraSans, "-", &cursor_x, &cursor_y, NULL);epd_poweroff();

  for (i=800; i < 900; i++)
    {
        OTPLine="";
        j = random(0,26); //1 
        OTPLine += ALPHA[j];
        j = random(0,26); //2
        OTPLine += ALPHA[j];
        j = random(0,26); //3
        OTPLine += ALPHA[j]; 
            if (OTPLine = "ZZZ") //ZZZ is reserved
              {OTPLine="";
                j = random(0,26); //1 
                OTPLine += ALPHA[j];
                j = random(0,26); //2
                OTPLine += ALPHA[j];
                j = random(0,26); //3
                OTPLine += ALPHA[j];
              }
            OTPLine +="\0";
              int ind = -1;
              for (int k=0;k<1199;k++)
              {
              ind = TRICODES[k].indexOf(OTPLine);
              if (ind!=-1){i--;break;}//if (ind!=-1){OTPLine=""; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j];}
              }
            TRICODES[i]=OTPLine;

      }

time_now = millis();
//epd_poweron(); cursor_x =580; cursor_y = 240; write_string((GFXfont *)&FiraSans, "-", &cursor_x, &cursor_y, NULL);epd_poweroff();

  for (i=900; i < 1000; i++)
    {
        OTPLine="";
        j = random(0,26); //1 
        OTPLine += ALPHA[j];
        j = random(0,26); //2
        OTPLine += ALPHA[j];
        j = random(0,26); //3
        OTPLine += ALPHA[j]; 
            if (OTPLine = "ZZZ") //ZZZ is reserved
              {OTPLine="";
                j = random(0,26); //1 
                OTPLine += ALPHA[j];
                j = random(0,26); //2
                OTPLine += ALPHA[j];
                j = random(0,26); //3
                OTPLine += ALPHA[j];
              }
            OTPLine +="\0";
              int ind = -1;
              for (int k=0;k<1199;k++)
              {
              ind = TRICODES[k].indexOf(OTPLine);
              if (ind!=-1){i--;break;}//if (ind!=-1){OTPLine=""; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j];}
              }
            TRICODES[i]=OTPLine;

      }

time_now = millis();
//epd_poweron(); cursor_x =640; cursor_y = 240; write_string((GFXfont *)&FiraSans, "-", &cursor_x, &cursor_y, NULL);epd_poweroff();


  for (i=1000; i < 1100; i++)
    {
        OTPLine="";
        j = random(0,26); //1 
        OTPLine += ALPHA[j];
        j = random(0,26); //2
        OTPLine += ALPHA[j];
        j = random(0,26); //3
        OTPLine += ALPHA[j]; 
            if (OTPLine = "ZZZ") //ZZZ is reserved
              {OTPLine="";
                j = random(0,26); //1 
                OTPLine += ALPHA[j];
                j = random(0,26); //2
                OTPLine += ALPHA[j];
                j = random(0,26); //3
                OTPLine += ALPHA[j];
              }
            OTPLine +="\0";
              int ind = -1;
              for (int k=0;k<1199;k++)
              {
              ind = TRICODES[k].indexOf(OTPLine);
              if (ind!=-1){i--;break;}//if (ind!=-1){OTPLine=""; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j];}
              }
            TRICODES[i]=OTPLine;

      }
//epd_poweron(); cursor_x =640; cursor_y = 720; write_string((GFXfont *)&FiraSans, "-", &cursor_x, &cursor_y, NULL);epd_poweroff();
time_now = millis();

  for (i=1100; i < 1199; i++)
    {
        OTPLine="";
        j = random(0,26); //1 
        OTPLine += ALPHA[j];
        j = random(0,26); //2
        OTPLine += ALPHA[j];
        j = random(0,26); //3
        OTPLine += ALPHA[j]; 
            if (OTPLine = "ZZZ") //ZZZ is reserved
              {OTPLine="";
                j = random(0,26); //1 
                OTPLine += ALPHA[j];
                j = random(0,26); //2
                OTPLine += ALPHA[j];
                j = random(0,26); //3
                OTPLine += ALPHA[j];
              }
            OTPLine +="\0";
              int ind = -1;
              for (int k=0;k<1199;k++)
              {
              ind = TRICODES[k].indexOf(OTPLine);
              if (ind!=-1){i--;break;}//if (ind!=-1){OTPLine=""; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j];}
              }
            TRICODES[i]=OTPLine;

      }

//reset_buffer(); epd_poweron(); epd_clear();cursor_x =40; cursor_y = 140; write_string((GFXfont *)&FiraSans, "Checking Randomization", &cursor_x, &cursor_y, NULL);epd_poweroff();delay(3000);
time_now = millis();
Serial.println("List");
int ind = -1;
int k=1;
for (i=0;i<1199;i++)
  {
  //1
  for (int k=1+i;k<1199;k++)
      {
      if (ind != -1)
      {
      Serial.println("");
      Serial.println(i);
      Serial.println(k);
      Serial.println(TRICODES[i]+" "+TRICODES[k]);
      OTPLine=""; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j]; j = random(0,26); OTPLine += ALPHA[j];OTPLine+="\0";TRICODES[k]=OTPLine;time_now = millis();
      Serial.println(TRICODES[i]+" "+TRICODES[k]);
      i=-1;
      Serial.println("");
      
      reset_buffer(); epd_poweron(); epd_clear();cursor_x =40; cursor_y = 140; write_string((GFXfont *)&FiraSans, "Checking Randomization", &cursor_x, &cursor_y, NULL);epd_poweroff();delay(3000);
      }
    }
  }

reset_buffer();epd_poweron();epd_clear();cursor_x = 400; cursor_y = 280; write_string((GFXfont *)&FiraSans, "PRINTING\nTRIGRAMS", &cursor_x, &cursor_y, NULL);epd_poweroff();


printer.println("\n+++++++++ ENCODE ++++++++++"); 
printer.println("ZZZ END LINE"); delay(1000);

i=0;
OTPLine="";
  for (i=0; i < 100; i++)
    {
      OTPLine+=TRICODES[i];
      OTPLine+=" ";
      strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[i])));OTPLine += buffer;
      OTPLine+="\n";
    }
time_now = millis();printer.print(OTPLine);OTPLine="";delay(5000);

  for (i=100; i < 200; i++)
    {
      OTPLine+=TRICODES[i];
      OTPLine+=" ";
      strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[i])));OTPLine += buffer;
      OTPLine+="\n";
    }
time_now = millis();printer.print(OTPLine);OTPLine="";delay(5000);

  for (i=200; i < 300; i++)
    {
      OTPLine+=TRICODES[i];
      OTPLine+=" ";
      strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[i])));OTPLine += buffer;
      OTPLine+="\n";
    }
time_now = millis();printer.print(OTPLine);OTPLine="";delay(5000);

   for (i=300; i < 400; i++)
    {
      OTPLine+=TRICODES[i];
      OTPLine+=" ";
      strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[i])));OTPLine += buffer;
      OTPLine+="\n";
    }
time_now = millis();printer.print(OTPLine);OTPLine="";delay(5000);

   for (i=300; i < 400; i++)
    {
      OTPLine+=TRICODES[i];
      OTPLine+=" ";
      strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[i])));OTPLine += buffer;
      OTPLine+="\n";
    }
time_now = millis();printer.print(OTPLine);OTPLine="";delay(5000);

   for (i=400; i < 500; i++)
    {
      OTPLine+=TRICODES[i];
      OTPLine+=" ";
      strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[i])));OTPLine += buffer;
      OTPLine+="\n";
    }
time_now = millis();printer.print(OTPLine);OTPLine="";delay(5000);

   for (i=500; i < 600; i++)
    {
      OTPLine+=TRICODES[i];
      OTPLine+=" ";
      strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[i])));OTPLine += buffer;
      OTPLine+="\n";
    }
time_now = millis();printer.print(OTPLine);OTPLine="";delay(5000);

   for (i=600; i < 700; i++)
    {
      OTPLine+=TRICODES[i];
      OTPLine+=" ";
      strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[i])));OTPLine += buffer;
      OTPLine+="\n";
    }
time_now = millis();printer.print(OTPLine);OTPLine="";delay(5000);

   for (i=700; i < 800; i++)
    {
      OTPLine+=TRICODES[i];
      OTPLine+=" ";
      strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[i])));OTPLine += buffer;
      OTPLine+="\n";
    }
time_now = millis();printer.print(OTPLine);OTPLine="";delay(5000);

   for (i=800; i < 900; i++)
    {
      OTPLine+=TRICODES[i];
      OTPLine+=" ";
      strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[i])));OTPLine += buffer;
      OTPLine+="\n";
    }
time_now = millis();printer.print(OTPLine);OTPLine="";delay(5000);

   for (i=900; i < 1000; i++)
    {
      OTPLine+=TRICODES[i];
      OTPLine+=" ";
      strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[i])));OTPLine += buffer;
      OTPLine+="\n";
    }
time_now = millis();printer.print(OTPLine);OTPLine="";delay(5000);

   for (i=1000; i < 1100; i++)
    {
      OTPLine+=TRICODES[i];
      OTPLine+=" ";
      strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[i])));OTPLine += buffer;
      OTPLine+="\n";
    }
time_now = millis();printer.print(OTPLine);OTPLine="";delay(5000);

   for (i=1100; i < 1199; i++)
    {
      OTPLine+=TRICODES[i];
      OTPLine+=" ";
      strcpy_P(buffer, (char *)pgm_read_ptr(&(TRIGRAMS[i])));OTPLine += buffer;
      OTPLine+="\n";
    }
time_now = millis();printer.print(OTPLine);OTPLine="";delay(5000);

printer.println("\n+++++++++++++++++++++++++++++\n\n"); 


//////////////////////////////////////////////////////////////////////BUTTON NECESSARY FOR NEXT STEP
reset_buffer(); epd_poweron(); epd_clear();cursor_x =40; cursor_y = 140; write_string((GFXfont *)&FiraSans, "Change Printer Paper \nand Click Button\nfor Decode Trigram List ", &cursor_x, &cursor_y, NULL);epd_poweroff();
time_now = millis();
while (millis() < time_now + period)
{
button[0].Update();
if(button[0].clicks == 1){time_now = millis();TRIGRAMDECODE();}
}
time_now = millis();
while (millis() < time_now + period)
{
button[0].Update();
if(button[0].clicks == 1){time_now = millis();TRIGRAMDECODE();}
}
time_now = millis();
while (millis() < time_now + period)
{
button[0].Update();
if(button[0].clicks == 1){time_now = millis();TRIGRAMDECODE();}
}
time_now = millis();
while (millis() < time_now + period)
{
button[0].Update();
if(button[0].clicks == 1){time_now = millis();TRIGRAMDECODE();}
}

ESP.restart();
}








void ALPHAOTP() {
reset_buffer();epd_poweron();epd_clear();cursor_x = 400; cursor_y = 280; write_string((GFXfont *)&FiraSans, "PRINTING", &cursor_x, &cursor_y, NULL);epd_poweroff();
time_now = millis();
printer.println("\n+++++++++++++++++++++++++++++");
bootloader_random_enable();
OTPLine+="+++++++++++++++++++++++++++++\n";
    for (uint8_t i = 0; i < 40; i++)
    {
    int j = random(0,26); //1 
        OTPLine += ALPHA[j];
        j = random(0,26); //2
        OTPLine += ALPHA[j];
        j = random(0,26); //3
        OTPLine += ALPHA[j];
        j = random(0,26); //4
        OTPLine += ALPHA[j];
        j = random(0,26); //5
        OTPLine += ALPHA[j]; OTPLine += " ";

        j = random(0,26); //6
        OTPLine += ALPHA[j];
        j = random(0,26); //7
        OTPLine += ALPHA[j];
        j = random(0,26); //8
        OTPLine += ALPHA[j];
        j = random(0,26); //9
        OTPLine += ALPHA[j];
        j = random(0,26); //10
        OTPLine += ALPHA[j]; OTPLine += " ";

        j = random(0,26); //11
        OTPLine += ALPHA[j];
        j = random(0,26); //12
        OTPLine += ALPHA[j];
        j = random(0,26); //13
        OTPLine += ALPHA[j];
        j = random(0,26); //14
        OTPLine += ALPHA[j];
        j = random(0,26); //15
        OTPLine += ALPHA[j]; OTPLine += " ";

        j = random(0,26); //16
        OTPLine += ALPHA[j];
        j = random(0,26); //17
        OTPLine += ALPHA[j];
        j = random(0,26); //18
        OTPLine += ALPHA[j];
        j = random(0,26); //19
        OTPLine += ALPHA[j];
        j = random(0,26); //20
        OTPLine += ALPHA[j]; OTPLine += " ";

        j = random(0,26); //21
        OTPLine += ALPHA[j];
        j = random(0,26); //22
        OTPLine += ALPHA[j];
        j = random(0,26); //23
        OTPLine += ALPHA[j];
        j = random(0,26); //24
        OTPLine += ALPHA[j];
        j = random(0,26); //25
        OTPLine += ALPHA[j]; OTPLine += "\n";
    }

OTPLine+="\n";

bootloader_random_disable();

if (PRINTIT == 10){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 9){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 8){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 7){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 6){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 5){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 4){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 3){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 2){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 1){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);}
ESP.restart();
};


void NUMEROTP() {
reset_buffer();epd_poweron();epd_clear();cursor_x = 400; cursor_y = 280; write_string((GFXfont *)&FiraSans, "PRINTING", &cursor_x, &cursor_y, NULL);epd_poweroff();

time_now = millis();
printer.println("\n+++++++++++++++++++++++++++++\n");
OTPLine="";
OTPLine+="++++++++++++++++++++++++++++\n";
OTPLine += "A-1   B-70   P-80   FIG-90\n";
OTPLine += "E-2   C-71   Q-81   (.)-91\n";
OTPLine += "I-3   D-72   R-82   (:)-92\n";
OTPLine += "N-4   F-73   S-83   (')-93\n";
OTPLine += "O-5   G-74   U-84   (,)-94\n";
OTPLine += "T-6   H-75   V-85   (+)-95\n";
OTPLine += "      J-76   W-86   (-)-96\n";
OTPLine += "      K-77   X-87   (=)-97\n";
OTPLine += "      L-78   Y-88   (?)-98\n";
OTPLine += "      M-79   Z-89   BRK-99\n";
OTPLine += "                    SPC-0\n";

OTPLine += "Transmit 1st 5 key numbers\nunencrypted to match lines\n with receiver\n\n";
OTPLine += "Encode: Subtract Message Letter from Key # \n(Original Msg - Key)\n";
OTPLine += "   If Total < 0, add 10\n\n";
OTPLine += "Decode: Add Message Letter \nto Key # \n(Encoded Msg + Key)\n";
OTPLine += "   If Total > 9, subtract 10\n\n";
bootloader_random_enable();
    for (uint8_t i = 0; i < 40; i++)
    {
    int j = random(0,9); //1 
        OTPLine += NUMER[j];
        j = random(0,9); //2
        OTPLine += NUMER[j];
        j = random(0,9); //3
        OTPLine += NUMER[j];
        j = random(0,9); //4
        OTPLine += NUMER[j];
        j = random(0,9); //5
        OTPLine += NUMER[j]; OTPLine += " ";

        j = random(0,9); //6
        OTPLine += NUMER[j];
        j = random(0,9); //7
        OTPLine += NUMER[j];
        j = random(0,9); //8
        OTPLine += NUMER[j];
        j = random(0,9); //9
        OTPLine += NUMER[j];
        j = random(0,9); //10
        OTPLine += NUMER[j]; OTPLine += " ";

        j = random(0,9); //11
        OTPLine += NUMER[j];
        j = random(0,9); //12
        OTPLine += NUMER[j];
        j = random(0,9); //13
        OTPLine += NUMER[j];
        j = random(0,9); //14
        OTPLine += NUMER[j];
        j = random(0,9); //15
        OTPLine += NUMER[j]; OTPLine += " ";

        j = random(0,9); //16
        OTPLine += NUMER[j];
        j = random(0,9); //17
        OTPLine += NUMER[j];
        j = random(0,9); //18
        OTPLine += NUMER[j];
        j = random(0,9); //19
        OTPLine += NUMER[j];
        j = random(0,9); //20
        OTPLine += NUMER[j]; OTPLine += " ";

        j = random(0,9); //21
        OTPLine += NUMER[j];
        j = random(0,9); //22
        OTPLine += NUMER[j];
        j = random(0,9); //23
        OTPLine += NUMER[j];
        j = random(0,9); //24
        OTPLine += NUMER[j];
        j = random(0,9); //25
        OTPLine += NUMER[j]; OTPLine += "\n";
    }

OTPLine+="\n";

bootloader_random_disable();

if (PRINTIT == 10){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 9){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 8){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 7){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 6){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 5){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 4){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 3){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 2){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);PRINTIT--;}
if (PRINTIT == 1){printer.println(OTPLine);printer.print("\n");delay(5000);printer.println(OTPLine);delay(5000);}

ESP.restart();
};



//960 x 540
Rect_t area1 = {
    .x = 0,
    .y = 100,
    .width = 320,
    .height = 110
};

Rect_t area2 = {
    .x = 335,
    .y = 100,
    .width = 310,
    .height = 110
};

Rect_t area3 = {
    .x = 643,
    .y = 100,
    .width = 305,
    .height = 110
};

Rect_t area4 = {
    .x = 0,
    .y = 310,
    .width = 320,
    .height = 110
};

Rect_t area5 = {
    .x = 335,
    .y = 310,
    .width = 310,
    .height = 110
};

Rect_t area6 = {
    .x = 643,
    .y = 310,
    .width = 305,
    .height = 110
};

Rect_t areaADDR = {
    .x = 23,
    .y = 270,
    .width = 260,
    .height = 180
};

Rect_t areaXPUB = {
    .x = 350,
    .y = 270,
    .width = 260,
    .height = 180
};

Rect_t areaPRIV = {
    .x = 675,
    .y = 270,
    .width = 260,
    .height = 180
};


//////////////////////////////////////////////////////////////////////////////
int calc_buffer_size(QRCode *qrcode, int scale) {

  int size = qrcode->version * 5 + 7;
  return ((size * scale + 7) / 8) * size * scale;
}
byte x;
byte y;
QRCode qrcode;
uint8_t blockValue = qrcode_getModule(&qrcode, x, y);

void buffer_qr(QRCode *qrcode, uint8_t buffer[], int scale)
{
  int size = qrcode->version * 5 + 7;
  int gridByteSize = (size * scale + 7) / 8;
  int gridSize = size * scale;

  int pixelNum=0, byteNum, x, y, b, i;

  for(byteNum=y=0; y<gridSize; y++) { // Each row...
    for(x=0; x<gridByteSize; x++) { // Each 8-pixel block within row...
      b = 0;
      for(i=0; i < 8; i++) {// each bit in byte
        b = b << 1;
        b += qrcode_getModule(qrcode, (x * 8 + i) / scale, y / scale);
      }
      buffer[byteNum] = b;
      byteNum++;
    }
  }
}



uint8_t generate_random_8bit()
{
    RANDO = esp_random();
    return (uint8_t)RANDO;
}

///////////////////////////////////////////////////////////////////////////// FOR BTC QR CODES

//void passmenu()
//{
//  time_now = millis();
//  while (millis() < time_now + period)
//  {
//    button[0].Update();
//     if(button[0].clicks == 2){break;} 
//  }
//}


void ADDRESS1_QR()
{
uint8_t qrVersion = 10;
uint8_t qrErrorLevel = ECC_MEDIUM;
byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
int offset = 10;
int32_t blockSize = ((EPD_HEIGHT - (offset * 2)) / qrcode.size)/2;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// BEGIN ADDRESS 1
  qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, PBL4);
  // QR Code block characteristics will depend on the display:
  // QR code needs a "quiet zone" of background color around it, hence the offset:
  offset = 10;
  blockSize = ((EPD_HEIGHT - (offset * 2)) / qrcode.size)/2;
  
//////////// fill with the background color:
//    epd_poweron();
//    epd_clear();
//    framebuffer = NULL;framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);

//  // read the bytes of the QR code and set the blocks light or dark, accordingly:
//  // vertical loop:
  for (byte y = 0; y < qrcode.size; y++) {
    // horizontal loop:
    for (byte x = 0; x < qrcode.size; x++) {
      // caculate the block's X and Y positions:
      blockX = (x * blockSize) + offset;
      blockY = (y * blockSize) + offset;
      // read the block value from the QRcode:
      int blockValue = qrcode_getModule(&qrcode, x, y);
      // set the default block color:
      blockColor = 2;
      // if the block value is 1, set color to foreground color instead:
      if (blockValue == 1) {
        blockColor = 255;
      }
epd_fill_rect(blockX+50, blockY+120, blockSize, blockSize,blockColor,framebuffer);  
    }
  }

//PBL4_PAGE 
displaystring = "";stringlength=0;
stringlength = PB4.length();
displaystring = PB4.substring(0,25)+"\n"+PB4.substring(25,stringlength);
PBL4_PAGE = displaystring.c_str();
cursor_x =30; cursor_y = 10; write_string((GFXfont *)&FiraSans, "\nPublic Address #1", &cursor_x, &cursor_y, NULL);time_now = millis();
cursor_x =355; cursor_y = 230; write_string((GFXfont *)&FiraSans, PBL4_PAGE, &cursor_x, &cursor_y, NULL);time_now = millis();
cursor_x =30; cursor_y = 400; write_string((GFXfont *)&FiraSans, "\nUse this to confirm the Watch Wallet \nand/or Private Keys are correct.", &cursor_x, &cursor_y, NULL);time_now = millis();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// END ADDRESS 1
epd_draw_grayscale_image(epd_full_screen(),framebuffer);epd_poweroff();



  time_now = millis();
//passmenu();

}

void XPUB_QR()
{
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// BEGIN XPUB
uint8_t qrVersion = 10;
uint8_t qrErrorLevel = ECC_MEDIUM;
byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
int offset = 10;
int32_t blockSize = ((EPD_HEIGHT - (offset * 2)) / qrcode.size)/2;
/////////---------------------------------------------------------------------//////////

  qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, XXPUB);
  // QR Code block characteristics will depend on the display:
  // QR code needs a "quiet zone" of background color around it, hence the offset:
  offset = 10;
  blockSize = ((EPD_HEIGHT - (offset * 2)) / qrcode.size)/2;
//  // read the bytes of the QR code and set the blocks light or dark, accordingly:
//  // vertical loop:
  for (byte y = 0; y < qrcode.size; y++) {
    // horizontal loop:
    for (byte x = 0; x < qrcode.size; x++) {
      // caculate the block's X and Y positions:
      blockX = (x * blockSize) + offset;
      blockY = (y * blockSize) + offset;
      // read the block value from the QRcode:
      int blockValue = qrcode_getModule(&qrcode, x, y);
      // set the default block color:
      blockColor = 2;
      // if the block value is 1, set color to foreground color instead:
      if (blockValue == 1) {
        blockColor = 255;
      }



epd_fill_rect(blockX+30, blockY+120, blockSize, blockSize,blockColor,framebuffer);

    
    }

  }

//XPUB_PAGE 
////////////////////////////////////////// SD CARD
    SPI.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);
    SdFat SD;
    if (!SD.begin(SD_CS, SD_SCK_MHZ(10))) 
      {cursor_x =750; cursor_y = 60; write_string((GFXfont *)&FiraSans, "No SD Fat", &cursor_x, &cursor_y, NULL);    } 
    else 
      { 
        SD.remove("XPUB.txt"); //This is the format for importing to Blue Wallet
        File myFile = SD.open("XPUB.txt", FILE_WRITE);
        if (myFile) {cursor_x =750; cursor_y = 60; write_string((GFXfont *)&FiraSans, "✓ SD Fat", &cursor_x, &cursor_y, NULL);}
        myFile.println(BWxpub);
        myFile.close();
       }
/////////////////////////////////////////
displaystring = "";stringlength=0;
stringlength = BWxpub.length();
for(int i = 0; i <= stringlength; i+=25)
{displaystring += BWxpub.substring(i,i+25)+"\n";}
XPUB_PAGE = displaystring.c_str();
cursor_x =30; cursor_y = 10; write_string((GFXfont *)&FiraSans, "\nWatch Wallet or \"XPUB\"", &cursor_x, &cursor_y, NULL);time_now = millis();
cursor_x =310; cursor_y = 130; write_string((GFXfont *)&FiraSans, XPUB_PAGE, &cursor_x, &cursor_y, NULL);time_now = millis();
cursor_x =30; cursor_y = 400; write_string((GFXfont *)&FiraSans, "\nImport as Receive Only Wallet \nand/or use with an offline signer to spend.", &cursor_x, &cursor_y, NULL);time_now = millis();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// END XPUB
epd_draw_grayscale_image(epd_full_screen(),framebuffer);
epd_poweroff();

  time_now = millis();
//passmenu();
}

void PRIVATE_QR()
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// BEGIN PRIVATE KEYS
uint8_t qrVersion = 10;
uint8_t qrErrorLevel = ECC_MEDIUM;
byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
int offset = 10;
int32_t blockSize = ((EPD_HEIGHT - (offset * 2)) / qrcode.size)/2;

  qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, PRIVATE);
  // QR Code block characteristics will depend on the display:
  // QR code needs a "quiet zone" of background color around it, hence the offset:
  offset = 10;
  blockSize = ((EPD_HEIGHT - (offset * 2)) / qrcode.size)/2;


//  // read the bytes of the QR code and set the blocks light or dark, accordingly:
//  // vertical loop:
  for (byte y = 0; y < qrcode.size; y++) {
    // horizontal loop:
    for (byte x = 0; x < qrcode.size; x++) {
      // caculate the block's X and Y positions:
      blockX = (x * blockSize) + offset;
      blockY = (y * blockSize) + offset;
      // read the block value from the QRcode:
      int blockValue = qrcode_getModule(&qrcode, x, y);
      // set the default block color:
      blockColor = 2;
      // if the block value is 1, set color to foreground color instead:
      if (blockValue == 1) {
        blockColor = 255;
      }


epd_fill_rect(blockX+30, blockY+145, blockSize, blockSize,blockColor,framebuffer);

    
    }

  }

//PRIV_PAGE 
////////////////////////////////////////// SD CARD
    SPI.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);
    SdFat SD;
    if (!SD.begin(SD_CS, SD_SCK_MHZ(10))) 
      {cursor_x =750; cursor_y = 60; write_string((GFXfont *)&FiraSans, "No SD Fat", &cursor_x, &cursor_y, NULL);    } 
    else 
      { File myFile;
        SD.remove("PUBLIC.txt");
        myFile = SD.open("PUBLIC.txt", FILE_WRITE);
        myFile.print(PB4);
        myFile.close();
      
        SD.remove("XPUB.txt");
        myFile = SD.open("XPUB.txt", FILE_WRITE);
        myFile.print(BWxpub);
        myFile.close();
      
        SD.remove("PHRASE.txt");
        myFile = SD.open("PHRASE.txt", FILE_WRITE);
        if (myFile) {cursor_x =750; cursor_y = 60; write_string((GFXfont *)&FiraSans, "✓ SD Fat", &cursor_x, &cursor_y, NULL);}
        myFile.print(phrase);
        myFile.close();
       }
/////////////////////////////////////////
displaystring = "1. ";stringlength=0;
stringlength = phra.length();
int j = 1;
for(int i = 0; i <= stringlength; i++)
{ if(isSpace(phrase[i]))
     {if(j < 6){j++;displaystring += "\n"+String(j)+". ";} else if(j == 6){j++;displaystring2 += String(j)+". ";}else if(j > 6){j++;displaystring2 += "\n"+String(j)+". ";}}
  else if(j<7) {displaystring += phrase[i];}
  else if(j>6) {displaystring2 += phrase[i];}
}
PRIV_PAGE = displaystring.c_str();
PRIV_PAGE2 = displaystring2.c_str();
cursor_x =30; cursor_y = 10; write_string((GFXfont *)&FiraSans, "\nPrivate Recovery Phrase", &cursor_x, &cursor_y, NULL);time_now = millis();
cursor_x =350; cursor_y = 160; write_string((GFXfont *)&FiraSans, PRIV_PAGE, &cursor_x, &cursor_y, NULL);time_now = millis();
cursor_x =680; cursor_y = 160; write_string((GFXfont *)&FiraSans, PRIV_PAGE2, &cursor_x, &cursor_y, NULL);time_now = millis();
cursor_x =30; cursor_y = 450; write_string((GFXfont *)&FiraSans, "\nImport as a Hot Wallet to Spend and Receive.", &cursor_x, &cursor_y, NULL);time_now = millis();
////////////////////////////////////////////////////////////////////////////////// END PRIVATE KEYS
epd_draw_grayscale_image(epd_full_screen(),framebuffer);epd_poweroff();


  time_now = millis();
//passmenu();
}






void printTHIS()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////printer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////--- can comment this out this section if you'd like, it is just for you to easily track the coin once it is given out
printer.feed(1);printer.println(F("\n+++++++++++++++++++++++++++"));
printer.justify('L');
printer.feed();
printer.println(F(PHR));
PRINTPRIV();
//////////////////////////////////////////
////////// XPUB /////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////
printer.justify('L');
printer.feed(1);
;printer.println(F("+++++++++++++++++++++++++++"));
printer.feed(1);
printer.print(F("FINGERPRINT: "));
printer.println(F(fing));
printer.println(F("WATCH WALLET: "));
PRINTXPUB();
printer.feed(1);printer.println(F("+++++++++++++++++++++++++++"));
////////////////////////////////////////////////////////////////////////////////////////////////////--- end section


printer.feed(1);printer.println(F("\n+++++++++++++++++++++++++++"));
printer.justify('L');
printer.feed();
printer.println(F(PHR));
PRINTPRIV();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////BLUE WALLET FOOTER
printer.justify('L');
printer.feed(1);printer.println(F("+++++++++++++++++++++++++++"));
printer.feed(1);
printer.println(F("Import Recovery Phrase to"));
printer.feed(1);
printer.println(F("BlueWallet for ease of use:"));
printer.feed(1);
printer.println(F("https://bluewallet.io"));
printer.feed(1);
//qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, "https://bluewallet.io/");
printer.feed(1);
printer.println(F("Step 1) Go to create new wallet; click but don't create yet"));
printer.feed(1);
printer.println(F("Step 2) Scroll down & click"));
printer.feed(1);
printer.println(F("      IMPORT"));
printer.feed(1);
printer.println(F("Step 3) Enter recovery phrase & continue. Enjoy!"));
printer.feed(1);
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////BLUE WALLET FOOTER
printer.justify('L');
printer.println(F("+++++++++++++++++++++++++++"));
printer.feed(1);
printer.println(F("Spend Using :"));
printer.feed(1);
printer.println(F("thebitcoincompany.com"));
printer.feed(1);
printer.println(F("Buy More Using :"));
printer.feed(1);
printer.println(F("https://strike.me/"));
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////
////////// XPUB /////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////

printer.justify('L');
printer.feed(1);
;printer.println(F("+++++++++++++++++++++++++++"));
printer.println(F("ADVANCED FEATURES..."));
printer.feed(1);
printer.print(F("FINGERPRINT: "));
printer.println(F(fing));
printer.println(F("WATCH WALLET: "));
PRINTXPUB();
printer.feed(1);printer.println(F("+++++++++++++++++++++++++++"));
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////
////////// PUBLIC ADDRESS 1 /////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////

printer.feed(1);
printer.justify('L');
printer.println(F("Public Address 1: "));
printer.feed(1);
printer.print(F(PBL4));
PRINTPUB();
////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
printer.feed(1);
printer.println(F("+++++++++++++++++++++++++++"));
printer.println(F("Learn More At:"));
printer.feed(1);
PRINTLEARN();
printer.feed();
printer.feed();
printer.feed();
}

void quoter()
{   
epd_poweron();
epd_clear();  
bootloader_random_enable();
int quote = random(0,12);
bootloader_random_disable();
if(quote == 0){cursor_x =40; cursor_y = 0; write_string((GFXfont *)&FiraSans, "\n\n\nWe can't solve problems \n\n            by using the same kind of thinking\n\n                        we used when we created them.\n\n                                  - Albert Einstein", &cursor_x, &cursor_y, NULL);};
if(quote == 1){cursor_x =120; cursor_y = 0; write_string((GFXfont *)&FiraSans, "\n\n\nOh, you should never, \n\n            never doubt what nobody\n\n                       is sure about.\n\n                                  - Hilaire Belloc", &cursor_x, &cursor_y, NULL);};
if(quote == 2){cursor_x =120; cursor_y = 0; write_string((GFXfont *)&FiraSans, "\n\n\nIf I had more time, \n\n            I would have written a \n\n                       shorter letter.\n\n                                  - Blaise Pascal", &cursor_x, &cursor_y, NULL);};

if(quote == 3){cursor_x =70; cursor_y = 00; write_string((GFXfont *)&FiraSans, "\n\n\nIf I have seen further, \n\n            than others, it is by standing \n\n                       upon the shoulders of giants.\n\n                                  - Isaac Newton", &cursor_x, &cursor_y, NULL);}
if(quote == 4){cursor_x =120; cursor_y = 30; write_string((GFXfont *)&FiraSans, "\n\n\nA little nonsense now and then \n\n             is relished by the wisest men.\n\n                       - Roald Dahl", &cursor_x, &cursor_y, NULL);}
if(quote == 5){cursor_x =120; cursor_y = 30; write_string((GFXfont *)&FiraSans, "\n\n\nNow is the time to understand more,\n\n            so that we may fear less.\n\n                       - Marie Curie", &cursor_x, &cursor_y, NULL);}

if(quote == 6){cursor_x =40; cursor_y = 00; write_string((GFXfont *)&FiraSans, "\n\n\nKeep your face always\n\n            toward the sunshine\n\n                       and shadows will fall behind you.\n\n                                  - Walt Whitman", &cursor_x, &cursor_y, NULL);}
if(quote == 7){cursor_x =120; cursor_y = 30; write_string((GFXfont *)&FiraSans, "\n\n\nI shall allow no man to belittle my soul \n\n             by making me hate him.\n\n              - Booker T Washington", &cursor_x, &cursor_y, NULL);}
if(quote == 8){cursor_x =120; cursor_y = 30; write_string((GFXfont *)&FiraSans, "\n\n\nHe will win who knows when\n\n            to fight and when not to fight.\n\n                       - Sun Zhu", &cursor_x, &cursor_y, NULL);}

if(quote == 9){cursor_x =80; cursor_y = 00; write_string((GFXfont *)&FiraSans, "\n\n\nWhen something is important enough,\n\n            you do it even if the odds\n\n                       are not in your favor.\n\n                                  - Elon Musk", &cursor_x, &cursor_y, NULL);}
if(quote == 10){cursor_x =25; cursor_y = 30; write_string((GFXfont *)&FiraSans, "\n\n\nSometimes life hits you in the head with a brick.\n\n                            Don't lose faith.\n\n                               - Steve Jobs", &cursor_x, &cursor_y, NULL);}
if(quote == 11){cursor_x =40; cursor_y = 30; write_string((GFXfont *)&FiraSans, "\n\n\nIf everyone is moving forward together,\n\n    then success takes care of itself.\n\n                                                          - Henry Ford", &cursor_x, &cursor_y, NULL);}

epd_poweroff();
}


void generate_wallet()
{
  const uint8_t pklen = 32;
    uint8_t pkbytes[pklen];

    bootloader_random_enable(); /*key to true random number generation, uses analog noise and other sources for entropy*/
    for (uint8_t i = 0; i < pklen; i++)
    {
        pkbytes[i] = generate_random_8bit();
    }
    bootloader_random_disable(); /*protects from wireless attack*/
    
    pkstr = "";
    for (uint8_t i = 0; i < pklen; i++)
    {
        if (pkbytes[i] <= 0x0f)
        {
            pkstr += "0";
        }
        pkstr += String(pkbytes[i], HEX);
    }
  
  
  String entropy = pkstr;
  phrase = generateMnemonic(12, entropy);

pkstr = ""; entropy = "";

phra = String("Private Recovery Phrase:\n\n")+phrase;
PRIVATE = phrase.c_str();
PHR = phra.c_str();

HDPrivateKey root(phrase, ""); // using default empty password, fill quotes if you want a password added

ROOOT = root;
finger = root.fingerprint();
fing = finger.c_str();
HDPrivateKey account = root.derive("m/84'/0'/0'");

HDPublicKey xpub = account.xpub();
pubx = account.xpub();
//Serial.println(pubx);
BWxpub = "["+finger+"/84h/0h/0h"+"]"+pubx;
//Serial.println(BWxpub);
XXPUB = BWxpub.c_str();

      String desc = ""; //watch wallet for Bitcoin Core
      desc = "wpkh([";
      // add fingerprint
      desc += root.fingerprint();
      // add derivation path. We need to remove leading `m`
      desc += "/84h/0h/0h]";
      // now pub xpub in normal form
      xpub.type = UNKNOWN_TYPE;
      desc += xpub.toString();
      desc += "/0/*)";
      // and add a checksum
      desc += String("#")+descriptorChecksum(desc);
      //Serial.println(desc);

      String desc2 = "";
      desc2 = "wpkh([";
      // add fingerprint
      desc2 += root.fingerprint();
      // add derivation path. We need to remove leading `m`
      desc2 += "/84h/0h/0h]";
      // now pub xpub in normal form
      xpub.type = UNKNOWN_TYPE;
      desc2 += xpub.toString();
      desc2 += "/1/*)";
      // and add a checksum
      desc2 += String("#")+descriptorChecksum(desc2);
      //Serial.println(desc2);

HDPublicKey pub1;
HDPublicKey pub2;
HDPublicKey pub3;
HDPublicKey pub4;

pub1 = xpub.child(0).child(1); //this will show as Address 2
//Serial.println(pub1.address());

pub2 = xpub.child(0).child(2); //this will show as Address 3
//Serial.println(pub2.address());

pub3 = xpub.child(0).child(3); //this will show as Address 4
//Serial.println(pub3.address());

pub4 = xpub.child(0).child(0); //this will show as Address 1 -- I KNOW THIS IS DUMB, BUT I DID THIS IN THE BEGINNING, AND I AM TOO LAZY TO CARE NOW.
//Serial.println(pub4.address());

pu1 = String("Public Address 2:\n\n")+String(pub1.address());
pu2 = String("Public Address 3:\n\n")+String(pub2.address());
pu3 = String("Public Address 4:\n\n")+String(pub3.address());
pu4 = String("Public Address 1:\n\n")+String(pub4.address());

P1 = pu1.c_str();
P2 = pu2.c_str();
P3 = pu3.c_str();
P4 = pu4.c_str();

PB1 = pub1.address();
PBL1 = PB1.c_str();

PB2 = pub2.address();
PBL2 = PB2.c_str();

PB3 = pub3.address();
PBL3 = PB3.c_str();

PB4 = pub4.address();
PBL4 = PB4.c_str();


reset_buffer();epd_poweron();epd_clear();

epd_fill_rect(22, 10, 260, 260, 0, framebuffer);
epd_fill_rect(350, 10, 260, 260, 0, framebuffer);
epd_fill_rect(675, 10, 260, 260, 0, framebuffer);

epd_draw_rect(33, 280, 240, 160, 0, framebuffer);
cursor_x =45; cursor_y = 320;  write_string((GFXfont *)&FiraSans, "    Reveal\n    Watch\n    Wallet", &cursor_x, &cursor_y, NULL);cursor_x =45; cursor_y = 320;
//epd_draw_rect(360, 280, 240, 160, 0, framebuffer);
cursor_x = 350; cursor_y = 320; write_string((GFXfont *)&FiraSans, "      Reveal\n      Public\n    Address 1", &cursor_x, &cursor_y, NULL);
//epd_draw_rect(685, 280, 240, 160, 0, framebuffer);
cursor_x = 695; cursor_y = 320; write_string((GFXfont *)&FiraSans, "    Reveal\n    Private \n      Keys", &cursor_x, &cursor_y, NULL);

epd_draw_grayscale_image(epd_full_screen(), framebuffer);
cursor_x = 20; cursor_y = 510; write_string((GFXfont *)&FiraSans, " *DANGEROUS to show to people and cameras!!!!", &cursor_x, &cursor_y, NULL);
epd_poweroff();      


reset_buffer();
state = 0;
bool INNER = false;
time_now = millis();
while (millis() < time_now + period)
{
  button[0].Update();
  if(button[0].clicks == 1 and INNER == false)
            {   state++;
                if(state > 2){state = 0;};
                if(state == 0){time_now = millis();reset_buffer();epd_poweron();epd_draw_rect(33, 280, 240, 160, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(),framebuffer);epd_clear_area(areaPRIV);cursor_x = 695; cursor_y = 320; write_string((GFXfont *)&FiraSans, "    Reveal\n    Private \n      Keys", &cursor_x, &cursor_y, NULL);epd_poweroff();time_now = millis();}
                if(state == 1){time_now = millis();reset_buffer();epd_poweron();epd_draw_rect(360, 280, 240, 160, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(),framebuffer);epd_clear_area(areaADDR);cursor_x =45; cursor_y = 320; write_string((GFXfont *)&FiraSans, "    Reveal\n    Watch\n    Wallet", &cursor_x, &cursor_y, NULL);epd_poweroff();time_now = millis();}
                if(state == 2){time_now = millis();reset_buffer();epd_poweron();epd_draw_rect(685, 280, 240, 160, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(),framebuffer);epd_clear_area(areaXPUB); cursor_x = 350; cursor_y = 320; write_string((GFXfont *)&FiraSans, "      Reveal\n      Public\n    Address 1", &cursor_x, &cursor_y, NULL);epd_poweroff();time_now = millis();}
            }   

    if(button[0].clicks == 2)
            {   
                if(state > 2){state = 0;};
                if(state == 0){time_now = millis();reset_buffer();epd_poweron();epd_clear();INNER=true;XPUB_QR();time_now = millis();} 
                if(state == 1){time_now = millis();reset_buffer();epd_poweron();epd_clear();INNER=true;ADDRESS1_QR();time_now = millis();} 
                if(state == 2){time_now = millis();reset_buffer();epd_poweron();epd_clear();INNER=true;PRIVATE_QR();time_now = millis();} 
                state++;
            } 
  

    if(button[0].clicks == 4){ESP.restart();}
}
if (millis() >= time_now + period){ESP.restart();}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void generate_wallet_print()
{while(PRINTIT>0)

{reset_buffer();epd_poweron();epd_clear();epd_poweroff();button[0].Update();
cursor_x = 400; cursor_y = 280; write_string((GFXfont *)&FiraSans, "PRINTING", &cursor_x, &cursor_y, NULL);epd_poweroff();

  const uint8_t pklen = 32;
    uint8_t pkbytes[pklen];

    bootloader_random_enable(); /*key to true random number generation, uses analog noise and other sources for entropy*/
    for (uint8_t i = 0; i < pklen; i++)
    {
        pkbytes[i] = generate_random_8bit();
    }
    bootloader_random_disable(); /*protects from wireless attack*/
    
    pkstr = "";
    for (uint8_t i = 0; i < pklen; i++)
    {
        if (pkbytes[i] <= 0x0f)
        {
            pkstr += "0";
        }
        pkstr += String(pkbytes[i], HEX);
    }
  
  
  String entropy = pkstr;
  phrase = generateMnemonic(12, entropy);
  pkstr = ""; entropy = "";

phra = String("Private Recovery Phrase:\n\n")+phrase;
PRIVATE = phrase.c_str();
PHR = phra.c_str();

HDPrivateKey root(phrase, ""); // using default empty password, fill quotes if you want a password added

ROOOT = root;
finger = root.fingerprint();
fing = finger.c_str();
HDPrivateKey account = root.derive("m/84'/0'/0'");

HDPublicKey xpub = account.xpub();
pubx = account.xpub();
//Serial.println(pubx);
BWxpub = "["+finger+"/84h/0h/0h"+"]"+pubx;
//Serial.println(BWxpub);
XXPUB = BWxpub.c_str();

      String desc = ""; //watch wallet for Bitcoin Core
      desc = "wpkh([";
      // add fingerprint
      desc += root.fingerprint();
      // add derivation path. We need to remove leading `m`
      desc += "/84h/0h/0h]";
      // now pub xpub in normal form
      xpub.type = UNKNOWN_TYPE;
      desc += xpub.toString();
      desc += "/0/*)";
      // and add a checksum
      desc += String("#")+descriptorChecksum(desc);
      //Serial.println(desc);

      String desc2 = "";
      desc2 = "wpkh([";
      // add fingerprint
      desc2 += root.fingerprint();
      // add derivation path. We need to remove leading `m`
      desc2 += "/84h/0h/0h]";
      // now pub xpub in normal form
      xpub.type = UNKNOWN_TYPE;
      desc2 += xpub.toString();
      desc2 += "/1/*)";
      // and add a checksum
      desc2 += String("#")+descriptorChecksum(desc2);
      //Serial.println(desc2);

HDPublicKey pub1;
HDPublicKey pub2;
HDPublicKey pub3;
HDPublicKey pub4;

pub1 = xpub.child(0).child(1); //this will show as Address 2
//Serial.println(pub1.address());

pub2 = xpub.child(0).child(2); //this will show as Address 3
//Serial.println(pub2.address());

pub3 = xpub.child(0).child(3); //this will show as Address 4
//Serial.println(pub3.address());

pub4 = xpub.child(0).child(0); //this will show as Address 1 -- I KNOW THIS IS DUMB, BUT I DID THIS IN THE BEGINNING, AND I AM TOO LAZY TO CARE NOW.
//Serial.println(pub4.address());

pu1 = String("Public Address 2:\n\n")+String(pub1.address());
pu2 = String("Public Address 3:\n\n")+String(pub2.address());
pu3 = String("Public Address 4:\n\n")+String(pub3.address());
pu4 = String("Public Address 1:\n\n")+String(pub4.address());

P1 = pu1.c_str();
P2 = pu2.c_str();
P3 = pu3.c_str();
P4 = pu4.c_str();

PB1 = pub1.address();
PBL1 = PB1.c_str();

PB2 = pub2.address();
PBL2 = PB2.c_str();

PB3 = pub3.address();
PBL3 = PB3.c_str();

PB4 = pub4.address();
PBL4 = PB4.c_str();



printTHIS();PRINTIT--;

}
//
//time_now = millis();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//display wallet
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

reset_buffer();epd_poweron();epd_clear();

epd_fill_rect(22, 10, 260, 260, 0, framebuffer);
epd_fill_rect(350, 10, 260, 260, 0, framebuffer);
epd_fill_rect(675, 10, 260, 260, 0, framebuffer);

epd_draw_rect(33, 280, 240, 160, 0, framebuffer);
cursor_x =45; cursor_y = 320;  write_string((GFXfont *)&FiraSans, "    Reveal\n    Watch\n    Wallet", &cursor_x, &cursor_y, NULL);cursor_x =45; cursor_y = 320;
//epd_draw_rect(360, 280, 240, 160, 0, framebuffer);
cursor_x = 350; cursor_y = 320; write_string((GFXfont *)&FiraSans, "      Reveal\n      Public\n    Address 1", &cursor_x, &cursor_y, NULL);
//epd_draw_rect(685, 280, 240, 160, 0, framebuffer);
cursor_x = 695; cursor_y = 320; write_string((GFXfont *)&FiraSans, "    Reveal\n    Private \n      Keys", &cursor_x, &cursor_y, NULL);

epd_draw_grayscale_image(epd_full_screen(), framebuffer);
cursor_x = 20; cursor_y = 510; write_string((GFXfont *)&FiraSans, " *DANGEROUS to show to people and cameras!!!!", &cursor_x, &cursor_y, NULL);
epd_poweroff();      


reset_buffer();
state = 0;
bool INNER = false;
time_now = millis();
while (millis() < time_now + period)
{
  button[0].Update();
  if(button[0].clicks == 1 and INNER == false)
            {   state++;
                if(state > 2){state = 0;};
                if(state == 0){time_now = millis();reset_buffer();epd_poweron();epd_draw_rect(33, 280, 240, 160, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(),framebuffer);epd_clear_area(areaPRIV);cursor_x = 695; cursor_y = 320; write_string((GFXfont *)&FiraSans, "    Reveal\n    Private \n      Keys", &cursor_x, &cursor_y, NULL);epd_poweroff();time_now = millis();}
                if(state == 1){time_now = millis();reset_buffer();epd_poweron();epd_draw_rect(360, 280, 240, 160, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(),framebuffer);epd_clear_area(areaADDR);cursor_x =45; cursor_y = 320; write_string((GFXfont *)&FiraSans, "    Reveal\n    Watch\n    Wallet", &cursor_x, &cursor_y, NULL);epd_poweroff();time_now = millis();}
                if(state == 2){time_now = millis();reset_buffer();epd_poweron();epd_draw_rect(685, 280, 240, 160, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(),framebuffer);epd_clear_area(areaXPUB); cursor_x = 350; cursor_y = 320; write_string((GFXfont *)&FiraSans, "      Reveal\n      Public\n    Address 1", &cursor_x, &cursor_y, NULL);epd_poweroff();time_now = millis();}
            }   

    if(button[0].clicks == 2)
            {   
                if(state > 2){state = 0;};
                if(state == 0){time_now = millis();reset_buffer();epd_poweron();epd_clear();INNER=true;XPUB_QR();time_now = millis();} 
                if(state == 1){time_now = millis();reset_buffer();epd_poweron();epd_clear();INNER=true;ADDRESS1_QR();time_now = millis();} 
                if(state == 2){time_now = millis();reset_buffer();epd_poweron();epd_clear();INNER=true;PRIVATE_QR();time_now = millis();} 
                state++;
            } 
  
  
  if(button[0].clicks == 4){reset_buffer();epd_poweron();epd_clear();epd_poweroff();button[0].Update();ESP.restart();}
}
if (millis() >= time_now + period){ESP.restart();}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void generate_infinite_print()
{reset_buffer();epd_poweron();epd_clear();epd_poweroff();button[0].Update();
cursor_x = 400; cursor_y = 280; write_string((GFXfont *)&FiraSans, "INFINITE\nPRINTING", &cursor_x, &cursor_y, NULL);epd_poweroff();
  
  
  
while(1)

{

    const uint8_t pklen = 32;
    uint8_t pkbytes[pklen];

    bootloader_random_enable(); /*key to true random number generation, uses analog noise and other sources for entropy*/
    for (uint8_t i = 0; i < pklen; i++)
    {
        pkbytes[i] = generate_random_8bit();
    }
    bootloader_random_disable(); /*protects from wireless attack*/
    
    pkstr = "";
    for (uint8_t i = 0; i < pklen; i++)
    {
        if (pkbytes[i] <= 0x0f)
        {
            pkstr += "0";
        }
        pkstr += String(pkbytes[i], HEX);
    }
  
  
  String entropy = pkstr;
  phrase = generateMnemonic(12, entropy);
  pkstr = ""; entropy = "";

phra = String("Private Recovery Phrase:\n\n")+phrase;
PRIVATE = phrase.c_str();
PHR = phra.c_str();

HDPrivateKey root(phrase, ""); // using default empty password, fill quotes if you want a password added

ROOOT = root;
finger = root.fingerprint();
fing = finger.c_str();
HDPrivateKey account = root.derive("m/84'/0'/0'");

HDPublicKey xpub = account.xpub();
pubx = account.xpub();
//Serial.println(pubx);
BWxpub = "["+finger+"/84h/0h/0h"+"]"+pubx;
//Serial.println(BWxpub);
XXPUB = BWxpub.c_str();

      String desc = ""; //watch wallet for Bitcoin Core
      desc = "wpkh([";
      // add fingerprint
      desc += root.fingerprint();
      // add derivation path. We need to remove leading `m`
      desc += "/84h/0h/0h]";
      // now pub xpub in normal form
      xpub.type = UNKNOWN_TYPE;
      desc += xpub.toString();
      desc += "/0/*)";
      // and add a checksum
      desc += String("#")+descriptorChecksum(desc);
      //Serial.println(desc);

      String desc2 = "";
      desc2 = "wpkh([";
      // add fingerprint
      desc2 += root.fingerprint();
      // add derivation path. We need to remove leading `m`
      desc2 += "/84h/0h/0h]";
      // now pub xpub in normal form
      xpub.type = UNKNOWN_TYPE;
      desc2 += xpub.toString();
      desc2 += "/1/*)";
      // and add a checksum
      desc2 += String("#")+descriptorChecksum(desc2);
      //Serial.println(desc2);

HDPublicKey pub1;
HDPublicKey pub2;
HDPublicKey pub3;
HDPublicKey pub4;

pub1 = xpub.child(0).child(1); //this will show as Address 2
//Serial.println(pub1.address());

pub2 = xpub.child(0).child(2); //this will show as Address 3
//Serial.println(pub2.address());

pub3 = xpub.child(0).child(3); //this will show as Address 4
//Serial.println(pub3.address());

pub4 = xpub.child(0).child(0); //this will show as Address 1 -- I KNOW THIS IS DUMB, BUT I DID THIS IN THE BEGINNING, AND I AM TOO LAZY TO CARE NOW.
//Serial.println(pub4.address());

pu1 = String("Public Address 2:\n\n")+String(pub1.address());
pu2 = String("Public Address 3:\n\n")+String(pub2.address());
pu3 = String("Public Address 4:\n\n")+String(pub3.address());
pu4 = String("Public Address 1:\n\n")+String(pub4.address());

P1 = pu1.c_str();
P2 = pu2.c_str();
P3 = pu3.c_str();
P4 = pu4.c_str();

PB1 = pub1.address();
PBL1 = PB1.c_str();

PB2 = pub2.address();
PBL2 = PB2.c_str();

PB3 = pub3.address();
PBL3 = PB3.c_str();

PB4 = pub4.address();
PBL4 = PB4.c_str();



printTHIS();
}
}

void menunav()
{
  
  if(state == 0)
    {
    epd_poweron();  
    epd_draw_rect(30, 100, 280, 100, 0, framebuffer);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer); 
    cursor_x = 700; cursor_y = 350;
    epd_clear_area(area6);
    write_string((GFXfont *)&FiraSans, "  Trigram\n   Printer", &cursor_x, &cursor_y, NULL);
    reset_buffer();
    epd_poweroff();
    }

  if(state == 1)
    {
    epd_poweron();  
    epd_draw_rect(348, 100, 280, 100, 0, framebuffer); 
    epd_draw_grayscale_image(epd_full_screen(), framebuffer); 
    cursor_x = 20; cursor_y = 140;
    epd_clear_area(area1);
    write_string((GFXfont *)&FiraSans, "  Create Wallet\n      No Print", &cursor_x, &cursor_y, NULL);
    reset_buffer();
    epd_poweroff();
    }
  
  if(state == 2)
    {
    epd_poweron();  
    epd_draw_rect(675, 100, 240, 100, 0, framebuffer); 
    epd_draw_grayscale_image(epd_full_screen(), framebuffer); 
    cursor_x = 338; cursor_y = 140;
    epd_clear_area(area2);
    write_string((GFXfont *)&FiraSans, "  Create Wallet\n        Print", &cursor_x, &cursor_y, NULL);
    reset_buffer();
    epd_poweroff();
    }

  if(state == 3)
    {
    epd_poweron();  
    epd_draw_rect(30, 310, 280, 100, 0, framebuffer); 
    epd_draw_grayscale_image(epd_full_screen(), framebuffer); 
    cursor_x = 700;cursor_y = 140;
    epd_clear_area(area3);
    write_string((GFXfont *)&FiraSans, "   Signer\n  Raw TX", &cursor_x, &cursor_y, NULL);
    reset_buffer();
    epd_poweroff();
    }

  if(state == 4)
    {
    epd_poweron();  
    epd_draw_rect(348, 310, 280, 100, 0, framebuffer); 
    epd_draw_grayscale_image(epd_full_screen(), framebuffer); 
    cursor_x = 20;cursor_y = 350;
    epd_clear_area(area4);
    write_string((GFXfont *)&FiraSans, "          OTP\n    Alpha Print", &cursor_x, &cursor_y, NULL);
    reset_buffer();
    epd_poweroff();
    }

  if(state == 5)
    {
    epd_poweron();  
    epd_draw_rect(675, 310, 240, 100, 0, framebuffer); 
    epd_draw_grayscale_image(epd_full_screen(), framebuffer); 
    epd_clear_area(area5);
    cursor_x = 338; cursor_y = 350;
    write_string((GFXfont *)&FiraSans, "          OTP\n  Numeric Print", &cursor_x, &cursor_y, NULL);
    reset_buffer();
    epd_poweroff();
    }
}
;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////MAIN MENU + CHOICES
void signer()
{
time_now = millis();
reset_buffer(); epd_poweron(); epd_clear();
cursor_x = 20; cursor_y = 140; write_string((GFXfont *)&FiraSans, "Insert SD Card with Recovery Phrase \n& Click Left Button", &cursor_x, &cursor_y, NULL); 
epd_poweroff();
  
     time_now = millis();
     while (millis() < time_now + period)
     {
      button[0].Update();
      if(button[0].clicks == 1){break;}
     }
time_now = millis();
////////////////////////////////////////// SD CARD
    SPI.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);
    SdFat SD;
    if (!SD.begin(SD_CS, SD_SCK_MHZ(10))) 
      {reset_buffer(); epd_poweron(); epd_clear();cursor_x =750; cursor_y = 60; write_string((GFXfont *)&FiraSans, "No SD Fat", &cursor_x, &cursor_y, NULL);epd_poweroff(); delay(6000); ESP.restart(); } 
   
      else
      {
            delay(100);
            File myFile = SD.open("PHRASE.txt");
            while (myFile.available())
            {
              finalString += (char)myFile.read();
            }
            myFile.close();
            
            int strlength = finalString.length();
            String finalfinal = finalString.substring(0,(strlength-0));
            delay(100);
            Serial.println(finalfinal);
            PHRS = finalfinal.c_str();
            
            strlength=0;

            //determine if using an xprv or a bip39 phrase
            if(finalfinal.indexOf(" ")>-1)
            {root = HDPrivateKey(PHRS,"");}
            else{HDPrivateKey root(PHRS);}
            
            finalString="";
            HDPrivateKey account = root.derive("m/84'/0'/0'");
//            Serial.println(root);
//            Serial.println(root.fingerprint());
            finger = root.fingerprint();
//            Serial.println(account);
//            Serial.println(account.xpub());
            
            HDPublicKey xpub = account.xpub();
            pubx = account.xpub();
//            Serial.println(pubx);
            XXPUBS = pubx.c_str();
//            Serial.println(XXPUBS);


                  String desc = "";
                  desc = "wpkh([";
                  // add fingerprint
                  desc += root.fingerprint();
                  // add derivation path. We need to remove leading `m`
                  desc += "/84h/0h/0h]";
                  // now pub xpub in normal form
                  xpub.type = UNKNOWN_TYPE;
                  desc += xpub.toString();
                  desc += "/0/*)";
                  // and add a checksum
                  desc += String("#")+descriptorChecksum(desc);
                  //Serial.println(desc);
            
                  String desc2 = "";
                  desc2 = "wpkh([";
                  // add fingerprint
                  desc2 += root.fingerprint();
                  // add derivation path. We need to remove leading `m`
                  desc2 += "/84h/0h/0h]";
                  // now pub xpub in normal form
                  xpub.type = UNKNOWN_TYPE;
                  desc2 += xpub.toString();
                  desc2 += "/1/*)";
                  // and add a checksum
                  desc2 += String("#")+descriptorChecksum(desc2);
                  //Serial.println(desc2);

                  if(!SD.begin(SD_CS, SD_SCK_MHZ(16)))
                  {Serial.println("whatever");}
                  else 
                  {
                  delay(100);
                  SD.remove("COREWATCH.txt");
                  myFile = SD.open("COREWATCH.txt", FILE_WRITE);
                  myFile.println(desc);
                  myFile.println(desc2);
                  myFile.print(XXPUBS);
                  myFile.close();
                  Serial.println("COREWATCH text written to SD");
                  }
      }

delay(100);
String fingers = "\nCheck Fingerprint for Verification:  "+finger+"\n\nStep 1: Remove SD card with Recovery Phrase\n\n\Step 2: Press Top Left Button to continue";
const char* fingersconst = fingers.c_str();
reset_buffer(); epd_poweron(); epd_clear();cursor_x = 20; cursor_y = 140; write_string((GFXfont *)&FiraSans, fingersconst, &cursor_x, &cursor_y, NULL);epd_poweroff();


     time_now = millis();
     while (millis() < time_now + period)
     {
      button[0].Update();
      if(button[0].clicks == 1){break;}
     }
time_now = millis();

reset_buffer(); epd_poweron(); epd_clear();cursor_x = 20; cursor_y = 140; 
write_string((GFXfont *)&FiraSans, "Step 1: Insert SD card with PSBT\n           from External Wallet\n\n\nStep 2: Press Top Left Button to continue", &cursor_x, &cursor_y, NULL);
epd_poweroff();


     time_now = millis();
     while (millis() < time_now + period)
     {
      button[0].Update();
      if(button[0].clicks == 1){break;}
     }
time_now = millis();     

//  //////////////READ PSBT FROM BLUEWALLET & SIGN IT AND WRITE IT TO SD
//  ////////////////////////////////////////////////////need to put a button step here to allow SD Swapping
//      //////////////////////////////////////////
      if(!SD.begin(SD_CS, SD_SCK_MHZ(16)))
      {
        reset_buffer(); epd_poweron(); epd_clear();cursor_x = 20; cursor_y = 140; 
        write_string((GFXfont *)&FiraSans, "Check for SD Fat format, not Fat32. \nIf formatted correctly,\n you may need to reseat the SD Card.", &cursor_x, &cursor_y, NULL);
        epd_poweroff();delay(6000);ESP.restart();
      }

      else
      {
            delay(100);
            File myFile = SD.open("This.psbt");
            while (myFile.available())
            {
              psbtString += (char)myFile.read();
            }
            myFile.close();}
delay(100);
int strlength = psbtString.length();
String finalpsbt = psbtString;
Serial.println(finalpsbt);
const char* signedpsbt = finalpsbt.c_str();
psbtString="";
strlength=0;

////////////////////////
//psbt.parseBase64("");
//psbt.parseBase64("");
psbt.parseBase64(signedpsbt);
Serial.print("ROOTCHECK: ");
Serial.println(root);
if(!psbt){
        reset_buffer(); epd_poweron(); epd_clear();cursor_x = 20; cursor_y = 140; 
        write_string((GFXfont *)&FiraSans, "PSBT format incorrect. \nCheck wallet settings for \nfingerprint and derivation. \n\nResetting now.", &cursor_x, &cursor_y, NULL);
        epd_poweroff();delay(6000);ESP.restart();
  }
  
uint8_t zero[4] = { 0 };
for(unsigned int i = 0; i < psbt.tx.inputsNumber; i++){
    for(unsigned int j = 0; j < psbt.txInsMeta[i].derivationsLen; j++){
        // check if psbt has zero fingerprint, if so - fill ours instead
        if(memcmp(psbt.txInsMeta[i].derivations[j].fingerprint, zero, 4) == 0){
            root.fingerprint(psbt.txInsMeta[i].derivations[j].fingerprint);
        }
    }
}


  Serial.println("Transactions details:");
  // going through all outputs to print info
  Serial.println("Outputs:");
  for(int i=0; i<psbt.tx.outputsNumber; i++){
    if(i==0)
    { transaction += "RECEIVING ADDRESS:\n";};
    if(i==1)
    { transaction += "\nWALLET ADDRESS:\n";};
    // print addresses
    Serial.println(i);
    Serial.print(psbt.tx.txOuts[i].address(&Mainnet));
    transaction += String(psbt.tx.txOuts[i].address(&Mainnet));
    transaction += "\n\n";
    if(psbt.txOutsMeta[i].derivationsLen > 0){ // there is derivation path
      // considering only single key for simplicity
      PSBTDerivation der = psbt.txOutsMeta[i].derivations[0];
      HDPublicKey pub = root.derive(der.derivation, der.derivationLen).xpub();
      if(pub.address() == psbt.tx.txOuts[i].address()){
        Serial.print(" (change) ");
      }
    }
    Serial.print(" -> ");
    Serial.print(psbt.tx.txOuts[i].btcAmount()*1e3);
    Serial.println(" mBTC");
//    Serial.println(psbt.tx.txOuts[i].btcAmount()*1000000);
    if(i==0)
    {transaction += "SEND AMOUNT -> ";
    transaction += String(psbt.tx.txOuts[i].btcAmount()*1000000*100,0);
    transaction += " Sats\n";}

    if(i==1)
    {
      if(pub.address() == psbt.tx.txOuts[i].address()){
      transaction += "LEFTOVER IN WALLET -> ";
      transaction += String(psbt.tx.txOuts[i].btcAmount()*1000000*100,0);
      transaction += " Sats\n";
        }
      else {transaction += "LEFTOVER IN WALLET -> ";
      transaction += String(psbt.tx.txOuts[i].btcAmount()*1000000*100,0);
      transaction += " Sats\n";}
    }
  }
  Serial.print("Fee: ");
  Serial.print(float(psbt.fee())/100); // Arduino can't print 64-bit ints
  Serial.println(" bits");


if(transaction.indexOf("LEFTOVER") == -1)
{transaction += "LEFTOVER IN WALLET ->  0 Sats\n";}

transaction += "\nFEE: ";
transaction += String(float(psbt.fee())/100);
transaction += " bits\n";

transaction += "\n------------------------\n\nPress Left Button to Sign";

//Serial.println(transaction);
const char* PSBTdetails = transaction.c_str();
//Serial.println(PSBTdetails);


        reset_buffer(); epd_poweron(); epd_clear();cursor_x = 20; cursor_y = 40; 
        write_string((GFXfont *)&OpenSans12B, PSBTdetails, &cursor_x, &cursor_y, NULL);
        epd_poweroff();delay(3000);

time_now = millis();
while (millis() < time_now + period)
{
button[0].Update();
if(button[0].clicks == 1){break;}
}
time_now = millis();

  psbt.sign(root);
  Serial.println(psbt.toBase64());

  String signedthat = psbt.toBase64();
  Serial.println(signedthat);
  /////////////////////////////////////////////////////////////////////////////////////////////
  SD.remove("that.psbt");
  File  myFile = SD.open("that.psbt", FILE_WRITE);
  myFile.print(signedthat);
  myFile.close();


        reset_buffer(); epd_poweron(); epd_clear();cursor_x = 20; cursor_y = 140; 
        write_string((GFXfont *)&FiraSans, "\n\nRemove SD card\nwith signed PSBT.", &cursor_x, &cursor_y, NULL);
        epd_poweroff();delay(10000);

 
ESP.restart();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void options()
{    state=0;
     time_now = millis();
     while (millis() < time_now + period)
     {button[0].Update();
       if(button[0].clicks == 1)
            {   state++;
                if(state > 5){state = 0;};
                menunav();
                time_now = millis();
            }     

        if(button[0].clicks == 2)
        {
          if(state == 0){generate_wallet();}
          if(state == 1){generate_wallet_print();}
          if(state == 2){signer();}
          if(state == 3){ALPHAOTP();}
          if(state == 4){NUMEROTP();}
          if(state == 5){TRIGRAMENCODE();}
        }     

        if(button[0].clicks == 3)
        { PRINTIT++;
          if(PRINTIT == 2){reset_buffer();epd_poweron();epd_fill_circle(70, 500, 15, 0, framebuffer);epd_fill_circle(120, 500, 15, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(), framebuffer);epd_poweroff();time_now = millis();}
          if(PRINTIT == 3){reset_buffer();epd_poweron();epd_fill_circle(170, 500, 15, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(), framebuffer);epd_poweroff();time_now = millis();}
          if(PRINTIT == 4){reset_buffer();epd_poweron();epd_fill_circle(220, 500, 15, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(), framebuffer);epd_poweroff();time_now = millis();}
          if(PRINTIT == 5){reset_buffer();epd_poweron();epd_fill_circle(270, 500, 15, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(), framebuffer);epd_poweroff();time_now = millis();}
          
          if(PRINTIT == 6){reset_buffer();epd_poweron();epd_fill_circle(390, 500, 15, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(), framebuffer);epd_poweroff();time_now = millis();}
          if(PRINTIT == 7){reset_buffer();epd_poweron();epd_fill_circle(440, 500, 15, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(), framebuffer);epd_poweroff();time_now = millis();}
          if(PRINTIT == 8){reset_buffer();epd_poweron();epd_fill_circle(490, 500, 15, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(), framebuffer);epd_poweroff();time_now = millis();}
          if(PRINTIT == 9){reset_buffer();epd_poweron();epd_fill_circle(540, 500, 15, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(), framebuffer);epd_poweroff();time_now = millis();}
          if(PRINTIT == 10){reset_buffer();epd_poweron();epd_fill_circle(590, 500, 15, 0, framebuffer);epd_draw_grayscale_image(epd_full_screen(), framebuffer);epd_poweroff();time_now = millis();}
          if(PRINTIT == 11){PRINTIT=1;hiddenmenu();}
        }
    
    
        
        if(button[0].clicks == 4){reset_buffer();epd_poweron();epd_clear();epd_poweroff();button[0].Update();break;}  

        if(button[0].clicks == 6){generate_infinite_print();}
      } 

quoter();
//loop();
}

void hiddenmenu()
{reset_buffer();
epd_poweron();
epd_clear();

cursor_x = 20;
cursor_y = 140;
        //epd_clear_area(area1);
        write_string((GFXfont *)&FiraSans, "  Create Wallet\n      No Print", &cursor_x, &cursor_y, NULL); 

cursor_x = 338;
cursor_y = 140;
        //epd_clear_area(area2);
        write_string((GFXfont *)&FiraSans, "  Create Wallet\n        Print", &cursor_x, &cursor_y, NULL); 
        
cursor_x = 700;
cursor_y = 140;
        //epd_clear_area(area3);
        write_string((GFXfont *)&FiraSans, "   Signer\n  Raw TX", &cursor_x, &cursor_y, NULL);

cursor_x = 20;
cursor_y = 350;
        //epd_clear_area(area4);
        write_string((GFXfont *)&FiraSans, "          OTP\n    Alpha Print", &cursor_x, &cursor_y, NULL);

cursor_x = 338;
cursor_y = 350;
        //epd_clear_area(area5);
        write_string((GFXfont *)&FiraSans, "          OTP\n  Numeric Print", &cursor_x, &cursor_y, NULL);

cursor_x = 700;
cursor_y = 350;
        //epd_clear_area(area6);
        write_string((GFXfont *)&FiraSans, "  Trigram\n   Printer", &cursor_x, &cursor_y, NULL);

//////epd_draw_rect(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t color, uint8_t *framebuffer);
//// rectangle 1    void epd_draw_rect(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t color, uint8_t *framebuffer);
    epd_draw_rect(30, 100, 280, 100, 0, framebuffer);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);    

epd_poweroff();

options();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{

    framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);
//    if (!framebuffer) {
//        Serial.println("alloc memory failed !!!");
//        while (1);
//    }
    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);

    epd_init();
//    Serial.begin(115200);

    
    Serial0.begin(9600);  // Initialize HardwareSerial for Printer
    delay(100);
    printer.begin();        // Init printer (same regardless of serial type)

    
    
PB1.reserve(400);
PB2.reserve(400);
PB3.reserve(400);
PB4.reserve(400);
finger.reserve(400);
BWxpub.reserve(400);
pu1.reserve(400);
pu2.reserve(400);
pu3.reserve(400);
pu4.reserve(400);
phra.reserve(400);
phrase.reserve(400);
ROOOT.reserve(400);
pubx.reserve(400);
finalString.reserve(400);
psbtString.reserve(400);
OTPLine.reserve(30000);

quoter();
}

void loop() {

button[0].Update();

if (button[0].clicks == 1){quoter();}
if (button[0].clicks == 4){hiddenmenu();}




}
