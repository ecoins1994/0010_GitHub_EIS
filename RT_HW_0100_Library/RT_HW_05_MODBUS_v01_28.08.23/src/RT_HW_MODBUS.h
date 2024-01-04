//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						БИБЛИОТЕКА ДЛЯ РАБОТЫ С MODBUS	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef RT_HW_MODBUS_h
#define RT_HW_MODBUS_h
//-------------------------------------------------------------------------------------------------
#include "RT_HW_BASE.h"						//--Подключение базовой библиотеки;
#define RT_HW_MODBUS_VER			11		//--Номер версии библиотеки;
#define RT_HW_MODBUS_MAX_DEVICE	  	8		//--Максимальнон кол-во допустимых устройств;
#define RT_HW_MODBUS_PERIOD_BLINK   50 		//--Период тиков для тактового генератора;
#define RT_HW_MODBUS_TIMEOUT_READ   100		//--Тайм-аут на принятие посылки;
#define RT_HW_MODBUS_BUFF_REG_SIZE  40		//--Размер приемного буфера посылки из Nextion (8 байт служебные);
#define RT_HW_MODBUS_WATCH_DOG_BUSY 10      //--Размер WatchDog(ms) при передаче транзакций;
//-------------------------------------------------------------------------------------------------
#define RT_HW_MODBUS_MAX_DATABIT 	2		//--Размер массива uint16_t (COLINS);
#define RT_HW_MODBUS_QNT_BIT 	    8       //--Размер массива bit(для COLINS);
#define RT_HW_MODBUS_QNT_BYTE       6		//--Размер массива uint8_t;
#define RT_HW_MODBUS_QNT_WORD       4		//--Размер массива uint16_t;
#define RT_HW_MODBUS_QNT_LONG       2		//--Размер массива uint32_t;
#define RT_HW_MODBUS_QNT_FLOAT      3		//--Размер массива float;

//=================================================================================================
//						    		I.СТРУКТУРЫ БАЗОВЫЕ						
//=================================================================================================
//--------------------------------------------------------------------------------------------------
//                    		1.1.Структура общих для всех устройств MODBUS данных
//--------------------------------------------------------------------------------------------------
struct  RT_HW_STRUCT_MODBUS_HIVE{ 
uint16_t set=0;								//--Флаги занятости устройства (устройства с номерами 1-15)
uint8_t  qnt=0; 							//--Кол-во зарегистрированных устройств;
uint32_t vr;
uint16_t dataBit  [RT_HW_MODBUS_MAX_DATABIT]; 	uint16_t regBit  [RT_HW_MODBUS_QNT_BIT ]; 	//--Тестовый массив bit(для COILS);
uint8_t  dataByte [RT_HW_MODBUS_QNT_BYTE ]; 	uint16_t regByte [RT_HW_MODBUS_QNT_BYTE ];	//--Тестовый массив uint8_t;
uint16_t dataWord [RT_HW_MODBUS_QNT_WORD ];		uint16_t regWord [RT_HW_MODBUS_QNT_WORD ];	//--Тестовый массив uint16_t;
uint32_t dataLong [RT_HW_MODBUS_QNT_LONG ];		uint16_t regLong [RT_HW_MODBUS_QNT_LONG ];	//--Тестовый массив uint32_t;
float    dataFloat[RT_HW_MODBUS_QNT_FLOAT];		uint16_t regFloat[RT_HW_MODBUS_QNT_FLOAT];	//--Тестовый массив float;
};
//=================================================================================================
//		         			1.2.Структура данных устройства
//=================================================================================================
struct  RT_HW_STRUCT_MODBUS_DEVICE{		   
//-----------------Основные параметры управления---------------------------------------------------
uint8_t  custom=0;				//--Код настройки: =0 не настраивался; =1 успешно настроен; >1 код ошибки настройки;
uint8_t  num=0; 				//--Номер устройства (от 1 до MAX_DEVICE).По этому номеру внешние блоки привязываются к устройству;
//-------------------------------------------------------------------------------------------------
uint8_t  ddr=0;					//--Этапы основной       программы управления устройствами;
uint8_t  dir=0;					//--Этапы основной       программы управления устройствами;
uint8_t  step;					//--Этапы дополнительной программы управления устройствами;
//-------------------------------------------------------------------------------------------------
uint8_t  busy=0;				//--Флаг занятости устройства (RT_HW_MODBUS.ptr[num]->busy);
uint8_t  blink=0, agoBlink=0;   //--Меандр 50мс        		  (RT_HW_MODBUS.ptr[num]->blink);
uint8_t  wdBusy=0;				//--Счетчик сторожевого таймера от зависания флага занятости busy);
//-----------------Параметры для работы с массивами данных-----------------------------------------
uint16_t lenBit  =RT_HW_MODBUS_QNT_BIT;		uint16_t *ptrDataBit;	uint16_t *ptrRegBit;	//--Параметры для массива для COLINS;
uint16_t lenByte =RT_HW_MODBUS_QNT_BYTE; 	uint8_t  *ptrDataByte;  uint16_t *ptrRegByte;	//--Параметры для массива для uint8_t;
uint16_t lenWord =RT_HW_MODBUS_QNT_WORD; 	uint16_t *ptrDataWord;  uint16_t *ptrRegWord;	//--Параметры для массива для uint16_t;
uint16_t lenLong =RT_HW_MODBUS_QNT_LONG; 	uint32_t *ptrDataLong;  uint16_t *ptrRegLong;	//--Параметры для массива для uint32_t;
uint16_t lenFloat=RT_HW_MODBUS_QNT_FLOAT; 	float    *ptrDataFloat; uint16_t *ptrRegFloat;	//--Параметры для массива для float;
//-------------------------------------------------------------------------------------------------
uint8_t  buff[RT_HW_MODBUS_BUFF_REG_SIZE];	//--Буфер для приема транзакции;
//-----------------Основные параметры управления---------------------------------------------------
uint8_t  codeErr;				//--Код ошибки;
//-----------------------------------------------------------------------------
uint8_t  readyRead:1;	//--Флаги; 
//----------------------------------------
uint32_t timeBeginGen;          //--Рабочий регистр для тактирующего генератора;
uint32_t timeBeginBusy;         //--Рабочий регистр для задержки флага busy;
uint32_t timeGet;				//--Рабочий регистр;
uint8_t	 timeOutGetByte=10;		//--Тайм-аут на прием очередного байта транзакции;
//---------------------------------------------------------------------------
uint8_t  index;					//--Счетчик кол-ва принятых байт;
uint8_t  head,func,adr,qnt,crc;
uint32_t crcCalc;
uint16_t cntGetPackAll; 		//--Счетчик принятых транзакций(всего);
uint16_t cntGetPackOk;			//--Счетчик принятых транзакций(успешных); 
uint16_t qntByte;
//-----------------------------------------
uint8_t  fresh=0;				//--Флаг обновления параметров структуры;
uint32_t vr;
//-----------------Параметры UART------------------------------
uint8_t  uart=255;				//--Номер UART;
uint32_t speed=115200;			//--Скорость UART;
uint8_t  ready=0;				//--Флаг успешной настройки UART;
};
//-------------------------------------------------------------------------------------------------
#include "0100_API_MODBUS/API_MODBUS_100_struct.hpp"           	//==Структуры данных;	




