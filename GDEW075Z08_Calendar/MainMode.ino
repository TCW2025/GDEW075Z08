
using namespace std;

void showMainModePage(){

 // display.setPartialWindow(200, 100, 500, 200 );
  display.setFullWindow();
  display.firstPage(); 
  display.fillScreen(GxEPD_WHITE);
  //更新時間
  tm timeinfo = checkRTCTime();

  StructLunarDate  iStructLunarDate =  gregorian_to_lunar ( timeinfo.tm_year, timeinfo.tm_mon, timeinfo.tm_mday);
  StructTemperature iStructTemperature = getTemperature();
  StructDayData *iStructDayData = print_monthly_calendar(timeinfo.tm_year, timeinfo.tm_mon);

  do {  

    // 畫中間分隔線
    display.drawLine(570, 0, 570, display.height(), GxEPD_BLACK);

    // 畫右邊的水平分隔線
    display.drawLine(570, 180, display.width(), 180, GxEPD_BLACK);

    //畫星期底色
    display.fillRect(0, 80, 80, 40, GxEPD_RED);

    display.fillRect(80, 80, 480, 40, GxEPD_BLACK);

    display.fillRect(480, 80, 90, 40, GxEPD_RED);

    // 畫左邊框的水平分隔線
    display.drawLine(0, 80, 570, 80, GxEPD_BLACK);

    display.drawLine(0, 120, 570, 120, GxEPD_BLACK);

    drawToDoList(timeinfo, iStructDayData);

    drawMonth(timeinfo, iStructDayData);

    drawWeekTitle();

    drawTime(timeinfo, iStructTemperature);

    drawDateTitle(timeinfo, iStructLunarDate);


  } while (display.nextPage());
  display.powerOff();

  //先釋放空間
  delete[] iStructDayData;
  iStructDayData = nullptr; 

}

void drawMonth(tm timeinfo, StructDayData *iStructDayData){
  for(int i =0 ; i< 7 * 6 ; i++){
    String lunarDate = String(iStructDayData[i].iStructLunarDate.lunarHoliday.name.c_str());
    if( lunarDate.length() == 0 ){
        lunarDate = String(iStructDayData[i].iStructLunarDate.solarTerm.c_str());
    } 
    if( lunarDate.length() == 0 ){
        lunarDate = String(iStructDayData[i].holiday.name.c_str());
    } 
    if( lunarDate.length() == 0 ){
        lunarDate = String(iStructDayData[i].iStructLunarDate.day.c_str());
    }
    String day = String(iStructDayData[i].day) ;
    int dayX = day.length()==1 ? 5 : 0;

    uint16_t bg_color = GxEPD_WHITE;
    uint16_t fg_color = ( i % 7 == 0 || i % 7 == 6 || iStructDayData[i].holiday.off || iStructDayData[i].iStructLunarDate.lunarHoliday.off)?GxEPD_RED:GxEPD_BLACK;

    if(String(timeinfo.tm_year) == String(iStructDayData[i].year) &&  String(timeinfo.tm_mon) == String(iStructDayData[i].month)  && String(timeinfo.tm_mday) == String(iStructDayData[i].day)){
      uint16_t tmp  = bg_color;
      bg_color = fg_color;
      fg_color = tmp;
      display.fillRect((i % 7) * 81 - 5, 125 + ( i/7 * 58 ), 85, 60, bg_color);
      textCh(iStructDayData[i].holiday.name.c_str(), 420 , 68 , GxEPD_BLACK, GxEPD_WHITE); 
    }

    text18(day.c_str(), 20 + (i % 7) * 81 + dayX, 150 + ( i/7 * 58 ) , fg_color, bg_color); 
    textCh(lunarDate.c_str(), 20 + (i % 7) * 81 , 170 + ( i/7 * 58 ) , fg_color, bg_color); 
  }
}



void onlnyUpdateRight(tm timeinfo){
  StructTemperature iStructTemperature = getTemperature();
  //如果到跨日 00:00 & 00:01 則需要設定到prefs(防止斷電)
  if(updatePrefsTime(timeinfo)){
    showMainModePage();
    return;
  }

  display.setPartialWindow(580, 0, 230, 180 );
  display.fillScreen(GxEPD_WHITE);
  display.firstPage();
  do {
    //display.fillRect(575, 5, 225, 175, GxEPD_WHITE);
    drawTime(timeinfo, iStructTemperature);
  } while (display.nextPageBW());
  display.powerOff();
}



void drawDateTitle(tm timeinfo, StructLunarDate  iStructLunarDate){
  String title = "西元";
  String mon = String(timeinfo.tm_mon);
  if( mon.length() == 1 ){
    mon = "0" + mon;
  }
  String day = String(timeinfo.tm_mday);
  if( day.length() == 1 ){
    day = "0" + day;
  }
  title = title + String(timeinfo.tm_year) + "年 " + mon + "月" + day +"日";
  textCh26(title.c_str(), 10, 40, GxEPD_BLACK, GxEPD_WHITE); 

  mon = String(iStructLunarDate.month.c_str());
  
  title = "農曆: ";
  title = title + String(iStructLunarDate.heavenlyStems.c_str()) + String(iStructLunarDate.earthlyBranches.c_str()) + "年  " + mon + String(iStructLunarDate.day.c_str()) ;
  title = title + " " + String(iStructLunarDate.lunarHoliday.name.c_str()) ;
  textCh(title.c_str(), 25, 68, GxEPD_BLACK, GxEPD_WHITE); 

  title = String(iStructLunarDate.zodiac.c_str()) + "年";
  textCh34(title.c_str(), 400, 45, GxEPD_RED, GxEPD_WHITE); 

}

