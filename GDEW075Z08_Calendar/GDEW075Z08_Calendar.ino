#include "GDEW075Z08_Calendar.h"

//用到的共用元件宣告
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
WiFiManager wifiManager;
Preferences prefs;

//全域變數
bool reset = false;
int selectMode = 0; // 1  選擇 1 , 2選擇 2
int mode = 0; // 0 選擇模式 1 設定模式 2 主系統模式


OneButton ButtonB(IO34, true);
OneButton ButtonC(IO35, true);
OneButton ButtonD(IO39, true);

void showSelectPage(tm timeinfo){
  do {  
    textTitle("E-Paper Calendar(offline)", 235, 100, GxEPD_BLACK, GxEPD_WHITE); 
    textCh34("請選擇模式:", 235, 160, GxEPD_BLACK, GxEPD_WHITE);  
    textCh("按鈕3、按鈕4為選擇鍵，長按按鈕4為確定鍵，按住三秒再放開", 235, 200, GxEPD_BLACK, GxEPD_WHITE); 
    if(prefs.getInt("set",0) == 0 ){
      textCh("*因為偵測到尚未輸入時間，請先選擇1", 235, 230, GxEPD_BLACK, GxEPD_WHITE);
    }
    textCh("1. 進入設定模式", 235, 270, GxEPD_BLACK, GxEPD_WHITE); 
    textCh("2. 進入主系統模式", 235, 300, GxEPD_BLACK, GxEPD_WHITE); 
    text12("Design by TCW", 340, 430, GxEPD_BLACK, GxEPD_WHITE);  
    String now = String(timeinfo.tm_year) + "年" + String(timeinfo.tm_mon) + "月"+ String(timeinfo.tm_mday) + "日 "+ String(timeinfo.tm_hour) + "時" + String(timeinfo.tm_min) + "分";
    if(prefs.getInt("BL8025T",0) == 1 ){
      now = now + "(BL8025T IC)";
    }
    textCh(now.c_str(), 500, 430, GxEPD_BLACK, GxEPD_WHITE);  
  } while (display.nextPage());
  display.powerOff();
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(100);
#if defined(ESP32) && defined(USE_HSPI_FOR_EPD)
//hspi->begin(HSPI_SCK, HSPI_MISO, HSPI_MOSI, SD_CS); 
  hspi.begin(18,19,23,5); 
  display.epd2.selectSPI(hspi, SPISettings(4000000, MSBFIRST, SPI_MODE0));
#endif
  display.init(115200, true, 2, false); 

  display.setFullWindow();
  display.firstPage(); 
  display.fillScreen(GxEPD_WHITE);

  u8g2Fonts.begin(display);
  u8g2Fonts.setFontDirection(0);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);  
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  

  prefs.begin("Calendar");

  ButtonB.attachClick(ButtonBClick);
  ButtonC.attachClick(ButtonCClick);
  ButtonD.attachClick(ButtonDClick);
  ButtonD.attachLongPressStop(ButtonDLongPress);

  //WiFi.setSleep(true);//關閉不必要的WIFI功能
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);//關閉WIFI功能
  pinMode(WAKE_IO, OUTPUT); //預設不讀取電壓
  digitalWrite(WAKE_IO, LOW); //LOW HIGH
  analogReadResolution(12);  // 設定 ADC 解析度 設定為 12-bit（0 ~ 4095）
  analogSetAttenuation(ADC_11db);// 設定 ADC 衰減，使其支援 3.3V 量測
  //先初始化時間
  haveBL8025T();
  tm timeinfo = checkRTCTime();

  // 檢查喚醒原因
  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0:
       Serial.println("Wakeup caused by external signal using RTC_IO");
       showMainModePage();
       break;
    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("Wakeup caused by timer");
      //這裡是從深層睡眠喚醒
      mode = 2;
      onlnyUpdateRight(timeinfo);
      break;
    default:
      Serial.println("Wakeup was not caused by deep sleep");
      //系統重啟
      showSelectPage(timeinfo);
      //showMainModePage();
      break;
  }

}
void haveBL8025T(){
  int sec, min, hour, day, month, year;
  Wire.begin(I2C_SDA, I2C_SCL);  
  Wire.beginTransmission(BL8025T_ADDR);
  Wire.write(0x00);  // 設定讀取寄存器起始位址（秒數寄存器）
  Wire.endTransmission();
  Wire.requestFrom(BL8025T_ADDR, 7);  // 讀取 7 個字節（秒、分、時、日、月、年）
  if (Wire.available() == 7) {
      sec   = bcdToDec((uint8_t)Wire.read() & 0x7F);
      min   = bcdToDec((uint8_t)Wire.read() & 0x7F);
      hour  = bcdToDec((uint8_t)Wire.read() & 0x3F);
      day   = bcdToDec((uint8_t)Wire.read() & 0x3F);
      month = bcdToDec((uint8_t)Wire.read() & 0x1F);
      year  = bcdToDec((uint8_t)Wire.read()) + 2000;
      Serial.printf("Time: %04d-%02d-%02d %02d:%02d:%02d\n", year, month, day, hour, min, sec);
      prefs.putInt("BL8025T",1);
      prefs.end();
  }
  Wire.end();  // 關閉 I2C，降低功耗
}

unsigned long lastProcessTime = 0;
void loop()
{
  ButtonB.tick();
  ButtonC.tick();
  ButtonD.tick();
  if ( lastProcessTime == 0){
     lastProcessTime = millis();
  }

  if(mode == 2){ // 選擇到主畫面 ，每一分鐘醒來即可
    // 啟用 Light-sleep 模式
      Serial.end();
      tm timeinfo = checkRTCTime();
      onlnyUpdateRight(timeinfo);
      esp_sleep_enable_timer_wakeup(1000000ULL * 60); // 設置喚醒時間（微秒）
      esp_light_sleep_start(); 
      //esp_deep_sleep_start(); //深層睡眠相當於重新啟動了，因為深度睡眠會影響螢幕部分更新，所以不用了
  }else{
    delay(10);
    //超3分鐘沒有動作就直接進去主畫面
    unsigned long now = millis();
    if (now - lastProcessTime > 1000 * 60 * 3) {
      mode = 2;
      showMainModePage(); 
    }
  }

}





