//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     2. I/O EXPANDERS via
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     2.1. 74HC595.SPI
//=================================================================================================
RT_HW_74HC595_DEV dv74HC595;    RT_HW_STRUCT_SHED_TASK sh74HC595;  uint32_t vGenRun;
RT_HW_GENERATOR_EVENT_ID idGenRun;   RT_HW_COUNTER_ID idCntRun8;  uint8_t   vGenRun8=0;  //--For generator running "1" 0-8;
//=================================================================================================
void  genRun(){
if(idCntRun8.reset) {RT_HW_Base.counterReset(idCntRun8,  8,0,1,1);}  //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(RT_HW_Base.generatorEvent(idGenRun,50)){vGenRun8= RT_HW_Base.dc8(RT_HW_Base.counterS(idCntRun8));}}
//=================================================================================================
void direct595(){   
if(dv74HC595.custom==0){dv74HC595.custom=RT_HW_Base.spiSetParam(dv74HC595.dvS,cs74HC595,0,4000000);
                        dv74HC595.mi='S'; dv74HC595.qnt=1; dv74HC595.bitOrder=1;  //--qnt=Number of registers 74HC595(1-4);
                        RT_HW_Base.setTaskID(sh74HC595,'Q');}  //--Setting task: 'Q'-on change output in every  default=5th cycle; 
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(sh74HC595); 
//-------------------------------------------------------------------------------------------------
RT_HW_74hc595.direct(dv74HC595,vGenRun8,sh74HC595.run);
};
//=================================================================================================
