#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_3C.h>
//字形
#include <ESP32WROOM32E.h>
#include <U8g2_for_Adafruit_GFX.h>
//#include <EEPROM.h>
#include <WiFiManager.h>
#include <OneButton.h>
#include <Preferences.h>
#include <time.h>
#include "font.c"
#include "Date.h"
#include <ArduinoJson.h>

using namespace std;
#if defined(ESP32) && defined(USE_HSPI_FOR_EPD)
SPIClass hspi(HSPI);
#endif


GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT / 2> display(GxEPD2_750c_Z08(/*CS=5*/ 5, /*DC=*/ 19, /*RST=*/ 16, /*BUSY=*/ 17)); // GDEW075Z08 800x480, GD7965
//#define GxEPD2_DRIVER_CLASS GxEPD2_750c_Z08 // GDEW075Z08  800x480, EK79655 (GD7965), (WFT0583CZ61)

//https://hackmd.io/@Shinjia/ByYd0XXo8/%2FGTu9Ew4EQHKXpcwWC2uLGQ
//display.drawBitmap(0, 0, bmp_image, 128, 64, GxEPD_BLACK); // 畫圖


//宣告其他ino檔的副程式
//APMode.ino
void showAPModePage();
void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void text18(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void text40(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void textCh(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void textCh26(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void textCh34(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void textNum(const char *str, int16_t x, int16_t y, uint16_t fg_color , uint16_t bg_color );
void textNumBig(const char *str, int16_t x, int16_t y, uint16_t fg_color , uint16_t bg_color );
void textTitle(const char *str, int16_t x, int16_t y, uint16_t fg_color , uint16_t bg_color ) ;
void textBattery19(const char *str, int16_t x, int16_t y, uint16_t fg_color , uint16_t bg_color ) ;
void chineseZodiac32(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void textChDoubleime(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);

typedef struct
{
    String temperature;
    String humidity;
} StructTemperature;

//MainMode 
void showMainModePage();
StructTemperature getTemperature();
String getVoltage();
void setRTC(int year, int month, int day, int hour, int min, int sec) ;
tm getRTCTime();
tm checkRTCTime();
void onlnyUpdateRight(tm timeinfo);
void drawMonth(StructDayData *iStructDayData);
String getVoltageString();

//ButtonController
void ButtonBClick();
void ButtonCClick();
void ButtonDClick();
void ButtonDLongPress();


