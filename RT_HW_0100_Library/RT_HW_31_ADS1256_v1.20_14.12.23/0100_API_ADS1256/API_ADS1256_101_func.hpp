//=================================================================================================
//							1.Определение default пинов под тип MCU, других параметров
//=================================================================================================
void  constructorDevice(RT_HW_ADS1256_DEV &id){
if(id.constructorDeviceOk==0){
id.constructorDeviceOk=1;
id.initOk=id.beginOk=id.beginInit=0; 				//--Сброс флагаОВ;
id.ok=id.fresh=id.meterOk=0;						//--Сброс флагов готовности измерения;
//-------------------------------------------------------------------------------------------------
for(id.idx=0; id.idx<=11; id.idx++){clrADCpermit(id,id.idx);}  	//--Начальная инициализация разрешений работы с каналами;
//--------------------------------------------------------------------------------------------------
id.pinCS   =255;									//--default параметры для пина CS;
id.pinDRDY =255; id.blockPinDRDY=id.blockIntDRDY=1;	//--default параметры для пина DRDY;		
id.pinRESET=255; id.blockPinRESET=1;				//--default параметры для пина RESET;	
                 id.blockSpiDRDY=0;					//--default блоктровки получения DRDY через SPI;
//--------------------------------------------------------------------------------------------------
id.vFreq=id.userFreq=7.68;			//--default параметра "Значение частоты кварца ADS1256". В данной версси изменение частоты не поддерживается;	
id.vRef =id.userRef=2.5;			//--default параметра "Значение источника опорного напряжения;
id.vConverFactor=id.userConverFactor=1.0;	//--default параметра "Коэффициент корректировки результатов измерения";
//--------------------------------------------------------------------------------------------------
id.userBUFEN=1; id.codeBUFEN=id.userBUFEN & 0x01;				//--Настройка кода разрешения буферирования; 
id.userGAIN=1;  id.codeGAIN =id.userGAIN;   setCodeADCON(id);	//--Настройка кода усиления входного сигнала;
id.userSPS=8;	id.codeSPS  =id.userSPS;	setCodeDRATE(id);	//--Настройка кода скорости преобразования;
//--------------------------------------------------------------------------------------------------
id.vADCraw=id.vADCint=0;	id.vADCfloat=id.vADCvolt=0.0;		//--Начальная установка результатов измерения;
}};
//=================================================================================================
//							2.Инициализация параметров
//=================================================================================================
void  initParameters(RT_HW_ADS1256_DEV &id){
if(id.custom!=0)			{return;}		//--Выход, если устройство уже настроено;
if(!id.constructorDeviceOk)	{return;}		//--Ожидание выполнения библиотечного конструктора по настройке default-параметров;
//-------------------------------------------------------------------------------------------------
id.step=id.err=id.action=0;	id.codeErr=id.linkErr=0;		//--Очистка флагов;
id.checkDIR.state=id.checkSTEP.state=id.checkDRDY.state=0;	//--Очистка флагов ID функции checkDelay();
id.drdy=id.errDRDY=id.actDRDY=id.checkDRDY.state=0;			//--Очистка флагов для функции getDRDY();
id.ok=0; id.clear=1;										//--Очистка флагов;
//-------------------------------------------------------------------------------------------------
id.permitBusSPI=id.permitPinCS=id.permitPinRESET=0;			//--Сброс разрешения использования bus,пинов;
id.permitIntDRDY=0; id.numIntDRDY=255;						//--Сброс разрешения прерывания от пина DRDY;
//-------------------------------------------------------------------------------------------------
//				3.Настройка параметров ADC
//-------------------------------------------------------------------------------------------------
if(id.userConverFactor>=0.1){
id.vConverFactor=id.userConverFactor;}						//--Установка корректирующего коэффициента;
id.codeBUFEN=id.userBUFEN & 0x01;							//--Настройка кода разрешения буферирования;
id.codeGAIN =id.userGAIN; setCodeADCON(id); 				//--Обработка параметра "Усиление входного сигнала";
id.codeSPS  =id.userSPS;  setCodeDRATE(id);					//--Обработка параметра "Скорость преобразования";				
//-------------------------------------------------------------------------------------------------
//				4.Настройка параметров SPI
//-------------------------------------------------------------------------------------------------
id.speed=(id.vFreq *1000000)/4;												//--Расчет скорости обмена      SPI;
if(RT_HW_Base.spiCheckBus(id.bus)) 						{id.permitBusSPI=1;}//--Проверка  допустимости шины SPI;  
if(!id.permitBusSPI) {					id.codeErr=40;	id.err=1;	return;}//--Выход  по ошибке       шины SPI;
//-------------------------------------------------------------------------------------------------
//				5.Настройка пина CS
//-------------------------------------------------------------------------------------------------
if(RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,id.pinCS)){id.permitPinCS=1;}	//--Проверка  допустимости пина СS;
if(!id.permitPinCS)	 { 					id.codeErr=41;	id.err=1;	return;}	//--Выход по  ошибке       пина CS;																	 		  	
digitalWrite(id.pinCS,1); 	pinMode(id.pinCS,RT_HW_PIN_MODE_OUTPUT);				//--Настройка на вывод     пина CS;
//-------------------------------------------------------------------------------------------------
//				6.Настройка пина DRDY
//-------------------------------------------------------------------------------------------------
if(!id.blockPinDRDY){															//--Проверка  блокировки   пина DRDY;
if(RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DIN_ID,id.pinDRDY)){id.permitPinDRDY=1;}//--Проверка допустимости  пина DRDY;
if(id.permitPinDRDY){		pinMode(id.pinDRDY, RT_HW_PIN_MODE_INPUT_PULLUP); }}//--Настройка на ввод      пина DRDY; 
//--------------------------------------------------------------------------------------------------
if((!id.blockPinDRDY) && (!id.blockIntDRDY) && (id.permitPinDRDY)){				//--Проверка  блокировки пина,Interrupt,допустимости DRDY;
if(digitalPinToInterrupt(id.pinDRDY)>=0){id.permitIntDRDY=1; id.numIntDRDY=digitalPinToInterrupt(id.pinDRDY);}} //--Установка номера прерываний;
//-------------------------------------------------------------------------------------------------
//				7.Настройка пина  RESET
//-----------------------------------------------------------------------------------------------
if(!id.blockPinRESET){
if(RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,id.pinRESET)){id.permitPinRESET=1;}//-Проверка  допустимости пина RESET;
if(id.permitPinRESET){	 														//--Проверка  permit       пина RESET;  
digitalWrite(id.pinRESET,1); pinMode(id.pinRESET,RT_HW_PIN_MODE_OUTPUT);}      	//--Настройка на вывод     пина RESET;
}
//-------------------------------------------------------------------------------------------------
id.custom=1;};
//=================================================================================================
//							3.Управление CS
//=================================================================================================
void  csLOW (RT_HW_ADS1256_DEV &id){digitalWrite(id.pinCS, LOW);}	//--cs LOW;
void  csHIGH(RT_HW_ADS1256_DEV &id){digitalWrite(id.pinCS, HIGH);}//--cs HIGH;
//=================================================================================================
//							4.Чтение регистра
//=================================================================================================
uint8_t readReg(RT_HW_ADS1256_DEV &id, uint8_t reg) {
if(!RT_HW_Base.spiSetBusy(id.bus)){id.link=0; return 0;}			//--Захват шины или выход, если шина занята;
//-------------------------------------------------------------------------------------------------
csLOW(id);															//--cs=LOW;
RT_HW_Base.spiBeginTransaction(id.speed,MSBFIRST,SPI_MODE1,id.bus); //--Начало транзакции;
RT_HW_Base.spiTransfer((RT_HW_ADS1256_CMD_RREG | reg),     id.bus); //--1-й байт команды: 0x10 = 0001 0000 | = RREG;
RT_HW_Base.spiTransfer(0,                                  id.bus);	//--2-й байт команды;
delayMicroseconds(7); 												//--Задержка t6=(4*tCLKIN 50*0.13=6.5 us);
id.vReg8=RT_HW_Base.spiTransfer(0,						   id.bus);	//--Чтение регистра
delayMicroseconds(1); 												//--Задержка t11=(4*tCLKIN 4*0.13 = 0.52 us);
RT_HW_Base.spiEndTransaction(                              id.bus);	//--Окончание транзакции;
csHIGH(id);															//--cs=HIGH;
//-------------------------------------------------------------------------------------------------
RT_HW_Base.spiClearBusy(id.bus);									//--Освобождение шины;
id.link=1;	return 1;}												//--Установка флага успешного завершения транзакции;
//=================================================================================================
//							5.Запись байта в регистр
//=================================================================================================
uint8_t writeReg(RT_HW_ADS1256_DEV &id, uint8_t reg, uint8_t var){	
if(!RT_HW_Base.spiSetBusy(id.bus)){id.link=0; return 0;}			//--Захват шины или выход, если шина занята;
//-------------------------------------------------------------------------------------------------
csLOW(id);															//--cs=LOW;
RT_HW_Base.spiBeginTransaction(id.speed,MSBFIRST,SPI_MODE1,id.bus); //--Начало транзакции;
RT_HW_Base.spiTransfer((RT_HW_ADS1256_CMD_WREG | reg),     id.bus); //--1-й байт команды: 0x50 = 0101 0000 | = reg;
RT_HW_Base.spiTransfer(0,                                  id.bus);	//--2-й байт команды;
RT_HW_Base.spiTransfer(var,                                id.bus); //--Запись байта;
delayMicroseconds(1);												//--Задержка(для устойчивости работы);
RT_HW_Base.spiEndTransaction(                              id.bus);	//--Окончание транзакции;
csHIGH(id);															//--cs=HIGH;
//-------------------------------------------------------------------------------------------------
RT_HW_Base.spiClearBusy(id.bus);									//--Освобождение шины;
id.link=1;	return 1;}												//--Установка флага успешного завершения транзакции;
//=================================================================================================
//							6.Запись команды
//=================================================================================================
uint8_t sendCommand(RT_HW_ADS1256_DEV &id, uint8_t vCMD){	
if(!RT_HW_Base.spiSetBusy(id.bus)){id.link=0; return 0;}			//--Захват шины или выход, если шина занята;
//-------------------------------------------------------------------------------------------------
csLOW(id);															//--cs=LOW;
RT_HW_Base.spiBeginTransaction(id.speed,MSBFIRST,SPI_MODE1,id.bus); //--Начало транзакции;
RT_HW_Base.spiTransfer(vCMD,     id.bus); 							//--Отправка команды;
delayMicroseconds(1);												//--Задержка t11=(4*tCLKIN 4*0.13=0.52мкс);
RT_HW_Base.spiEndTransaction(                              id.bus);	//--Окончание транзакции;
csHIGH(id);															//--cs=HIGH;
//-------------------------------------------------------------------------------------------------
RT_HW_Base.spiClearBusy(id.bus);									//--Освобождение шины;
id.link=1;	return 1;};												//--Установка флага успешного завершения транзакции;  

