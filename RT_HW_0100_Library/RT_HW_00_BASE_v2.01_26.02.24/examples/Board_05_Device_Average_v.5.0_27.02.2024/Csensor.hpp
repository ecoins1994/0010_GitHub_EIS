//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     1. Сенсоры через пины
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                    1.1. HC-SR04 через пин Trig (соединить с Echo чере R=470ом) по прерываниям;
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_SR04
RT_HW_STRUCT_SR04_ID  dvSR04;     RT_HW_STRUCT_SHED_TASK shSR04;
RT_HW_FILTER_MEDIAN_3    <uint16_t>   filterSR04;   //--Параметры фильтра SR04(скользящее среднее 3-го порядка);
//--------------------------------------------------------------
RT_HW_IRAM_ATTR void RT_HW_IRQ_SR04_handler_dvSR04(){                     //==Функция: Обработчик прерываний от пина echo HC-SR04;
  if(dvSR04.state==2) {if( RT_HW_PIN_DIR_READ(dvSR04.ddPin)){dvSR04.timeBegin=micros(); dvSR04.state=3;}}
  if(dvSR04.state==3) {if(!RT_HW_PIN_DIR_READ(dvSR04.ddPin)){dvSR04.timeEnd  =micros(); dvSR04.state=4;}}}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void snsSR04(){                                                           //==Функция: Управление HC-SR04;
  if(shSR04.custom==0){RT_HW_Base.setTaskID(shSR04,'P',75);}              //--Периодический вызов 75ms;
  if(dvSR04.custom==0){dvSR04.custom=1; dvSR04.extPinTrig=pinSR04; dvSR04.maxLen=400;}    //--Настройка параметров;
  dvSR04.run=RT_HW_Base.directTask(shSR04);                               //--Управление задачей; 
  RT_HW_sr04.direct(dvSR04);                                              //--Управление устройством;
  if(dvSR04.state==1){dvSR04.state++;  attachInterrupt(dvSR04.numIRQ, RT_HW_IRQ_SR04_handler_dvSR04,CHANGE);}
  if(dvSR04.fresh)   {dvSR04.fresh=0;  dvSR04.LenMcs=filterSR04.filtered(dvSR04.echoMcs); //--Обновление данных;
                      dvSR04.Len=round(dvSR04.LenMcs * dvSR04.speedSoundAir/10.0);        //--Вычисление расстояние в см;  
                   if(dvSR04.Len>dvSR04.maxLen){dvSR04.Len=dvSR04.maxLen;}                //--Ограничение максимальной длины;
            vSR04_Len=dvSR04.Len;  vSR04_ok=dvSR04.ok;}};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsSR04(){;};     //==Функция: Заглушка вместо функции управления snsSR04();
#endif

