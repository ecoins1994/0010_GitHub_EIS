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
RT_HW_STRUCT_NEXT_WRITE_VAR mID_0;      //--ID контроллера;
RT_HW_STRUCT_NEXT_WRITE_VAR mBoard_1;   //--Параметры платы;
RT_HW_STRUCT_NEXT_WRITE_VAR mSys_2;     //--Время работы контроллера(сек) после сброса;
RT_HW_STRUCT_NEXT_WRITE_VAR mMotor_3;   //--Время работы контроллера(сек) после сброса;
RT_HW_STRUCT_NEXT_WRITE_VAR mTime_4;    //--Время;
RT_HW_STRUCT_NEXT_WRITE_VAR mDate_5;    //--дата;
RT_HW_STRUCT_NEXT_WRITE_VAR mUNIX_6;    //--дата;
RT_HW_STRUCT_NEXT_WRITE_VAR mSP0_7;     //--Быстродействие CORE0;
RT_HW_STRUCT_NEXT_WRITE_VAR mSP1_8;     //--Быстродействие CORE0;
RT_HW_STRUCT_NEXT_WRITE_VAR mIP_10;     //--Быстродействие CORE0;
RT_HW_STRUCT_NEXT_WRITE_VAR mMAC1_11;   //--MAC-адрес;
RT_HW_STRUCT_NEXT_WRITE_VAR mMAC2_12;   //--MAC-адрес
//--------------------------------------------------------------------------------------
RT_HW_STRUCT_NEXT_WRITE_VAR mADC_20;    //--ADC;
RT_HW_STRUCT_NEXT_WRITE_VAR mPWM_21;    //--PWM;
RT_HW_STRUCT_NEXT_WRITE_VAR mSERVO_22;  //--Servo;
RT_HW_STRUCT_NEXT_WRITE_VAR mDAC_23;    //--DAC;
RT_HW_STRUCT_NEXT_WRITE_VAR mRUN_24;    //--Бегущая "1";
//--------------------------------------------------------------------------------------
RT_HW_STRUCT_NEXT_WRITE_VAR mDIN_30;    //--ADC;
RT_HW_STRUCT_NEXT_WRITE_VAR mDOT_31;    //--PWM;
RT_HW_STRUCT_NEXT_WRITE_VAR devOk_39;       //--Ok устройств;
//--------------------------------------------------------------------------------------
RT_HW_STRUCT_NEXT_WRITE_VAR ADS1115f0_50;   //--ADC;
RT_HW_STRUCT_NEXT_WRITE_VAR ADS1115f1_51;   //--ADC;
RT_HW_STRUCT_NEXT_WRITE_VAR ADS1115f2_52;   //--ADC;
RT_HW_STRUCT_NEXT_WRITE_VAR ADS1115f3_53;   //--ADC;

//--------------------------------------------------------------------------------------
  RT_HW_STRUCT_NEXT_WRITE_VAR AHTxt_100;      //--AHTx.Temp;
  RT_HW_STRUCT_NEXT_WRITE_VAR AHTxh_101;      //--AHTx.Hum;
  RT_HW_STRUCT_NEXT_WRITE_VAR SHT3xt_102;     //--SHT3x.Temp;
  RT_HW_STRUCT_NEXT_WRITE_VAR SHT3xh_103;     //--SHT3x.Hum;
