



//=================================================================================================
//                                      2.2.SHT3X.i2c
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
//                                     2.4.BME280.i2c     
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
//                                     2.4.BMP180.i2c     
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
//                                      2.6.HTU21.i2c
//  Setting task Temp:  'P'-periodic call, no more than 5 cycles, period 2200ms;
//  Setting task Hum:   'P'-periodic call, no more than 5 cycles, period 2500ms;
//  Setting sensor: adr=i2cAdrHTU21, bus=0, speed=0;
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_HTU21
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_HTU21_DEV   dvHTU21;      RT_HW_STRUCT_SHED_TASK shHTU21Temp,  shHTU21Hum;
//-------------------------------------------------------------------------------------------------
void snsHTU21(){
//----------------------------------------------------------------------
if(dvHTU21.custom==0) {dvHTU21.mi='I';             
                       dvHTU21.custom=RT_HW_Base.i2cSetParam(dvHTU21.dvI,i2cAdrHTU21,0,0); //--adr,bus,speed;
                       shHTU21Temp.periodLimit=50; RT_HW_Base.setTaskID  (shHTU21Temp,'P',2200);        //--modeTask='P',period=2200; 
                       shHTU21Hum.periodLimit=50;  RT_HW_Base.setTaskID  (shHTU21Hum,'P',2500);}        //--modeTask='P',period=2500; 
//----------------------------------------------------------------------
RT_HW_Base.directTask(shHTU21Temp); //--Launching task Temp;
RT_HW_Base.directTask(shHTU21Hum);  //--Launching task Hum;
RT_HW_htu21.direct(dvHTU21,shHTU21Temp.run,shHTU21Hum.run);  //--Sensor control;
//-------------------------------------------------------------------------------------------------
if(dvHTU21.fresh){dvHTU21.fresh=0; vHTU21_Temp=dvHTU21.vTemp; vHTU21_Hum=dvHTU21.vHum; vHTU21_ok=dvHTU21.ok;} //--Updating measured data;
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsHTU21(){;};
#endif
//=================================================================================================
//                                      2.7.BH1750
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     3.SENSORS via SPI
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     3.1.MAX6675.SPI
//  Setting task:   'P'-periodic call, no more than 5 cycles, period 1200ms;
//  Setting sensor: cs=csMAX6675, bus=0, speed=0;
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_MAX6675
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_MAX6675_DEV dvMAX6675;    RT_HW_STRUCT_SHED_TASK shMAX6675;
//-------------------------------------------------------------------------------------------------
void snsMAX6675(){
//-------------------------------------------------------------------------------------------------
if(dvMAX6675.custom==0){dvMAX6675.mi='S';
                        dvMAX6675.custom=RT_HW_Base.spiSetParam(dvMAX6675.dvS,csMAX6675,0,4000000); 
                        shMAX6675.periodLimit=50; RT_HW_Base.setTaskID(shMAX6675,'P',1200);}                                            
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shMAX6675);                                         //--Launching task;                     
RT_HW_max6675.direct(dvMAX6675,shMAX6675.run);                            //--Sensor control;                                              
//-------------------------------------------------------------------------------------------------
if(dvMAX6675.fresh){dvMAX6675.fresh=0; vMAX6675Temp=dvMAX6675.vTemp; vMAX6675ok=dvMAX6675.ok;} //--Updating measured data;
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsMAX6675(){;};
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     4.SENSORS via SPN
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     4.1.MAX6675 SPN
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_MAX6675N
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_MAX6675_DEV dvMAX6675N;   RT_HW_STRUCT_SHED_TASK shMAX6675N; 
//-------------------------------------------------------------------------------------------------
void snsMAX6675N(){  
//-------------------------------------------------------------------------------------------------
if(dvMAX6675N.custom==0){dvMAX6675N.mi='N'; 
                         dvMAX6675N.custom=RT_HW_Base.spnSetParam(dvMAX6675N.dvN,sckMAX6675N,misoMAX6675N,255,csMAX6675N,0);                            
                         shMAX6675N.periodLimit=50;           RT_HW_Base.setTaskID(shMAX6675N,'P',1200);}
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shMAX6675N);                                         //--Launching task;                     
RT_HW_max6675.direct(dvMAX6675N,shMAX6675N.run);                           //--Sensor control;                                              
//-------------------------------------------------------------------------------------------------
if(dvMAX6675N.fresh){dvMAX6675N.fresh=0; vMAX6675NTemp=dvMAX6675N.vTemp; vMAX6675Nok=dvMAX6675N.ok;} //--Updating measured data;
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void snsMAX6675N(){;};
#endif
//=================================================================================================
