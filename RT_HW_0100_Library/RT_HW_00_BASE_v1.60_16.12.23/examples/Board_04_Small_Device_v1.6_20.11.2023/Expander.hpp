//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     1. I/O EXPANDERS via i2c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     1.1.MCP23017.i2c;
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_MCP23017
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_MCP23x17_DEV dvMCP23017;  RT_HW_STRUCT_SHED_TASK shMCP23017in, shMCP23017out;
  uint8_t vGenA,vGenB;
//RT_HW_GENERATOR_EVENT_ID idGenA,idGenB; RT_HW_COUNTER_ID idCntA,idCntB; uint8_t vCntA,vCntB;      //--For generator MCP23x17;
  RT_HW_GENERATOR_EVENT_ID idGenAB;       RT_HW_COUNTER_ID idCntAB;       uint16_t vCntAB,vGenAB;   //--For generator MCP23x17;
//------------------------------------------------------------------------------------------------
void expMCP23017(){ 
//------------------------------------------------------------------------------------------------
if(idCntAB.reset){RT_HW_Base.counterReset(idCntAB,16,0,1,1);}   //--init counter: Upper limit=16,   Down limit=0, Change step=1,   Initial value=0;
if(RT_HW_Base.generatorEvent(idGenAB,100)) {vCntAB=RT_HW_Base.counterS(idCntAB); vGenAB=RT_HW_Base.dc16(vCntAB);

                                           vGenA=vGenAB     &0xFF;
                                           vGenB=(vGenAB>>8)&0xFF;
//RT_HW_Base.consoleTest(String("vCnt"),  vCntAB,';');
//RT_HW_Base.consoleTest(String(" vGen"), vGenAB,';','H');
//RT_HW_Base.consoleTest(String(" vGenA"),vGenA, ';','H');  
//RT_HW_Base.consoleTest(String(" vGenB"),vGenB, ';','H');
//RT_HW_Base.consoleCR();                                        
                                           }
//------------------------------------------------------------------------------------------------
//if(idCntA.reset){RT_HW_Base.counterReset(idCntA,8,0,1,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
//if(idCntB.reset){RT_HW_Base.counterReset(idCntB,8,0,1,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
//if(RT_HW_Base.generatorEvent(idGenA,50)) {vCntA=RT_HW_Base.counterT(idCntA); vGenA=RT_HW_Base.dc8(vCntA);
//                                          vCntB=RT_HW_Base.counterS(idCntB); vGenB=RT_HW_Base.dc8(vCntB);}
//------------------------------------------------------------------------------------------------  
if(dvMCP23017.custom==0){dvMCP23017.custom=RT_HW_Base.i2cSetParam(dvMCP23017.dvI,i2cAdrMCP23017,0,0);
                         dvMCP23017.mi='I';
                         dvMCP23017.cnfgA=0x00; dvMCP23017.cnfgIPOLA=0xFF; dvMCP23017.cnfgGPPUA=0xFF;
                         dvMCP23017.cnfgB=0x00; dvMCP23017.cnfgIPOLB=0xFF; dvMCP23017.cnfgGPPUB=0xFF;                        
                         RT_HW_Base.setTaskID(shMCP23017in, 'P',500);  
                         RT_HW_Base.setTaskID(shMCP23017out,'Q',5); 
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
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     2. I/O EXPANDERS via SPI
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     1.1.MCP23S17.i2c;
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_MCP23S17
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RT_HW_MCP23x17_DEV dvMCP23S17;  RT_HW_STRUCT_SHED_TASK shMCP23S17in, shMCP23S17out;
  uint8_t vGenSA,vGenSB;
//RT_HW_GENERATOR_EVENT_ID idGenSA,idGenSB; RT_HW_COUNTER_ID idCntSA,idCntSB; uint8_t vCntSA,vCntSB;      //--For generator MCP23S17;
  RT_HW_GENERATOR_EVENT_ID idGenSAB;        RT_HW_COUNTER_ID idCntSAB;        uint16_t vCntSAB,vGenSAB;   //--For generator MCP23x17;
//------------------------------------------------------------------------------------------------
void expMCP23S17(){ 
//------------------------------------------------------------------------------------------------
if(idCntSAB.reset){
pinMode(csMCP23S17,OUTPUT);
RT_HW_Base.spiBegin(0);
digitalWrite(csMCP23S17,LOW);  SPI.transfer(0x40); SPI.transfer(0x00); SPI.transfer(0x00); digitalWrite(csMCP23S17, HIGH);
digitalWrite(csMCP23S17,LOW);  SPI.transfer(0x40); SPI.transfer(0x01); SPI.transfer(0x00); digitalWrite(csMCP23S17, HIGH);   
RT_HW_Base.counterReset(idCntSAB,8,0,1,1);    //--init counter: Upper limit=16,   Down limit=0, Change step=1,   Initial value=0;
}
//------------------------------------------------------------------------------------------------
if(RT_HW_Base.generatorEvent(idGenSAB,100)){
vCntSAB=RT_HW_Base.counterS(idCntSAB); vGenSA=RT_HW_Base.dc8(vCntSAB); vGenSB=RT_HW_Base.dc8(8-vCntSAB);                                  
digitalWrite(csMCP23S17,0); SPI.transfer(0x40); SPI.transfer(0x12); SPI.transfer(vGenSA); digitalWrite(csMCP23S17,1);
delayMicroseconds(100);
digitalWrite(csMCP23S17,0); SPI.transfer(0x40); SPI.transfer(0x13); SPI.transfer(vGenSB); digitalWrite(csMCP23S17,1); 
}
//-------------------------------------------------------------------------------------------------
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void expMCP23S17(){;};
#endif




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
