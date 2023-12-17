//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                   1.Data EXPANDERS
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
RT_HW_STRUCT_SPI_DEV dvDM13C;   RT_HW_STRUCT_SHED_TASK shDM13C; uint16_t vDM13C=0xFFFF; uint32_t inDM13C=0;
//=================================================================================================
//                                   1.2.Expander via i2c
//=================================================================================================
RT_HW_MCP4725_DEV  dvMCP4725; 
RT_HW_MCP23x17_DEV dvMCP23x17;  RT_HW_STRUCT_SHED_TASK shMCP23x17in, shMCP23x17out;  uint8_t mcp23x17inA,mcp23x17inB;
RT_HW_PCF8575_DEV  dvPCF8575;   RT_HW_STRUCT_SHED_TASK shPCF8575in,  shPCF8575out;   uint8_t PCF8575inA, PCF8575inB;
RT_HW_ADS1115_DEV  dvADS1115;   RT_HW_STRUCT_SHED_TASK shADS1115;
//=================================================================================================
//                                   1.3.Expander via SPI,SPN
//=================================================================================================
RT_HW_74HC595_DEV dv74HC595;    RT_HW_STRUCT_SHED_TASK sh74HC595;  uint32_t vGenRun;
RT_HW_74HC595_DEV dv74HC595N;   RT_HW_STRUCT_SHED_TASK sh74HC595N; uint32_t vGenRunN;
RT_HW_74HC165_DEV dv74HC165;    RT_HW_STRUCT_SHED_TASK sh74HC165;  uint32_t v74HC165,  ago74HC165;
RT_HW_74HC165_DEV dv74HC165N;   RT_HW_STRUCT_SHED_TASK sh74HC165N; uint32_t v74HC165N, ago74HC165N;
//=================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                   0.3.Generators, counter
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
RT_HW_GENERATOR_EVENT_ID idGenRun;      RT_HW_COUNTER_ID idCntRun8;     uint8_t  vGenRun8=0;  //--For generator running "1" 0-8;
                                        RT_HW_COUNTER_ID idCntRun16;    uint16_t vGenRun16=0; //--For generator running "1" 0-16;
                                        RT_HW_COUNTER_ID idCntRun24;    uint32_t vGenRun24=0; //--For generator running "1" 0-24;
                                        RT_HW_COUNTER_ID idCntRun32;    uint32_t vGenRun32=0; //--For generator running "1" 0-32;