//=================================================================================================
//                                    1.2. DS1820 через 1-Wire
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_DS1820
RT_HW_ONEWIRE           dvNW;
RT_HW_STRUCT_DS1820_ID  dvDS1820; 
RT_HW_STRUCT_SHED_TASK  shDS1820;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void snsDS1820(){
  if(shDS1820.custom==0){RT_HW_Base.setTaskID(shDS1820,'P',2200); shDS1820.periodLimit=50;}   //--Периодический вызов 2.2сек;
  if(dvDS1820.custom==0){RT_HW_ds1820.setParam(dvDS1820,pinDS1820);}        //--Настройка параметров;
  dvDS1820.run=RT_HW_Base.directTask(shDS1820);                             //--Управление задачей;
  RT_HW_ds1820.direct(dvNW,dvDS1820);                                       //--Управление устройством; 
  if(dvDS1820.fresh){                                                       //==Обновление данных;
   //RT_HW_ds1820.messDS1820(dvDS1820,4);                                   //--Вывод на консоль;
     dvDS1820.fresh=0; vDS1820_Temp=dvDS1820.vTemp; vDS1820_ok=dvDS1820.ok; //--Сохранение данных;
   }
//-------------------------------------------------------------------------------------------------
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsDS1820(){;};
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     2. Сенсоры через i2c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                    2.1. AHTxx.i2c (T,H)      
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_AHTx
RT_HW_AHTxx_DEV   dvAHTxx;      RT_HW_STRUCT_SHED_TASK shAHTxx; 
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void snsAHTxx(){
//-------------------------------------------------------------------------------------------------
  if(dvAHTxx.custom==0) {dvAHTxx.mi='I';          
     dvAHTxx.custom=RT_HW_Base.i2cSetParam(dvAHTxx.dvI,i2cAdrAHTxx,0,0);  //--Настройка параметров (адрес i2c, номер шины, скорость);
     shAHTxx.periodLimit=50;  RT_HW_Base.setTaskID  (shAHTxx,'P',1200);}  //--Периодический вызов 75ms;
//-------------------------------------------------------------------------------------------------
  RT_HW_Base.directTask(shAHTxx);                                         //--Управление задачей;  
  RT_HW_ahtxx.direct(dvAHTxx,shAHTxx.run);                                //--Управление устройством;
  if(dvAHTxx.fresh){                                                      //==Обновление данных; 
     dvAHTxx.fresh=0; vAHTxx_ok=dvAHTxx.ok;                               //--Сохранение данных;
      vAHTxx_Temp=dvAHTxx.vTemp; vAHTxx_Hum=dvAHTxx.vHum;                 //--Сохранение данных;
  }
};
#else
void snsAHTxx(){;};     //==Функция: Заглушка вместо функции управления snsAHTxx();
#endif
//=================================================================================================

//=================================================================================================
//                                      2.2. SHT3X.i2c(T,H)
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_SHT3x
RT_HW_SHT3x_DEV   dvSHT3x;      RT_HW_STRUCT_SHED_TASK shSHT3x;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void snsSHT3x(){                                                          //==Функция: Управление SHT3x;
//-------------------------------------------------------------------------------------------------
  if(dvSHT3x.custom==0) {                                                 //--Настройка параметров устройства и задачи;              
     dvSHT3x.custom=RT_HW_Base.i2cSetParam(dvSHT3x.dvI,i2cAdrSHT3x,0,0);  //  Настройка параметров: адрес i2c, номер шины, скорость;
     shSHT3x.periodLimit=50;  RT_HW_Base.setTaskID  (shSHT3x,'P',1200);}  //  Настройка задачи:     периодически='P', период=1200ms; 
//-------------------------------------------------------------------------------------------------
   RT_HW_Base.directTask(shSHT3x);                                        //--Управление задачей; 
   RT_HW_sht3x.direct(dvSHT3x,shSHT3x.run);                               //--Управление устройством;
   if(dvSHT3x.fresh){                                                     //==Обновление данных; 
      dvSHT3x.fresh=0; vSHT3x_ok=dvSHT3x.ok;                              //--Сохранение данных;
      vSHT3x_Temp=dvSHT3x.vTemp; vSHT3x_Hum=dvSHT3x.vHum;                 //--Сохранение данных;
   }
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsSHT3x(){;};     //==Функция: Заглушка вместо функции управления snsSHT3x();
#endif
//=================================================================================================
//                                      2.3. BH1750
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_BH1750
RT_HW_BH1750_DEV  dvBH1750;     RT_HW_STRUCT_SHED_TASK shBH1750; 
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void snsBH1750(){                                                           //==Функция: Управление BH1750;
if(dvBH1750.custom==0) {                                                    //--Настройка параметров устройства и задачи; 
   dvBH1750.custom=RT_HW_Base.i2cSetParam(dvBH1750.dvI,i2cAdrBH1750,0,0);   //  Настройка параметров: адрес i2c, номер шины, скорость;
   shBH1750.periodLimit=50;  RT_HW_Base.setTaskID  (shBH1750,'P',500);}     //  Настройка задачи:     периодически='P', период=1200ms; 
   RT_HW_Base.directTask(shBH1750);                                         //--Управление задачей; 
RT_HW_bh1750.direct(dvBH1750,shBH1750.run);                                 //--Управление устройством;
//-------------------------------------------------------------------------------------------------
if(dvBH1750.fresh){dvBH1750.fresh=0; vBH1750_Lux=dvBH1750.vLux; vBH1750_ok=dvBH1750.ok;}};   //--Обновление данных;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsBH1750(){;};
#endif
//=================================================================================================
//                                     2.4. BME280.i2c     
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_BME280
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_BME280_DEV  dvBME280;     RT_HW_STRUCT_SHED_TASK shBME280Press;
//-------------------------------------------------------------------------------------------------
void snsBME280(){
//-------------------------------------------------------------------------------------------------
if(dvBME280.custom==0 ){                                                    //--Настройка параметров устройства и задачи; 
   dvBME280.custom=RT_HW_Base.i2cSetParam(dvBME280.dvI,i2cAdrBME280,0,0);   //  Настройка параметров: адрес i2c, номер шины, скорость;
   dvBME280.permitTemp=0; dvBME280.permitHum=0; dvBME280.permitPress=1;     //  Настройка разрешения измерения давления;
   shBME280Press.periodLimit=50; RT_HW_Base.setTaskID(shBME280Press,'P',1400);}//Настройка задачи:     периодически='P', период=1400ms; 
   RT_HW_Base.directTask(shBME280Press);                                    //--Управление задачей; 
   RT_HW_bme280.direct(dvBME280,shBME280Press.run);                         //--Управление устройством;   
   if(dvBME280.fresh){dvBME280.fresh=0; vBMPx80_ok=dvBME280.ok; vBMPx80_Press=dvBME280.vPress;}   //--Обновление данных;
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsBME280(){;};
#endif
//=================================================================================================
//                                     2.5. BMP180.i2c     
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_BMP180
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_BMP180_DEV  dvBMP180;     RT_HW_STRUCT_SHED_TASK shBMP180Press;
void snsBMP180(){
//-------------------------------------------------------------------------------------------------
if(dvBMP180.custom==0) {                                                  //--Настройка параметров устройства и задачи; 
   dvBMP180.custom=RT_HW_Base.i2cSetParam(dvBMP180.dvI,i2cAdrBMP180,0,0); //  Настройка параметров: адрес i2c, номер шины, скорость; 
   dvBMP180.permitTemp=0; dvBMP180.permitPress=1;                         //  Настройка разрешения измерения давления;
   shBMP180Press.periodLimit=50; RT_HW_Base.setTaskID(shBMP180Press,'P',1400);}//Настройка задачи:     периодически='P', период=1400ms;
   RT_HW_Base.directTask(shBMP180Press);                                  //--Управление задачей; 
   RT_HW_bmp180.direct(dvBMP180,shBMP180Press.run);                       //--Управление устройством;   
//-------------------------------------------------------------------------------------------------
   if(dvBMP180.fresh){dvBMP180.fresh=0; vBMPx80_ok=dvBMP180.ok; vBMPx80_Press=dvBMP180.vPress;}   //--Обновление данных;
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsBMP180(){;};
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                    3. СЕНСОРЫ через SPI
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                      3.1. MAX6675.SPI
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_MAX6675
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_MAX6675_DEV dvMAX6675;    RT_HW_STRUCT_SHED_TASK shMAX6675;
//-------------------------------------------------------------------------------------------------
void snsMAX6675(){
//-------------------------------------------------------------------------------------------------
if(dvMAX6675.custom==0){                                                  //--Настройка параметров устройства и задачи;
   dvMAX6675.mi='S';                                                      //--Тип шины SPI;
   dvMAX6675.custom=RT_HW_Base.spiSetParam(dvMAX6675.dvS,csMAX6675,0,4000000);//-Настройка параметров: пин сs, номер шины, скорость;
   shMAX6675.periodLimit=50; RT_HW_Base.setTaskID(shMAX6675,'P',1200);}   //Настройка задачи:     периодически='P', период=1400ms;                                          
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shMAX6675);                                         //--Управление задачей;                      
RT_HW_max6675.direct(dvMAX6675,shMAX6675.run);                            //--Управление устройством;                                              
//-------------------------------------------------------------------------------------------------
if(dvMAX6675.fresh){dvMAX6675.fresh=0; vMAX6675_Temp=dvMAX6675.vTemp; vMAX6675_ok=dvMAX6675.ok;}    //--Обновление данных;
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsMAX6675(){;};
#endif
//=================================================================================================