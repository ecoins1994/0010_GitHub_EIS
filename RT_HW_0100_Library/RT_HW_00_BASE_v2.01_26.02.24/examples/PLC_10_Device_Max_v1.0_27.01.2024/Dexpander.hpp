//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     4. СИСТЕМНЫЕ РАСШИРИТЕЛИ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     4.1. 74HC595.SPI Ввывод бегущей '1'
//=================================================================================================
RT_HW_74HC595_DEV           dv74HC595;    RT_HW_STRUCT_SHED_TASK sh74HC595;
RT_HW_GENERATOR_EVENT_ID idGen74HC595;    RT_HW_COUNTER_ID    idCnt74HC595;   uint32_t vCnt74HC595=0;    uint32_t vGen74HC595=0;  
RT_HW_GENERATOR_RUN_ID  idRun;  
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_TEST_PERMIT_74HC595
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void exp74HC595(){   
//------------------------------------------------------------------------------------------------
if(idCnt74HC595.reset){RT_HW_Base.counterReset(idCnt74HC595,8,0,1,0);}      //--Инициализация счетчика: top=8, bottom=0, шаг изменения=1, начальное значение=0;
if(RT_HW_Base.generatorEvent(idGen74HC595,100)) {vCnt74HC595=RT_HW_Base.counterS(idCnt74HC595);  vGen74HC595=RT_HW_Base.dc8(vCnt74HC595);}; //--Пилa, бегущая "1", 32 разряда;
//------------------------------------------------------------------------------------------------
if(dv74HC595.custom==0){dv74HC595.custom=RT_HW_Base.spiSetParam(dv74HC595.dvS,cs74HC595,0,4000000);
                        dv74HC595.mi='S'; dv74HC595.qnt=1;  //--Кол-во регистров 74HC595(1-4);
                        dv74HC595.bitOrder=0;               //--Последовательность вывода: =1 - впереди старший бит;
                        RT_HW_Base.setTaskID(sh74HC595, 'Q',5); //--Вывод по изменениям с проверкой каждые 5 циклов программы; 
}
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(sh74HC595);
RT_HW_74hc595.direct(dv74HC595,vGen74HC595,sh74HC595.run);   pinDOT=vGen74HC595;};
#else
void exp74HC595(){;};
#endif
//=================================================================================================
//                                     2.2. 74HC165.SPI
//=================================================================================================
RT_HW_74HC165_DEV dv74HC165;    RT_HW_STRUCT_SHED_TASK sh74HC165;
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_TEST_PERMIT_74HC165
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void exp74HC165(){  
if(dv74HC165.custom==0){dv74HC165.custom=RT_HW_Base.spiSetParam(dv74HC165.dvS,cs74HC165,0,4000000);
                        dv74HC165.mi='S'; dv74HC165.qnt=1; dv74HC165.bitOrder=1;  //--qnt=Кол-во регистров 74HC595(1-4);
                        RT_HW_Base.setTaskID(sh74HC165,'P',50);                   //--Периодический вызов задачи: 'P';                      
                        }                  
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(sh74HC165); 
//-------------------------------------------------------------------------------------------------
RT_HW_74hc165.direct(dv74HC165,sh74HC165.run); 
if(dv74HC165.fresh) {dv74HC165.fresh=0;  v74HC165=dv74HC165.var; pinDIN=v74HC165;
};
}; //--END void exp74HC165()
#else
void exp74HC165(){;};
#endif