//=================================================================================================
//							7.Установка кода управления мультиплексором
//=================================================================================================
void setCodeMUX(RT_HW_ADS1256_DEV &id, uint8_t numChannel){
//-------------------------------------------------------------------------------------------------
											  id.codeMUXN=RT_HW_ADS1256_MUXN_AINCOM;
switch (numChannel){
 case 0: id.codeMUXP=RT_HW_ADS1256_MUXP_AIN0; break;
 case 1: id.codeMUXP=RT_HW_ADS1256_MUXP_AIN1; break;
 case 2: id.codeMUXP=RT_HW_ADS1256_MUXP_AIN2; break;
 case 3: id.codeMUXP=RT_HW_ADS1256_MUXP_AIN3; break;
 case 4: id.codeMUXP=RT_HW_ADS1256_MUXP_AIN4; break;
 case 5: id.codeMUXP=RT_HW_ADS1256_MUXP_AIN5; break;
 case 6: id.codeMUXP=RT_HW_ADS1256_MUXP_AIN6; break;
 case 7: id.codeMUXP=RT_HW_ADS1256_MUXP_AIN7; break; 
 case 8: id.codeMUXP=RT_HW_ADS1256_MUXP_AIN0; id.codeMUXN=RT_HW_ADS1256_MUXN_AIN1; break;
 case 9: id.codeMUXP=RT_HW_ADS1256_MUXP_AIN2; id.codeMUXN=RT_HW_ADS1256_MUXN_AIN3; break;
 case 10:id.codeMUXP=RT_HW_ADS1256_MUXP_AIN4; id.codeMUXN=RT_HW_ADS1256_MUXN_AIN5; break;
 case 11:id.codeMUXP=RT_HW_ADS1256_MUXP_AIN6; id.codeMUXN=RT_HW_ADS1256_MUXN_AIN7; break; 
 default:id.codeMUXP=RT_HW_ADS1256_MUXP_AIN0; 									   break;}	 
//-------------------------------------------------------------------------------------------------
id.codeMUX=(id.codeMUXP) | id.codeMUXN;}; 			//--Расчет номера канала;		 

