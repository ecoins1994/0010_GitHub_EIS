RT_HW_ADS1256_DEV dv1256;      RT_HW_STRUCT_SHED_TASK sh1256;
RT_HW_GENERATOR_EVENT_ID  gen1256; uint8_t dvCnt=0;
#ifdef     RT_HW_TEST_PERMIT_ADS1256
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//======================================================================================
void expADS1256(){
//-------------------------------------------------------------------------------------------------
if(dv1256.custom==0){
if(dv1256.codeErr==0){
if(!RT_HW_Base.console.ok){return;}  
RT_HW_ads1256.constructorDevice(dv1256);    //--Определение default пинов под тип MCU, других параметров;
//-------------------------------------------
//
//-------------------------------------------
RT_HW_ads1256.printParam(dv1256,1);           //--Вывод параметров;
//--------------------------------------------------------------------------------------------------
  //dv1256.blockSpiDRDY=1;                    //--Блокировка(=1) получение DRDY через SPI;
  dv1256.blockPinDRDY=1;  dv1256.pinDRDY=17;  //--Здесь можно разрешить использования пина DRDY; 
  dv1256.blockPinRESET=1; dv1256.pinRESET=16; //--Здесь можно разрешить использования пина RESET;
  dv1256.pinCS=csADS1256;                     //--Здесь можно переопределить параметры;
  dv1256.userRef=((float)250)/100.0;          //--Величина опорного напряжения;
  dv1256.userSPS=11;                          //--Скорость обработки (8->100PCS);
  dv1256.userGAIN=1;                          //--Коэффициент усиления входного сигнала; 
  dv1256.userBUFEN=1;                         //--Установка параметра "Разрешение буферизации" (1/0);
  for(dv1256.idx=0; dv1256.idx<12; dv1256.idx++){RT_HW_ads1256.setADCpermit(dv1256,dv1256.idx);} //--Разрешение каналов;
RT_HW_ads1256.initParameters(dv1256);         //--Инициализация параметров;
RT_HW_ads1256.printParam(dv1256,2);           //--Вывод параметров;
//-------------------------------------------------------------------------------------------------
sh1256.periodLimit=0;  RT_HW_Base.setTaskID(sh1256,'P',250);  //--Периодический вызов 250ms;                                        
dv1256.freshBegin=1;
}}
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(sh1256);              //--Управление задачей;  
if(sh1256.run){if(dvCnt++>12){dvCnt=0;}}
if(dvCnt==0) {dv1256.userSPS=8;  dv1256.userGAIN=1;};
if(dvCnt==4) {dv1256.userSPS=9;  dv1256.userGAIN=1;};
if(dvCnt==8) {dv1256.userSPS=10; dv1256.userGAIN=1;};
if(dvCnt==12){dv1256.userSPS=11; dv1256.userGAIN=1;};
//if(dvCnt==15){dv1256.userSPS=8;  dv1256.userGAIN=2;};
//-------------------------------------------------------------------------------------------------
RT_HW_ads1256.direct(dv1256,sh1256.run);    //--Управление устройством;
vAdcOk=dv1256.ok;                           //--Установка флага Ok;
//-------------------------------------------------------------------------------------------------
if((dv1256.clear) || ((dv1256.fresh) && (dv1256.numChannel==0))) {vADC0 =RT_HW_ads1256.outADCvolt(dv1256);  vAdc0 =RT_HW_ads1256.outADCint(dv1256);}
if((dv1256.clear) || ((dv1256.fresh) && (dv1256.numChannel==1))) {vADC1 =RT_HW_ads1256.outADCvolt(dv1256);  vAdc1 =RT_HW_ads1256.outADCint(dv1256);}
if((dv1256.clear) || ((dv1256.fresh) && (dv1256.numChannel==2))) {vADC2 =RT_HW_ads1256.outADCvolt(dv1256);  vAdc2 =RT_HW_ads1256.outADCint(dv1256);}
if((dv1256.clear) || ((dv1256.fresh) && (dv1256.numChannel==3))) {vADC3 =RT_HW_ads1256.outADCvolt(dv1256);  vAdc3 =RT_HW_ads1256.outADCint(dv1256);}
if((dv1256.clear) || ((dv1256.fresh) && (dv1256.numChannel==4))) {vADC4 =RT_HW_ads1256.outADCvolt(dv1256);  vAdc4 =RT_HW_ads1256.outADCint(dv1256);}
if((dv1256.clear) || ((dv1256.fresh) && (dv1256.numChannel==5))) {vADC5 =RT_HW_ads1256.outADCvolt(dv1256);  vAdc5 =RT_HW_ads1256.outADCint(dv1256);}
if((dv1256.clear) || ((dv1256.fresh) && (dv1256.numChannel==6))) {vADC6 =RT_HW_ads1256.outADCvolt(dv1256);  vAdc6 =RT_HW_ads1256.outADCint(dv1256);}
if((dv1256.clear) || ((dv1256.fresh) && (dv1256.numChannel==7))) {vADC7 =RT_HW_ads1256.outADCvolt(dv1256);  vAdc7 =RT_HW_ads1256.outADCint(dv1256);}
if((dv1256.clear) || ((dv1256.fresh) && (dv1256.numChannel==8))) {vADC01=RT_HW_ads1256.outADCvolt(dv1256);  vAdc01=RT_HW_ads1256.outADCint(dv1256);}
if((dv1256.clear) || ((dv1256.fresh) && (dv1256.numChannel==9))) {vADC23=RT_HW_ads1256.outADCvolt(dv1256);  vAdc23=RT_HW_ads1256.outADCint(dv1256);}
if((dv1256.clear) || ((dv1256.fresh) && (dv1256.numChannel==10))){vADC45=RT_HW_ads1256.outADCvolt(dv1256);  vAdc45=RT_HW_ads1256.outADCint(dv1256);}
if((dv1256.clear) || ((dv1256.fresh) && (dv1256.numChannel==11))){vADC67=RT_HW_ads1256.outADCvolt(dv1256);  vAdc67=RT_HW_ads1256.outADCint(dv1256);}
//-------------------------------------------------------------------------------------------------
} //--END expADS1256;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void expADS1256(){;};
#endif
//======================================================================================
