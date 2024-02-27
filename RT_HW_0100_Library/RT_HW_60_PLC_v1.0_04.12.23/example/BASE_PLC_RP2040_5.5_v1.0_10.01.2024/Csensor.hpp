//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     3.Сенсоры через i2c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                    3.1.AHTxx.i2c (T,H)      
//=================================================================================================
RT_HW_AHTxx_DEV   dvAHTxx;      RT_HW_STRUCT_SHED_TASK shAHTxx; 
#ifdef RT_HW_TEST_PERMIT_AHTx
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void snsAHTxx(){
//-------------------------------------------------------------------------------------------------
if(dvAHTxx.custom==0) {dvAHTxx.mi='I';          
                 dvAHTxx.custom=RT_HW_Base.i2cSetParam(dvAHTxx.dvI,i2cAdrAHTxx,0,0);  //--Настройка параметров (адрес i2c, номер шины, скорость);
                 shAHTxx.periodLimit=50;  RT_HW_Base.setTaskID  (shAHTxx,'P',1200);}  //--Периодический вызов 75ms;
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shAHTxx);                                                       //--Управление задачей;  
RT_HW_ahtxx.direct(dvAHTxx,shAHTxx.run);                                              //--Управление устройством;
//-------------------------------------------------------------------------------------------------
if(dvAHTxx.fresh){
//-------------------------------------------------------------------------------------------------
//if(RT_HW_Base.consoleOk()){  
//sign='-'; if(dvAHTxx.ok){sign='+';} RT_HW_Base.consoleVar(sign);    //--Вывод а консоль;
//RT_HW_Base.consoleTest(String(F("AHTxx  T")),dvAHTxx.vTemp,';'); 
//RT_HW_Base.consoleTest(String(F(" H")),      dvAHTxx.vHum),'E';
//}
//-------------------------------------------------------------------------------------------------
}
if(dvAHTxx.fresh){dvAHTxx.fresh=0; vAHTxx_ok=dvAHTxx.ok; vAHTxx_Temp=dvAHTxx.vTemp; vAHTxx_Hum=dvAHTxx.vHum;}  //--Обновление данных;
};
#else
void snsAHTxx(){;};
#endif
//=================================================================================================
//                                      3.2.SHT3X.i2c
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_SHT3x
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_SHT3x_DEV   dvSHT3x;      RT_HW_STRUCT_SHED_TASK shSHT3x;
//-------------------------------------------------------------------------------------------------
void snsSHT3x(){
//-------------------------------------------------------------------------------------------------
if(dvSHT3x.custom==0) {dvSHT3x.mi='I';          
                       dvSHT3x.custom=RT_HW_Base.i2cSetParam(dvSHT3x.dvI,i2cAdrSHT3x,0,0); //--adr,bus,speed;
                       shSHT3x.periodLimit=50;  RT_HW_Base.setTaskID  (shSHT3x,'P',1200); }    //--modeTask='P',period=1200; 
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shSHT3x);           //--Launching AHTXX task; 
RT_HW_sht3x.direct(dvSHT3x,shSHT3x.run);  //--Sensor control; AHTxx;
//-------------------------------------------------------------------------------------------------
if(dvSHT3x.fresh){dvSHT3x.fresh=0; vSHT3x_ok=dvSHT3x.ok; vSHT3x_Temp=dvSHT3x.vTemp; vSHT3x_Hum=dvSHT3x.vHum;}  //--Updating measured data;
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsSHT3x(){;};
#endif
//=================================================================================================
//                                     3.3.BME280.i2c     
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_BME280
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_BME280_DEV  dvBME280;     RT_HW_STRUCT_SHED_TASK shBME280Temp, shBME280Hum,shBME280Press;
//-------------------------------------------------------------------------------------------------
void snsBME280(){
//-------------------------------------------------------------------------------------------------
if(dvBME280.custom==0 ){dvBME280.mi='I';              
                        dvBME280.custom=RT_HW_Base.i2cSetParam(dvBME280.dvI,i2cAdrBME280,0,0); //--adr,bus,speed; 
                        shBME280Temp.periodLimit=50;  RT_HW_Base.setTaskID  (shBME280Temp, 'P',1200);
                        shBME280Hum.periodLimit=50;   RT_HW_Base.setTaskID  (shBME280Hum,  'P',2600);
                        shBME280Press.periodLimit=50; RT_HW_Base.setTaskID  (shBME280Press,'P',1400);}
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shBME280Temp);    //--Launching BME280 Temp   task;   
RT_HW_Base.directTask(shBME280Hum);     //--Launching BME280 Hum    task;
RT_HW_Base.directTask(shBME280Press);   //--Launching BME280 Press  task;
//-------------------------------------------------------------------------------------------------
RT_HW_bme280.direct(dvBME280,shBME280Temp.run,shBME280Hum.run,shBME280Press.run);  //--Sensor control BME280;   
if(dvBME280.fresh){dvBME280.fresh=0; vBMP_ok=vBME280_ok=dvBME280.ok; vBMP_Temp=vBME280_Temp=dvBME280.vTemp; vBMP_Hum=vBME280_Hum=dvBME280.vHum; vBMP_Press=vBME280_Press=dvBME280.vPress;}   //--Updating measured data;
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsBME280(){;};
#endif
//=================================================================================================
//                                     3.4.BMP180.i2c     
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_BMP180
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_BMP180_DEV  dvBMP180;     RT_HW_STRUCT_SHED_TASK shBMP180Temp, shBMP180Press;
void snsBMP180(){
//-------------------------------------------------------------------------------------------------
if(dvBMP180.custom==0) {dvBMP180.mi='I';             
                        dvBMP180.custom=RT_HW_Base.i2cSetParam(dvBMP180.dvI,i2cAdrBMP180,0,0); //--adr,bus,speed;
                        shBMP180Temp.periodLimit=50;  RT_HW_Base.setTaskID  (shBMP180Temp, 'P',1200);        //--modeTask='P',period=1200; 
                        shBMP180Press.periodLimit=50; RT_HW_Base.setTaskID  (shBMP180Press,'P',1400);}       //--modeTask='P',period=1400; 
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shBMP180Temp);    //--Launching BMP180 Temp   task;   
RT_HW_Base.directTask(shBMP180Press);   //--Launching BMP180 Press  task;
//-------------------------------------------------------------------------------------------------
RT_HW_bmp180.direct(dvBMP180,shBMP180Temp.run,shBMP180Press.run);  //--Sensor control BMP180;   
//-------------------------------------------------------------------------------------------------
if(dvBMP180.fresh){dvBMP180.fresh=0; vBMP_ok=vBMP180_ok=dvBMP180.ok; vBMP_Temp=vBMP180_Temp=dvBMP180.vTemp; vBMP_Press=vBMP180_Press=dvBMP180.vPress;}   //--Updating measured data;
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsBMP180(){;};
#endif
//=================================================================================================
//                                      3.5.BH1750
//  Setting task:   'P'-periodic call, no more than 5 cycles, period 2200ms;
//  Setting sensor: adr=i2cAdrBH1750, bus=0, speed=0;
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_BH1750
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_BH1750_DEV  dvBH1750;     RT_HW_STRUCT_SHED_TASK shBH1750; 
//-------------------------------------------------------------------------------------------------
void snsBH1750(){
//-------------------------------------------------------------------------------------------------
if(dvBH1750.custom==0) {dvBH1750.custom=RT_HW_Base.i2cSetParam(dvBH1750.dvI,i2cAdrBH1750,0,0);  //--adr,bus,speed;
                        dvBH1750.mi='I';
                        shBH1750.periodLimit=50;  RT_HW_Base.setTaskID  (shBH1750,'P',500);}    //--modeTask='P',period=500; 
//----------------------------------------------------------------------
RT_HW_Base.directTask(shBH1750);                        //--Launching AHTXX task; 
RT_HW_bh1750.direct(dvBH1750,shBH1750.run);             //--Sensor control; AHTxx;
//-------------------------------------------------------------------------------------------------
if(dvBH1750.fresh){dvBH1750.fresh=0; vBH1750Lux=dvBH1750.vLux; vBH1750ok=dvBH1750.ok;} //--Updating measured data;
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsBH1750(){;};
#endif
//=================================================================================================