//=================================================================================================
//							9.Расчет кода скорости и тайм аута на время ожидания
//=================================================================================================
void setCodeDRATE(RT_HW_ADS1256_DEV &id){
switch (id.codeSPS){
 case  0: id.codeDRATE = RT_HW_ADS1256_DRATE_2_5SPS; 	id.timeChannel=1000000UL / 2; 		break;	//--vDRATE=0x03
 case  1: id.codeDRATE = RT_HW_ADS1256_DRATE_5SPS;  	id.timeChannel=1000000UL / 5;		break;	//--vDRATE=0x13
 case  2: id.codeDRATE = RT_HW_ADS1256_DRATE_10SPS;		id.timeChannel=1000000UL / 10;		break;	//--vDRATE=0x23 
 case  3: id.codeDRATE = RT_HW_ADS1256_DRATE_15SPS;		id.timeChannel=1000000UL / 15;		break;	//--vDRATE=0x33
 case  4: id.codeDRATE = RT_HW_ADS1256_DRATE_25SPS; 	id.timeChannel=1000000UL / 25;		break;	//--vDRATE=0x43
 case  5: id.codeDRATE = RT_HW_ADS1256_DRATE_30SPS; 	id.timeChannel=1000000UL / 30;		break;	//--vDRATE=0x53
 case  6: id.codeDRATE = RT_HW_ADS1256_DRATE_50SPS;		id.timeChannel=1000000UL / 50;		break;	//--vDRATE=0x63 
 case  7: id.codeDRATE = RT_HW_ADS1256_DRATE_60SPS;		id.timeChannel=1000000UL / 60;		break;	//--vDRATE=0x72
 case  8: id.codeDRATE = RT_HW_ADS1256_DRATE_100SPS; 	id.timeChannel=1000000UL / 100;		break;  //--vDRATE=0x82, timeChannel=10000us;
 case  9: id.codeDRATE = RT_HW_ADS1256_DRATE_500SPS; 	id.timeChannel=1000000UL / 500;		break;  //--vDRATE=0x92, timeChannel= 2000us;
 case 10: id.codeDRATE = RT_HW_ADS1256_DRATE_1000SPS;	id.timeChannel=1000000UL / 1000;	break;  //--vDRATE=0xA1, timeChannel= 1000us; 
 case 11: id.codeDRATE = RT_HW_ADS1256_DRATE_2000SPS;	id.timeChannel=1000000UL / 2000;	break;  //--vDRATE=0xB0, timeChannel=  500us;
 case 12: id.codeDRATE = RT_HW_ADS1256_DRATE_3750SPS; 	id.timeChannel=1000000UL / 3750;	break;  //--vDRATE=0xC0
 case 13: id.codeDRATE = RT_HW_ADS1256_DRATE_7500SPS; 	id.timeChannel=1000000UL / 7500;	break;  //--vDRATE=0xD0 
 case 14: id.codeDRATE = RT_HW_ADS1256_DRATE_15000SPS; 	id.timeChannel=1000000UL / 15000;	break;  //--vDRATE=0xE0
 case 15: id.codeDRATE = RT_HW_ADS1256_DRATE_30000SPS; 	id.timeChannel=1000000UL / 30000;	break;  //--vDRATE=0xF0  
 default: id.codeDRATE = RT_HW_ADS1256_DRATE_100SPS;	id.timeChannel=1000000UL / 100;}};          //--vDRATE=0x82
