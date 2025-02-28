
可以使用這個網站直接轉文字(但是只有單一大小)
https://stonez56.com/u8g2/index.php#sampleCodes


自訂自型方式如下

找到你要的*.ttf檔案，並執行以下指令，其中p是指你要的大小
otf2bdf.exe x.ttf -p 26 -o x.bdf  -E unicode
在執行以下指令，匯出u8g2_font_unifont_myfonts_26.c檔案
bdfconv.exe -v x.bdf -b 0 -f 1 -M chinese1.map -d x.bdf -n u8g2_font_unifont_myfonts_26 -o u8g2_font_unifont_myfonts_26.c


