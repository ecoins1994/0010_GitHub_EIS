////#################################################################################################
//
//                        				API.h для i2c
//ecoins@mail.ru 21.05.2023г.
//=================================================================================================
// AVR     - one  i2c(Wire)  bus, combined master/slave library;
// SAM3X   - one  i2c(Wire)  bus, combined master/slave library;
// ESP8266 - one  i2c(Wire)  bus, combined master/slave library;
// ESP32S  - two  i2c Master bus(Wire1, Wire2) buses,   Wire.h library.
//           two  i2c Slave  bus(WireSlave1,WireSlave2),ESP32_I2C_Slave library.
// Raspberry Pi Pico - two i2c default;
//			 Wire (SDA,SCL) - 0,1; 4,5;  8, 9; 12,13; 16,17; 20,21;
//			 Wire1(SDA,SCL) - 2,3; 6,7; 10,11; 14,15; 18,19; 26,27;
// STM32   - three i2c(Wire) bus, combined master/slave library;
//           Wire is defined by default 
//           Wire1 needs to define TwoWire Wire1(RT_HW_I2C1_SDA, RT_HW_I2C1_SCL),
//           Wire2 needs to define TwoWire Wire2(RT_HW_I2C2_SDA, RT_HW_I2C2_SCL);
// Seeeduino-six bus i2c(Wire,Wire1-5), combined master/slave library;
//=================================================================================================
// code Err0r: 0-ok,1-too much data; 2-Nack on address transfer; 3-Nack on data transfer; 4-another error i2c; 
//             5-time out waitting byte; 
//             50-invalid number bus; 51-invalid address device(>=254), 52-bus i2c no Master;
//			   60,61,62-error number sda,scl;
//			   65-No CORE;
//-------------------------------------------------------------------------------------------------

//=================================================================================================

//=================================================================================================	
//  #define  RT_HW_LINK_I2C			//---FUNCTION CONNECTION DEFINER I2C
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//										0.STRUCTURE FOR I2C
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct RT_HW_STRUCT_I2C {
uint8_t  custom=0;				//--1.Setting option;
uint8_t  status=0;				//--2.State bus: no init=0; Master=1; Slave=2;
uint8_t  codeErr=0;				//--3.Code error; 	
uint8_t  busy=0;  				//--4.busy bus;
//-------------------------------------------------------------------------------------------------
uint8_t  sda=255; 				//--2.pin SDA;
uint8_t  scl=255;				//--3.pin SCL;  
uint8_t  adr=0; 				//--4.Adddress Slave: for Master=0;
uint8_t  cntByte;   			//--5.Received bytes counter;	
//-------------------------------------------------------------------------------------------------
uint8_t  idx=0;					//--9.index;
uint8_t  bf8;   				//--10.Received bytes counter;
uint16_t bf16;					//--11.Buffer for transfer;
//-------------------------------------------------------------------------------------------------
uint32_t speed=RT_HW_I2C_SPEED; //--12.Speed bus;
uint32_t timeBegin;				//--13.Time Begin for time out;
uint32_t timeEnd;				//--14.Time End   for time out;
uint32_t timeOut;   			//--15.Register to timeout when receiving bytes;
};
//=================================================================================================
//									1. CREATE LinkI2Cx
//=================================================================================================