//=================================================================================================
//							10.Расчет кода усилителя входного сигнала.
//   Биты 2–0 	PGA2, PGA1, PGA0 - программируемый усилитель входного сигнала;
//=================================================================================================
void setCodeADCON(RT_HW_ADS1256_DEV &id){
switch (id.codeGAIN){
 case  1: id.codePGA = RT_HW_ADS1256_GAIN_1; 		break;  //-->=0x00;
 case  2: id.codePGA = RT_HW_ADS1256_GAIN_2;  	 	break;  //-->=0x01;
 case  4: id.codePGA = RT_HW_ADS1256_GAIN_4;		break;  //-->=0x02; 
 case  8: id.codePGA = RT_HW_ADS1256_GAIN_8;		break;  //-->=0x03;
 case 16: id.codePGA = RT_HW_ADS1256_GAIN_16; 		break;  //-->=0x04;
 case 32: id.codePGA = RT_HW_ADS1256_GAIN_32; 	 	break;  //-->=0x05;
 case 64: id.codePGA = RT_HW_ADS1256_GAIN_64;		break;  //-->=0x06; 
 default: id.codePGA = RT_HW_ADS1256_GAIN_1;}				//-->=0x00;
id.codeADCON=id.codePGA;}									//--Формирование ADCON;
									
