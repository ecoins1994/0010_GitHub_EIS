#ifdef RT_HW_TEST_PERMIT_LCD5_NEXT
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//============================1.Objects and variables Nexttion===========================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                   0.3.Generators, counter
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
RT_HW_GENERATOR_EVENT_ID idGenNextRun;  RT_HW_COUNTER_ID idCntNextRun;  uint8_t   vCntNextRun,vGenNextRun;  //--For generator running "1" 0-8;
RT_HW_GENERATOR_EVENT_ID idGenNextDAC;  RT_HW_COUNTER_ID idCntNextDAC;  uint16_t  vGenNextDAC=0;            //--For generator DAC;
//-------------------------------------------------------------------------------------------------
//=================================================================================================
void genNextion(){         
if(idCntNextRun.reset){RT_HW_Base.counterReset(idCntNextRun,8,0,1,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(RT_HW_Base.generatorEvent(idGenNextRun,150)) {vCntNextRun=RT_HW_Base.counterT(idCntNextRun);} vGenNextRun=RT_HW_Base.dc8(vCntNextRun);
//------------------------------------------------------------------------------------------------
if(idCntNextDAC.reset){RT_HW_Base.counterReset(idCntNextDAC,4095,0,50,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(RT_HW_Base.generatorEvent(idGenNextDAC,50)) {vGenNextDAC=RT_HW_Base.counterT(idCntNextDAC);} 
};
//=================================================================================================
//----------------------------1.1.Common control unit----------------------------------
RT_HW_STRUCT_NEXT_DEVICE  nxt;            //--Common control unit;
#define nxtSizeByte 20                    //--Receive array size uint8_t;
#define nxtSizeWord 2                     //--Receive array size uint16_t;
#define nxtSizeLong 2                     //--Receive array size uint32_t;
uint8_t  nxtArrByte[nxtSizeByte + 1];     //--Array for input variables uint8_t;
uint16_t nxtArrWord[nxtSizeWord + 1];     //--Array for input variables uint16_t;
uint32_t nxtArrLong[nxtSizeLong + 1];     //--Array for input variables uint32_t;
//--------------------------------------------------------------------------------------
uint8_t nxtNum=0;
//---------------------------1.2.Output blocks-------------------------------------------
RT_HW_STRUCT_NEXT_WRITE_VAR nxt0;   //--System flags;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt2;   //--Speed CORE0;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt3;   //--Speed CORE1;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt4;   //--Operating time;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt8;   //--Flags of sensors, expanders;  
//--------------------------------------------------------------------------------------
RT_HW_STRUCT_NEXT_WRITE_VAR nxt10;  //--Running "1";
RT_HW_STRUCT_NEXT_WRITE_VAR nxt11;  //--PWM;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt12;  //--ADC(0-4095)
RT_HW_STRUCT_NEXT_WRITE_VAR nxt13;  //--Triangle generator(0-4095);
RT_HW_STRUCT_NEXT_WRITE_VAR nxt14;  //--MCP4725(0-4095);
RT_HW_STRUCT_NEXT_WRITE_VAR nxt15;  //--MCP23017;
//--------------------------------------------------------------------------------------
RT_HW_STRUCT_NEXT_WRITE_VAR nxt30;  //--AHTxx.Temp;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt31;  //--AHTxx.Hum;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt32;  //--DS1820.Temp;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt33;  //--HC-SR04.Len;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt34;  //--MAX6675.Temp;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt35;  //--BH1750.Lux;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt36;  //--BMPx80.Press;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt37;  //--SHT3x.Temp;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt38;  //--SHT3x.Hum;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt39;  //--DHT22.Temp;
RT_HW_STRUCT_NEXT_WRITE_VAR nxt40;  //--DHT22.Hum;
//======================================================================================
//                                  2.Nextion setup
//======================================================================================
void Lcd5_Nextion(){
genNextion();
//--------------------------------------------------------------------------------------
if(nxt.custom==0){
  nxt.uart=uartNextion;   //--Установка номера UART;
  nxt.speed=115200;       //--Установка скорости UART;
  RT_HW_Next.setDeviceID (nxt,nxtArrByte, nxtArrWord, nxtArrLong, nxtSizeByte, nxtSizeWord, nxtSizeLong);
  nxtNum=nxt.num; }
//======================================================================================
//                                  3.Control Nextion
//======================================================================================
RT_HW_Next.direct(nxt); 
//======================================================================================
//                                  4.Read Nextion
//======================================================================================
nxtPage=RT_HW_Next.getSystem(nxt.num,'P');
nxtVr1=RT_HW_Next.getVarArr (nxt.num,0);
nxtVr2=RT_HW_Next.getVarArr (nxt.num,1);
nxtVr3=RT_HW_Next.getVarArr (nxt.num,2);
nxtVr4=RT_HW_Next.getVarArr (nxt.num,3);
//======================================================================================
//                                  4.Output Nextion
//======================================================================================
//-------------------------------4.0.System flags---------------------------------------
if(nxt0.custom==0) {RT_HW_Next.setVarID(nxt0, nxtNum,'A',100,2500); nxt0.numReg=0;}     RT_HW_Next.directTask(nxt0); 
if(nxt0.run>0)     {                                   nxt0.var=flagSystem;}            RT_HW_Next.sendINXX(  nxt0);
//-------------------------------4.2.Speed CORE0----------------------------------------
if(nxt2.custom==0) {RT_HW_Next.setVarID(nxt2, nxtNum,'A',500,2500); nxt2.numReg=2;}     RT_HW_Next.directTask(nxt2); 
if(nxt2.run>0)     {                    nxt2.var=vSpeedMCUF;}                           RT_HW_Next.sendINXX(  nxt2);
//-------------------------------4.3.Speed CORE1-------------------------------
if(nxt3.custom==0) {RT_HW_Next.setVarID(nxt3, nxtNum,'A',500,2500); nxt3.numReg=3;}     RT_HW_Next.directTask(nxt3); 
if(nxt3.run>0)     {                    nxt3.var=vspeedMCUF;}                           RT_HW_Next.sendINXX  (nxt3);
//-------------------------------4.4.Operating time-------------------------------------
if(nxt4.custom==0) {RT_HW_Next.setVarID(nxt4, nxtNum,'A',500,2500); nxt4.numReg=4;}     RT_HW_Next.directTask(nxt4); 
if(nxt4.run>0)     {                    nxt4.var=RT_HW_Base.shed.cntSec;}               RT_HW_Next.sendINXX  (nxt4);
//-------------------------------4.8.Device flags---------------------------------------
if(nxt8.custom==0) {RT_HW_Next.setVarID(nxt8, nxtNum,'A',50,2500);  nxt8.numReg=8;}     RT_HW_Next.directTask(nxt8); 
if(nxt8.run>0)     {                                    nxt8.var=flagDevice;}           RT_HW_Next.sendINXX(  nxt8);
//=======================================================================================
//-------------------------------4.10.Running "1"----------------------------------------
if(nxt10.custom==0){RT_HW_Next.setVarID(nxt10,nxtNum,'A',100,2500); nxt10.numReg=10;}   RT_HW_Next.directTask(nxt10); 
if(nxt10.run>0)    {                    nxt10.var=vGenNextRun;}                         RT_HW_Next.sendINXX  (nxt10);
//-------------------------------4.11.PWM-----------------------------------------------
if(nxt11.custom==0){RT_HW_Next.setVarID(nxt11,nxtNum,'A',500,2500); nxt11.numReg=11;}   RT_HW_Next.directTask(nxt11); 
if(nxt11.run>0)    {                    nxt11.var=vPWM;}                                RT_HW_Next.sendINXX  (nxt11);
//-------------------------------4.12.Operating time------------------------------------
if(nxt12.custom==0){RT_HW_Next.setVarID(nxt12,nxtNum,'A',100,2500); nxt12.numReg=12;}   RT_HW_Next.directTask(nxt12); 
if(nxt12.run>0)    {                    nxt12.var=vADCF;}                               RT_HW_Next.sendINXX  (nxt12);
//-------------------------------4.13.Generatot Cnt-------------------------------------
if(nxt13.custom==0){RT_HW_Next.setVarID(nxt13,nxtNum,'A',100,2500); nxt13.numReg=13;}   RT_HW_Next.directTask(nxt13); 
if(nxt13.run>0)    {                    nxt13.var=vGenNextDAC;}                         RT_HW_Next.sendINXX  (nxt13);
//=======================================================================================
//-------------------------------4.30.AHTxx.Temp-----------------------------------------
if(nxt30.custom==0){RT_HW_Next.setVarID(nxt30,nxtNum,'A',1000,2500); nxt30.numReg=30;}  RT_HW_Next.directTask(nxt30); 
if(nxt30.run>0)    {                    nxt30.var=(int32_t)(vAHTxx_Temp*100);}          RT_HW_Next.sendINXX  (nxt30);
//-------------------------------4.31.AHTxx.Hum------------------------------------------
if(nxt31.custom==0){RT_HW_Next.setVarID(nxt31,nxtNum,'A',1000,2500); nxt31.numReg=31;}  RT_HW_Next.directTask(nxt31); 
if(nxt31.run>0)    {                    nxt31.var=(int32_t)(vAHTxx_Hum*100);}           RT_HW_Next.sendINXX  (nxt31);
//-------------------------------4.32.DS1820.Temp-----------------------------------------
if(nxt32.custom==0){RT_HW_Next.setVarID(nxt32,nxtNum,'A',500,2500); nxt32.numReg=32;}   RT_HW_Next.directTask(nxt32); 
if(nxt32.run>0)    {                    nxt32.var=(int32_t)(vDS1820Temp*100);}          RT_HW_Next.sendINXX  (nxt32);
//-------------------------------4.33.HC-SR04.Len------------------------------------------
if(nxt33.custom==0){RT_HW_Next.setVarID(nxt33,nxtNum,'A',100,2500); nxt33.numReg=33;}   RT_HW_Next.directTask(nxt33); 
if(nxt33.run>0)    {                    nxt33.var=vSR04Len;}                            RT_HW_Next.sendINXX  (nxt33);
//-------------------------------4.34.DS1820.Temp-----------------------------------------
if(nxt34.custom==0){RT_HW_Next.setVarID(nxt34,nxtNum,'A',500,2500); nxt34.numReg=34;}   RT_HW_Next.directTask(nxt34); 
if(nxt34.run>0)    {                    nxt34.var=(int32_t)(vMAX6675Temp*100);}         RT_HW_Next.sendINXX  (nxt34);
//-------------------------------4.35.BH1750.Lux------------------------------------------
if(nxt35.custom==0){RT_HW_Next.setVarID(nxt35,nxtNum,'A',1000,2500); nxt35.numReg=35;}  RT_HW_Next.directTask(nxt35); 
if(nxt35.run>0)    {                    nxt35.var=vBH1750Lux;}                          RT_HW_Next.sendINXX  (nxt35);
//-------------------------------4.36.BME280.Press------------------------------------------
if(nxt36.custom==0){RT_HW_Next.setVarID(nxt36,nxtNum,'A',1000,2500); nxt36.numReg=36;}  RT_HW_Next.directTask(nxt36); 
if(nxt36.run>0)    {                    nxt36.var=(int32_t)(vBME280_Press*100);}        RT_HW_Next.sendINXX  (nxt36);
//-------------------------------4.37.SHTxx.Temp-----------------------------------------
if(nxt37.custom==0){RT_HW_Next.setVarID(nxt37,nxtNum,'A',1000,2500); nxt37.numReg=37;}  RT_HW_Next.directTask(nxt37); 
if(nxt37.run>0)    {                    nxt37.var=(int32_t)(vSHT3x_Temp*100);}          RT_HW_Next.sendINXX  (nxt37);
//-------------------------------4.38.SHTxx.Hum------------------------------------------
if(nxt38.custom==0){RT_HW_Next.setVarID(nxt38,nxtNum,'A',1000,2500); nxt38.numReg=38;}  RT_HW_Next.directTask(nxt38); 
if(nxt38.run>0)    {                    nxt38.var=(int32_t)(vSHT3x_Hum*100);}           RT_HW_Next.sendINXX  (nxt38);
//-------------------------------4.39.DHT22.Temp-----------------------------------------
if(nxt39.custom==0){RT_HW_Next.setVarID(nxt39,nxtNum,'A',1000,2500); nxt39.numReg=39;}  RT_HW_Next.directTask(nxt39); 
if(nxt39.run>0)    {                    nxt39.var=(int32_t)(vDHT22Temp*100);}           RT_HW_Next.sendINXX  (nxt39);
//-------------------------------4.40.DHT22.Hum------------------------------------------
if(nxt40.custom==0){RT_HW_Next.setVarID(nxt40,nxtNum,'A',1000,2500); nxt40.numReg=40;}  RT_HW_Next.directTask(nxt40); 
if(nxt40.run>0)    {                    nxt40.var=(int32_t)(vDHT22Hum*100);}            RT_HW_Next.sendINXX  (nxt40);
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void Lcd5_Nextion(){;};
#endif