//=================================================================================================
//                                     4.4.MCP4725.i2c;
//=================================================================================================
RT_HW_MCP4725_DEV        dvMCP4725;   RT_HW_STRUCT_SHED_TASK shMCP4725;
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_TEST_PERMIT_MCP4725
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void expMCP4725(){ 
//-------------------------------------------------------------------------------------------------
if(dvMCP4725.custom==0){dvMCP4725.custom=RT_HW_Base.i2cSetParam(dvMCP4725.dvI,i2cAdrMCP4725,0,800000); //--800 кГц;
                        dvMCP4725.mi='I'; RT_HW_Base.setTaskID(shMCP4725,'Q'); shMCP4725.period=0;}
//------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shMCP4725);                         //--Launching task; 
RT_HW_mcp4725.direct(dvMCP4725,vDAC,shMCP4725.run );   //--Direct MCP4725;
};
#else
void expMCP4725(){;};
#endif
//=================================================================================================
//                                     4.5.MCP4725x.i2c;
//=================================================================================================
RT_HW_MCP4725_DEV        dvMCP4725x;   RT_HW_STRUCT_SHED_TASK shMCP4725x;
RT_HW_GENERATOR_EVENT_ID idGenDACx;    RT_HW_COUNTER_ID idCntDACx;      uint16_t vGenDACx=0;                //--For generator 0-4095 DAC;
#ifdef RT_HW_TEST_PERMIT_MCP4725x
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//-------------------------------------------------------------------------------------------------
void expMCP4725x(){ 
//------------------------------------------------------------------------------------------------
if(idCntDACx.reset){RT_HW_Base.counterReset(idCntDACx,4095,0,10,0);}  //--init counter: Upper limit=4095, Down limit=0, Change step=10, Initial value=0;
if(RT_HW_Base.generatorEvent(idGenDACx,10)) {vGenDACx=RT_HW_Base.counterT(idCntDACx);}; //--Triangle generator 0-4095 for DAC,100 ms;
//-------------------------------------------------------------------------------------------------
if(dvMCP4725x.custom==0){dvMCP4725x.custom=RT_HW_Base.i2cSetParam(dvMCP4725x.dvI,i2cAdrMCP4725x,0,800000); //--800 кГц;
                        dvMCP4725x.mi='I'; RT_HW_Base.setTaskID(shMCP4725x,'Q'); shMCP4725x.period=0;}
//------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shMCP4725x);                          //--Launching task; 
RT_HW_mcp4725.direct(dvMCP4725x,vGenDACx,shMCP4725x.run );   //--Direct MCP4725;
};
#else
void expMCP4725x(){;};
#endif

