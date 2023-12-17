//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//           					ADS1256
//
//=================================================================================================
//-------------------------------------------------------------------------------------------------
// 						Адреса регистров
//-------------------------------------------------------------------------------------------------
#define RT_HW_ADS1256_REG_STATUS 	0x00		//--Регистр состояния;
#define RT_HW_ADS1256_REG_MUX 		0x01		//--Регистр управления входным мультиплексором;
#define RT_HW_ADS1256_REG_ADCON 	0x02
#define RT_HW_ADS1256_REG_DRATE 	0x03
#define RT_HW_ADS1256_REG_IO    	0x04
#define RT_HW_ADS1256_REG_OFC0 		0x05
#define RT_HW_ADS1256_REG_OFC1 		0x06
#define RT_HW_ADS1256_REG_OFC2 		0x07
#define RT_HW_ADS1256_REG_FSC0 		0x08
#define RT_HW_ADS1256_REG_FSC1 		0x09
#define RT_HW_ADS1256_REG_FSC2 		0x0A
//-------------------------------------------------------------------------------------------------
// 						Коды команд
//-------------------------------------------------------------------------------------------------
#define RT_HW_ADS1256_CMD_WAKEUP    0x00
#define RT_HW_ADS1256_CMD_RDATA     0x01
#define RT_HW_ADS1256_CMD_RDATAC    0x03
#define RT_HW_ADS1256_CMD_SDATAC    0x0F
#define RT_HW_ADS1256_CMD_RREG      0x10
#define RT_HW_ADS1256_CMD_WREG      0x50
#define RT_HW_ADS1256_CMD_SELFCAL   0xF0
#define RT_HW_ADS1256_CMD_SELFOCAL  0xF1
#define RT_HW_ADS1256_CMD_SELFGCAL  0xF2
#define RT_HW_ADS1256_CMD_SYSOCAL   0xF3
#define RT_HW_ADS1256_CMD_SYSGCAL   0xF4
#define RT_HW_ADS1256_CMD_SYNC      0xFC
#define RT_HW_ADS1256_CMD_STANDBY   0xFD
#define RT_HW_ADS1256_CMD_RESET     0xFE
//-------------------------------------------------------------------------------------------------
// 						Коды мультиплексирования
//-------------------------------------------------------------------------------------------------
#define RT_HW_ADS1256_MUXP_AIN0     0x00
#define RT_HW_ADS1256_MUXP_AIN1     0x10
#define RT_HW_ADS1256_MUXP_AIN2     0x20
#define RT_HW_ADS1256_MUXP_AIN3     0x30
#define RT_HW_ADS1256_MUXP_AIN4     0x40
#define RT_HW_ADS1256_MUXP_AIN5     0x50
#define RT_HW_ADS1256_MUXP_AIN6     0x60
#define RT_HW_ADS1256_MUXP_AIN7     0x70
#define RT_HW_ADS1256_MUXP_AINCOM   0x80