//=================================================================================================
//									1.0. I2C0
//=================================================================================================
#if defined(RT_HW_PERMIT_I2C0)		  
RT_HW_STRUCT_I2C 	LinkI2C0;										
#endif
//=================================================================================================
//									1.1. I2C1
//=================================================================================================
#if defined(RT_HW_PERMIT_I2C1)							
RT_HW_STRUCT_I2C 	LinkI2C1;
#endif
//=================================================================================================
//									1.2. I2C2
//=================================================================================================
#if defined(RT_HW_PERMIT_I2C2)	
RT_HW_STRUCT_I2C 	LinkI2C2;
#endif	//-----------------------------------------------------------------------------------------

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                          		2. INIT PINS, PARAM
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							+++++++ 2.1. Set Pins ++++++
//=================================================================================================
void	 i2cSetPins(uint8_t sda, uint8_t scl, uint8_t bus){
(void)sda; (void)scl; (void)bus;
//=================================================================================================
//									2.1.1. AVR,SAM3X,SAMD21,ANON
//=================================================================================================
#if defined(RT_HW_CORE_AVR) || defined(RT_HW_CORE_SAM3X) || defined(RT_HW_CORE_SAMD21) || defined(RT_HW_CORE_ANON)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C0)
if(bus==0){return;}										//--Successful Exit bus=0;
#endif
//--------------------------------------------------------------------------------------------------
return;											//--Exit by no bus AVR,SAMX,SAMD21,ANON;
#endif
//=================================================================================================
//									2.1.2. ESP8266
//=================================================================================================
#if defined(RT_HW_CORE_ESP8266)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0){
if(sda==scl){i2cSetCodeErr(60,bus); return;}		//--Exit by mistake on SDA=SCL;
if(sda>=16) {i2cSetCodeErr(61,bus); return;}		//--Exit by mistake on SDA;
if(sda>=17) {i2cSetCodeErr(62,bus); return;}		//--Exit by mistake on SCL;
LinkI2C0.sda=sda; LinkI2C0.scl=scl;					//--Set pins SDA,SCL bus=0;
return;   }											//--Successful Exit  bus=0;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1){
if(sda==scl){i2cSetCodeErr(60,bus); return;}	//--Exit by mistake on SDA=SCL;
if(sda>=16) {i2cSetCodeErr(61,bus); return;}	//--Exit by mistake on SDA;
if(sda>=17) {i2cSetCodeErr(62,bus); return;}	//--Exit by mistake on SCL;
LinkI2C1.sda=sda; LinkI2C1.scl=scl;				//--Set pins SDA,SCL bus=1;
return;   }										//--Successful Exit  bus=1;
#endif
//-------------------------------------------------------------------------------------------------
if(sda || scl || bus){return;}; 					//--To block warning C++;
return;												//--Exit by no bus ESP8266;
#endif
//=================================================================================================
//									2.1.3. ESP32
//=================================================================================================
#if defined(RT_HW_CORE_ESP32)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C0)
if(bus==0){
if(sda==scl){i2cSetCodeErr(60,bus); return;}	//--Exit by mistake on SDA=SCL;
if(sda>=34) {i2cSetCodeErr(61,bus); return;}	//--Exit by mistake on SDA;
if(sda>=34) {i2cSetCodeErr(62,bus); return;}	//--Exit by mistake on SCL;
LinkI2C0.sda=sda; LinkI2C0.scl=scl;				//--Set pins SDA,SCL bus=0;
return;   }										//--Successful Exit  bus=0;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C1)
if(bus==0){
if(sda==scl){i2cSetCodeErr(60,bus); return;}	//--Exit by mistake on SDA=SCL;
if(sda>=34) {i2cSetCodeErr(61,bus); return;}	//--Exit by mistake on SDA;
if(sda>=34) {i2cSetCodeErr(62,bus); return;}	//--Exit by mistake on SCL;
LinkI2C1.sda=sda; LinkI2C1.scl=scl;				//--Set pins SDA,SCL bus=0;
return;   }										//--Successful Exit  bus=0;
#endif
//-------------------------------------------------------------------------------------------------
return;											//--Exit by no bus ESP32;
#endif
//=================================================================================================
//									2.1.4. RP2040
//=================================================================================================
#if defined(RT_HW_CORE_RP2040)
i2cSetBuff(0,bus);
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C0)	
//----Wire (SDA,SCL): 0,1; 4,5;  8, 9; 12,13; 16,17; 20,21, 28,29;
if(bus==0){
if(!i2cGetBuff(bus)){if((sda== 0) && (scl== 1)){i2cSetBuff(1,bus);}}
if(!i2cGetBuff(bus)){if((sda== 4) && (scl== 5)){i2cSetBuff(1,bus);}}
if(!i2cGetBuff(bus)){if((sda== 8) && (scl== 9)){i2cSetBuff(1,bus);}}
if(!i2cGetBuff(bus)){if((sda==12) && (scl==13)){i2cSetBuff(1,bus);}}
if(!i2cGetBuff(bus)){if((sda==16) && (scl==17)){i2cSetBuff(1,bus);}}
if(!i2cGetBuff(bus)){if((sda==20) && (scl==21)){i2cSetBuff(1,bus);}}
if(!i2cGetBuff(bus)){if((sda==28) && (scl==29)){i2cSetBuff(1,bus);}}
if( i2cGetBuff(bus)){LinkI2C0.sda=sda; LinkI2C0.scl=scl; return;} 	//--Set pins SDA,SCL bus=0;
return;  }															//--Exit by mistake on SCL,SDA for bus=0;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C1)
//----Wire1(SDA,SCL): 2,3; 6,7; 10,11; 14,15; 18,19; 26,27;
if(bus==1){
if(!i2cGetBuff(bus)){if((sda== 2) && (scl== 3)){i2cSetBuff(1,bus);}}
if(!i2cGetBuff(bus)){if((sda== 6) && (scl== 7)){i2cSetBuff(1,bus);}}
if(!i2cGetBuff(bus)){if((sda==10) && (scl==11)){i2cSetBuff(1,bus);}}
if(!i2cGetBuff(bus)){if((sda==14) && (scl==15)){i2cSetBuff(1,bus);}}
if(!i2cGetBuff(bus)){if((sda==18) && (scl==19)){i2cSetBuff(1,bus);}}
if(!i2cGetBuff(bus)){if((sda==26) && (scl==27)){i2cSetBuff(1,bus);}}
if( i2cGetBuff(bus)){LinkI2C1.sda=sda; LinkI2C1.scl=scl; return;} 	//--Set pins SDA,SCL bus=1;
return;  }															//--Exit by mistake on SCL,SDA for bus=1;
#endif
//-------------------------------------------------------------------------------------------------
return;											//--Exit by no bus RP2040;
#endif
//=================================================================================================
//									2.1.5. STM32
//=================================================================================================
#if defined(RT_HW_CORE_STM32)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C0)
if(bus==0){
if(sda==scl){i2cSetCodeErr(60,bus); return;}	//--Exit by mistake on SDA=SCL;
LinkI2C0.sda=sda; LinkI2C0.scl=scl; 			//--Set pins SDA,SCL bus=1;
return;   }										//--Successful Exit  bus=1;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C1)
if(bus==1){
if(sda==scl){i2cSetCodeErr(60,bus); return;}	//--Exit by mistake on SDA=SCL;
LinkI2C1.sda=sda; LinkI2C1.scl=scl;				//--Set pins SDA,SCL bus=1;
return;   }										//--Successful Exit  bus=1;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C2)
if(bus==2){
if(sda==scl){i2cSetCodeErr(60,bus); return;}	//--Exit by mistake on SDA=SCL;
LinkI2C2.sda=sda; LinkI2C2.scl=scl;				//--Set pins SDA,SCL bus=2;
return;   }										//--Successful Exit  bus=2;
#endif
//-------------------------------------------------------------------------------------------------
return;											//--Exit by no bus STM32;
#endif
//=================================================================================================
//									2.1.6. No CORE									
//=================================================================================================
i2cSetCodeErr(65,bus);								//--Setting codeErr=No CORE;
return;												//--Exit by no bus;
};

