
void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK) 
{
  bool r2l = false;
  int8_t baseline = 10;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(u8g2_font_lubI12_tr);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y , str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y + baseline, str);
  }
}

void text18(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK) 
{
  bool r2l = false;
  int8_t baseline = 10;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(u8g2_font_lubI18_tr);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y , str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y + baseline, str);
  }
}

void text40(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK)  
{
  bool r2l = false;
  int8_t baseline = 42;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(u8g2_font_lubI24_tf);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y , str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y + baseline, str);
  }
}

void textCh26(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK) 
{
  bool r2l = false;
  int8_t baseline = 42;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(u8g2_font_unifont_myfonts_26);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y , str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y , str);
  }
}


void chineseZodiac32(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK) 
{
  bool r2l = false;
  int8_t baseline = 42;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(ChineseZodiac32);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y , str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y , str);
  }
}

void textCh34(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK) 
{
  bool r2l = false;
  int8_t baseline = 42;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(u8g2_font_unifont_myfonts_34);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y , str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y , str);
  }
}


void textChDoubleime(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK) 
{
  bool r2l = false;
  int8_t baseline = 42;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(TWKai98_18);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y , str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y , str);
  }
}

void textCh(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK) 
{
  bool r2l = false;
  int8_t baseline = 42;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(u8g2_font_unifont_myfonts);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y , str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y , str);
  }
}

void textNumBig(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK)  
{
  bool r2l = false;
  int8_t baseline = 42;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(Seven_Segment_84);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y , str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y + baseline, str);
  }
}


void textNum(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK)  
{
  bool r2l = false;
  int8_t baseline = 42;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(u8g2_font_7Segments_26x42_mn);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y , str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y + baseline, str);
  }
}

void textTitle(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK) 
{
  bool r2l = false;
  int8_t baseline = 42;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(logo_24_35);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y , str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y + baseline, str);
  }
}



// 012345678 9
void textBattery19(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK)  
{
  bool r2l = false;
  int8_t baseline = 42;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(battery19);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y , str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y + baseline, str);
  }
}


