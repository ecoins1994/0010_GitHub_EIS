//=================================================================================================
//								1. ФУНКЦИЯ ПОЛУЧЕНИЯ ИМЕН ПИНОВ (ESP8266,ESP32 и др.)
//=================================================================================================
String getNamePin(uint8_t pin){									//==Возвращает номера пина в текстовой форме (с учетом ESP8266, STM32);
#if !defined(RT_HM_COREM)				//==Резервирование для многоядерных контроллеров;
  uint8_t  i,j;
  char     chr;
#endif
(void)i; (void)j; (void)chr; 
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#if   defined(RT_HW_CORE_ESP8266)	
if(pin==16) {return String(F("D0"));}
if(pin== 5) {return String(F("D1"));}
if(pin== 4) {return String(F("D2"));}
if(pin== 0) {return String(F("D3"));}
if(pin== 2) {return String(F("D4"));}
if(pin==14) {return String(F("D5"));}
if(pin==12) {return String(F("D6"));}
if(pin==13) {return String(F("D7"));}
if(pin==15) {return String(F("D8"));}
if(pin== 3) {return String(F("D9"));}
if(pin== 1) {return String(F("D10"));}
if(pin==17) {return String(F("A0"));}
if(pin==3)	{return String(F("RX"));}
if(pin==1)  {return String(F("TX"));}
if(pin==3)	{return String(F("RX"));}
if(pin==1)	{return String(F("TX"));}
if(pin==2)	{return String(F("TX1"));}
if(pin==13) {return String(F("RX2"));}
if(pin==15) {return String(F("TX2"));}
if(pin>=255){return String(F(" * "));}
return (String(F("*"))+String(pin));		 
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_STM32)				 
if(pin>=254) {                     mess.str=String(' '); mess.str+=String('*'); 						return mess.str;}	
for(i=0; i<=8; i++){chr=char(((uint8_t)'A')+i); for(j=0; j<16; j++){
 if(getNumPinSTM32(chr,j)==pin) {mess.str=String('P'); mess.str+=String(chr); mess.str+=String(j); 	return mess.str;}}
                                 mess.str=String('P'); mess.str+=String('='); mess.str+=String(pin);	return mess.str;}
