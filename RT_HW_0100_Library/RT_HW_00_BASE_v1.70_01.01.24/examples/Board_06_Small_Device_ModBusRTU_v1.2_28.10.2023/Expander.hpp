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
