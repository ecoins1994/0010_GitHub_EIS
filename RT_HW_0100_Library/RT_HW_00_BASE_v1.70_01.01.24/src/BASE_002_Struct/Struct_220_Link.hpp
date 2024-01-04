//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						Data structure for working with the device via communication interface
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
//=================================================================================================
//						1.Data structure for working with the device via i2c
//=================================================================================================
struct RT_HW_STRUCT_I2C_DEV{
uint8_t  custom=0;				//--1.Setting option;
uint8_t  status=0;				//--2.Status device: =0 no init; =1 Master.MCU->Slave.device; =2 Slave;
uint8_t  link=0;				//--3.Completed transaction flag;
uint8_t  codeErr=0,err=0;		//--4.Code error;
uint8_t  bus=0;					//--5.Number bus;
uint8_t	 adr=255; 				//--6.Аddress;
uint8_t  expander=0,  agoExpander=255;  //--7.1.i2c expander address;
uint8_t  channel=255, agoChannel=255;	//--7.2.i2c expander channel number;	
//-------------------------------------------------------------------------------------------------
uint8_t  stop=1;				//--8.Stop bit;
//-------------------------------------------------------------------------------------------------
uint8_t  bf8;					//--Working register
uint8_t  idx;					//--Working index;
uint8_t  cnt;					//--Working counter;
uint8_t  cntErr;				//--Working counter Error;	
//-------------------------------------------------------------------------------------------------
uint32_t speed=RT_HW_I2C_SPEED;	//--Speed;	
};
//=================================================================================================
//						3.Data structure for working with the deviceс SPI
//=================================================================================================
struct RT_HW_STRUCT_SPI_DEV{
uint8_t  custom=0;				//--1.Флаг настройки параметров;
uint8_t  status=0;				//--2.Статус устройства: =0 не инициализировано; =1 Master; =2 Slave;
uint8_t  link=0;				//--3.Флаг успешной(=1) завершения транзакции;
uint8_t  codeErr=0,err=0;		//--4.Код ошибки;
uint8_t  bus=0;					//--5.Номер шины;
uint8_t  cs=255; 				//--6.Номер пина cs;
uint8_t  bitOrder=1;			//--7.Порядок следования битов  (=1 - впереди старший бит, в том числе и uint8_t,uint16_t,uint32_t);
uint8_t  dataMode=0;			//--8.Параметр dataMode для шины SPI;
uint8_t  qnt=1;					//--9.Кол-во передаваемых байт;
uint8_t  bf8,rx8;				//--11.Рабочий регистр;
uint32_t bf32;					//--12.Рабочий регистр;
int8_t   idx;					//--13.Рабочий индекс (-128: +127);
uint8_t  t1=0,t2=0,t3=0;		//--14.Задержки времени(mcs): t1- перед устновкой cs=0; t2-перед установкой cs=1;  t3-после установки cs=1;
uint32_t speed=RT_HW_SPI_SPEED;	//--15.Скорость шины в Гц;		
RT_HW_PIN_DIR_ID ddCS;			//--16.Структура для управления пином CS; 
};
//=================================================================================================
//						4.Data structure for working with the device via SPN
//=================================================================================================	
struct RT_HW_STRUCT_SPN_DEV{
//-------------------------------------------------------------------------------------------------
uint8_t  custom=0;				//--1.Setting option;
uint8_t  status=0;				//--2.Status device: =0 no init; =1 Master.MCU->Slave.device; =2 Slave;
uint8_t  link=0;				//--3.Completed transaction flag;
uint8_t  codeErr=0,err=0;		//--4.Code error;
//-------------------------------------------------------------------------------------------------
uint8_t  sck=255;				//--6.1.sck  Pin number;
uint8_t  miso=255;				//--6.2.miso Pin number;
uint8_t  mosi=255;				//--6.3.mosi Pin number;
uint8_t  cs=255;				//--6.4.cs Pin number;
uint8_t  bitOrder=1;			//--6.6.In var, the most significant bit is ahead; 
uint8_t  qnt=1;					//--6.9.Word size in bytes;
//-------------------------------------------------------------------------------------------------
uint32_t bf32;					//--Working register;
//-------------------------------------------------------------------------------------------------
int8_t   idx,idb;				//--Index;	
uint8_t	 permitRX=0, permitTX=0;
uint8_t	 userRX=1,   userTX=1;
//-------------------------------------------------------------------------------------------------
uint8_t  speed=100;				//--100% -max, 0%-min;
uint8_t  time=0;				//--Working delay time(0-10);
};
//=================================================================================================
//						5.Data structure for working with the device via UART
//=================================================================================================	
struct RT_HW_STRUCT_UART_DEV{
//-------------------------------------------------------------------------------------------------
uint8_t  custom=0;				//--1.Setting option;
uint8_t  status=0;				//--2.Status device: =0 no init; =1 Master.MCU->Slave.device; =2 Slave;
uint8_t  link=0;				//--3.Completed transaction flag;
uint8_t  codeErr=0;				//--4.Code error;
//-------------------------------------------------------------------------------------------------
uint8_t  bus=255;				//--6.number UART
//-------------------------------------------------------------------------------------------------
uint8_t  bf8;					//--Working register;
//-------------------------------------------------------------------------------------------------
int8_t   idx,idb;				//--Index;	
//-------------------------------------------------------------------------------------------------
uint32_t speed=115200;			//--Speed;
};
//=================================================================================================
//						6.Data structure for working with the device via USB
//=================================================================================================	
/*
struct RT_HW_STRUCT_UART_USB{
uint32_t timeBegin; 
uint16_t dir=0;
uint8_t  cnt=0; uint8_t bf8=0;
//-------------------------------------------------------------------------------------------------
uint8_t  custom=0;				//--1.Setting option;
uint8_t  status=0;				//--2.Status device: =0 no init; =1 Master.MCU->Slave.device; =2 Slave;
uint8_t  link=0;				//--3.Completed transaction flag;
uint8_t  codeErr=0;				//--4.Code error;
//-------------------------------------------------------------------------------------------------
uint32_t speed=115200;			//--Speed;
};
*/