//=================================================================================================
//						    		2.2. Init Param All
//=================================================================================================
void    i2cInitParamAll(){
for(uint8_t i=0; i<=6; i++){i2cInitParam(i);}	
}; 
//=================================================================================================
// 		    						2.3. Init default parameters
//=================================================================================================
void    i2cInitParam (uint8_t bus){						
#if defined(RT_HW_PERMIT_I2C0)							
if(bus==0) {LinkI2C0.busy=LinkI2C0.status=LinkI2C0.codeErr=0;	//--clear busy,status,codeErr;
			LinkI2C0.sda =readArrPGM(RT_HW_PGM_PIN_I2C_ID,0);	//--set pin SDA; 
			LinkI2C0.scl =readArrPGM(RT_HW_PGM_PIN_I2C_ID,1);	//--set pin SCL;
			LinkI2C0.speed=RT_HW_I2C_SPEED;            	    //--set speed;
return;}
#endif
#if defined(RT_HW_PERMIT_I2C1) 
if(bus==1){LinkI2C1.busy=LinkI2C1.status=LinkI2C1.codeErr=0;	//--clear busy,status,codeErr;
		   LinkI2C1.sda =readArrPGM(RT_HW_PGM_PIN_I2C_ID,2);	//--set pin SDA; 
		   LinkI2C1.scl =readArrPGM(RT_HW_PGM_PIN_I2C_ID,3);	//--set pin SCL;
		   LinkI2C1.speed=RT_HW_I2C_SPEED;            	    //--set speed;
return;}
#endif
#if defined(RT_HW_PERMIT_I2C2)
if(bus==2){LinkI2C2.busy=LinkI2C2.status=LinkI2C0.codeErr=0;	//--clear busy,status,codeErr;
		   LinkI2C2.sda =readArrPGM(RT_HW_PGM_PIN_I2C_ID,4);	//--set pin SDA; 
		   LinkI2C2.scl =readArrPGM(RT_HW_PGM_PIN_I2C_ID,5);	//--set pin SCL;
		   LinkI2C2.speed=RT_HW_I2C_SPEED;            	    //--set speed; 	
return;}
#endif
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                          		3.INIT DEVICE, FIND ADDRESS DEVICE
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
// 		    						3.1.Set parameters
//=================================================================================================
uint8_t i2cSetParam(RT_HW_STRUCT_I2C_DEV &id, uint8_t adr, uint8_t bus=0, uint32_t speed=0){
(void)adr; (void)bus; (void)speed;
if(id.custom==0){id.link=id.status=id.codeErr=id.err=0; id.adr=adr; id.bus=bus; id.speed=speed; id.custom=1;}
return id.custom;};
//=================================================================================================
// 		    						3.2.Init device 
//=================================================================================================
void  i2cInitDevice(RT_HW_STRUCT_I2C_DEV &id){
id.link=0;
if(id.custom==0){id.codeErr=50; id.link=1; return;} 
if(id.status==1){id.codeErr=0;  id.link=1; return;}
if(id.err==1)   {id.codeErr=51; id.link=1; return;}
id.status=id.codeErr=0;
//------------------------------------------------------------------------------------------------
if(!i2cCheckBus(id.bus))	{id.codeErr=50; id.err=1; id.link=1; return;}	//--Checking bus;
//-------------------------------------------------------------------------------------------------
if(!i2cBegin(id.bus))		{				             		 return;} 	//--Initting  i2c;
if( i2cGetStatus(id.bus)!=1){id.codeErr=52; id.err=1; id.link=1; return;}	//--Checking i2c as Master;
//-------------------------------------------------------------------------------------------------
if(id.speed==0){id.speed=RT_HW_I2C_SPEED;}			//--Normalisation speed;
id.status=i2cGetStatus(id.bus); id.link=1;};		//--Setting output parameters;
//=================================================================================================
// 		    						3.3.i2cBeginTransmission
//=================================================================================================
void  i2cBeginTransmission(RT_HW_STRUCT_I2C_DEV &id){
//i2cSetChannel(id);									//--Installing i2c expander channel;
i2cBeginTransmission(id.adr,id.bus);}; 				//--Begin of transaction adr device;
//=================================================================================================
// 		    						3.4.i2cEndTransmission
//=================================================================================================
void  i2cEndTransmission(RT_HW_STRUCT_I2C_DEV &id){
id.codeErr=i2cEndTransmission(id.bus);}				//--End   of transaction adr device;
//i2cClearChannel(id);};								//--Reset i2c expander channel;
//=================================================================================================
// 		    						3.5.i2SetChannel
//=================================================================================================
void  i2cSetChannel(RT_HW_STRUCT_I2C_DEV &id){
if(id.expander){if((id.channel>0) && (id.channel<=8)){	//--Checking the presence of an expander and an active channel number;
 id.bf8=0; bitSet(id.bf8,(id.channel-1));
 i2cBeginTransmission(id.expander,id.bus);			//--Begin of transaction expander;
 i2cWrite(id.bf8,id.bus);				//--Write On/Off channel;
 i2cEndTransmission(id.bus);}}};						//--End   of transaction expander;
//=================================================================================================
// 		    						3.6.i2cClearChannel
//=================================================================================================
void  i2cClearChannel(RT_HW_STRUCT_I2C_DEV &id){
if(id.expander){									//--Checking the presence of an expander;
 i2cBeginTransmission(id.expander,id.bus);			//--Begin of transaction expander;
 i2cWrite(0,id.bus);								//--Write On/Off channel;
 i2cEndTransmission(id.bus);}};						//--End   of transaction expander;
//=================================================================================================
// 		    						3.2.Finding an address on the i2c bus
//=================================================================================================
void  i2cFindAdr(RT_HW_STRUCT_I2C_DEV &id){ 
id.link=0;											//--Clearing link;
if(i2cSetBusy  (id.bus)==0) {return;}; 				//--i2c bus capture;
i2cSetClock(id.speed,id.bus);						//--Set speed for device;
i2cSetChannel(id);									//--Installing i2c expander channel;
//-------------------------------------------------------------------------------------------------
i2cBeginTransmission(id); 							//--Begin of transaction;	
i2cEndTransmission(id);								//--End   of transaction;
//-------------------------------------------------------------------------------------------------
i2cClearChannel(id);								//--Reset i2c expander channel;		
i2cSetClock(i2cGetSpeed(id.bus),id.bus);			//--Set speed default;
i2cClearBusy(id.bus); 								//--i2c bus   release;
id.link=1;};										//--Setting link and EXIT;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                          		4.Write/Read byte, arr[]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
// 		    						4.1. Write byte
//=================================================================================================
void i2cWrite(RT_HW_STRUCT_I2C_DEV &id, uint8_t var){
id.link=0;											//--Clearing link;
if(i2cGetStatus(id.bus)!=1) {id.link=1; return;}	//--Exit if i2c is not Master;
if(i2cSetBusy  (id.bus)==0) {           return;}; 	//--i2c bus capture;
i2cSetClock(id.speed,id.bus);						//--Set speed for device;
i2cSetChannel(id);									//--Installing i2c expander channel;
//-------------------------------------------------------------------------------------------------
i2cBeginTransmission(id); 							//--Begin of transaction;	
i2cWrite(var,id.bus); 								//--Sending byte;
i2cEndTransmission(id);								//--End   of transaction;
//-------------------------------------------------------------------------------------------------
i2cClearChannel(id);								//--Reset i2c expander channel;	
i2cSetClock(i2cGetSpeed(id.bus),id.bus);			//--Set speed default;
i2cClearBusy(id.bus); 								//--i2c bus   release;	
id.link=1;};										//--Setting link and EXIT;
//=================================================================================================
// 		    						4.2. Write arr[]
//=================================================================================================
void i2cWriteArr(RT_HW_STRUCT_I2C_DEV &id, uint8_t *arr, uint8_t qnt){
id.link=0; if(qnt>32) {qnt=32;};					//--Clearing link, Limiting the number of bytes sent;
if(i2cGetStatus(id.bus)!=1) {id.link=1; return;}	//--Exit if i2c is not Master;
if(i2cSetBusy  (id.bus)==0) {		    return;}; 	//--i2c bus capture;
i2cSetClock(id.speed,id.bus);						//--Setting speed for device;
i2cSetChannel(id);									//--Installing i2c expander channel;
//-------------------------------------------------------------------------------------------------
i2cBeginTransmission(id); 							//--Begin of transaction;;	
for(id.idx=0; id.idx<qnt; id.idx++){i2cWrite(arr[id.idx],id.bus);} //--Send qnt bytes;
id.codeErr=i2cEndTransmission(id.bus);				//--End   of transaction;
//-------------------------------------------------------------------------------------------------
i2cClearChannel(id);								//--Reset i2c expander channel;	
i2cSetClock(i2cGetSpeed(id.bus),id.bus);			//--Setting speed default;
i2cClearBusy(id.bus); 								//--i2c bus release;	
id.link=1;};										//--Setting link and EXIT;
//=================================================================================================
// 		    						4.3. Get byte to buff
//=================================================================================================
void i2cRead(RT_HW_STRUCT_I2C_DEV &id){ 
id.link=0;											//--Clearing link;
//-------------------------------------------------------------------------------------------------
if(i2cGetStatus(id.bus)!=1) {id.link=1; return;}	//--Exit if i2c is not Master;
if(i2cSetBusy  (id.bus)==0) {		    return;}; 	//--i2c bus capture;
i2cSetClock(id.speed,id.bus);						//--Setting speed for device;
i2cSetChannel(id);									//--Installing i2c expander channel;
//-------------------------------------------------------------------------------------------------
id.codeErr=0;										//--Cleanig code error;
id.cnt=i2cRequestFrom(1,id.adr,id.bus,id.stop);		//--Requestting byte;
if(id.cnt!=1){id.codeErr=5;}						//--if the number of received bytes does not match the requested;
//-------------------------------------------------------------------------------------------------
if(id.codeErr==0){									//--Checking code error;
 i2cInitTimeOut(id.bus);							//--Setting start time out;
 id.bf8=100;										//--Setting size  time out;
 do{id.cnt=i2cAvailable(id.bus);					//--Сhecking the receive buffer i2c;
    if(id.cnt>=1){break;}							//--Checking buffer completion;
    if(i2cGetPastTime(id.bus)>(id.bf8)){id.codeErr=6;}	//--Checking time out;
   }while(1);    }									//--Waitting for the DO loop;
//-------------------------------------------------------------------------------------------------
id.bf8=0; if(id.codeErr==0){id.bf8=i2cRead(id.bus);}//--Reading a byte from the i2c buffer;
//-------------------------------------------------------------------------------------------------
i2cClearChannel(id);								//--Reset i2c expander channel;	
i2cSetClock(i2cGetSpeed(id.bus),id.bus);	 		//--Setting speed default;
i2cClearBusy(id.bus); 								//--i2c bus release;
id.link=1;};										//--Setting link and EXIT;	
//=================================================================================================
// 		    						4.4. Get qnt bytes to arr
//=================================================================================================
void i2cReadArr(RT_HW_STRUCT_I2C_DEV &id, uint8_t *arr, uint8_t qnt){ 
id.link=0; if(qnt>32) {qnt=32;};					//--Clearing link, Limiting the number of bytes sent;
//-------------------------------------------------------------------------------------------------
if(i2cGetStatus(id.bus)!=1) {id.link=1; return;}	//--Exit if i2c is not Master;
if(i2cSetBusy  (id.bus)==0) {		    return;}; 	//--i2c bus capture;
i2cSetClock(id.speed,id.bus);						//--Setting speed for device;
i2cSetChannel(id);									//--Installing i2c expander channel;
//-------------------------------------------------------------------------------------------------
id.codeErr=0;										//--Cleanig code error;
id.cnt=i2cRequestFrom(qnt,id.adr,id.bus,id.stop);	//--Requestting qnt bytes;
if(id.cnt!=qnt){id.codeErr=5;}						//--if the number of received bytes does not match the requested;
//-------------------------------------------------------------------------------------------------
if(id.codeErr==0){									//--Checking code error;
 i2cInitTimeOut(id.bus);							//--Setting start time out;
 id.bf8=100;										//--Setting size  time out;
 do{id.cnt=i2cAvailable(id.bus);					//--Сhecking the receive buffer i2c;
    if(id.cnt>=qnt){break;}							//--Checking buffer completion;
    if(i2cGetPastTime(id.bus)>(id.bf8*qnt)){id.codeErr=6;}	//--Checking time out;
   }while(1);    }									//--Waitting for the DO loop;				  
//-------------------------------------------------------------------------------------------------
if(i2cGetCodeErr(id.bus)==0){for(id.idx=0; id.idx<qnt; id.idx++){arr[id.idx]=i2cRead(id.bus);}}//--Reading qnt bytes from the i2c buffer;					
//-------------------------------------------------------------------------------------------------
i2cClearChannel(id);								//--Reset i2c expander channel;	
i2cSetClock(i2cGetSpeed(id.bus),id.bus);	 		//--Setting speed default;
i2cClearBusy(id.bus); 								//--i2c bus release;
id.link=1;};										//--Setting link and EXIT;
//=================================================================================================
// 		    						4.5. Reading a byte from the start register
//=================================================================================================
void i2cREAD(RT_HW_STRUCT_I2C_DEV &id, uint8_t reg){
id.link=0;											//--Clearing link;
//-------------------------------------------------------------------------------------------------
if(i2cGetStatus(id.bus)!=1) {id.link=1; return;}	//--Exit if i2c is not Master;
if(i2cSetBusy  (id.bus)==0) {		    return;}; 	//--i2c bus capture;
i2cSetClock(id.speed,id.bus);						//--Setting speed for device;
i2cSetChannel(id);									//--Installing i2c expander channel;
//-------------------------------------------------------------------------------------------------
i2cBeginTransmission(id); 							//--Begin of transaction;	
i2cWrite(reg,id.bus); 								//--Sending byte;
i2cEndTransmission(id);								//--End   of transaction;
//------------------------------------------------------------------------------------------------
if(id.codeErr==0){									//--Checking code error;
id.cnt=i2cRequestFrom(1,id.adr,id.bus,id.stop);		//--Requestting byte;
if(id.cnt!=1){id.codeErr=5;}}						//--if the number of received bytes does not match the requested;
//-------------------------------------------------------------------------------------------------
if(id.codeErr==0){									//--Checking code error;
 i2cInitTimeOut(id.bus);							//--Setting start time out;
 id.bf8=100;										//--Setting size  time out;
 do{id.cnt=i2cAvailable(id.bus);					//--Сhecking the receive buffer i2c;
    if(id.cnt>=1){break;}							//--Checking buffer completion;
    if(i2cGetPastTime(id.bus)>(id.bf8)){id.codeErr=6;}//Checking time out;
   }while(1);    }									//--Waitting for the DO loop;
//-------------------------------------------------------------------------------------------------   
id.bf8=0; if(id.codeErr==0){id.bf8=i2cRead(id.bus);}//--Reading a byte from the i2c buffer;
//-------------------------------------------------------------------------------------------------
i2cClearChannel(id);								//--Reset i2c expander channel;	
i2cSetClock(i2cGetSpeed(id.bus),id.bus);	 		//--Setting speed default;
i2cClearBusy(id.bus); 								//--i2c bus release;
id.link=1;};										//--Setting link and EXIT;	
//=================================================================================================
// 		    						4.6. Reading a bytes from the start register
//=================================================================================================
void i2cREADArr(RT_HW_STRUCT_I2C_DEV &id, uint8_t reg, uint8_t *arr, uint8_t qnt){
id.link=0;
//-------------------------------------------------------------------------------------------------
if(i2cGetStatus(id.bus)!=1) {id.link=1; return;}	//--Exit if i2c is not Master;
if(i2cSetBusy  (id.bus)==0) {		    return;}; 	//--i2c bus capture;
i2cSetClock(id.speed,id.bus);						//--Setting speed for device;
i2cSetChannel(id);									//--Installing i2c expander channel;
id.codeErr=0;										//--Cleanig code error;
if(qnt>32){qnt=32;}									//--Limiting the number of requested bytes;
//-------------------------------------------------------------------------------------------------
i2cBeginTransmission(id); 							//--Begin of transaction;	
i2cWrite(reg,id.bus); 								//--Sending byte;
i2cEndTransmission(id);								//--End   of transaction;
//------------------------------------------------------------------------------------------------
if(i2cGetCodeErr(id.bus)==0){						//--Checking code error;
 i2cSetCntByte(i2cRequestFrom(qnt,id.adr,id.bus,id.stop),id.bus); //--Request a byte;									
 if(i2cGetCntByte(id.bus)!=qnt){i2cSetCodeErr(5,id.bus);}//-if the number of received bytes does not match the requested;
}
//-------------------------------------------------------------------------------------------------
if(id.codeErr==0){									//--Checking code error;
 i2cInitTimeOut(id.bus);							//--Setting start time out;
 id.bf8=100;										//--Setting size  time out;
 do{id.cnt=i2cAvailable(id.bus);					//--Сhecking the receive buffer i2c;
    if(id.cnt>=qnt){break;}							//--Checking buffer completion;
    if(i2cGetPastTime(id.bus)>(id.bf8)){id.codeErr=6;}	//--Checking time out;
   }while(1);										//--Waitting for the DO loop;
} 
id.bf8=0;
//-------------------------------------------------------------------------------------------------   
if(i2cGetCodeErr(id.bus)==0){for(id.idx=0; id.idx<qnt; id.idx++){arr[id.idx]=i2cRead(id.bus);}}//--Reading qnt bytes from the i2c buffer;	
//-------------------------------------------------------------------------------------------------
i2cClearChannel(id);								//--Reset i2c expander channel;	
i2cSetClock(i2cGetSpeed(id.bus),id.bus);	 		//--Setting speed default;
i2cClearBusy(id.bus); 								//--i2c bus release;
id.link=1;};										//--Setting link and EXIT;	
//=================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//									10.Exchange functions
// codeErr: 0-ok, 1-too much data; 2-Nack to transfer the address; 3-Nack on data transmission; 4-other i2c error;
// 5 - invalid controller; 6-invalid tire; 7 - invalid address (>=254), 8 - bus not configured as master, 8 other reasons; 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void     i2cSetClock (uint32_t speed,uint8_t bus);		//--Speed setting (hardware);
void     i2cBeginTransmission(uint8_t adr, uint8_t bus);//--Start of a hardware transaction;
uint8_t  i2cEndTransmission  (uint8_t bus);				//--End   of a hardware transaction;
uint8_t  i2cFlush            (uint8_t bus);				//--Flush();
uint8_t  i2cAvailable        (uint8_t bus);				//--Checking the number of received bytes in the i2c buffer;
uint8_t  i2cRead             (uint8_t bus);				//--Reading a byte from an i2c buffer;
void     i2cWrite(uint8_t var,uint8_t bus);				//--Write a byte;
void     i2cWrite(const uint8_t *arr, uint8_t qnt, uint8_t bus);//--Writing qnt bytes;
void     i2cWrite(const char    *arr, uint8_t qnt, uint8_t bus);//--Writing qnt char;
uint8_t  i2cRequestFrom(uint8_t qnt,  uint8_t adr, uint8_t bus, uint8_t sendStop=1);//--Reading qnt bytes from the specified register(reg);
//=================================================================================================
uint8_t  i2cBegin(uint8_t bus);							//--init i2c as Master;
uint8_t  i2cBegin(uint8_t adr, uint8_t bus);			//--init i2c as Slave;

//#################################################################################################
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//									1.Utilities for Internal Functions 
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									1.1. Check bus
//=================================================================================================
uint8_t  i2cCheckBus(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {return 1;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {return 1;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {return 1;}
#endif
//-------------------------------------
return 0;};
//=================================================================================================
// 									1.2.1. Get address
//=================================================================================================
uint8_t  i2cGetAdr(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {return LinkI2C0.adr;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {return LinkI2C1.adr;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {return LinkI2C2.adr;}
#endif
//-------------------------------------
if(bus) {return 255;}		//--To block warning C++;
return 255;};
//=================================================================================================
// 									1.2.2. Set address
//=================================================================================================
void     i2cSetAdr(uint8_t adr,	uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {LinkI2C0.adr=adr; return;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {LinkI2C1.adr=adr; return;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {LinkI2C2.adr=adr; return;}
#endif
//-------------------------------------
if(adr || bus){return;}	//--To block warning C++;
};
//=================================================================================================
// 									1.3.1. Get status
//=================================================================================================
uint8_t  i2cGetStatus(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {return LinkI2C0.status;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {return LinkI2C1.status;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {return LinkI2C2.status;}
#endif
//-------------------------------------
if(bus){return 0;}	//--To block warning C++;
return 0;};
//=================================================================================================
// 									1.3.2. Set status
//=================================================================================================
void     i2cSetStatus(uint8_t var, uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {LinkI2C0.status=var; return;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {LinkI2C1.status=var; return;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {LinkI2C2.status=var; return;}
#endif
//-------------------------------------
if(var || bus){return;}	//--To block warning C++;
};
//=================================================================================================
// 									1.4.1. Get code error
//=================================================================================================
uint8_t  i2cGetCodeErr(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {return LinkI2C0.codeErr;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {return LinkI2C1.codeErr;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {return LinkI2C2.status;}
#endif
//-------------------------------------
if(bus){return 0;}	//--To block warning C++;
return 0;};
//=================================================================================================
// 									1.4.2. Set code error
//=================================================================================================
void 	 i2cSetCodeErr(uint8_t var, uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {LinkI2C0.codeErr=var; return;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {LinkI2C1.codeErr=var; return;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {LinkI2C2.codeErr=var; return;}
#endif
//-------------------------------------
if(var || bus){return;}	//--To block warning C++;
};
//=================================================================================================
// 									1.4.3. Clear code error
//=================================================================================================
void 	 i2cClearCodeErr(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {LinkI2C0.codeErr=0; return;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {LinkI2C1.codeErr=0; return;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {LinkI2C2.codeErr=0; return;}
#endif
//-------------------------------------
if(bus){return;}	//--To block warning C++;
};
//=================================================================================================
//									1.5.1. Check busy
//=================================================================================================
uint8_t  i2cCheckBusy (uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {if(LinkI2C0.busy){return 1;} return 0;} 
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {if(LinkI2C1.busy){return 1;} return 0;} 
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {if(LinkI2C2.busy){return 1;} return 0;} 
#endif
//-------------------------------------
if(bus){return 0;}	//--To block warning C++;
return 0;};
//=================================================================================================
//									1.5.2. Capture bus
//=================================================================================================
uint8_t  i2cSetBusy(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {if(LinkI2C0.busy==0){LinkI2C0.busy=1;}  if(LinkI2C0.busy==0){LinkI2C0.busy=1;}; return LinkI2C0.busy;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {if(LinkI2C1.busy==0){LinkI2C1.busy=1;}  if(LinkI2C1.busy==0){LinkI2C1.busy=1;}; return LinkI2C1.busy;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {if(LinkI2C2.busy==0){LinkI2C2.busy=1;}  if(LinkI2C2.busy==0){LinkI2C2.busy=1;}; return LinkI2C2.busy;}
#endif
//-------------------------------------
if(bus){return 0;}	//--To block warning C++;
return 0;};
//=================================================================================================
//									1.5.3. Release bus
//=================================================================================================
void     i2cClearBusy(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {LinkI2C0.busy=0; return;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {LinkI2C1.busy=0; return;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {LinkI2C2.busy=0; return;}
#endif
//-------------------------------------
if(bus){return;}	//--To block warning C++;
return;};
//=================================================================================================
//									===1.6.1. Get index
//=================================================================================================
uint8_t  i2cIdxGet(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {return LinkI2C0.idx;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {return LinkI2C1.idx;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {return LinkI2C2.idx;}
#endif
//-------------------------------------
if(bus){return 0;}; //--For blocking warnings from C++;
return 0;}
//=================================================================================================
//									===1.6.2. Clear index
//=================================================================================================
void    i2cIdxClear(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {LinkI2C0.idx=0; return;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {LinkI2C1.idx=0; return;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {LinkI2C2.idx=0; return;}
#endif
//-------------------------------------
if(bus){return;}; //--For blocking warnings from C++;;
};
//=================================================================================================
//									===1.6.3. Increment index
//=================================================================================================
void    i2cIdxInc(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {LinkI2C0.idx++; return;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {LinkI2C1.idx++; return;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {LinkI2C2.idx++; return;}
#endif
//-------------------------------------
if(bus){return;}; //--For blocking warnings from C++;
};
//=================================================================================================
//								 	===1.6.4. Set index
//=================================================================================================
void    i2cIdxSet(uint8_t var, uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {LinkI2C0.idx=var; return;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {LinkI2C1.idx=var; return;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {LinkI2C2.idx=var; return;}
#endif
//-------------------------------------
if(var || bus){return;}; //--For blocking warnings from C++;
};
//=================================================================================================
//									===1.7.1. Get Buff
//=================================================================================================
uint8_t  i2cGetBuff(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {return LinkI2C0.bf8;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {return LinkI2C1.bf8;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {return LinkI2C2.bf8;}
#endif
//-------------------------------------
if(bus){return 0;}; //--For blocking warnings from C++;
return 0;}
//=================================================================================================
//								 	===1.7.2. Set buff
//=================================================================================================
void    i2cSetBuff(uint8_t var, uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {LinkI2C0.bf8=var; return;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {LinkI2C1.bf8=var; return;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {LinkI2C2.bf8=var; return;}
#endif
//-------------------------------------
if(var || bus){return;}; //--For blocking warnings from C++;
};

//=================================================================================================
// 									1.8.1. Get speed
//=================================================================================================
uint32_t i2cGetSpeed (uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {return LinkI2C0.speed;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {return LinkI2C1.speed;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {return LinkI2C2.speed;}
#endif
//-------------------------------------
if(bus) {return RT_HW_I2C_SPEED;}		//--To block warning C++;
return RT_HW_I2C_SPEED;};
//=================================================================================================
// 									1.8.2. Set speed
//=================================================================================================
void     i2cSetSpeed (uint8_t bus, uint32_t speed=0){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {if(speed>0){LinkI2C0.speed=speed;  return;}}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {if(speed>0){LinkI2C1.speed=speed;  return;}}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {if(speed>0){LinkI2C2.speed=speed;  return;}}
#endif
//-------------------------------------
if(speed || bus){return;}; //--For blocking warnings from C++;
};
//=================================================================================================
// 									====1.9.1. Set TimeOut
//=================================================================================================
void     i2cSetTimeOut(uint32_t vTm, uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {LinkI2C0.timeOut=vTm; return;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {LinkI2C1.timeOut=vTm; return;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {LinkI2C2.timеOut=vTm; return;}
#endif
//-------------------------------------
if(vTm || bus){return;}		//--To block warning C++;
};
//=================================================================================================
// 									===1.9.2. Get TimeOut
//=================================================================================================
uint32_t i2cGetTimeOut(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {return LinkI2C0.timeOut;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {return LinkI2C1.timeOut;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {return LinkI2C2.timeOut;}
#endif
//-------------------------------------
if(bus){return 0;}			//--To block warning C++;
return 0;};

//=================================================================================================
// 									1.9.3. Init time out
//=================================================================================================
void i2cInitTimeOut(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {LinkI2C0.timeBegin=micros();}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {LinkI2C1.timeBegin=micros();}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {LinkI2C2.timeBegin=micros();}
#endif
//-------------------------------------
if(bus){return;}			//--To block warning C++;
};

//=================================================================================================
// 									1.9.4. Get past time out
//=================================================================================================
uint32_t i2cGetPastTime(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {LinkI2C0.timeEnd=micros(); 
if(LinkI2C0.timeEnd>=LinkI2C0.timeBegin){return (LinkI2C0.timeEnd-LinkI2C0.timeBegin);} else {return(0xFFFFFFFF-LinkI2C0.timeBegin+LinkI2C0.timeEnd);}}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {LinkI2C1.timeEnd=micros(); 
if(LinkI2C1.timeEnd>=LinkI2C1.timeBegin){return (LinkI2C1.timeEnd-LinkI2C1.timeBegin);} else {return(0xFFFFFFFF-LinkI2C1.timeBegin+LinkI2C1.timeEnd);}}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==0) {LinkI2C2.timeEnd=micros(); 
if(LinkI2C2.timeEnd>=LinkI2C2.timeBegin){return (LinkI2C2.timeEnd-LinkI2C2.timeBegin);} else {return(0xFFFFFFFF-LinkI2C2.timeBegin+LinkI2C2.timeEnd);}}
#endif
//-------------------------------------
if(bus){return 0;}			//--To block warning C++;
return 0;};

//=================================================================================================
// 									===1.10.1. Set counter byte
//=================================================================================================
void     i2cSetCntByte(uint8_t  cnt, uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {LinkI2C0.cntByte=cnt; return;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {LinkI2C1.cntByte=cnt; return;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {LinkI2C2.cntByte=cnt; return;}
#endif
//-------------------------------------
if(cnt || bus){return;}			//--To block warning C++;
};
//=================================================================================================
// 									===1.10.2. Set counter byte
//=================================================================================================
uint8_t  i2cGetCntByte(       		uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {return LinkI2C0.cntByte;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {return LinkI2C1.cntByte;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {return LinkI2C2.cntByte;}
#endif
//-------------------------------------
if(bus){return 0;}			//--To block warning C++;
return 0;};
//=================================================================================================
// 									1.11.1. Get pin SCL
//=================================================================================================
uint8_t  i2cGetPinSCL(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {return LinkI2C0.scl;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {return LinkI2C1.scl;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {return LinkI2C2.scl;}
#endif
//-------------------------------------
if(bus) {return 255;}		//--To block warning C++;
return 255;};
//=================================================================================================
// 									1.11.2. Get pin SDA
//=================================================================================================
uint8_t  i2cGetPinSDA(uint8_t bus){
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0) {return LinkI2C0.sda;}
#endif
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1) {return LinkI2C1.sda;}
#endif
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==2) {return LinkI2C2.sda;}
#endif
//-------------------------------------
if(bus) {return 255;}		//--To block warning C++;
return 255;};	

//#################################################################################################