//=================================================================================================
//							11.ФУНКЦИИ короткие
//=================================================================================================
void    setADCpermit(RT_HW_ADS1256_DEV &id, uint8_t num)				{if(num>11){return;    } id.arrAI_permit[num]=1;};
void    clrADCpermit(RT_HW_ADS1256_DEV &id, uint8_t num)				{if(num>11){return;    } id.arrAI_permit[num]=0;};
uint8_t getADCpermit(RT_HW_ADS1256_DEV &id, uint8_t num)				{if(num>11){return 0;  } return id.arrAI_permit[num];};
float   outADCvolt  (RT_HW_ADS1256_DEV &id){if(id.clear){return 0.0;} else {return id.vADCvolt;}};
int32_t outADCint   (RT_HW_ADS1256_DEV &id){if(id.clear){return 0;}   else {return id.vADCint; }};
//float   getADCvolt  (RT_HW_ADS1256_DEV &id, int32_t var){return ((((float)var) / 0x7FFFFF) * ((2 * id.vRef) / (float)(1<<id.vPGA)) * id.vConverFactor);};
float   getADCvolt  (RT_HW_ADS1256_DEV &id, int32_t var){return (((float)var) / 0x7FFFFF) * id.vFactorFV;};
void    getFactorFV (RT_HW_ADS1256_DEV &id){id.vFactorFV=((2 * id.vRef) / (float)(1<<id.vPGA)) * id.vConverFactor;};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								20.СЕРВИСНЫЕ ФУНКЦИИ ДЛЯ ОТЛАдки
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							21.Вывод параметров
//=================================================================================================
void printParam(RT_HW_ADS1256_DEV &id, uint8_t num=0){
(void)num;
#ifdef RT_HW_ADS1256_DEBUG
if(!RT_HW_Base.console.ok){return;}	//--Ожидание готовности консоли;
RT_HW_Base.consoleHead(String(F("Parameters ADS1256")),'='); 
RT_HW_Base.consoleTest(String(F("num")),				num, 'E','U');
RT_HW_Base.consoleTest(String(F("vRef")),				id.vRef,     	    ',','3');
RT_HW_Base.consoleTest(String(F(" vConvertFactor")),	id.vConverFactor,   ',','3');
RT_HW_Base.consoleTest(String(F(" vFreq")),		   		id.vFreq,     	    ',','3');
RT_HW_Base.consoleTest(String(F(" vBUFEN")),     	    id.vBUFEN,     		'E','U');  
RT_HW_Base.consoleTest(String(F("SPI.bus->bus")),		id.bus,     	    ',','U');  
RT_HW_Base.consoleTest(String(F(" permitBus")),		    id.permitBusSPI,    ',','U');
RT_HW_Base.consoleTest(String(F(" blockSpiDRDY")),		id.blockSpiDRDY,    ',','U');
RT_HW_Base.consoleTest(String(F(" speed")),		   	    id.speed,     	    'E','U'); 
RT_HW_Base.consoleTest(String(F("CS---->pin")),    		id.pinCS,       	',','P');
RT_HW_Base.consoleTest(String(F(" permit")),   (uint8_t)id.permitPinCS,  	'E','U');
RT_HW_Base.consoleTest(String(F("DRDY-->pin")),    		id.pinDRDY,       	',','P');
RT_HW_Base.consoleTest(String(F(" permit")),   (uint8_t)id.permitPinDRDY,  	',','U');
RT_HW_Base.consoleTest(String(F(" block")),    (uint8_t)id.blockPinDRDY,   	',','U');
RT_HW_Base.consoleTest(String(F(" interrupt==>permit")),(uint8_t)id.permitIntDRDY,',','U');
RT_HW_Base.consoleTest(String(F(" num")),	            id.numIntDRDY,  	',','U');
RT_HW_Base.consoleTest(String(F(" block")),    (uint8_t)id.blockIntDRDY,    'E','U');
RT_HW_Base.consoleTest(String(F("RESET->pin")),    		id.pinRESET,       	',','P');
RT_HW_Base.consoleTest(String(F(" permit")),   (uint8_t)id.permitPinRESET,  ',','U');
RT_HW_Base.consoleTest(String(F(" block")),    (uint8_t)id.blockPinRESET,   'E','U');
RT_HW_Base.consoleTestArr(String(F("PermitAI")),    id.arrAI_permit,'E','U',12);
RT_HW_Base.consoleTest(String(F("userGAIN")),     	    id.userGAIN,     	',','U');
RT_HW_Base.consoleTest(String(F(" userSPS")),     		id.userSPS,     	'E','U');
RT_HW_Base.consoleTest(String(F("custom")),     	    id.custom,     		',','U');
RT_HW_Base.consoleTest(String(F(" codeErr")),     	    id.codeErr,         'E','U');
RT_HW_Base.consoleLine('-'); 
#endif	
};
//=================================================================================================
//							10.1.Вывод параметров
//=================================================================================================
void printChannel(RT_HW_ADS1256_DEV &id, uint8_t num=0){
(void)num;
#ifdef RT_HW_ADS1256_DEBUG
if(!RT_HW_Base.console.ok){return;}	//--Ожидание готовности консоли;
RT_HW_Base.consoleTest(String(F("num")),			num,                ';','U');
RT_HW_Base.consoleTest(String(F(" Channel")),    	id.numChannel,     	',','U'); 
RT_HW_Base.consoleTest(String(F(" MUX->MUXP")),   	id.codeMUXP,     	',','H'); 
RT_HW_Base.consoleTest(String(F(" MUXN")),   		id.codeMUXN,     	',','H'); 
RT_HW_Base.consoleTest(String(F(" MUX")),   		id.codeMUX,     	';','H'); 
RT_HW_Base.consoleTest(String(F(" GAIN")),     		id.codeGAIN,     	',','U'); 
RT_HW_Base.consoleTest(String(F(" SPS")),     		id.codeSPS,     	',','U');
RT_HW_Base.consoleTest(String(F(" time")), 			id.timeChannel,     ';','U'); 
RT_HW_Base.consoleTest(String(F("  ADC->raw")),     id.vADCraw,     	',','H');  
RT_HW_Base.consoleTest(String(F(" int")),     		id.vADCint,     	',','I');  
RT_HW_Base.consoleTest(String(F(" float")),      	id.vADCfloat,     	',','3');
RT_HW_Base.consoleTest(String(F(" volt")),     		id.vADCvolt,     	';','3'); 
RT_HW_Base.consoleCR();    
#endif	
};
//=================================================================================================
//							10.1.Вывод параметров
//=================================================================================================
void printBeginFresh(RT_HW_ADS1256_DEV &id, uint8_t num=0){
(void)num;
#ifdef RT_HW_ADS1256_DEBUG
if(!RT_HW_Base.console.ok){return;}						//--Ожидание готовности консоли;
if(!id.beginFresh)		  {return;}	id.beginFresh=0;	//--Ожидание обновления данных
RT_HW_Base.consoleHead(String(F("beginFresh ADS1256")),'='); 
RT_HW_Base.consoleTest(String(F(" num")),				num,                ';','U');
RT_HW_Base.consoleTest(String(F(" BUFEN")),     		id.codeBUFEN,     	',','U');  
RT_HW_Base.consoleTest(String(F(" GAIN->code")),     	id.codeGAIN,     	',','U'); 
RT_HW_Base.consoleTest(String(F(" user")),     	    	id.userGAIN,     	';','U');  
RT_HW_Base.consoleTest(String(F(" SPS->code")),     	id.codeSPS,     	',','U');  
RT_HW_Base.consoleTest(String(F(" user")),     		    id.userSPS,     	'E','U');

RT_HW_Base.consoleTest(String(F("STATUS")),     	    id.vSTATUS,     	';','H'); 
RT_HW_Base.consoleTest(String(F("  ADCON")),     	    id.vADCON,     		',','H');  
RT_HW_Base.consoleTest(String(F(" PGA")),     	        id.vPGA,     		';','H');  
RT_HW_Base.consoleTest(String(F("  DRATE")),     	    id.vDRATE,     		',','H'); 
RT_HW_Base.consoleTest(String(F("  FactorFV")),     	id.vFactorFV,     	'E','3'); 
RT_HW_Base.consoleLine('-');  
#endif	
};