void drawWeekTitle(){
    // 填充左邊中間框框的底色為黑色
    textCh26("日", 20, 115, GxEPD_WHITE, GxEPD_RED); 
    textCh26("一", 105, 115, GxEPD_WHITE, GxEPD_BLACK);
    textCh26("二", 180, 115, GxEPD_WHITE, GxEPD_BLACK); 
    textCh26("三", 260, 115, GxEPD_WHITE, GxEPD_BLACK); 
    textCh26("四", 340, 115, GxEPD_WHITE, GxEPD_BLACK); 
    textCh26("五", 420, 115, GxEPD_WHITE, GxEPD_BLACK); 
    textCh26("六", 500, 115, GxEPD_WHITE, GxEPD_RED);   
}

// 回傳：-1 (輸入時間較小), 0 (相同), 1 (輸入時間較大)
int compareDate(int yyyy, int mm, int dd, struct tm timeStruct) {
    if (yyyy < (timeStruct.tm_year )) return -1;
    if (yyyy > (timeStruct.tm_year )) return 1;

    if (mm < (timeStruct.tm_mon )) return -1;
    if (mm > (timeStruct.tm_mon )) return 1;

    if (dd < timeStruct.tm_mday) return -1;
    if (dd > timeStruct.tm_mday) return 1;

    return 0;  // 完全相等
}

void drawLightGrayFillRect(int x, int y, int w, int h) {
  for (int dx = 0; dx < w; dx++) {
    for (int dy = 0; dy < h; dy++) {
        if ((dx % 3 == 0) && (dy % 3 == 0)) {  
            display.drawPixel(x + dx, y + dy, GxEPD_BLACK);  // 只有部分像素是黑色
        } else {
            display.drawPixel(x + dx, y + dy, GxEPD_WHITE);  // 其他都是白色
        }
    }
  }
}

void drawToDoList(tm timeinfo, StructDayData *iStructDayData) {
    int index = 0;
    String sToDoList = prefs.getString("todos");  // 取得存儲的 JSON 字串
    //Serial.println(sToDoList);
    StaticJsonDocument<800> doc;
    JsonArray sortedArray;

    if (sToDoList.length() == 0) {
        //Serial.println("No ToDo list data found.");
        return ;
    }

    DeserializationError error = deserializeJson(doc, sToDoList);
    if (error) {
       // Serial.print("JSON Parsing Failed: ");
       // Serial.println(error.c_str());
        return ;
    }

    JsonArray todoList = doc.as<JsonArray>();

    for (JsonObject obj : todoList) {
        // **檢查 JSON 物件是否包含必要欄位**
        if (!obj.containsKey("date") || !obj.containsKey("name")) {
           // Serial.println("Error: JSON object missing 'date' or 'name'.");
            continue;
        }

        String date = obj["date"].as<String>();
        String name = obj["name"].as<String>();

        // **檢查 date 格式 (避免長度錯誤)**
        if (date.length() < 10) {
           // Serial.println("Error: Invalid date format.");
            continue;
        }

        // **解析日期**
        int yyyy = date.substring(0, 4).toInt();
        int mm = date.substring(5, 7).toInt();
        int dd = date.substring(8, 10).toInt();

        // **比對時間，篩選符合條件的 ToDo**
        if (compareDate(yyyy, mm, dd, timeinfo) > -1) {
            String displayText = date + " : " + name;
            textCh(displayText.c_str(), 580, 200 + index * 30, GxEPD_BLACK, GxEPD_WHITE);
            index++;
        }

        //本月有代辦事項的畫底色
        for(int i =0 ; i< 7 * 6 ; i++){
          if( iStructDayData[i].year == yyyy && iStructDayData[i].month ==  mm && iStructDayData[i].day == dd){
              drawLightGrayFillRect((i % 7) * 81 - 5, 125 + ( i/7 * 58 ), 85, 60);
          }
        }
    }
}


void drawTime(tm timeinfo, StructTemperature iStructTemperature){
  String hour = String(timeinfo.tm_hour);
  if( hour.length() == 1  ){
    hour = "0" + hour;
  }
  String min = String(timeinfo.tm_min);
  if( min.length() == 1  ){
    min = "0" + min;
  }
  hour = hour + ":" + min;
  textNumBig(hour.c_str(), 585, 100, GxEPD_BLACK, GxEPD_WHITE); 

  hour = "溫度:";
  hour = hour + iStructTemperature.temperature + " C  濕度:" + iStructTemperature.humidity + "%";
  textCh(hour.c_str(), 585, 130, GxEPD_BLACK, GxEPD_WHITE); 

  float voltage = getVoltage().toFloat();
  float index = (voltage - 3.1) / (3.89 - 3.1) * 100.0 ;
  hour = "電量:" + String(voltage, 3) + "V , " + String(index, 0) + "%";
  textCh(hour.c_str(), 585, 155, GxEPD_BLACK, GxEPD_WHITE); 
}


