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

  WiFi.setSleep(true);//關閉不必要的WIFI功能
  pinMode(WAKE_IO, OUTPUT); //預設不讀取電壓
  digitalWrite(WAKE_IO, LOW); //LOW HIGH
  analogReadResolution(12);  // 設定 ADC 解析度 設定為 12-bit（0 ~ 4095）
  analogSetAttenuation(ADC_11db);// 設定 ADC 衰減，使其支援 3.3V 量測
  //先初始化時間
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




unsigned long lastProcessTime = 0;
void loop()
{
  //delay(5000);
  ButtonB.tick();
  ButtonC.tick();
  ButtonD.tick();
  delay(100);

  unsigned long now = millis();
  if (now - lastProcessTime > 1000) {  // 每 1s 執行一次
    lastProcessTime = now;
    //getVoltage();
    if(mode == 2){ // 選擇到主畫面 ，每一分鐘醒來即可
      // 啟用 Light-sleep 模式
       tm timeinfo = checkRTCTime();
       onlnyUpdateRight(timeinfo);
       delay(100);
       esp_sleep_enable_timer_wakeup(1000000ULL * 40); // 設置喚醒時間（微秒）
       esp_light_sleep_start(); 
       //esp_deep_sleep_start(); //深層睡眠相當於重新啟動了
    }
  }

}





