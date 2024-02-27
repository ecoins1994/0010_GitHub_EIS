
#if defined(ARDUINO_ARCH_STM32)
//=================================================================================================
//						2.1.КЛАСС для работы с внутренним RTC STM3232
//                    (объект с именем unixTime создается в RT_HW_BASE.h)
//=================================================================================================
class   RT_HW_CLASS_STM32_RTC{
public:
uint8_t  custom=0, isInit=0;
    bool isInit = false;
    uint32_t startReadTime = 0;
    uint32_t reqestPeriod = 250;
uint32_t timeUNIX;         				//--1.Время в сек от 01.01.1970г. по Гринвичу;
int16_t  zone=3;                    	//--2.Номер часового пояса. Если это от 1 по 12, то это показание в минутах;
uint8_t  hours,minutes,seconds;      	//--3.Время:часы,минуты,секунды;
uint8_t  day,month,weekDay,year2;       //--4.Дата: день,месяц,день недели,две младших цифры в годе;
uint16_t year;							//--5.Год,;
uint16_t w0,w1,w2;
uint8_t  b0,b1,b2;
uint32_t d0,d1,d2;
uint8_t  idx;
//-------------------------------------------------------------------------------------------------
systemRTC(){;};
void stm32RtcPool(RT_HW_STRUCT_STM32_RTC_ID &id){(void)id;}
void stm32RtcReadTime(RT_HW_STRUCT_STM32_RTC_ID &id){
if (!id.isInit){initDevice();}
uint8_t year, month, data, day, hour, minute, second;
uint32_t subSec;
hourAM_PM_t period;
    RTC_GetDate(&year, &month, &data, &day);
    RTC_GetTime(&hour, &minute, &second, &subSec, &period);
    now.second = second;
    now.minute = minute;
    now.hour = hour;
    now.day = day;
    now.date = data;
    now.month = month;
    now.year = year;
    startCalculationTime = millis();
}

void initDevice(){RTC_init(HOUR_FORMAT_24, LSE_CLOCK, false); isInit = true;}

/*
void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t date, uint8_t month, uint8_t year, uint8_t day)
{
    RTC_SetTime(hours, minutes, seconds, 0, HOUR_AM);
    RTC_SetDate(year, month, date, day);
    readTime();
}
*/
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#else
//-------------------------------------------------------------------------------------------------		

#endif
//-------------------------------------------------------------------------------------------------	