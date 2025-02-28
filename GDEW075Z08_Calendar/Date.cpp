#include "Date.h"
#include <stdio.h>
#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string.h>

using namespace std;


string lunarMonth[]= {" ","正月","二月","三月","四月","五月","六月","七月","八月","九月","十月","冬月","臘月"};
string lunarDay[]= {"零","一","二","三","四","五","六","七","八","九","十"};
string lunarDay2[]= {"初","十","廿","卅"};

/** 農歷查詢表  來源：https://www.jianshu.com/p/57e7bd43c00b
 *  Ox0c950     是5個16進制數，共20bit
 *  第1位       表示假如有閏月，0代表閏小月，1代表閏大月
 *  第2-4位     表示12個二進制位 一位表示一個月是大月還是小月
 *  第5位       表示閏哪個月，0表示不閏
 */
unsigned int sg_lunarCalendar[141] =
{

    0x0c950,/*1939年*/   /*查詢公歷1940年1月，農歷其實是1939年*/
    0x0d4a0,0x1d8a6,0x0b550,0x056a0,0x1a5b4,0x025d0,0x092d0,0x0d2b2,0x0a950,0x0b557, /* 1940 ~1949 */
    0x06ca0,0x0b550,0x15355,0x04da0,0x0a5d0,0x14573,0x052d0,0x0a9a8,0x0e950,0x06aa0, /* 1950 ~1959 */
    0x0aea6,0x0ab50,0x04b60,0x0aae4,0x0a570,0x05260,0x0f263,0x0d950,0x05b57,0x056a0, /* 1960 ~1969 */
    0x096d0,0x04dd5,0x04ad0,0x0a4d0,0x0d4d4,0x0d250,0x0d558,0x0b540,0x0b5a0,0x195a6, /* 1970 ~1979 */
    0x095b0,0x049b0,0x0a974,0x0a4b0,0x0b27a,0x06a50,0x06d40,0x0af46,0x0ab60,0x09570, /* 1980  */
    0x04af5,0x04970,0x064b0,0x074a3,0x0ea50,0x06b58,0x055c0,0x0ab60,0x096d5,0x092e0, /* 1990  */
    0x0c960,0x0d954,0x0d4a0,0x0da50,0x07552,0x056a0,0x0abb7,0x025d0,0x092d0,0x0cab5, /* 2000  */
    0x0a950,0x0b4a0,0x0baa4,0x0ad50,0x055d9,0x04ba0,0x0a5b0,0x15176,0x052b0,0x0a930, /* 2010  */
    0x07954,0x06aa0,0x0ad50,0x05b52,0x04b60,0x0a6e6,0x0a4e0,0x0d260,0x0ea65,0x0d530, /* 2020  */
    0x05aa0,0x076a3,0x096d0,0x04bd7,0x04ad0,0x0a4d0,0x1d0b6,0x0d250,0x0d520,0x0dd45, /* 2030  */
    0x0b5a0,0x056d0,0x055b2,0x049b0,0x0a577,0x0a4b0,0x0aa50,0x1b255,0x06d20,0x0ada0, /* 2040  */
    0x14B63,0x09370,0x049f8,0x04970,0x064b0,0x168a6,0x0ea50,0x06b20,0x1a6c4,0x0aae0, /* 2050  */
    0x0a2e0,0x0d2e3,0x0c960,0x0d557,0x0d4a0,0x0da50,0x05d55,0x056a0,0x0a6d0,0x055d4, /* 2060  */
    0x052d0,0x0a9b8,0x0a950,0x0b4a0,0x0b6a6,0x0ad50,0x055a0,0x0aba4,0x0a5b0,0x052b0 /* 2070 - 2079 */
};


/** 通式壽星公式 計算二十四節氣  公式來源：https://www.jianshu.com/p/1f814c6bb475*/
// 21世紀C值
float C_value_21[]= {3.87,18.73,5.63,20.646,4.81,20.1,5.52,21.04,5.678,21.37,7.108,22.83,7.5,23.13,7.646,23.042,8.318,23.438,7.438,22.36,7.18,21.94,5.4055,20.12};
// 20世紀C值
float C_value_20[]= {4.6295,19.4599,6.3826,21.4155,5.59,20.888,6.318,21.86,6.5,22.2,7.928,23.65,28.35,23.95,8.44,23.822,9.098,24.218,8.218,23.08,7.9,22.6,6.11,20.84};
// 節氣基礎月
float C_month[]= {2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};