return (String(F("P="))+String(pin));
#endif
//-------------------------------------------------------------------------------------------------
return String(pin);		
};
//=================================================================================================
//							2. ФУНКЦИЯ ПОЛУЧЕНИЯ НОМЕРОВ ПИНОВ  (STM32)
//=================================================================================================
uint8_t getNumPinSTM32(char reg, uint8_t num){ 	//==Возвращает номер пина по регистру reg(A,B,C,D,E,F,G) и номеру num(0-15). Если отсутствует, возвращает -1;                                       
#if defined(RT_HW_CORE_STM32)	
//===============================================
if(reg=='A'){
//-----------------------------------------------
if(num==0){
#if defined(PA0)
return PA0;
#endif
}//----------------------------------------------
if(num==1){
#if defined(PA1)
return PA1;
#endif
}//----------------------------------------------
if(num==2){
#if defined(PA2)
return PA2; 
#endif
}//----------------------------------------------
if(num==3){
#if defined(PA3)
return PA3; 
#endif
}//-----------------------------------------------
if(num==4){
#if defined(PA4)
return PA4; 
#endif
}//-----------------------------------------------
if(num==5){
#if defined(PA5)
return PA5; 
#endif
}//-----------------------------------------------
if(num==6){
#if defined(PA6)
return PA6; 
#endif
}//-----------------------------------------------
if(num==7){
#if defined(PA7)
return PA7; 
#endif
}//----------------------------------------------
if(num==8){
#if defined(PA8)
return PA8;
#endif
}//----------------------------------------------
if(num==9){
#if defined(PA9)
return PA9;
#endif
}//----------------------------------------------
if(num==10){
#if defined(PA10)
return PA10; 
#endif
}//----------------------------------------------
if(num==11){
#if defined(PA11)
return PA11; 
#endif
}//-----------------------------------------------
if(num==12){
#if defined(PA12)
return PA12; 
#endif
}//-----------------------------------------------
if(num==13){
#if defined(PA13)
return PA13; 
#endif
}//-----------------------------------------------
if(num==14){
#if defined(PA14)
return PA14; 
#endif
}//-----------------------------------------------
if(num==15){
#if defined(PA15)
return PA15; 
#endif
}
} // END PA ---и т.д. 0-15;
//===============================================
if(reg=='B'){
//-----------------------------------------------
if(num==0){
#if defined(PB0)
return PB0;
#endif
}//----------------------------------------------
if(num==1){
#if defined(PB1)
return PB1;
#endif
}//----------------------------------------------
if(num==2){
#if defined(PB2)
return PB2; 
#endif
}//----------------------------------------------
if(num==3){
#if defined(PB3)
return PB3; 
#endif
}//-----------------------------------------------
if(num==4){
#if defined(PB4)
return PB4; 
#endif
}//-----------------------------------------------
if(num==5){
#if defined(PB5)
return PB5; 
#endif
}//-----------------------------------------------
if(num==6){
#if defined(PB6)
return PB6; 
#endif
}//-----------------------------------------------
if(num==7){
#if defined(PB7)
return PB7; 
#endif
}//----------------------------------------------
if(num==8){
#if defined(PB8)
return PB8;
#endif
}//----------------------------------------------
if(num==9){
#if defined(PB9)
return PB9;
#endif
}//----------------------------------------------
if(num==10){
#if defined(PB10)
return PB10; 
#endif
}//----------------------------------------------
if(num==11){
#if defined(PB11)
return PB11; 
#endif
}//-----------------------------------------------
if(num==12){
#if defined(PB12)
return PB12; 
#endif
}//-----------------------------------------------
if(num==13){
#if defined(PB13)
return PB13; 
#endif
}//-----------------------------------------------
if(num==14){
#if defined(PB14)
return PB14; 
#endif
}//-----------------------------------------------
if(num==15){
#if defined(PB15)
return PB15; 
#endif
}
}	// END PB ---и т.д. 0-15;
//===============================================
if(reg=='C'){
//-----------------------------------------------
if(num==0){
#if defined(PC0)
return PC0;
#endif
}//----------------------------------------------
if(num==1){
#if defined(PC1)
return PC1;
#endif
}//----------------------------------------------
if(num==2){
#if defined(PC2)
return PC2; 
#endif
}//----------------------------------------------
if(num==3){
#if defined(PC3)
return PC3; 
#endif
}//-----------------------------------------------
if(num==4){
#if defined(PC4)
return PC4; 
#endif
}//-----------------------------------------------
if(num==5){
#if defined(PC5)
return PC5; 
#endif
}//-----------------------------------------------
if(num==6){
#if defined(PC6)
return PC6; 
#endif
}//-----------------------------------------------
if(num==7){
#if defined(PC7)
return PC7; 
#endif
}//----------------------------------------------
if(num==8){
#if defined(PC8)
return PC8;
#endif
}//----------------------------------------------
if(num==9){
#if defined(PC9)
return PC9;
#endif
}//----------------------------------------------
if(num==10){
#if defined(PC10)
return PC10; 
#endif
}//----------------------------------------------
if(num==11){
#if defined(PC11)
return PC11; 
#endif
}//-----------------------------------------------
if(num==12){
#if defined(PC12)
return PC12; 
#endif
}//-----------------------------------------------
if(num==13){
#if defined(PC13)
return PC13; 
#endif
}//-----------------------------------------------
if(num==14){
#if defined(PC14)
return PC14; 
#endif
}//-----------------------------------------------
if(num==15){
#if defined(PC15)
return PC15; 
#endif
}}// END PC ---и т.д. 0-15;
//===============================================
if(reg=='D'){
//-----------------------------------------------
if(num==0){
#if defined(PD0)
return PD0;
#endif
}//----------------------------------------------
if(num==1){
#if defined(PD1)
return PD1;
#endif
}//----------------------------------------------
if(num==2){
#if defined(PD2)
return PD2; 
#endif
}//----------------------------------------------
if(num==3){
#if defined(PD3)
return PD3; 
#endif
}//-----------------------------------------------
if(num==4){
#if defined(PD4)
return PD4; 
#endif
}//-----------------------------------------------
if(num==5){
#if defined(PD5)
return PD5; 
#endif
}//-----------------------------------------------
if(num==6){
#if defined(PD6)
return PD6; 
#endif
}//-----------------------------------------------
if(num==7){
#if defined(PD7)
return PD7; 
#endif
}//----------------------------------------------
if(num==8){
#if defined(PD8)
return PD8;
#endif
}//----------------------------------------------
if(num==9){
#if defined(PD9)
return PD9;
#endif
}//----------------------------------------------
if(num==10){
#if defined(PD10)
return PD10; 
#endif
}//----------------------------------------------
if(num==11){
#if defined(PD11)
return PD11; 
#endif
}//-----------------------------------------------
if(num==12){
#if defined(PD12)
return PD12; 
#endif
}//-----------------------------------------------
if(num==13){
#if defined(PD13)
return PD13; 
#endif
}//-----------------------------------------------
if(num==14){
#if defined(PD14)
return PD14; 
#endif
}//-----------------------------------------------
if(num==15){
#if defined(PD15)
return PD15; 
#endif
}}// END PD ---и т.д. 0-15;
//===============================================
if(reg=='E'){
//-----------------------------------------------
if(num==0){
#if defined(PE0)
return PE0;
#endif
}//----------------------------------------------
if(num==1){
#if defined(PE1)
return PE1;
#endif
}//----------------------------------------------
if(num==2){
#if defined(PE2)
return PE2; 
#endif
}//----------------------------------------------
if(num==3){
#if defined(PE3)
return PE3; 
#endif
}//-----------------------------------------------
if(num==4){
#if defined(PE4)
return PE4; 
#endif
}//-----------------------------------------------
if(num==5){
#if defined(PE5)
return PE5; 
#endif
}//-----------------------------------------------
if(num==6){
#if defined(PE6)
return PE6; 
#endif
}//-----------------------------------------------
if(num==7){
#if defined(PE7)
return PE7; 
#endif
}//----------------------------------------------
if(num==8){
#if defined(PE8)
return PE8;
#endif
}//----------------------------------------------
if(num==9){
#if defined(PE9)
return PE9;
#endif
}//----------------------------------------------
if(num==10){
#if defined(PE10)
return PE10; 
#endif
}//----------------------------------------------
if(num==11){
#if defined(PE11)
return PE11; 
#endif
}//-----------------------------------------------
if(num==12){
#if defined(PE12)
return PE12; 
#endif
}//-----------------------------------------------
if(num==13){
#if defined(PE13)
return PE13; 
#endif
}//-----------------------------------------------
if(num==14){
#if defined(PE14)
return PE14; 
#endif
}//-----------------------------------------------
if(num==15){
#if defined(PE15)
return PE15; 
#endif
}}	//--END PE ---и т.д. 0-15;
//===============================================
if(reg=='F'){
//-----------------------------------------------
if(num==0){
#if defined(PF0)
return PF0;
#endif
}//----------------------------------------------
if(num==1){
#if defined(PF1)
return PF1;
#endif
}//----------------------------------------------
if(num==2){
#if defined(PF2)
return PF2; 
#endif
}//----------------------------------------------
if(num==3){
#if defined(PF3)
return PF3; 
#endif
}//-----------------------------------------------
if(num==4){
#if defined(PF4)
return PF4; 
#endif
}//-----------------------------------------------
if(num==5){
#if defined(PF5)
return PF5; 
#endif
}//-----------------------------------------------
if(num==6){
#if defined(PF6)
return PF6; 
#endif
}//-----------------------------------------------
if(num==7){
#if defined(PF7)
return PF7; 
#endif
}//----------------------------------------------
if(num==8){
#if defined(PF8)
return PF8;
#endif
}//----------------------------------------------
if(num==9){
#if defined(PF9)
return PF9;
#endif
}//----------------------------------------------
if(num==10){
#if defined(PF10)
return PF10; 
#endif
}//----------------------------------------------
if(num==11){
#if defined(PF11)
return PF11; 
#endif
}//-----------------------------------------------
if(num==12){
#if defined(PF12)
return PF12; 
#endif
}//-----------------------------------------------
if(num==13){
#if defined(PF13)
return PF13; 
#endif
}//-----------------------------------------------
if(num==14){
#if defined(PF14)
return PF14; 
#endif
}//-----------------------------------------------
if(num==15){
#if defined(PF15)
return PF15; 
#endif
}}	//--END PF ---и т.д. 0-15;
//===============================================
if(reg=='G'){
//-----------------------------------------------
if(num==0){
#if defined(PG0)
return PG0;
#endif
}//----------------------------------------------
if(num==1){
#if defined(PG1)
return PG1;
#endif
}//----------------------------------------------
if(num==2){
#if defined(PG2)
return PG2; 
#endif
}//----------------------------------------------
if(num==3){
#if defined(PG3)
return PG3; 
#endif
}//-----------------------------------------------
if(num==4){
#if defined(PG4)
return PG4; 
#endif
}//-----------------------------------------------
if(num==5){
#if defined(PG5)
return PG5; 
#endif
}//-----------------------------------------------
if(num==6){
#if defined(PG6)
return PG6; 
#endif
}//-----------------------------------------------
if(num==7){
#if defined(PG7)
return PG7; 
#endif
}//----------------------------------------------
if(num==8){
#if defined(PG8)
return PG8;
#endif
}//----------------------------------------------
if(num==9){
#if defined(PG9)
return PG9;
#endif
}//----------------------------------------------
if(num==10){
#if defined(PG10)
return PG10; 
#endif
}//----------------------------------------------
if(num==11){
#if defined(PG11)
return PG11; 
#endif
}//-----------------------------------------------
if(num==12){
#if defined(PG12)
return PG12; 
#endif
}//-----------------------------------------------
if(num==13){
#if defined(PG13)
return PG13; 
#endif
}//-----------------------------------------------
if(num==14){
#if defined(PG14)
return PG14; 
#endif
}//-----------------------------------------------
if(num==15){
#if defined(PG15)
return PG15; 
#endif
}}	//--END PG ---и т.д. 0-15;
#endif   		//--END #if defined(RT_HW_ARCH_STM32DUINO) 
//================================================
if((reg>'G') || (num>15)) {return 255;}	//--Защита от предупреждений компилятора;
return 255;};	//--END getNumPinSTM32(char reg, uint8_t num)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