//RT_HW_STRUCT_NEXT_WRITE_VAR BMP180t_104;    //--BMP180.Temp;
//RT_HW_STRUCT_NEXT_WRITE_VAR BMP180p_105;    //--BMP180.Press;
//RT_HW_STRUCT_NEXT_WRITE_VAR BMP280t_106;    //--BMP280.Temp;
//RT_HW_STRUCT_NEXT_WRITE_VAR BMP280p_107;    //--BMP280.Press;
//RT_HW_STRUCT_NEXT_WRITE_VAR BME280t_108;    //--BME280.Temp;
//RT_HW_STRUCT_NEXT_WRITE_VAR BME280h_109;    //--BME280.Hum
//RT_HW_STRUCT_NEXT_WRITE_VAR BME280p_110;    //--BME280.Press;
//RT_HW_STRUCT_NEXT_WRITE_VAR CMTHPt_111;     //--CMTHP.Temp;
//RT_HW_STRUCT_NEXT_WRITE_VAR CMTHPh_112;     //--CMTHP.Hum
//RT_HW_STRUCT_NEXT_WRITE_VAR CMTHPp_113;     //--CMTHP.Press;
//RT_HW_STRUCT_NEXT_WRITE_VAR 114;            //--DHT22.Temp;
//RT_HW_STRUCT_NEXT_WRITE_VAR 115;            //--DHT22.Hum;
  RT_HW_STRUCT_NEXT_WRITE_VAR BH1750lx_116;   //--BH1750.Lux;
  RT_HW_STRUCT_NEXT_WRITE_VAR DS1820t_117;    //--DS1820.Temp;
  RT_HW_STRUCT_NEXT_WRITE_VAR SR04Len_118;    //--HC-SR04.Len;
  RT_HW_STRUCT_NEXT_WRITE_VAR MAX6675t_119;   //--MAX6675.Temp;
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
//-------------------------------4.0.ID платы-------------------------------------------
if(mID_0.custom==0)   {RT_HW_Next.setVarID(mID_0, nxtNum,'A',500,2500); mID_0.numReg=0;}          RT_HW_Next.directTask(mID_0);
if(mID_0.run>0)       {mID_0.var=RT_HW_Base.buff.vRandom;}                                        RT_HW_Next.sendINXX  (mID_0);
//-------------------------------4.1.Хар-ки платы---------------------------------------
if(mBoard_1.custom==0){RT_HW_Next.setVarID(mBoard_1, nxtNum,'A',500,2500);  mBoard_1.numReg=1;}   RT_HW_Next.directTask(mBoard_1);
if(mBoard_1.run>0)    {mBoard_1.var=(RT_HW_Base.device.board.codeArch<<8)| RT_HW_Base.device.board.codeBoard;}  RT_HW_Next.sendINXX(mBoard_1);
//-------------------------------4.2.Системные флаги------------------------------------
if(mSys_2.custom==0)  {RT_HW_Next.setVarID(mSys_2, nxtNum,'A',50,2500); mSys_2.numReg=2;}         RT_HW_Next.directTask(mSys_2);
if(mSys_2.run>0)      {mSys_2.var=flagSystem;}                                                    RT_HW_Next.sendINXX  (mSys_2);
//-------------------------------4.3.Мотосекунды----------------------------------------
if(mMotor_3.custom==0){RT_HW_Next.setVarID(mMotor_3, nxtNum,'A',500,2500); mMotor_3.numReg=3;}    RT_HW_Next.directTask(mMotor_3);
if(mMotor_3.run>0)    {mMotor_3.var=vMotorSec;}                                                   RT_HW_Next.sendINXX  (mMotor_3);
//-------------------------------4.4.Время текущее--------------------------------------
if(mTime_4.custom==0){RT_HW_Next.setVarID(mTime_4, nxtNum,'A',500,2500); mTime_4.numReg=4;}    RT_HW_Next.directTask(mTime_4);
if(mTime_4.run>0)    {mTime_4.var=(RT_HW_Base.unixID.hours<<16)| (RT_HW_Base.unixID.minutes<<8)|(RT_HW_Base.unixID.seconds);} RT_HW_Next.sendINXX(mTime_4);
//-------------------------------4.5.Дата текущая---------------------------------------
if(mDate_5.custom==0){RT_HW_Next.setVarID(mDate_5, nxtNum,'A',500,2500); mDate_5.numReg=5;}    RT_HW_Next.directTask(mDate_5);
if(mDate_5.run>0)    {mDate_5.var=(RT_HW_Base.unixID.weekDay<<24) | (RT_HW_Base.unixID.day<<16)| (RT_HW_Base.unixID.month<<8)|(RT_HW_Base.unixID.year2);} RT_HW_Next.sendINXX(mDate_5);
//-------------------------------4.6.Время UNIX--    -----------------------------------
if(mUNIX_6.custom==0){RT_HW_Next.setVarID(mUNIX_6, nxtNum,'A',500,2500); mUNIX_6.numReg=6;}    RT_HW_Next.directTask(mUNIX_6);
if(mUNIX_6.run>0)    {mUNIX_6.var= RT_HW_Base.unixID.timeUNIX;} RT_HW_Next.sendINXX(mUNIX_6);
//-------------------------------4.7.CORE 0--------------------------------------------
if(mSP0_7.custom==0)  {RT_HW_Next.setVarID(mSP0_7, nxtNum,'A',500,2500); mSP0_7.numReg=7;}        RT_HW_Next.directTask(mSP0_7);
if(mSP0_7.run>0)      {mSP0_7.var=vSpeedMCUF;}                                                    RT_HW_Next.sendINXX  (mSP0_7);
//-------------------------------4.8.CORE 1--------------------------------------------
if(mSP1_8.custom==0)  {RT_HW_Next.setVarID(mSP1_8, nxtNum,'A',500,2500); mSP1_8.numReg=8;}        RT_HW_Next.directTask(mSP1_8);
if(mSP1_8.run>0)      {mSP1_8.var=vspeedMCUF;}                                                    RT_HW_Next.sendINXX  (mSP1_8);
//-------------------------------4.10.IP Ethernet---------------------------------------
if(mIP_10.custom==0)  {RT_HW_Next.setVarID(mIP_10, nxtNum,'A',500,2500); mIP_10.numReg=10;}       RT_HW_Next.directTask(mIP_10);
if(mIP_10.run>0)      {mIP_10.var=(ethIP[0]<<24) | (ethIP[1]<<16) | (ethIP[2]<<8) | (ethIP[3]);}  RT_HW_Next.sendINXX  (mIP_10);
//-------------------------------4.11.MAC1----------------------------------------------
if(mMAC1_11.custom==0){RT_HW_Next.setVarID(mMAC1_11, nxtNum,'A',500,2500); mMAC1_11.numReg=11;}   RT_HW_Next.directTask(mMAC1_11);
if(mMAC1_11.run>0)    {mMAC1_11.var=(RT_HW_Base.buff.mac[0]<<16) | (RT_HW_Base.buff.mac[1]<<8) | (RT_HW_Base.buff.mac[2]);}  RT_HW_Next.sendINXX(mMAC1_11);
//-------------------------------4.12.MAC2----------------------------------------------
if(mMAC2_12.custom==0){RT_HW_Next.setVarID(mMAC2_12, nxtNum,'A',500,2500); mMAC2_12.numReg=12;}   RT_HW_Next.directTask(mMAC2_12);
if(mMAC2_12.run>0)    {mMAC2_12.var=(RT_HW_Base.buff.mac[3]<<16) | (RT_HW_Base.buff.mac[4]<<8) | (RT_HW_Base.buff.mac[5]);}  RT_HW_Next.sendINXX(mMAC2_12);
//-------------------------------4.20.ADC----------------------------------------------
if(mADC_20.custom==0){RT_HW_Next.setVarID(mADC_20, nxtNum,'A',200,2500); mADC_20.numReg=20;}      RT_HW_Next.directTask(mADC_20);
if(mADC_20.run>0)    {mADC_20.var=vADCF;}                                                         RT_HW_Next.sendINXX(mADC_20);
//-------------------------------4.23.DAC----------------------------------------------
if(mDAC_23.custom==0){RT_HW_Next.setVarID(mDAC_23, nxtNum,'A',100,2500); mDAC_23.numReg=23;}      RT_HW_Next.directTask(mDAC_23);
if(mDAC_23.run>0)    {mDAC_23.var=vGenNextDAC;}                                                          RT_HW_Next.sendINXX(mDAC_23);
//-------------------------------4.24.RUN----------------------------------------------
if(mRUN_24.custom==0){RT_HW_Next.setVarID(mRUN_24, nxtNum,'A',100,2500); mRUN_24.numReg=24;}      RT_HW_Next.directTask(mRUN_24);
if(mRUN_24.run>0)    {mRUN_24.var=vGenNextRun;}                                                   RT_HW_Next.sendINXX(mRUN_24);
//-------------------------------4.30.mDIN----------------------------------------------
if(mDIN_30.custom==0){RT_HW_Next.setVarID(mDIN_30, nxtNum,'A',100,2500); mDIN_30.numReg=30;}      RT_HW_Next.directTask(mDIN_30);
if(mDIN_30.run>0)    {mDIN_30.var=pinDIN;}                                                        RT_HW_Next.sendINXX(mDIN_30);
//-------------------------------4.31.mDOT----------------------------------------------
if(mDOT_31.custom==0){RT_HW_Next.setVarID(mDOT_31, nxtNum,'A',100,2500); mDOT_31.numReg=31;}      RT_HW_Next.directTask(mDOT_31);
if(mDOT_31.run>0)    {mDOT_31.var=pinDOT;}                                                        RT_HW_Next.sendINXX(mDOT_31);
//-------------------------------4.39.Флаги устройств----------------------------------
if(devOk_39.custom==0){RT_HW_Next.setVarID(devOk_39, nxtNum,'A',500,2500); devOk_39.numReg=39;}   RT_HW_Next.directTask(devOk_39);
if(devOk_39.run>0)    {devOk_39.var=flagDevice;}                                                  RT_HW_Next.sendINXX(devOk_39);
//-------------------------------4.50.ADS1115f0----------------------------------
if(ADS1115f0_50.custom==0){RT_HW_Next.setVarID(ADS1115f0_50, nxtNum,'A',500,2500); ADS1115f0_50.numReg=50;} RT_HW_Next.directTask(ADS1115f0_50);
if(ADS1115f0_50.run>0)    {ADS1115f0_50.var=(int32_t)(vADS1115_A0f*1000);}                                  RT_HW_Next.sendINXX(ADS1115f0_50);
//-------------------------------4.51.ADS1115f1----------------------------------
if(ADS1115f1_51.custom==0){RT_HW_Next.setVarID(ADS1115f1_51, nxtNum,'A',500,2500); ADS1115f1_51.numReg=51;} RT_HW_Next.directTask(ADS1115f1_51);
if(ADS1115f1_51.run>0)    {ADS1115f1_51.var=(int32_t)(vADS1115_A1f*1000);}                                  RT_HW_Next.sendINXX(ADS1115f1_51);
//-------------------------------4.50.ADS1115f2----------------------------------
if(ADS1115f2_52.custom==0){RT_HW_Next.setVarID(ADS1115f2_52, nxtNum,'A',500,2500); ADS1115f2_52.numReg=52;} RT_HW_Next.directTask(ADS1115f2_52);
if(ADS1115f2_52.run>0)    {ADS1115f2_52.var=(int32_t)(vADS1115_A2f*1000);}                                  RT_HW_Next.sendINXX(ADS1115f2_52);
//-------------------------------4.50.ADS1115f3----------------------------------
if(ADS1115f3_53.custom==0){RT_HW_Next.setVarID(ADS1115f3_53, nxtNum,'A',500,2500); ADS1115f3_53.numReg=53;} RT_HW_Next.directTask(ADS1115f3_53);
if(ADS1115f3_53.run>0)    {ADS1115f3_53.var=(int32_t)(vADS1115_A3f*1000);}                                  RT_HW_Next.sendINXX(ADS1115f3_53);
//-------------------------------4.100.AHTxt----------------------------------
if(AHTxt_100.custom==0){RT_HW_Next.setVarID(AHTxt_100, nxtNum,'A',500,2500);AHTxt_100.numReg=100;}RT_HW_Next.directTask(AHTxt_100);
if(AHTxt_100.run>0)    {AHTxt_100.var=(int32_t)(vAHTxx_Temp*1000);}                              RT_HW_Next.sendINXX(AHTxt_100);
//-------------------------------4.101.AHTxh----------------------------------
if(AHTxh_101.custom==0){RT_HW_Next.setVarID(AHTxh_101, nxtNum,'A',500,2500); AHTxh_101.numReg=101;} RT_HW_Next.directTask(AHTxh_101);
if(AHTxh_101.run>0)    {AHTxh_101.var=(int32_t)(vAHTxx_Hum*1000);}                                 RT_HW_Next.sendINXX(AHTxh_101);
//-------------------------------4.100.AHTxt----------------------------------
if(SHT3xt_102.custom==0){RT_HW_Next.setVarID(SHT3xt_102, nxtNum,'A',500,2500); SHT3xt_102.numReg=102;}  RT_HW_Next.directTask(SHT3xt_102);
if(SHT3xt_102.run>0)    {SHT3xt_102.var=(int32_t)(vSHT3x_Temp*1000);}                                  RT_HW_Next.sendINXX(SHT3xt_102);
//-------------------------------4.101.AHTxh----------------------------------
if(SHT3xh_103.custom==0){RT_HW_Next.setVarID(SHT3xh_103, nxtNum,'A',500,2500);SHT3xh_103.numReg=103;}   RT_HW_Next.directTask(SHT3xh_103);
if(SHT3xh_103.run>0)    {SHT3xh_103.var=(int32_t)(vSHT3x_Hum*1000);}                                   RT_HW_Next.sendINXX(SHT3xh_103);
//-------------------------------4.116.BH1750lx----------------------------------
if(BH1750lx_116.custom==0){RT_HW_Next.setVarID(BH1750lx_116, nxtNum,'A',500,2500); BH1750lx_116.numReg=116;}  RT_HW_Next.directTask(BH1750lx_116);
if(BH1750lx_116.run>0)    {BH1750lx_116.var=vBH1750Lux;}                                                     RT_HW_Next.sendINXX(BH1750lx_116);
//-------------------------------4.117.DS1820t----------------------------------
if(DS1820t_117.custom==0){RT_HW_Next.setVarID(DS1820t_117, nxtNum,'A',500,2500);DS1820t_117.numReg=117;}    RT_HW_Next.directTask(DS1820t_117);
if(DS1820t_117.run>0)    {DS1820t_117.var=(int32_t)(vDS1820Temp*1000);}                                    RT_HW_Next.sendINXX(DS1820t_117);
//-------------------------------4.118.HS-SR04lx----------------------------------
if(SR04Len_118.custom==0){RT_HW_Next.setVarID(SR04Len_118, nxtNum,'A',500,2500); SR04Len_118.numReg=118;}   RT_HW_Next.directTask(SR04Len_118);
if(SR04Len_118.run>0)    {SR04Len_118.var=vSR04Len;}                                                       RT_HW_Next.sendINXX(SR04Len_118);
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void Lcd5_Nextion(){;};
#endif
