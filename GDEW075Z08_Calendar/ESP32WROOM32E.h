// 電源與系統控制
#define VDD33     3    // 3.3V 電源輸出 (不可用作 GPIO)
#define GND       1    // 地 (不可用作 GPIO)
#define EN        4    // 使能 (Enable)
 
// 模擬輸入（ADC）
#define SENSOR_VP 36   // IO36, ADC1_CH0
#define SENSOR_VN 39   // IO39, ADC1_CH3
#define GPIO34   34   // IO34, ADC1_CH6

//偵測電壓相關
#define WAKE_IO   25   // IO25, 控制 Q5/Q6 用於電池監測
#define ADC_BAT 36     // 用於測量電池電壓
 
// 主要 GPIO 分配
#define GPIO0     0    // IO0, 用於 Boot Mode (必須注意影響)
#define GPIO1     1    // IO1, TX0 (USB 串列 TX)
#define GPIO2     2    // IO2, LED 指示燈 / Flash Mode
#define GPIO3     3    // IO3, RX0 (USB 串列 RX)
#define GPIO4     4    // IO4, 可作為通用 GPIO
#define GPIO5     5    // IO5, SPI CS (建議可用)
 
// SPI 接口
#define SPI_CLK   18   // IO18, SPI Clock
#define SPI_MISO  19   // IO19, SPI MISO
#define SPI_MOSI  23   // IO23, SPI MOSI
#define SPI_CS    5    // IO5, SPI CS
 
// I2C 接口
#define I2C_SDA   21   // IO21, I2C SDA
#define I2C_SCL   22   // IO22, I2C SCL
 
// UART 接口
#define UART0_TX  1    // IO1, UART0 TX (USB 串口)
#define UART0_RX  3    // IO3, UART0 RX (USB 串口)
#define UART2_TX  17   // IO17, UART2 TX
#define UART2_RX  16   // IO16, UART2 RX
 
// SDIO / SD 卡接口
#define SD_CMD    15   // IO15, SD Command
#define SD_CLK    14   // IO14, SD Clock
#define SD_DATA0  2    // IO2, SD Data 0
#define SD_DATA1  4    // IO4, SD Data 1
#define SD_DATA2  12   // IO12, SD Data 2
#define SD_DATA3  13   // IO13, SD Data 3
 
// E-Paper (電子紙) 屏幕控制
#define EPD_BUSY  17   // IO17, EPD 忙碌狀態
#define EPD_RST   16   // IO16, EPD 重置
#define EPD_DC    19   // IO19/MISO, EPD 資料/指令  
#define EPD_CS    5    // IO5, EPD 片選
#define EPD_CLK   18   // IO18, SPI CLK
#define EPD_DIN   23   // IO23, SPI MOSI
 
// 按鍵與外部控制
#define IO34      34   // IO34, 按鍵 2
#define IO35      35   // IO35, 按鍵 3
#define IO39      39   // IO39, 按鍵 4
 
// 其他可用 GPIO
#define GPIO13    13   // IO13, 可用 GPIO
#define GPIO26    26   // IO26, 可用 GPIO
#define GPIO27    27   // IO27, 可用 GPIO

#define SHT30_ADDR 0x44  // SHT30 I2C 地址
//#define BL8025T_ADDR 0x32  // BL8025T 的 I2C 地址  0x32  <--沒有這個東西