//=================================================================================================
//							10.4.Вывод состояния шагов dir,step,stepDRDY
//=================================================================================================
uint8_t printDir(RT_HW_ADS1256_DEV &id, uint8_t num=0){
(void)num; uint8_t fresh; fresh=0;
#ifdef RT_HW_ADS1256_DEBUG
if(!RT_HW_Base.console.ok){return 0;}	//--Ожидание готовности консоли;
if(num==0)				  {return 0;}
if(num>=1){if(id.agoDIR!= id.dir) {fresh=1; id.agoDIR =id.dir; }}
if(num>=2){if(id.agoSTEP!=id.step){fresh=1; id.agoSTEP=id.step;}}
if(num>=3){if(id.agoDRDY!=id.drdy){fresh=1; id.agoDRDY=id.drdy;}}
if(fresh){
RT_HW_Base.consoleTest(String(F("num")),			num,   		 ';','U');
RT_HW_Base.consoleTest(String(F(" dir")),     	  	id.dir,      ',','U');             
RT_HW_Base.consoleTest(String(F(" step")),          id.step,     ',','U');  
RT_HW_Base.consoleTest(String(F(" drdy")),     	    id.drdy,     ';','U');   
RT_HW_Base.consoleCR();}
#endif	
return fresh;};
//=================================================================================================