//-------------------------------------------------------------------------------------------------
RT_HW_GENERATOR_EVENT_ID idGenDAC;      RT_HW_COUNTER_ID idCntDAC;      uint16_t vGenDAC=0;                //--For generator 0-4095 DAC;
RT_HW_GENERATOR_EVENT_ID idGenA,idGenB; RT_HW_COUNTER_ID idCntA,idCntB; uint8_t  vCntA,vCntB,vGenA,vGenB;  //--For generator MCP23x17;
//=================================================================================================
void  genRun(void){
if(idCntRun8.reset) {RT_HW_Base.counterReset(idCntRun8,  8,0,1,1);}  //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(idCntRun16.reset){RT_HW_Base.counterReset(idCntRun16,16,0,1,1);}  //--init counter: Upper limit=16,  Down limit=0, Change step=1,   Initial value=0;
if(idCntRun24.reset){RT_HW_Base.counterReset(idCntRun24,24,0,1,1);}  //--init counter: Upper limit=24,  Down limit=0, Change step=1,   Initial value=0;
if(idCntRun32.reset){RT_HW_Base.counterReset(idCntRun32,32,0,1,1);}  //--init counter: Upper limit=32,  Down limit=0, Change step=1,   Initial value=0;
if(RT_HW_Base.generatorEvent(idGenRun,50)){
  vGenRun8= RT_HW_Base.dc8(RT_HW_Base.counterS(idCntRun8));
  vGenRun16=RT_HW_Base.dc16(RT_HW_Base.counterS(idCntRun16));
  vGenRun24=RT_HW_Base.dc24(RT_HW_Base.counterS(idCntRun24));
  vGenRun32=RT_HW_Base.dc32(RT_HW_Base.counterS(idCntRun32));
  }                                            
} //--Saw generator 100 ms;
//=================================================================================================
void genDAC(){         
if(idCntDAC.reset){RT_HW_Base.counterReset(idCntDAC,4095,0,10,0);}  //--init counter: Upper limit=4095, Down limit=0, Change step=10, Initial value=0;
if(RT_HW_Base.generatorEvent(idGenDAC,10)) {vGenDAC=RT_HW_Base.counterT(idCntDAC);}; //--Triangle generator 0-4095 for DAC,100 ms;
};
//=================================================================================================
void genMCP23x17(){         
if(idCntA.reset){RT_HW_Base.counterReset(idCntA,8,0,1,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(idCntB.reset){RT_HW_Base.counterReset(idCntB,8,0,1,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(RT_HW_Base.generatorEvent(idGenA,50)) {vCntA=RT_HW_Base.counterT(idCntA); vGenA=RT_HW_Base.dc8(vCntA);
                                          vCntB=RT_HW_Base.counterS(idCntB); vGenB=RT_HW_Base.dc8(vCntB);}
//------------------------------------------------------------------------------------------------
};
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     1. I/O EXPANDERS via i2c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     1.2.MCP23017.i2c;
//=================================================================================================
void extMCP23x17_i2c(){ 
if(dvMCP23x17.custom==0){dvMCP23x17.custom=RT_HW_Base.i2cSetParam(dvMCP23x17.dvI,i2cAdrMCP23x17,0,0);
                         dvMCP23x17.mi='I';
                         dvMCP23x17.cnfgA=0x00; dvMCP23x17.cnfgIPOLA=0xFF; dvMCP23x17.cnfgGPPUA=0xFF;
                         dvMCP23x17.cnfgB=0x00; dvMCP23x17.cnfgIPOLB=0xFF; dvMCP23x17.cnfgGPPUB=0xFF;                        
                         RT_HW_Base.setTaskID(shMCP23x17in, 'P',500);  
                         RT_HW_Base.setTaskID(shMCP23x17out,'Q',100); 
                        }
RT_HW_Base.directTask(shMCP23x17in);
RT_HW_Base.directTask(shMCP23x17out);
if(shMCP23x17out.run){dvMCP23x17.extA=vGenA; dvMCP23x17.extB=vGenB;}
RT_HW_mcp23x17.direct(dvMCP23x17,shMCP23x17in.run,shMCP23x17out.run);
};
//=================================================================================================
//                                     1.3.PCF8575.i2c;
//=================================================================================================
void extPCF8575(){ 
if(dvPCF8575.custom==0){dvPCF8575.custom=RT_HW_Base.i2cSetParam(dvPCF8575.dvI,i2cAdrPCF8575,0,0);
                         dvPCF8575.mi='I';
                         dvPCF8575.cnfgA=0x00; dvPCF8575.invOutA=0xFF;  dvPCF8575.invInA=0xFF;
                         dvPCF8575.cnfgB=0x00; dvPCF8575.invOutB=0xFF;  dvPCF8575.invInB=0xFF;                     
                         RT_HW_Base.setTaskID(shPCF8575in, 'P',100);  
                         RT_HW_Base.setTaskID(shPCF8575out,'Q',100); 
                        }
RT_HW_Base.directTask(shPCF8575in);
RT_HW_Base.directTask(shPCF8575out);
if(shPCF8575out.run){dvPCF8575.extA=vGenA; dvPCF8575.extB=vGenB;}
RT_HW_pcf8575.direct(dvPCF8575,shPCF8575in.run,shPCF8575out.run);
if(dvPCF8575.fresh){};
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     2. I/O EXPANDERS via SPI
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     1.3.PCF8575.i2c;
//=================================================================================================
void extDM13C(){ 
if(dvDM13C.custom==0){csDM13C=46;
                      dvDM13C.custom=RT_HW_Base.spiSetParam(dvDM13C,csDM13C,0,0);                    
                      RT_HW_Base.setTaskID(shDM13C, 'Q',20);  
                     }
RT_HW_Base.directTask(shDM13C);
if(shDM13C.run){RT_HW_Base.spiInitDevice(dvDM13C);
  if(vDM13C!=vGenRun16){vDM13C=vGenRun16; RT_HW_Base.spiTransfer(dvDM13C,vDM13C,inDM13C,2);}}
};
//=================================================================================================