//=================================================================================================
//		                           КЛАСС: RT_HW_MODBUS
//=================================================================================================
class RT_HW_MODBUS{
public:
//------Данные-------------------------------------------------------------------------------------
RT_HW_STRUCT_MODBUS_HIVE	hive;								//--Общие данные для работы библиотеки;
RT_HW_STRUCT_MODBUS_DEVICE *ptr[RT_HW_MODBUS_MAX_DEVICE+1];		//==Массив указателей на данные со структурой устройств;
RT_HW_STRUCT_MODBUS_DEVICE  dvTest;							    //--Данные тестового устройства;
//-------------------------------------------------------------------------------------------------
//									1.Конструктор											
//-------------------------------------------------------------------------------------------------
RT_HW_MODBUS(){
hive.set=0x00; hive.qnt=0;
//-------------------------------------------------------------------------------------------------
for(int8_t i=0; i<=RT_HW_MODBUS_MAX_DEVICE;i++){								//--Заполнение указателей ссылкой на непустое устройство;
 ptr[i]=&dvTest; 																//--Запись указателя;
 ptr[i]->custom=0; ptr[i]->num=0;  					  							//--Запись параметров;
 ptr[i]->lenBit  =RT_HW_MODBUS_QNT_BIT;		ptr[i]->ptrDataBit  =hive.dataBit;	   	ptr[i]->ptrRegBit  =hive.regBit; 	//--Начальная запись параметров массива v8;
 ptr[i]->lenByte =RT_HW_MODBUS_QNT_BYTE;  	ptr[i]->ptrDataByte =hive.dataByte;		ptr[i]->ptrRegByte =hive.regByte;	//--Начальная запись параметров массива v8;
 ptr[i]->lenWord =RT_HW_MODBUS_QNT_WORD;  	ptr[i]->ptrDataWord =hive.dataWord;		ptr[i]->ptrRegWord =hive.regWord;	//--Начальная запись параметров массива v16;   
 ptr[i]->lenLong =RT_HW_MODBUS_QNT_LONG;  	ptr[i]->ptrDataLong =hive.dataLong;		ptr[i]->ptrRegLong =hive.regLong;	//--Начальная запись параметров массива v32;
 ptr[i]->lenFloat=RT_HW_MODBUS_QNT_FLOAT; 	ptr[i]->ptrDataFloat=hive.dataFloat;	ptr[i]->ptrRegFloat=hive.regFloat;	//--Начальная запись параметров массива float;
}};	
//-------------------------------------------------------------------------------------------------
//									2.Вывод параметров массивов											
//-------------------------------------------------------------------------------------------------
void printParamDevice(uint8_t num){
//if(!RT_HW_Base.console.ok){return;}
//if(!ptr[num]->fresh)      {return;} ptr[num]->fresh=0;
if(num>RT_HW_MODBUS_MAX_DEVICE){return;}
RT_HW_Base.consoleTest(String(F("Mosbus num")),num,':');
RT_HW_Base.consoleVar(String(F("len,adr,reg")),'E');
//-------------------------------------------------------------------------------------------------
RT_HW_Base.consoleVar(String(F("Bit  ")),':'); 
RT_HW_Base.consoleVar(getLen    (num,'R'),',',3,'U');
RT_HW_Base.consoleVar(getPtrData(num,'R'),',',0,'H'); 
RT_HW_Base.consoleVar(getPtrReg (num,'R'),';',0,'H'); 
RT_HW_Base.consoleTestArr(String(F(" num")),ptr[num]->ptrRegBit,',','U', ptr[num]->lenBit); 
RT_HW_Base.consoleCR();
//-------------------------------------------------------------------------------------------------
RT_HW_Base.consoleVar(String(F("Byte ")),':'); 
RT_HW_Base.consoleVar(getLen    (num,'B'),',',3,'U');
RT_HW_Base.consoleVar(getPtrData(num,'B'),',',0,'H'); 
RT_HW_Base.consoleVar(getPtrReg (num,'B'),';',0,'H'); 
RT_HW_Base.consoleTestArr(String(F(" num")),ptr[num]->ptrRegByte,';','U', ptr[num]->lenByte); 
//-------------------------------------------------------------------------------------------------
RT_HW_Base.consoleCR();RT_HW_Base.consoleVar(String(F("Word ")),':'); 
RT_HW_Base.consoleVar(getLen    (num,'W'),',',3,'U');
RT_HW_Base.consoleVar(getPtrData(num,'W'),',',0,'H'); 
RT_HW_Base.consoleVar(getPtrReg (num,'W'),';',0,'H'); 
RT_HW_Base.consoleTestArr(String(F(" num")),ptr[num]->ptrRegWord,';','U', ptr[num]->lenWord); 
RT_HW_Base.consoleCR();
//-------------------------------------------------------------------------------------------------
RT_HW_Base.consoleVar(String(F("Long ")),':'); 
RT_HW_Base.consoleVar(getLen    (num,'L'),',',3,'U');
RT_HW_Base.consoleVar(getPtrData(num,'L'),',',0,'H'); 
RT_HW_Base.consoleVar(getPtrReg (num,'L'),';',0,'H'); 
RT_HW_Base.consoleTestArr(String(F(" num")),ptr[num]->ptrRegLong,';','U', ptr[num]->lenLong); 
RT_HW_Base.consoleCR();
//-------------------------------------------------------------------------------------------------
RT_HW_Base.consoleVar(String(F("Float")),':'); 
RT_HW_Base.consoleVar(getLen    (num,'F'),',',3,'U');
RT_HW_Base.consoleVar(getPtrData(num,'F'),',',0,'H'); 
RT_HW_Base.consoleVar(getPtrReg (num,'F'),';',0,'H'); 
RT_HW_Base.consoleTestArr(String(F(" num")),ptr[num]->ptrRegFloat,';','U', ptr[num]->lenFloat); 
RT_HW_Base.consoleCR();


//hive.vr=(uint32_t)ptr[num]->ptrArrByte;  RT_HW_Base.consoleTest(String(F(" Byte")), ptr[num]->lenArrByte,','); RT_HW_Base.consoleVar(hive.vr,';',0,'H');
//hive.vr=(uint32_t)ptr[num]->ptrArrWord;  RT_HW_Base.consoleTest(String(F(" Word")), ptr[num]->lenArrWord,','); RT_HW_Base.consoleVar(hive.vr,';',0,'H');
//hive.vr=(uint32_t)ptr[num]->ptrArrLong;  RT_HW_Base.consoleTest(String(F(" Long")), ptr[num]->lenArrLong,','); RT_HW_Base.consoleVar(hive.vr,';',0,'H');
//hive.vr=(uint32_t)ptr[num]->ptrArrFloat; RT_HW_Base.consoleTest(String(F(" Float")),ptr[num]->lenArrFloat,',');RT_HW_Base.consoleVar(hive.vr,';',0,'H');
RT_HW_Base.consoleCR();
//hive.vr=ptr[num]->ptrArrByte;  RT_HW_Base.consoleTest(String(F("array Byte len")),ptr[num]->lenArrByte); RT_HW_Base.consoleTest(String(F(" adr")),hive.vr,'E',H);
//hive.vr=ptr[num]->ptrArrFloat; RT_HW_Base.consoleTest(String(F("array Byte len")),ptr[num]->lenArrByte); RT_HW_Base.consoleTest(String(F(" adr")),hive.vr,'E',H);
};		
//-------------------------------------------------------------------------------------------------
//									2.Вывод параметров массивов											
//-------------------------------------------------------------------------------------------------
//void printDataModbus(RT_HW_STRUCT_MODBUS_DATA_WORD<8> &id){
//if(!RT_HW_Base.console.ok){return;}
//if(!ptr[num]->fresh)      {return;} ptr[num]->fresh=0;
//if(num>RT_HW_MODBUS_MAX_DEVICE){return;}
//RT_HW_Base.consoleTest(String(F("Modbus Data size")),id.size,';');
//RT_HW_Base.consoleTest(String(F(" type")),id.typeData,';');
//uint32_t vr;
//vr=(uint32_t)*id->arr;
//RT_HW_Base.consoleTest(String(F(" data")),vr, ','); 
//RT_HW_Base.consoleTest(String(F(" reg")),vr, 'E');
//RT_HW_Base.consoleTestArr(String(F("reg")),id.reg,'E','U',id.sz);
//RT_HW_Base.consoleCR();
//};	

		
#include "0100_API_MODBUS/API_MODBUS_101_func_direct.hpp"		//==Функции управления;
#include "0100_API_MODBUS/API_MODBUS_120_func_transfer.hpp"	//==Функции отправки данных  в Modbus;
//=================================================================================================
};  //---END class RT_HW_MODBUS
//-------------------------------------------------------------------------------------------------
extern RT_HW_MODBUS RT_HW_Modbus; //--Создание объекта 
//-------------------------------------------------------------------------------------------------
#endif //---RT_HW_MODBUS_h
//=================================================================================================