bool updatePrefsTime(tm timeinfo){
  if((timeinfo.tm_min == 0 || timeinfo.tm_min == 1) && timeinfo.tm_hour == 0){
    //每天00:00 & 00:01 則需要設定到prefs(防止斷電)
    prefs.putString("year",String(timeinfo.tm_year));
    prefs.putString("month",String(timeinfo.tm_mon));
    prefs.putString("day",String(timeinfo.tm_mday));
    prefs.putString("time","00:00");
    prefs.end();
    return true;
  }
  return false;
}

tm checkRTCTime(){
  prefs.begin("Calendar");
  struct tm timeinfo = getRTCTime();
  if( prefs.getInt("set",0) == 0 ){
    Serial.println("沒有設定時間，無法復原");
  } else if( timeinfo.tm_year == 70 ){
    Serial.println("因為應該是重啟了，所以要處理時間");
    String str = prefs.getString("time");
    int commaIndex = str.indexOf(':');
    String hour = str.substring(0, commaIndex);
    String min = str.substring(commaIndex + 1);
    setRTC(prefs.getString("year").toInt(),prefs.getString("month").toInt(),prefs.getString("day").toInt(), hour.toInt() , min.toInt(), 0) ;
    //重新取得時間 印出確認沒問題
    timeinfo = getRTCTime();
  }else{
    Serial.println("RTC時間還在，所以不處理時間");
  }
  return timeinfo;
}



StructTemperature getTemperature(){

    StructTemperature iStructTemperature;
    Wire.begin(I2C_SDA, I2C_SCL, 50000);
    sht30_wake();
    Wire.beginTransmission(SHT30_ADDR);
    Wire.write(0x2C);
    Wire.write(0x06);
    Wire.endTransmission();
    delay(100);  // 等待感測器處理數據
    Wire.requestFrom(SHT30_ADDR, 6);
    if (Wire.available() == 6) {

        uint16_t rawTemp = (Wire.read() << 8) | Wire.read();
        Wire.read();  // 忽略 CRC
        uint16_t rawHum = (Wire.read() << 8) | Wire.read();
        Wire.read();  // 忽略 CRC

        float temperature = -45.0 + (175.0 * ((float)rawTemp / 65535.0));
        float humidity = 100.0 * ((float)rawHum / 65535.0);

        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C, Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");

        iStructTemperature.temperature = String(temperature, 1);
        iStructTemperature.humidity = String(humidity, 1);

    } else {
        Serial.println("Failed to read from SHT30");
    }
    sht30_sleep();
    Wire.end();  // 關閉 I2C，降低功耗
    return iStructTemperature;
}



void sht30_sleep() {
    Wire.beginTransmission(SHT30_ADDR);
    Wire.write(0x30);
    Wire.write(0x93);  // 進入睡眠模式指令
    Wire.endTransmission();
}

void sht30_wake() {
    Wire.beginTransmission(SHT30_ADDR);
    Wire.write(0x30);
    Wire.write(0xA2);  // 喚醒 SHT30
    Wire.endTransmission();
}

String getVoltage(){
  //先開啟讀取電壓
  pinMode(WAKE_IO, OUTPUT);
  digitalWrite(WAKE_IO, HIGH); 
  //等待通電
  delay(100);
  int raw = analogRead(ADC_BAT);
  float voltage = (raw / 4095.0) * 3.3 * 2;  //3.86
  Serial.println(voltage);
  //關閉電壓
  pinMode(WAKE_IO, OUTPUT);
  digitalWrite(WAKE_IO, LOW); 
  return String(voltage);
}



void setRTC(int year, int month, int day, int hour, int min, int sec) {
    struct tm timeinfo;
    timeinfo.tm_year = year - 1900;  // tm_year 需要從 1900 開始算
    timeinfo.tm_mon  = month - 1;    // tm_mon 需要從 0 開始
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min  = min;
    timeinfo.tm_sec  = sec;

    time_t t = mktime(&timeinfo);  // 轉換為 time_t
    struct timeval now = { .tv_sec = t, .tv_usec = 0 };
    settimeofday(&now, NULL);  // 設定 ESP32 內部 RTC
}

tm getRTCTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      Serial.println("無法獲取 RTC 時間");
    }else{
      timeinfo.tm_year = timeinfo.tm_year +1900;
      timeinfo.tm_mon = timeinfo.tm_mon + 1;
      Serial.printf("當前 RTC 時間：%04d-%02d-%02d %02d:%02d:%02d\n", 
                    timeinfo.tm_year, timeinfo.tm_mon, timeinfo.tm_mday, 
                    timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    }
    return timeinfo;
}

uint32_t getChipTemperature(){
	//Serial.println(" °C");
	return temperatureRead();
}