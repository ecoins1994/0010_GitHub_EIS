//=================================================================================================
//                                      1.1.SHT3X.i2c
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
