//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                   1.1.Data EXPANDERS
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
RT_HW_PCF8575_DEV  dvPCF8575;   RT_HW_STRUCT_SHED_TASK shPCF8575in,  shPCF8575out;   uint8_t PCF8575inA=0, PCF8575inB=0;
RT_HW_STRUCT_SPI_DEV dvDM13C;   RT_HW_STRUCT_SHED_TASK shDM13C; uint16_t vDM13C=0xFFFF; uint32_t inDM13C=0;
//=================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                   1.2.Data Generators, Сounter
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
void genAB(){         
if(idCntA.reset){RT_HW_Base.counterReset(idCntA,8,0,1,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(idCntB.reset){RT_HW_Base.counterReset(idCntB,8,0,1,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(RT_HW_Base.generatorEvent(idGenA,50)) {vCntA=RT_HW_Base.counterT(idCntA); vGenA=RT_HW_Base.dc8(vCntA);
                                          vCntB=RT_HW_Base.counterS(idCntB); vGenB=RT_HW_Base.dc8(vCntB);}
};
//=================================================================================================
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
//                                     4. I/O EXPANDERS via SPI
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     4.1.DM13C;
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
