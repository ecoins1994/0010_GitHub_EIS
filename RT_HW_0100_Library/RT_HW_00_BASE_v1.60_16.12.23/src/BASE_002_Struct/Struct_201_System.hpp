 #include "RT_HW_BASE.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						1.Структуры для системных параметров 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
//=================================================================================================
//						1.1.Структура рабочих буферов (объекты создаются в RT_HW_BASE.h)
//=================================================================================================				  
struct RT_HW_STRUCT_BUFF	{uint8_t bf8,vu8; int8_t vi8; int16_t vi16; uint16_t bf16,vu16; uint32_t vu32;};
struct RT_HW_STRUCT_INDEX	{uint8_t i,j,m;};
//=================================================================================================
//						1.2.Структуры системных параметров (структуры используются в RT_HW_STRUCT_DEVICE)
//=================================================================================================
struct RT_HW_STRUCT_BOARD   {uint8_t  codeArch=255, codeBoard=255; 
							 uint8_t  permitCheckPin=0;								//--Флаг разрешения проверки допустимости использования пина;					 
                             uint16_t vccCPU=3300; uint16_t freqCPU=8;};			//--Параметры контр.(архитектура и пр.);
struct RT_HW_STRUCT_PWM   	{uint8_t  qntChannel=16; uint16_t channel; uint8_t idx; uint16_t freq;}; 	//--Макс.кол-во каналов,биты занятости каналов, частота;
struct RT_HW_STRUCT_TIMER   {uint8_t  qnt=16;        uint16_t busy=0;}; //--Макс.кол-во таймеров,биты занятости таймеров;
struct RT_HW_STRUCT_DEPTH 	{uint8_t  sys=12, adc=10, adcDrift=0, adcNull=0, tch=0, pwm=8, dac=0;};  	//--Разрешения устройств и дрейфы ADC;
struct RT_HW_STRUCT_PIN_SPI {uint8_t  cs0=255,     cs1=255,   cs2=255,    cs3=255,    cs4=255,   cs5=255, cs6=255, cs7=255,	//--Тестовые пины  SPI->cs0-7;
                                      busETH=255,  csETH=255, intETH=255, busCAN=255, csCAN=255, intCAN=255;};					//--Тестовые bus,пины  SPI->ETH,CAN;
struct RT_HW_STRUCT_PIN_GPIO{uint8_t  control=255, led=255,  button=255, ws2812=255, debug=255;
                             uint8_t  adc=255,     pwm=255,  dac=255,    servo=255;
                             uint8_t  adc1=255,    pwm1=255, dac1=255,   servo1=255;};	//--Номера пинов платы;