const char* temp[24]= {"立春","雨水","驚蟄","春分","清明","谷雨","立夏","小滿","芒種","夏至","小暑","大暑","立秋","處暑","白露","秋分","寒露","霜降","立冬","小雪","大雪","冬至","小寒","大寒"};




/**
 * 通過年份節氣，獲取對應具體日期
 */
StructsolarTerm get_solar_term(int year1, int tmp)
{
    StructsolarTerm iStructsolarTerm;
    int year,month,day;
    year=year1;
    // tmp 表示節氣順序
   

    if(tmp==0||tmp==1||tmp==22||tmp==23)
    {
        if(year>=2000)
        {
            month=C_month[tmp];
            day=floor((year%100)*0.2422+C_value_21[tmp])-floor((year%100-1)/4);
        }
        else
        {
            month=C_month[tmp];
            day=floor((year%100)*0.2422+C_value_20[tmp])-floor((year%100-1)/4);
        }
    }
    else
    {
        if(year>=2000)
        {
            month=C_month[tmp];
            day=floor((year%100)*0.2422+C_value_21[tmp])-floor((year%100)/4);
        }
        else
        {
            month=C_month[tmp];
            day=floor((year%100)*0.2422+C_value_20[tmp])-floor((year%100)/4);
        }
    }

    // 特殊情況
    if((year==2026 && tmp==1)||(year==1918 && tmp==21)||(year==2021 && tmp==21)||(year==2019 && tmp==22))
    {
        day--;
    }
    if((year==2084 && tmp==3)||(year==1911 && tmp==6)||(year==2008 && tmp==7)||(year==1902 && tmp==8)||(year==1928 && tmp==9)||(year==1925 && tmp==10)||(year==2016 && tmp==10)||(year==1922&& tmp==11)||(year==2002&&tmp==12)||(year==1927&&tmp==14)||(year==1942&&tmp==15)||(year==2089 && tmp==17)||(year==2089&&tmp==18)||(year==1978&&tmp==19)||(year==2054 && tmp==20)||(year==1982&&tmp==22)||(year==2000 && tmp==23)||(year==2082&&tmp==23))
    {
        day++;
    }
    if(C_month[tmp]>12)
    {
        month=1;
    }
    //cout<<temp[tmp]<<": ";
    // 根據公式計算的年月日，將其轉換為農歷
    //gregorian_to_lunar (year,month,day);
    iStructsolarTerm.month = month;
    iStructsolarTerm.day = day;
    iStructsolarTerm.year = year;
    return iStructsolarTerm;
}

StructsolarTerm* get_date_by_solar_term(int year){
    StructsolarTerm *allStructsolarTerm  = new StructsolarTerm[24];
    for(int i =0 ; i < 24 ;i++ ){
        StructsolarTerm iStructsolarTerm  = get_solar_term(year, i);
        iStructsolarTerm.solarTerm = temp[i];
        allStructsolarTerm[i] = iStructsolarTerm;
    }
    return allStructsolarTerm;
}


/**
 * 判斷year年是否是閏年
 */