#define RT_HW_ADS1256_MUXN_AIN0     0x00
#define RT_HW_ADS1256_MUXN_AIN1     0x01
#define RT_HW_ADS1256_MUXN_AIN2     0x02
#define RT_HW_ADS1256_MUXN_AIN3     0x03
#define RT_HW_ADS1256_MUXN_AIN4     0x04
#define RT_HW_ADS1256_MUXN_AIN5     0x05
#define RT_HW_ADS1256_MUXN_AIN6     0x06
#define RT_HW_ADS1256_MUXN_AIN7     0x07
#define RT_HW_ADS1256_MUXN_AINCOM   0x08
//-------------------------------------------------------------------------------------------------
// 						Коды GAIN
//-------------------------------------------------------------------------------------------------
#define RT_HW_ADS1256_GAIN_1        0x00
#define RT_HW_ADS1256_GAIN_2        0x01
#define RT_HW_ADS1256_GAIN_4        0x02
#define RT_HW_ADS1256_GAIN_8        0x03
#define RT_HW_ADS1256_GAIN_16       0x04
#define RT_HW_ADS1256_GAIN_32       0x05
#define RT_HW_ADS1256_GAIN_64       0x06
//-------------------------------------------------------------------------------------------------
// 						Коды скорости передачи для частоты кристалла 7.68мГц
//-------------------------------------------------------------------------------------------------
#define RT_HW_ADS1256_DRATE_30000SPS 0xF0
#define RT_HW_ADS1256_DRATE_15000SPS 0xE0
#define RT_HW_ADS1256_DRATE_7500SPS  0xD0
#define RT_HW_ADS1256_DRATE_3750SPS  0xC0
#define RT_HW_ADS1256_DRATE_2000SPS  0xB0
#define RT_HW_ADS1256_DRATE_1000SPS  0xA1
#define RT_HW_ADS1256_DRATE_500SPS   0x92
#define RT_HW_ADS1256_DRATE_100SPS   0x82
#define RT_HW_ADS1256_DRATE_60SPS    0x72
#define RT_HW_ADS1256_DRATE_50SPS    0x63
#define RT_HW_ADS1256_DRATE_30SPS    0x53
#define RT_HW_ADS1256_DRATE_25SPS    0x43
#define RT_HW_ADS1256_DRATE_15SPS    0x33
#define RT_HW_ADS1256_DRATE_10SPS    0x23
#define RT_HW_ADS1256_DRATE_5SPS     0x13
#define RT_HW_ADS1256_DRATE_2_5SPS   0x03