//template <uint16_t SIZE>
//struct RT_HW_STRUCT_MODBUS_DATA_WORD{
//public:
//uint16_t arr[SIZE];    	//--Массив данных;
//uint16_t reg[SIZE];		//--Массив номеров регистров Modbus;	
//uint16_t sz=SIZE;		//--Размер массива;
//char     typeData='W';  //--Тип массива: bit[R],uint8_t[B],uint16_t[W],uint32_t[L],float[F];
//uint16_t idx;			//--Рабочий индекс;			       
//-------------------------------------------------------------------------------------------------
//};	//+++END CLASS RT_HW_DATA_MODBUS;
//=================================================================================================
//=================================================================================================
//						    		CLASS DATA MODBUS 							
//=================================================================================================
//template < typename TYPE, char mode, uint16_t SIZE, uint16_t numReg=0>
//class RT_HW_DATA_MODBUS{
//public:
//TYPE     arr[SIZE];    	//--Массив данных;
//uint16_t reg[SIZE];		//--Массив номеров регистров Modbus;	
//uint16_t sz=SIZE;		//--Размер массива;
//char     typeData=mode; //--Тип массива: bit[R],uint8_t[B],uint16_t[W],uint32_t[L],float[F];
//uint16_t idx;			//--Рабочий индекс;
//-------------------------------------------------------------------------------------------------
//									Конструктор
// 1.Заполняет массив регистров значениями начиная c numReg (можно будет потом изменить);
//-------------------------------------------------------------------------------------------------
//RT_HW_DATA_MODBUS(){for(idx=0; idx<sz; idx++){reg[idx]=numReg+idx;}}			       
//-------------------------------------------------------------------------------------------------
//};	//+++END CLASS RT_HW_DATA_MODBUS;

//template < typename TYPE, char mode, uint16_t SIZE, uint16_t numReg=0>
//class RT_HW_DATA_MODBUS{
//public:
//TYPE     arr[SIZE];    	//--Массив данных;
//uint16_t reg[SIZE];		//--Массив номеров регистров Modbus;	
//uint16_t sz=SIZE;		//--Размер массива;
//char     typeData=mode; //--Тип массива: bit[R],uint8_t[B],uint16_t[W],uint32_t[L],float[F];
//uint16_t idx;			//--Рабочий индекс;
//-------------------------------------------------------------------------------------------------
//									Конструктор
// 1.Заполняет массив регистров значениями начиная c numReg (можно будет потом изменить);
//-------------------------------------------------------------------------------------------------
//RT_HW_DATA_MODBUS(){for(idx=0; idx<sz; idx++){reg[idx]=numReg+idx;}}			       
//-------------------------------------------------------------------------------------------------
//};	//+++END CLASS RT_HW_DATA_MODBUS;



