//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     1.Сенсоры через пины
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                    1.1.HC-SR04 через пин Trig (соединить с Echo чере R=470ом) по прерываниям;
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
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     2.Сенсоры через i2c
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
     vAHTxx_Temp=dvAHTxx.vTemp; vAHTxx_Hum=dvAHTxx.vHum;                  //--Сохранение данных;
  }
};
#else
void snsAHTxx(){;};     //==Функция: Заглушка вместо функции управления snsAHTxx();
#endif
//=================================================================================================
