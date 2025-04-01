

void ButtonBClick() {
  buttonClick(2);
}
void ButtonCClick() {
  buttonClick(3);
}
void ButtonDClick() {
  buttonClick(4);
}


void buttonClick(int index){
  Serial.println("showTextDemo");
  if( mode == 0 ) // 0 選擇模式
  {
    if(index==2)
      return;
    display.setPartialWindow(235, 250, 250, 100 );
    display.fillScreen(GxEPD_WHITE);
    display.firstPage();
    do {
      u8g2Fonts.setCursor(235, 220);
      if(index == 3 ){
        textCh("1. 選擇-進入設定模式", 235, 270, GxEPD_BLACK, GxEPD_WHITE); 
        textCh("2. 進入主系統模式", 235, 300,GxEPD_WHITE, GxEPD_WHITE); 
        selectMode = 1;
      }else if(index == 4 ){
        textCh("1. 進入設定模式", 235, 270, GxEPD_WHITE, GxEPD_WHITE); 
        textCh("2. 選擇-進入主系統模式", 235, 300,GxEPD_BLACK, GxEPD_WHITE); 
        selectMode = 2;
      }
    } while (display.nextPageBW());
    display.powerOff();
  }else if( mode = 2) {
    //主畫面模式  
    //showMainModePage();
     if(index == 2 ){
        showMainModePage();
     }else if(index == 3 ){
        tm timeinfo = checkRTCTime();
        if(timeinfo.tm_mon==1){
          timeinfo.tm_mon=12;
          timeinfo.tm_year--;
        }else{
          timeinfo.tm_mon--;
        }
        showNextPage(timeinfo);
     }else if(index == 4 ){
        tm timeinfo = checkRTCTime();
        if(timeinfo.tm_mon==12){
          timeinfo.tm_mon=1;
          timeinfo.tm_year++;
        }else{
          timeinfo.tm_mon++;
        }
        showNextPage(timeinfo);
     }
  }
}

void ButtonDLongPress()
{
  if( mode == 0 ) // 0 選擇模式
  {
    if( selectMode == 1 )
    {
       mode = 1;
      showAPModePage();
    } else {
      if( prefs.getInt("set",0) == 1 && selectMode == 2){
        mode = 2;
        showMainModePage();
      }
    }
  }else{
    buttonClick(4);
  }
}