#define RT_HW_ADS1256_DRDY_TIMEOUT_US   (uint32_t)3000000	//--Тайм-аут ожидания занятости устройства (3сек)
//=================================================================================================


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.1.Structute for ADS1256(SPI)
// struct RT_HW_STRUCT_TIME{uint32_t startTime,curTime; uint16_t sizeDelay; 
//                                    uint8_t  state=0; uint8_t  pointTime;};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
struct RT_HW_ADS1256_DEV{ 
RT_HW_STRUCT_TIME checkDIR, checkSTEP, checkDRDY; 
//-------------------------------------------------------------------------------------------------
uint8_t  custom=0;				//--Флаг настройки параметров;
uint8_t  constructorDeviceOk=0;	//--Флаг настройки внутреннего конструктора;
//-------------------------------------------------------------------------------------------------
uint8_t  bus=0;						//--Номер шины SPI;
uint32_t speed=0;					//--Скорость шины SPI=vFreq*1000000/4;
uint8_t  link=0;					//--Флаг успешной транзакции;
uint8_t  status=0;					//--Статус устройства связи: =0 no init; =1 Master.MCU->Slave.device; =2 Slave;
//--------------------------------------------------------------------------------------------------
uint8_t  pinCS=255;	   				//--Номер пина CS;
uint8_t  pinDRDY=255,numIntDRDY=255;//--Номер пина DRDY, номер вектора прерываний от пина DRDY;
uint8_t  pinRESET=255; 				//--Номер пина RESET (аппаратный сброс устройства);
uint8_t  permitBusSPI:1,linkErr:1,permitPinCS:1;	//--Флаги для работы  с шиной SPI,CS;	 
uint8_t  blockPinDRDY:1, permitPinDRDY:1,  blockIntDRDY:1, permitIntDRDY:1, //--Флаги для работы  с пином DRDY;
		 blockPinRESET:1,permitPinRESET:1, blockSpiDRDY:1;						//--Флаги для работы  с пином RESET;
uint8_t  freshBegin:1;	//--Флаг изменения пользовательских параметров(DRATE,GAIN);					 
uint8_t  busyDRDY;					//--Флаг занятости ADS1256;
//-------------------------------------------------------------------------------------------------
uint8_t  dir=0,  agoDIR=255;					//--Этапы основной программы;
uint8_t  step=0, agoSTEP=255, err,    action;	//--Этапы и флаги функций;	
uint8_t  drdy=0, agoDRDY=255, errDRDY,actDRDY;	//--Этапы и флаги функций;
uint32_t timeBeginDRDY, timeEndDRDY;			//--Рабочие регистры меток времени;
uint8_t  codeErr=0;								//--Код ошибки;
uint8_t  debug=0; uint16_t cntDebug=0;			//--Параметры для отладки;
//-------------------------------------------------------------------------------------------------
//						Флаги управления и состояния
//-------------------------------------------------------------------------------------------------
uint8_t  run,runADC,initOk,beginOk,beginInit,beginFresh=0;	//--Флаги;
uint8_t	 ok=0;					//--Устройство готово (после успешного завершения begin();
uint8_t  fresh,meterOk,clear;	//--События завершения измерения одного канала и группы каналов, очистка выходных данных;
uint32_t timeChannel;			//--Расчетное время измерения одного канала (функция от скорости преобразования);
uint8_t  idx;					//--Рабочий индекс;
//-------------------------------------------------------------------------------------------------
//						Параметры для функции getDRDY()
//-------------------------------------------------------------------------------------------------
uint8_t  vInterruptDRDY=0;	  	//--Флаг взводится функцией внешнего прерывания при переходе пина DRDY 1->0;
uint8_t  cntErrRptDRDY,cntRptDRDY, cntDelayDRDY;	
//-------------------------------------------------------------------------------------------------
//						Состояние регистров ADS1256
//-------------------------------------------------------------------------------------------------
uint8_t  vSTATUS,codeSTATUS,	//--Значение регистра статуса STATUS(0x00),
		 vID=0xE0, 				//   bits 7-4: ID устройства;
		 vBUFEN,				//   bit 1: разрешение буферирования;
		 vDRDY,					//   bit 0: cостояние бита 0 регистра STATUS (дублируется состоянием пина pinDRDY);				
		 codeBUFEN,userBUFEN; 	//   Коды использования буферирования;
uint8_t  vADCON,				//--Значение регистра ADCON(0x02) (контроль A/D);
         vCLKOUT, 				//   bits 6-5: CLK1, CLK0  - установка скорости тактового сигнала D0/CLKOUT.
		 vSDCS,  				//   bits 4-3: SCDS1,SCDS0 - код обнаружения сенсора;
		 vPGA,   				//   bits 2-0: PGA2,PGA1,PGA0 - коэффициент усиления(1,2,4,8,16,32,64,64); 
         codeADCON,				//--Значение для записи в регистр ADCON(;
         codePGA,				//--Код PGA, устанавливается в функции setADCON() как FUNC(codeGAIN); 
		 codeGAIN,userGAIN;		//  Коды коэффициента усиления(1,2,4,8,16,32,64,64);
uint8_t  vDRATE, codeDRATE,		//--Значение регистра DRATE(0x03) (скорость преобразования ADC);
         codeSPS,userSPS;		//--Коды скорости преобразования (0-15);
uint8_t  vMUX,					//--Значение регистра мультиплексора MUX(0x01);
		 codeMUX,				//--Код для записи в регистр мультиплексора;
		 codeMUXP,				//   bits 7-4: код входа+; 
		 codeMUXN;				//   bits 3-0: код входа-; 
//------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------
float    vRef,  userRef=2.5;	//--Опорное напряжение;//
float    vFreq, userFreq=7.68;	//--Частота кварца ADS1256;
float    vConverFactor=1.0, userConverFactor=1.0;	//--Корректирующий коэффициент;//
//-------------------------------------------------------------------------------------------------
//						Результаты измерения ADC
//-------------------------------------------------------------------------------------------------
uint8_t  arr[3];				//--Массив для считывания 3-х байт ADC(24 разряда);
uint32_t vADCraw;  int32_t vADCint;	//--Измеренные значения в формате RAW,int32;			 
float    vADCfloat,vADCvolt;	//------Измеренные значения в формате float,volt;
float    vFactorFV;		    	//--Вспомогательный коэфффициент преобразования float->volt [Func(Ref,PGA,ConverFactor)]; 
uint8_t  arrAI_permit[12]; 		//--Разрешение работы для 12 каналов (AI0-7, AI01,AI23,AI45,AI67
int8_t   numChannel=0; 			//--Текущий номер канала;
uint8_t  cntErrRepeat;			//--Счетчик для обработки одиночных ошибок;
//-------------------------------------------------------------------------------------------------
//						Рабочие буферы
//-------------------------------------------------------------------------------------------------
uint8_t  vReg8,bf8;					//--Буфер для чтения ,байтового регистра;
uint32_t bf32,var;
int16_t  bf16;    
//-------------------------------------------------------------------------------------------------
};
