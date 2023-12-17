//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                   1.Data SENSORS
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                   1.1.1.Data Sensors via pins
//=================================================================================================
RT_HW_DHT22   dvDHT22;            RT_HW_STRUCT_SHED_TASK shDHT22;    
RT_HW_STRUCT_DS1820_ID  dvDS1820; RT_HW_STRUCT_SHED_TASK shDS1820;  RT_HW_ONEWIRE dvNW;
//=================================================================================================
//                                   1.1.2.HC-SR04 sensors via Trig pin with interrupts
//=================================================================================================
RT_HW_STRUCT_SR04_ID  dvSR04;     RT_HW_STRUCT_SHED_TASK shSR04;
RT_HW_FILTER_MEDIAN_3 <uint16_t> ftrSR04;     uint16_t vSR04LenF;   //--Parameters for the HC-SR04 filter (3rd order median);
//-----------------------------------1.2.2.1.Interrupt handler HC-SR04-----------------------------
RT_HW_IRAM_ATTR void RT_HW_IRQ_SR04_handler_dvSR04(){
  if(dvSR04.state==2) {if( RT_HW_PIN_DIR_READ(dvSR04.ddPin)){dvSR04.timeBegin=micros(); dvSR04.state=3;}}
  if(dvSR04.state==3) {if(!RT_HW_PIN_DIR_READ(dvSR04.ddPin)){dvSR04.timeEnd  =micros(); dvSR04.state=4;}}}
//=================================================================================================
//                                   1.3.Data Sensors via i2c
//=================================================================================================
RT_HW_AHTxx_DEV   dvAHTxx;      RT_HW_STRUCT_SHED_TASK shAHTxx;
RT_HW_BMP180_DEV  dvBMP180;     RT_HW_STRUCT_SHED_TASK shBMP180Temp, shBMP180Press;
RT_HW_BME280_DEV  dvBME280;     RT_HW_STRUCT_SHED_TASK shBME280Temp, shBME280Hum,shBME280Press; 
//=================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                          SENSORS via pin
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                      1.1.DS1820 через 1-Wire
//  Setting task: 'P'-periodic call, no more than 50 cycles, 2200ms period;
//=================================================================================================
void snsDS1820(){
if(shDS1820.custom==0){RT_HW_Base.setTaskID(shDS1820,'P',2200); shDS1820.periodLimit=50;}
if(dvDS1820.custom==0){RT_HW_ds1820.setParam(dvDS1820,pinDS1820);}//--Setting sensor parameters;
dvDS1820.run=RT_HW_Base.directTask(shDS1820);                     //--Launching task;
RT_HW_ds1820.direct(dvNW,dvDS1820);                               //--Sensor control; 
if(dvDS1820.fresh){dvDS1820.fresh=0; vDS1820Temp=dvDS1820.vTemp; vDS1820ok=dvDS1820.ok;} //--Updating measured data;
};
//=================================================================================================
//                                      1.2.DHT22.pin
//  Setting task: 'P'-periodic call, default no more than 50 cycles, 2500ms period;
//=================================================================================================
void snsDHT22(){
if(shDHT22.custom==0){RT_HW_Base.setTaskID(shDHT22,'P',2500); shDHT22.periodLimit=50;}
if(dvDHT22.custom==0){dvDHT22.setParam(pinDHT22);}                //--Setting sensor parameters;
dvDHT22.run=RT_HW_Base.directTask(shDHT22);                       //--Launching task;
dvDHT22.direct();                                                 //--Sensor control;
if(dvDHT22.fresh){dvDHT22.fresh=0; vDHT22Temp=dvDHT22.vTemp; vDHT22Hum=dvDHT22.vHum; vDHT22ok=dvDHT22.ok;} //--Updating measured data;
};
//=================================================================================================
//                                      1.3.HC-SR04 via pinTrig 
//                              (Echo connected to Trig via R=470 ohm)
//  Setting task: 'P'-periodic call, default no more than 5 cycles, 75ms period;
//=================================================================================================
void snsSR04(){
if(shSR04.custom==0){RT_HW_Base.setTaskID(shSR04,'P',75);}    //--Setting task: 'P'-periodic call, no more than 5 cycles, 75ms period;
if(dvSR04.custom==0){dvSR04.custom=1; dvSR04.extPinTrig=pinSR04; dvSR04.maxLen=400;}    //--Setting sensor parameters;
dvSR04.run=RT_HW_Base.directTask(shSR04);                       //--Launching task;  
RT_HW_sr04.direct(dvSR04);                                      //--Sensor control;
if(dvSR04.state==1){dvSR04.state++;  attachInterrupt(dvSR04.numIRQ, RT_HW_IRQ_SR04_handler_dvSR04,CHANGE);}
if(dvSR04.fresh)   {dvSR04.fresh=0;  dvSR04.LenMcs=ftrSR04.filtered(dvSR04.echoMcs);   //--Updating measured data;
                    dvSR04.Len=round(dvSR04.LenMcs * dvSR04.speedSoundAir/10.0) ;  
                 if(dvSR04.Len>dvSR04.maxLen){dvSR04.Len=dvSR04.maxLen;}
                    vSR04Len=dvSR04.Len;  vSR04ok=dvSR04.ok;}         
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                    2.SENSORS via i2c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                    2.1.AHTxx.i2c (T,H)      
//=================================================================================================
void snsAHTxx(){
//-------------------------------------------------------------------------------------------------
if(dvAHTxx.custom==0) {dvAHTxx.mi='I';          
                       dvAHTxx.custom=RT_HW_Base.i2cSetParam(dvAHTxx.dvI,i2cAdrAHTxx,0,0);  //--adr,bus,speed;
                       shAHTxx.periodLimit=50;  RT_HW_Base.setTaskID  (shAHTxx,'P',1200);}  //--modeTask='P',period=1200; 
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shAHTxx);             //--Launching AHTXX task; 
RT_HW_ahtxx.direct(dvAHTxx,shAHTxx.run);    //--Sensor control AHTxx;
//-------------------------------------------------------------------------------------------------
if(dvAHTxx.fresh){dvAHTxx.fresh=0; vAHTxx_ok=dvAHTxx.ok; vAHTxx_Temp=dvAHTxx.vTemp; vAHTxx_Hum=dvAHTxx.vHum;}  //--Updating measured data;
};
//=================================================================================================
//                                     2.4.BMP180.i2c     
//=================================================================================================
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
//=================================================================================================
//                                     2.5.BME280.i2c     
//=================================================================================================
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
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
if(dvBME280.fresh){dvBME280.fresh=0; vBMP_ok=vBME280_ok=dvBME280.ok; vBMP_Temp=vBME280_Temp=dvBME280.vTemp; vBMP_Hum=vBME280_Hum=dvBME280.vHum; vBMP_Press=vBME280_Press=dvBME280.vPress;}   //--Updating measured data;
};
//=================================================================================================
