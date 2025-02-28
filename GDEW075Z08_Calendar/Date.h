#include <string>

#ifndef DATE_H
#define DATE_H

using namespace std;


typedef struct
{
    string name = "";
    bool off  = false;
} Holiday;


//農曆回傳結構 by 天
typedef struct
{
    string year;
    string month;
    string day;
    string heavenlyStems; //天干
    string earthlyBranches; //地支
    string zodiac;//生肖
    Holiday lunarHoliday ; //農曆節日
    string solarTerm = "";  //二十四節氣名稱
} StructLunarDate;

typedef struct
{
    int year = 0 ;
    int month;
    int day;
    Holiday holiday;
    StructLunarDate iStructLunarDate ; //每一天的農曆日期
    bool notice = false;

} StructDayData;

typedef struct
{
    string solarTerm; //二十四節氣名稱
    int month; //西元的月份
    int day;   //西元的日
    int year;

} StructsolarTerm;


/**
 * 输入西元，給出月曆
 */
StructDayData * print_monthly_calendar(int year,int month);


/**
 * 輸入西元，給出農曆日期
 */
StructLunarDate gregorian_to_lunar (int year,int month,int day);

/**
 * 输入西元年份，輸出為二十四節氣西元時間
 */

StructsolarTerm* get_date_by_solar_term(int year);
StructsolarTerm get_solar_term(int year1, int tmp);

string get_lunar_solar_term_holiday(StructsolarTerm* structsolarTermArray, int month, int day);

int get_day_of_week(int year,int month,int day);
int get_days_of_month(int year,int month);
Holiday get_holiday(int month, int day);

#endif // DATE_H