struct RT_HW_STRUCT_PIN_TFT {uint8_t  bus=255,     cs=255,   dc=255,     led=255;};		//--Номер шины SPI и номера пинов дисплея TFT; 
struct RT_HW_STRUCT_PIN_DEV {uint8_t  oneWire=255, dht22=255,sr04=255;};	//--Тестовые пины устройств->1-Wire(ds1820),DHT22,HC-SR04.echo,HC-SR04.trig;
struct RT_HW_STRUCT_NUM_UART{uint8_t  console,     modbus1=255, modbus2=255, nextion=255, wifi=255, eth1=255, eth2=255, device=255;};	//--Номера UART; 
//=================================================================================================
//						1.3.Обобщенная структура системных устройств (объект создается в RT_HW_BASE.h)
//=================================================================================================
struct RT_HW_STRUCT_DEVICE{
RT_HW_STRUCT_BOARD      board;	//--Параметры контроллера (архитектура и пр.);
RT_HW_STRUCT_DEPTH		depth;	//--Разрешения устройств и дрейфы ADC;
RT_HW_STRUCT_PWM 		pwm;	//--PWM  ->макс.кол-во каналов, биты занятости каналов, частота;
RT_HW_STRUCT_TIMER  	timer;  //--Timer->макс.кол-во таймеров,биты занятости таймеров;
RT_HW_STRUCT_PIN_SPI 	spi;	//--Тестовые пины SPI->cs0,cs1,cs2,cs3;
RT_HW_STRUCT_PIN_GPIO  	pin;	//--Номера пинов платы;
RT_HW_STRUCT_PIN_TFT 	tft;	//--Номер шины SPI и номера пинов дисплея TFT; 
RT_HW_STRUCT_PIN_DEV 	dev;	//--Данные для работы с устройствами 1-Wire,bus WS2812,HC-SR04.Echo,HC-SR04.Trig,DHT22;
RT_HW_STRUCT_NUM_UART 	uart;	//--Номер UART; 
};
//=================================================================================================
//						2.1.Структура для работы с консолью (объект создается в RT_HW_BASE.h)
// dir-этапы настройки консоли; 
// ok-флаг готовности консоли; 
// head-флаг разрешения вывода заголовков (включается на один цикл при ok=1); 
// all-разрешение вывода после вывода заголовков;
// numUart: =0-8-аппаратные UART; =9-программный UART;  
//=================================================================================================
struct RT_HW_STRUCT_CONSOLE {
uint8_t dir=0; 
uint8_t run=0;
uint8_t ok=0; 
uint8_t head=0; 
uint8_t all=0; 
uint8_t numUart=0; 
uint8_t bf8; 
uint8_t i; 
uint8_t idxOk,idx;
uint8_t lenText,lenBuff;
uint8_t arr[10];
};
//=================================================================================================
//						2.2.Структуры для работы с сообщениями (объект создается в RT_HW_BASE.h)   
//=================================================================================================	
struct RT_HW_STRUCT_MESS {
uint8_t size=0;					//--Размер формируемого поля;
char 	agoAlig,    alig='L';  	//--Выравнивание в поле ('N',L','C','R');
char 	agoBlank,   blank=' ';	//--Код символа заполнителя;
char 	agoSignBit, signBit='1';//--Код набора символов  при выводе в битовой форме ('0','1'...'9');
char 	orderBit='F'; 			//--Порядок вывода битов при выводе в битовой форме;  
char 	modePin='T';   			//--Форматы вывода номера пина: D-десятичный, T-текстовый,   A-комбинированный;
char 	modeAdr='T';   			//--Форматы вывода адреса  i2c: D-десятичный, H-шестнадцат., A-комбинированный;
char    modeVar='B';			//--Формат переменной B,W,L,F,R,C,S;
char    mode='Z';				//--Формат вывода P,A,X,T,C,F,B,H,U,I,Z,z,0,1,2,3;
char    separator=',';			//--Разделитель. Используется при выводе массивов;
uint8_t qntBit=8;				//--Кол-во выводимых бит при выводе в битовой форме;
//--------------------------------------------------------------------------------------------------
uint8_t lenPin=3;	  			//--Длина поля для выводимого пина;
char    suff='~';				//--Суффикс;
uint8_t lenSuff,lenCR,hexShort=0;//--Длина mess.str,длины заполнителей до и после mess.str;
uint8_t lenVar,lenBegin,lenEnd;	//--Длины заполнителей до и после mess.str;
uint8_t bf8;					//--Рабочий регистр;
uint8_t index;					//--Индекс для выбора символов RT_HW_READ_BYTE_PGM(RT_HW_ARR_BOOL_SIGN_x,index);
uint8_t idx;					//--Рабочий индекс для реализации циклов;
uint8_t adx=255;				//--Индекс для вывода массивов переменных;
uint8_t qnt;					//--Рабочее кол-во; 
String  str;			    	//--Формируемая строка;
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						3.Структура для преобразования числа в символы
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct RT_HW_BASE_VAL_ID {uint32_t val; uint16_t len:4, index:4, num:4, mess:4; uint8_t mode:2,minus:1,point:2,pnt:1;};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						4.Структура для callback
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef void(*CallBack)(void);
//=================================================================================================