//=====================================================================================================



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     1. I/O EXPANDERS via i2c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     1.1.MCP23017.i2c;
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_MCP23017
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_MCP23x17_DEV dvMCP23017;  RT_HW_STRUCT_SHED_TASK shMCP23017in, shMCP23017out;
RT_HW_GENERATOR_EVENT_ID idGenA,idGenB; RT_HW_COUNTER_ID idCntA,idCntB; uint8_t  vCntA,vCntB,vGenA,vGenB;  //--For generator MCP23x17;
//------------------------------------------------------------------------------------------------
void expMCP23017(){ 
//------------------------------------------------------------------------------------------------
if(idCntA.reset){RT_HW_Base.counterReset(idCntA,8,0,1,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(idCntB.reset){RT_HW_Base.counterReset(idCntB,8,0,1,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(RT_HW_Base.generatorEvent(idGenA,50)) {vCntA=RT_HW_Base.counterT(idCntA); vGenA=RT_HW_Base.dc8(vCntA);
                                          vCntB=RT_HW_Base.counterS(idCntB); vGenB=RT_HW_Base.dc8(vCntB);}
//------------------------------------------------------------------------------------------------  
if(dvMCP23017.custom==0){dvMCP23017.custom=RT_HW_Base.i2cSetParam(dvMCP23017.dvI,i2cAdrMCP23017,0,0);
                         dvMCP23017.mi='I';
                         dvMCP23017.cnfgA=0x00; dvMCP23017.cnfgIPOLA=0xFF; dvMCP23017.cnfgGPPUA=0xFF;
                         dvMCP23017.cnfgB=0x00; dvMCP23017.cnfgIPOLB=0xFF; dvMCP23017.cnfgGPPUB=0xFF;                        
                         RT_HW_Base.setTaskID(shMCP23017in, 'P',500);  
                         RT_HW_Base.setTaskID(shMCP23017out,'Q',100); 
                        }
RT_HW_Base.directTask(shMCP23017in);
RT_HW_Base.directTask(shMCP23017out);
if(shMCP23017out.run){dvMCP23017.extA=vGenA; dvMCP23017.extB=vGenB;}
RT_HW_mcp23x17.direct(dvMCP23017,shMCP23017in.run,shMCP23017out.run);
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void expMCP23017(){;};
#endif

//=================================================================================================
//                                     1.2.PCF8575.i2c;
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_PCF8575
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_PCF8575_DEV  dvPCF8575;   RT_HW_STRUCT_SHED_TASK shPCF8575in,  shPCF8575out;
RT_HW_GENERATOR_EVENT_ID idGnA,idGnB; RT_HW_COUNTER_ID idCnA,idCnB; uint8_t  vCnA,vCnB,vGnA,vGnB;  //--For generator MCP23x17;
//------------------------------------------------------------------------------------------------
void expPCF8575(){ 
//------------------------------------------------------------------------------------------------
if(idCnA.reset){RT_HW_Base.counterReset(idCnA,8,0,1,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(idCnB.reset){RT_HW_Base.counterReset(idCnB,8,0,1,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(RT_HW_Base.generatorEvent(idGnA,50)) {vCnA=RT_HW_Base.counterT(idCnA); vGnA=RT_HW_Base.dc8(vCnA);
                                         vCnB=RT_HW_Base.counterS(idCnB); vGnB=RT_HW_Base.dc8(vCnB);}
//------------------------------------------------------------------------------------------------
if(dvPCF8575.custom==0){dvPCF8575.custom=RT_HW_Base.i2cSetParam(dvPCF8575.dvI,i2cAdrPCF8575,0,0);
                         dvPCF8575.mi='I';
                         dvPCF8575.cnfgA=0x00; dvPCF8575.invOutA=0xFF;  dvPCF8575.invInA=0xFF;
                         dvPCF8575.cnfgB=0x00; dvPCF8575.invOutB=0xFF;  dvPCF8575.invInB=0xFF;                     
                         RT_HW_Base.setTaskID(shPCF8575in, 'P',100);  
                         RT_HW_Base.setTaskID(shPCF8575out,'Q',100); 
                        }
RT_HW_Base.directTask(shPCF8575in);
RT_HW_Base.directTask(shPCF8575out);
if(shPCF8575out.run){dvPCF8575.extA=vGnA; dvPCF8575.extB=vGnB;}
RT_HW_pcf8575.direct(dvPCF8575,shPCF8575in.run,shPCF8575out.run);
if(dvPCF8575.fresh){};
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void expPCF8575(){;};
#endif
//=================================================================================================
//                                     1.3.ADS1115.i2c;
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_ADS1115
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_ADS1115_DEV  dvADS1115;   RT_HW_STRUCT_SHED_TASK shADS1115;
//-------------------------------------------------------------------------------------------------
void expADS1115(){ 
if(dvADS1115.custom==0){dvADS1115.custom=RT_HW_Base.i2cSetParam(dvADS1115.dvI,i2cAdrADS1115,0,800000);
                        dvADS1115.mi='I';RT_HW_Base.setTaskID(shADS1115,'P',200);}
//------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shADS1115);                         //--Launching task; 
RT_HW_ads1115.direct(dvADS1115,shADS1115.run );           //--Direct ADS1115;
//-------------------------------------------------------------------------------------------------
if(dvADS1115.fresh){dvADS1115.fresh=0;                  vADS1115_ok=dvADS1115.ok; 
vADS1115_A0f=RT_HW_ads1115.getVar_V(dvADS1115,dvADS1115.vA0);  
vADS1115_A1f=RT_HW_ads1115.getVar_V(dvADS1115,dvADS1115.vA1); 
vADS1115_A2f=RT_HW_ads1115.getVar_V(dvADS1115,dvADS1115.vA2);  
vADS1115_A3f=RT_HW_ads1115.getVar_V(dvADS1115,dvADS1115.vA3);
}};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void expADS1115(){;};
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     2. I/O EXPANDERS via SPI
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//=================================================================================================
//                                     2.1.DM13C.SPI сдвиговый регистр вывода/ввода
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_DM13C
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_STRUCT_SPI_DEV dvDM13C;         RT_HW_STRUCT_SHED_TASK shDM13C; uint32_t vDM13C=0xFFFF, inDM13C, xDM13C=0;
RT_HW_GENERATOR_EVENT_ID idGenDM13C;  RT_HW_COUNTER_ID idCntDM13C;    uint32_t vGenDM13C=0, vCntDM13C=0;   
//------------------------------------------------------------------------------------------------
void expDM13C(){ 
//------------------------------------------------------------------------------------------------
if(idCntDM13C.reset){RT_HW_Base.counterReset(idCntDM13C,16,0,1,0);}  //--init counter: Upper limit=32, Down limit=0, Change step=1, Initial value=0;
if(RT_HW_Base.generatorEvent(idGenDM13C,50)) {vCntDM13C=RT_HW_Base.counterS(idCntDM13C);  vGenDM13C=RT_HW_Base.dc32(vCntDM13C);}; //--Пилa, бегущая "1", 32 разряда;
//-----------------------------------------------------------------------------------------------
if(dvDM13C.custom==0){dvDM13C.custom=RT_HW_Base.spiSetParam(dvDM13C,csDM13C,0,0);                    
                      RT_HW_Base.setTaskID(shDM13C, 'Q',5);  
                     }
RT_HW_Base.directTask(shDM13C);
if(shDM13C.run){RT_HW_Base.spiInitDevice(dvDM13C);
  if(vDM13C!=vGenDM13C){xDM13C=vDM13C=vGenDM13C;
  //xDM13C |=0xF000<<16;
  //xDM13C |=0xF000;
  RT_HW_Base.spiTransfer(dvDM13C,xDM13C,inDM13C,4);}
  }
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void expDM13C(){;};
#endif
//=================================================================================================