//=================================================================================================
//						6.Data structure for working with the LCD HD44780 с BUS via pins
//=================================================================================================
struct RT_HW_STRUCT_LCD_DEV{
uint8_t  custom=0;				//--1.Setting option;
uint8_t  status=0;				//--2.Status device: =0 no init; =1 Master.MCU->Slave.device; =2 Slave;
uint8_t  link=0;				//--3.Completed transaction flag;
uint8_t  codeErr=0;				//--4.Code error;
//-------------------------------------------------------------------------------------------------
uint8_t  pin[11];				//--RS,RW(E2),E1,D0-D7; 
uint8_t  permitE2=0;			//--Permit E2 (for LCD 40x4 =1);
//-------------------------------------------------------------------------------------------------
uint8_t  bf8;					//--Working register;
//-------------------------------------------------------------------------------------------------
int8_t   idx,idb;				//--Index;	
uint8_t  step;					//--Step for inner function;
uint32_t timeBegin;				//--Time for inner function;
//-------------------------------------------------------------------------------------------------
uint8_t  speed=100;				//--100% -max, 0%-min;
uint8_t  time=0;				//--Working delay time(0-10);
};
//=================================================================================================
//						7.Data structure for working with Link
//=================================================================================================
struct RT_HW_STRUCT_LINK_DEV{
//-------------------------------------------------------------------------------------------------
char     mi='x';				//--0.Mode interface;
uint8_t  custom=0;				//--1.Setting option;	
uint8_t  status=0;				//--2.Status device: =0 no init; =1 Master.MCU->Slave.device; =2 Slave;
uint8_t  link=0;				//--3.Completed transaction flag;
uint8_t  codeErr=0;				//--4.Code error;	
//--------------------------------------------------------------------------------------------------
uint8_t  dir=0;					//--5.Working  dir for direct();
//uint8_t  step;					//--6.Working step for add function;
uint8_t  ok;					//--7.1.Device ok;
uint8_t  fresh;					//--7.2.Fresh data;
//-------------------------------------------------------------------------------------------------
uint8_t  cnt,cntErr;			//--8.Counters;
//uint8_t  err:1,action:1;		//--9.Working flags;
//-------------------------------------------------------------------------------------------------
uint8_t  workDelay=0;			//--10.Working register; 
uint8_t  pointDelay;			//--11.Return point from a function;
uint16_t sizeDelay;				//--12.Size delay;	
uint32_t startDelay;		   	//--13.Working register;
//--------------------------------------------------------------------------------------------------
uint8_t  run=1;    				//--7.1.Flags to start reading;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						2.Структуры для работы с консолью 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	

