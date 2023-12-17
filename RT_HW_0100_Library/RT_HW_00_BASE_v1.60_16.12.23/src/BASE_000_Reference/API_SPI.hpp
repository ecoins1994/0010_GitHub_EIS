//#################################################################################################
//
//                        				API.h для SPI
//ecoins@mail.ru 18.11.2023г.
//=================================================================================================
// 							ДОСТУПНЫЕ ШИНЫ 													[РАЗДЕЛ  1]  (line 87)
// AVR  	- SPI;
// ESP8266  - SPI;
// ESP32S   - SPI,SPI1; 
// SAM3     - SPI;
// STM32    - SPI, дополнительно создаются шины SPI1x,SPI2x,SPI3x,SPI4x,SPI5x;
// RP2040   - SPI,SPI1;
//   Для каждой из доступной шины создается объект LinkSPIx [RT_HW_STRUCT_SPI LinkSPIx]	[РАЗДЕЛ  1].
//   (описание структуры ниже - line 91), в котором содержатся параметры шины (номера пинов, скорость и пр.).
//=================================================================================================
// 2.Для чтения/записи параметров LinkSPIx предусмотрены необходимые функции     			[РАЗДЕЛ  2]   (line 154)
//=================================================================================================
//                    		БАЗОВЫЙ ФУНКЦИИ ДЛЯ РАБОТЫ С ШИНОЙ SPIx.						[РАЗДЕЛЫ 3,4] (line 646,865)
//-------------------------------------------------------------------------------------------------
// 3.Для инициализации параметров предусмотрены  функции 									[Раздел 3]	  (line 646) 
// void     spiInitParam(										uint8_t bus=0)	//==Инициализация параметров          шины SPIx из описания контроллера  Board;
// void     spiInitParamAll()													//==Инициализация параметров для всех шины SPIx из описаний контроллеров Board;					
// void     spiSetPins(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t bus=0) 	//==Установка пинов sck,miso,mosi для выбранной шины SPI(bus);
//-------------------------------------------------------------------------------------------------
// 4.Базовые функции из библиотеки SPI.h  													[Раздел 4]	  (line 865) 
//   (для разных контроллеров библиотеки SPI.h разные).
// void  	spiBeginTransaction(uint32_t speed, uint8_t bitOrder, uint8_t dataMode, uint8_t bus=0);	//==Начало транзакции с параметрами speed,        bitOrder,         dataMode;
// void  	spiBeginTransaction(uint32_t speed, uint8_t bus=0);									   	//==Начало транзакции с параметрами speed         bitOrder=MSBFIRST,dataMode=MODE0;
// void  	spiBeginTransaction(uint8_t bus=0);														//==Начало транзакции с параметрами speed=default,bitOrder=MSBFIRST,dataMode=MODE0;
// void 	spiEndTransaction  (uint8_t bus=0);														//==Конец транзакции;
// uint8_t  spiTransfer        (uint8_t  val, uint8_t bus);											//==Передача байта. Возвращает принятый байт;
// uint8_t  spiBegin           (uint8_t bus=0);														//==Инициализации шины. Функция использует параметры из объекта LinkSPIx(пины и др.);
//                                                          										//  Функция инициализация выполняется при id.status=0. 
//=================================================================================================
//                    		ФУНКЦИИ ДЛЯ РАБОТЫ С УСТРОЙСТВАМИ НА ШИНЕ SPIx.					[РАЗДЕЛЫ 5-8] (line 646) 
//	Рекомендуется для использования именно этот набор функций, как более удобный. 
//  Устройство описывается структурой  src\BASE_002_Sruct\Struct_220_Link
//	struct RT_HW_STRUCT_SPI_DEV{
//	uint8_t  custom=0;				//--1.Флаг настройки параметров;
//	uint8_t  status=0;				//--2.Статус устройства: =0 не инициализировано; =1 Master; =2 Slave;
//	uint8_t  link=0;				//--3.Флаг успешной(=1) завершения транзакции;
//	uint8_t  codeErr=0,err=0;		//--4.Код ошибки;
//	uint8_t  bus=0;					//--5.Номер шины;
//	uint8_t  cs=255; 				//--6.Номер пина cs;
//	uint8_t  bitOrder=1;			//--7.Порядок следования битов  (=1 - впереди старший бит, в том числе и uint8_t,uint16_t,uint32_t);
//	uint8_t  dataMode=0;			//--8.Параметр dataMode для шины SPI;
//	uint8_t  qnt=1;					//--9.Кол-во передаваемых байт;
//	uint8_t  bf8,bfx;				//--11.Рабочий регистр;
//	uint32_t bf32;					//--12.Рабочий регистр;
//	int8_t   idx;					//--13.Рабочий индекс (-128: +127);
//	uint8_t  t1=0,t2=0,t3=0;		//--14.Задержки времени(mcs): t1- перед устновкой cs=0; t2-перед установкой cs=1;  t3-после установки cs=1;
//  uint32_t speed=RT_HW_SPI_SPEED;	//--15.Скорость шины в Гц;	
//};
//-------------------------------------------------------------------------------------------------
//  5.Функции настройки параметров устройства SPI.											[Раздел 5] (line 865) 
//    Перед примененем функций работы с устройствами на шине SPI, параметры устройство должны быть настроены функциями:
//  spiSetParam(   RT_HW_STRUCT_SPI_DEV &id, uint8_t cs, uint8_t bus, uint32_t speed=0)   - установка cs, номер шины,скорости. 
//                                                                     Возвращает параметр id.custom=1; Для повторной настройки нужно сбросить id.custom=0; 
//  spiSetParam(   RT_HW_STRUCT_SPI_DEV &id, uint8_t cs)                                  - аналогичная установка cs, номер шины=0, скорость=0 (при инициализации RT_HW_SPI_SPEED->id.speed); 
//-------------------------------------------------------------------------------------------------
//  6.Настройка устройства.																	[Раздел 6] (line 883) 
//  Перед примененем функций работы с устройствами на шине SPI, после настройки параметров устройства, устройство должно быть настроено функцией:
//  spiInitDevice( RT_HW_STRUCT_SPI_DEV &id)											  - настройка устройства;
//-------------------------------------------------------------------------------------------------
//	7.Функции обмена с устройствами на шине SPI:											[Раздел 7] (line 903) 
//  spiTransfer   (RT_HW_STRUCT_SPI_DEV &id, uint32_t tx, uint32_t &rx, uint8_t qnt=1) - обмен  от 1 до 4 байтами;
//  spiWrite      (RT_HW_STRUCT_SPI_DEV &id, uint32_t tx,               uint8_t qnt=1) - запись от 1 до 4 байтов;
//  spiRead       (RT_HW_STRUCT_SPI_DEV &id,                            uint8_t qnt=1) - чтение от 1 до 4 байт;
//  spiREAD       (RT_HW_STRUCT_SPI_DEV &id, uint8_t reg)                              - чтение из регистра reg 
//                                                                   (отправляется номер регистра и возвращает результат в буфере id.bf32);
//  spiREADArr    (RT_HW_STRUCT_SPI_DEV &id, uint8_t reg, uint8_t *arr, uint8_t qnt=1) - чтение массива длиной qnt начиная с регистра reg 
//                                                                   (отправляется номер регистра и возвращает результат в массиве arr);
//  spiRead74HC165(RT_HW_STRUCT_SPI_DEV &id,                            uint8_t qnt=1) - чтение от 1 до 4 байт из каскадно-соединенных сдвиговых регистров 74HC165;
//  spiTransferArr(RT_HW_STRUCT_SPI_DEV &id, uint8_t *tx, uint8_t *rx,  uint8_t qnt=1) - обмен  массива tx,rx длиной qnt;
//  spiWriteArr   (RT_HW_STRUCT_SPI_DEV &id, uint8_t *tx,               uint8_t qnt=1) - запись массива tx    длиной qnt;
//  spiReadArr    (RT_HW_STRUCT_SPI_DEV &id,              uint8_t *rx,  uint8_t qnt=1) - чтение массива    rx длиной qnt;
//
//-------------------------------------------------------------------------------------------------
//  8.Внутренние функции.																	[Раздел 8]  (line 1041) 
//  spiBeginTransaction(RT_HW_STRUCT_SPI_DEV &id) - начало    транзакции и установка пина CS LOW  после задержки=id.t1;
//  spiEndTransaction  (RT_HW_STRUCT_SPI_DEV &id) - окончание транзакции и установка пина CS HIGH после задержки=id.t2, далее дополнительная задержка id.t3;
//-------------------------------------------------------------------------------------------------

//=================================================================================================
//#################################################################################################