bool is_leap_year(int year)
{
    // 可以被4且100整除或者可以被400整除
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

/**
 * 獲取year年month月有多少天
 */
int get_days_of_month(int year,int month)
{
    // 平年各月公歷天數
    int days[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
    if(is_leap_year(year)&&month==2)
        return 29;
    else
        return days[month-1];
}

/**
 * 獲取year年month月day日到1939年1月1日的天數
 */
int get_days_to_1939(int year,int month,int day)
{
    int days=0;
    // 從1939年開始計算,直到year-1年,它們都是整數年
    for(int i=year-1; i>=1939; i--)
    {
        if(is_leap_year(i))
            days+=366;
        else
            days+=365;
    }
    // 計算year年1月到year年month-1月,它們是整數月
    for(int i=month-1; i>0; i--)
    {
        days+=get_days_of_month(year,i);
    }
    // 計算year年month月1日到yera年month月day日天數
    days+=day;
    return days-1;
}

/**
 * 獲取year年month月day日是星期幾
 */
string get_str_day_of_week(int year,int month,int day)
{
    string weeks[7]= {"星期日","星期一","星期二","星期三","星期四","星期五","星期六"};
    // 獲取year年month月day日到1939年1月1日的天數
    int days=get_days_to_1939(year,month,day);
    int week=days%7;
    return weeks[week];
}
/**
 * 獲取year年month月day日是星期幾，整數版
 */
int get_day_of_week(int year,int month,int day)
{
    int days=get_days_to_1939(year,month,day);
    int week=days-(days/7)*7;
    return week;
}

/**
 * 檢查年月日合法性
 */
bool is_legal(int year,int month,int day)
{
    // 還需要判斷 year年month月  是否含day天，比如4月有30天，輸入31就是錯誤的
    return !(year<1939||year>2079||month<0||month>12||day<0||day>get_days_of_month(year,month));
}


/**
 * 判斷潤年閏月是大月還是小月
 */
bool is_large_month_of_leap_year(int year)
{
    // 查表找出是否為閏月 判斷high是不是為0
    int high =(sg_lunarCalendar[year-1939]>>16);
    if(high==0x00)
        return false;
    else
        return true;
}
/**
 * 返回 潤幾月  0代表不閏
 */
int get_nonth_of_leap_year(int year)
{
    // 輸出農歷潤幾月
    int month = sg_lunarCalendar[year-1939] & 0xF;
    return month;
}

/**
 * 判斷農歷某年某月多少天
 */
int get_days_of_lunar_month(int year,int month)
{
    // 查表，根據大小月，計算農歷月天數
    int bit=1 << (16-month);
    if((sg_lunarCalendar[year-1939]/*&0x0000FFFF*/&bit)==0)
        return 29;
    else
        return 30;
}

// 判斷某年農歷多少天
int get_days_of_lunar_year(int year)
{
    int days=0;
    // 農歷十二個月天數
    for(int i=1; i<=12; i++)
    {
        days+=get_days_of_lunar_month(year,i);
    }
    // 假如有閏月，加上閏月天數
    if(get_nonth_of_leap_year(year)!=0)
    {
        if(is_large_month_of_leap_year(year))
            days+=30;
        else
            days+=29;
    }
    return days;
}


/**
 * 輸入年份月份輸出月日歷表
 */
StructDayData * print_monthly_calendar(int year,int month)
{
    StructDayData * iStructDayData = new StructDayData[42];
    StructsolarTerm* structsolarTermArrayBefor = get_date_by_solar_term(year-1);
    StructsolarTerm* structsolarTermArray = get_date_by_solar_term(year);
    StructsolarTerm* structsolarTermArrayNew = get_date_by_solar_term(year+1);
    
    if(year>2079||year<1939||month>12||month<1)
    {
        cout<<"日期輸入出錯，請確保日期在1939-2079年之間"<<endl;
        return iStructDayData;
    }
    // 計算year年month月1日星期幾 ，星期日為 0  星期六為 6
    int week = get_day_of_week(year,month,1);
    int weekend = 0 ;//塞到最後是禮拜幾
    int days = 0 ;
    int temp_month = month ;
    int temp_year = year;
    int lastIndex = 0 ;
    if( week != 0 ){ //如果本月份不是剛好為禮拜天
        if( month == 1 ){ //如果遇到1月則要往前年看
            temp_year = temp_year -1;
            temp_month = 12 ;
            days = get_days_of_month(temp_year, 12);
        }else{
            temp_year = year;
            temp_month = temp_month -1;
            days = get_days_of_month(year, temp_month);
        }
        days = days -  week + 1;  
        for( int i = 0 ; i < week ; i++ ){
                iStructDayData[i].day = days;
                iStructDayData[i].month = temp_month;
                iStructDayData[i].year = temp_year;
                iStructDayData[i].iStructLunarDate = gregorian_to_lunar(temp_year, temp_month, days);
                iStructDayData[i].holiday = get_holiday(temp_month, days);
                if(temp_year == year){
                    iStructDayData[i].iStructLunarDate.solarTerm = get_lunar_solar_term_holiday(structsolarTermArray, temp_month, days);
                }else{
                    iStructDayData[i].iStructLunarDate.solarTerm = get_lunar_solar_term_holiday(structsolarTermArrayBefor, temp_month, days );
                }
                days++;
        }
        days = get_days_of_month(year,month);
        int day = 0;
        for( int i = week ; i <  week + days ; i++ ){
                day = i - week + 1 ;
                iStructDayData[i].day = day ;
                iStructDayData[i].month = month;
                iStructDayData[i].year = year;
                iStructDayData[i].iStructLunarDate = gregorian_to_lunar(year, month, day);
                iStructDayData[i].holiday = get_holiday(month, day);
                iStructDayData[i].iStructLunarDate.solarTerm = get_lunar_solar_term_holiday(structsolarTermArray, month, day);
        }
        
        lastIndex = week + days;
    }else{
        days = get_days_of_month(year,month);
        for( int i = 1 ; i <= days ; i++ ){
            iStructDayData[i-1].day = i ;
            iStructDayData[i-1].iStructLunarDate = gregorian_to_lunar(year, month, i);
            iStructDayData[i-1].month = month;
            iStructDayData[i-1].year = year;
            iStructDayData[i-1].holiday = get_holiday(month, i);
            iStructDayData[i-1].iStructLunarDate.solarTerm = get_lunar_solar_term_holiday(structsolarTermArray, month, i);
        }
        lastIndex = days ;
    }
    weekend = get_day_of_week(year, month, days);
    //星期日為 0  星期六為 6
    
    temp_month = month ;
    temp_year = year;
    if(month == 12){ //跨年
        temp_month = 1 ;
        temp_year = temp_year + 1 ;
    }else{
        temp_month = month + 1 ;
    }
    for( int i = 0 ; i <= 6 + (6 - weekend) ; i++ ){
            if( i + lastIndex >= 42)
                break;
            iStructDayData[i + lastIndex].day = i + 1 ;
            iStructDayData[i + lastIndex].iStructLunarDate = gregorian_to_lunar(temp_year, temp_month, i + 1);
            iStructDayData[i + lastIndex].month = temp_month;
            iStructDayData[i + lastIndex].year = temp_year;
            iStructDayData[i + lastIndex].holiday = get_holiday(temp_month, i + 1 );
            if(temp_year == year){
                iStructDayData[i + lastIndex].iStructLunarDate.solarTerm = get_lunar_solar_term_holiday(structsolarTermArray, temp_month, i + 1 );
            }else{
                iStructDayData[i + lastIndex].iStructLunarDate.solarTerm = get_lunar_solar_term_holiday(structsolarTermArrayNew, temp_month, i + 1 );
            }
    }

    return iStructDayData;
}

string get_lunar_solar_term_holiday(StructsolarTerm* structsolarTermArray, int month, int day){

    for(int i =0 ; i < 24 ;i++){
        if(structsolarTermArray[i].day == day  && structsolarTermArray[i].month == month){
             return structsolarTermArray[i].solarTerm;
        }
        if(!structsolarTermArray[i].solarTerm.compare("春分")){
            if( (15 - (31 - structsolarTermArray[i].day))  ==  day  && structsolarTermArray[i].month + 1 == month){
             return "清明節";
            }
        }
    }
    return "";
}

string get_holiday(int month, int day){
   
   if(month == 1 &&  day == 1){
     return "元旦";
   }
   if(month == 10 &&  day == 10){
     return "雙十節";
   }
   if(month == 4 &&  day == 4){
     return "兒童節";
   }
   if(month == 2 &&  day == 28){
     return "和平紀念日";
   }
   if(month == 12 &&  day == 25){
     return "聖誕節";
   }
   if(month == 10 &&  day == 31){
     return "萬聖節";
   }
   if(month == 5 &&  day == 1){
     return "勞動節";
   }
   if(month == 8 &&  day == 8){
     return "父親節";
   }
   return "";
}


/**
 * 輸出農歷日歷
 */
StructLunarDate print_lunar_date(int days)
{
    StructLunarDate iStructLunarDate;
    int year=1939,month=1,day=1;
    // 由於1939年1月1日往往是農歷1938年，所以減去48天，從1939年正月初一計算，因為本計算器計算範圍為1940年-2040年 所以可以滿足
    days-=48;

    // 判斷減去下一年的天數，會不會是負值，不是便減去並增加農歷年
    for(int i=1939; (days-get_days_of_lunar_year(i))>0; i++)
    {
        days-=get_days_of_lunar_year(i);
        year=i+1;
    }
    int num;
    int signal=0;
    // 判斷減去下一月天數，會不會是負值，不會便農歷月加1
    for(int j=1; ((days-get_days_of_lunar_month(year,j))>0)&&j<12; j++)
    {
        days-=get_days_of_lunar_month(year,j);
        if(j==get_nonth_of_leap_year(year))
        {
            if(is_large_month_of_leap_year(year))
            {
                days-=30;
                num=30;
            }
            else
            {
                days-=29;
                num=29;
            }
        }
        // 當減去農歷月的時候，加入變為負值，那麽再加回來
        if(days<0)
        {
            // 農歷閏月標記
            signal=1;
            days +=num;
            month=j;
            break;
        }
        month=month+1;
    }
    // 剩余天數便是農歷日
    day=days;
    //cout<<year<<"年";
    iStructLunarDate.year = std::to_string(year);
    iStructLunarDate.month =  "";

    if(signal==1){
       iStructLunarDate.month =  " 潤";
    }

    iStructLunarDate.month.append(lunarMonth[month]);

    //cout<<lunarMonth[month];

    if(day>0&&day<=10)
    {
        //cout<<"初"<<lunarDay[day];
        iStructLunarDate.day = "初";
        iStructLunarDate.day.append(lunarDay[day]);
    }
    else if(day>10&&day<20)
    {
        //cout<<"十"<<lunarDay[day%10];
        iStructLunarDate.day = "十";
        iStructLunarDate.day.append(lunarDay[day%10]);
    }
    else if(day==20)
    {
       // cout<<"二十";
        iStructLunarDate.day = "二十";
    }
    else if(day>20 && day<30)
    {
        //cout<<"廿"<<lunarDay[day%10];
        iStructLunarDate.day = "廿";
        iStructLunarDate.day.append(lunarDay[day%10]);
    }
    else if(day==30)
    {
        //cout<<"三十";
        iStructLunarDate.day = "三十";
    }
	
	string zodiac[12]= {"鼠","牛","虎","兔","龍","蛇","馬","羊","猴","雞","狗","豬"};
    
    //cout<<zodiac[(year-1900)%12];
    iStructLunarDate.zodiac = zodiac[(year-1900)%12];

    string heavenlyStems[10]= {"甲","乙","丙","丁","戊","己","庚","辛","壬","癸"};
    string earthlyBranches[12]= {"子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥"};


    iStructLunarDate.heavenlyStems = heavenlyStems[(year-1864)%10];
    iStructLunarDate.earthlyBranches = earthlyBranches[(year-1864)%12];
    iStructLunarDate.lunarHoliday = "";

    //盡量三個字
    if(month == 1 && day == 1)
    {    iStructLunarDate.lunarHoliday =  "春節";}
    else if(month == 1 && day == 15)
    {    iStructLunarDate.lunarHoliday =  "元宵節";}
    else if(month == 5 && day == 5)
    {    iStructLunarDate.lunarHoliday =  "端午節";}
    else if(month == 7 && day == 7)
    {    iStructLunarDate.lunarHoliday =  "七夕節";}
    else if(month == 7 && day == 15)
    {    iStructLunarDate.lunarHoliday =  "中元節";}
    else if(month == 8 && day == 15)
    {    iStructLunarDate.lunarHoliday =  "中秋節";}
    else if(month == 9 && day == 9)
    {    iStructLunarDate.lunarHoliday =  "重陽節";}
    else if(month == 12 && day == 8)
    {    iStructLunarDate.lunarHoliday =  "臘八節";}

    return iStructLunarDate;
}


/**
 * 取得農歷
 */
StructLunarDate gregorian_to_lunar (int year,int month,int day)
{

    int days=get_days_to_1939(year,month,day);
    // 根據天數打印農歷
    return print_lunar_date(days);
}

