//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                   1.Data EXPANDERS
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                   1.3.Expander via SPI,SPN
//=================================================================================================
RT_HW_74HC595_DEV dv74HC595;    RT_HW_STRUCT_SHED_TASK sh74HC595;  uint32_t vGenRun;
//=================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                   0.3.Generators, counter
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
RT_HW_GENERATOR_EVENT_ID idGenRun;      RT_HW_COUNTER_ID idCntRun8;     uint8_t  vGenRun8=0;  //--For generator running "1" 0-8;
                                        RT_HW_COUNTER_ID idCntRun16;    uint16_t vGenRun16=0; //--For generator running "1" 0-16;
                                        RT_HW_COUNTER_ID idCntRun24;    uint32_t vGenRun24=0; //--For generator running "1" 0-24;
                                        RT_HW_COUNTER_ID idCntRun32;    uint32_t vGenRun32=0; //--For generator running "1" 0-32;
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
}; //--Saw generator 100 ms;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     2. I/O EXPANDERS via SPI
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     2.1.DM13C;
//=================================================================================================
RT_HW_GENERATOR_EVENT_ID idGenDM13C;  RT_HW_COUNTER_ID idCntDM13C;    uint32_t vGenDM13C=0, vCntDM13C=0;      
//------------------------------------------------------------------------------------------------
void genCntDM13C(){         
if(idCntDM13C.reset){RT_HW_Base.counterReset(idCntDM13C,32,0,1,0);}  //--init counter: Upper limit=32, Down limit=0, Change step=1, Initial value=0;
if(RT_HW_Base.generatorEvent(idGenDM13C,500)) {vCntDM13C=RT_HW_Base.counterS(idCntDM13C);  vGenDM13C=RT_HW_Base.dc32(vCntDM13C);}; //--Пилa, бегущая "1", 32 разряда;
};
//=================================================================================================
RT_HW_STRUCT_SPI_DEV dvDM13C;         RT_HW_STRUCT_SHED_TASK shDM13C; uint32_t vDM13C=0xFFFF, inDM13C, xDM13C=0;
//------------------------------------------------------------------------------------------------
void extDM13C(){ 
genCntDM13C();
if(dvDM13C.custom==0){dvDM13C.custom=RT_HW_Base.spiSetParam(dvDM13C,csDM13C,0,0);                    
                      RT_HW_Base.setTaskID(shDM13C, 'Q',5);  
                     }
RT_HW_Base.directTask(shDM13C);
if(shDM13C.run){RT_HW_Base.spiInitDevice(dvDM13C);
  if(vDM13C!=vGenDM13C){xDM13C=vDM13C=vGenDM13C;
  xDM13C |=0xF000<<16;
  xDM13C |=0xF000;
  RT_HW_Base.spiTransfer(dvDM13C,xDM13C,inDM13C,4);}
  }
};
//=================================================================================================
