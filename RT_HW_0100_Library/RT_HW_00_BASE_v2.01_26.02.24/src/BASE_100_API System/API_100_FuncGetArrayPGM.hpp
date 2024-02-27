//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//				1.ФУНКЦИИ ДЛЯ РАБОТЫ МАССИВАМИ PGM БИБЛИОТЕКИ RT_HW_BASE.h(kind - тип массива)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//			   			1.1.Получение 3-x символьного имени массива
//=================================================================================================	
String getNameKindPin(uint8_t kind){
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_ALL_ID) {return String(F("ALL"));}	
if(kind==RT_HW_PGM_PIN_DIN_ID) {return String(F("DIN"));}
if(kind==RT_HW_PGM_PIN_ADC_ID) {return String(F("ADC"));}
if(kind==RT_HW_PGM_PIN_TCH_ID) {return String(F("TCH"));}	
if(kind==RT_HW_PGM_PIN_DOT_ID) {return String(F("DOT"));}
if(kind==RT_HW_PGM_PIN_PWM_ID) {return String(F("PWM"));}
if(kind==RT_HW_PGM_PIN_DAC_ID) {return String(F("DAC"));}
if(kind==RT_HW_PGM_PIN_INT_ID) {return String(F("INT"));} 
if(kind==RT_HW_PGM_PIN_N5V_ID) {return String(F("N5V"));}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_UHS_ID) {return String(F("UHS"));}	
if(kind==RT_HW_PGM_PIN_USS_ID) {return String(F("USS"));}	
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_I2C_ID) {return String(F("I2C"));}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_SPI_ID) {return String(F("SPI"));}
if(kind==RT_HW_PGM_PIN_SPF_ID) {return String(F("SPF"));}
if(kind==RT_HW_PGM_PIN_SDC_ID) {return String(F("SDC"));}
if(kind==RT_HW_PGM_PIN_SPN_ID) {return String(F("SPN"));}	
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_ETH_ID) {return String(F("ETH"));}
if(kind==RT_HW_PGM_PIN_CAN_ID) {return String(F("CAN"));}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_BRD_ID) {return String(F("BRD"));}	
if(kind==RT_HW_PGM_PIN_CSX_ID) {return String(F("CSX"));}
//-------------------------------------------------------------------------------------------------	
if(kind==RT_HW_PGM_PIN_LC4_ID) {return String(F("LC4"));}	
if(kind==RT_HW_PGM_PIN_LC6_ID) {return String(F("LC6"));}	
if(kind==RT_HW_PGM_PIN_TFT_ID) {return String(F("TFT"));}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_TST_DIS_ID) {return String(F("DIS"));}	
if(kind==RT_HW_PGM_TST_ANL_ID) {return String(F("ANL"));}	
if(kind==RT_HW_PGM_TST_SRV_ID) {return String(F("SRV"));}
if(kind==RT_HW_PGM_TST_DEV_ID) {return String(F("DEV"));}
if(kind==RT_HW_PGM_TST_URT_ID) {return String(F("URT"));}
//-------------------------------------------------------------------------------------------------
return String(F(" - "));  };
//=================================================================================================
//			   			1.2.Получение значения из массива по типу и индексу
//=================================================================================================	
uint8_t  getFromArrPGM (uint8_t kind, uint8_t n){
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_ALL_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_ALL,n);}
if(kind==RT_HW_PGM_PIN_DIN_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_DIN,n);}
if(kind==RT_HW_PGM_PIN_ADC_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_ADC,n);}
if(kind==RT_HW_PGM_PIN_TCH_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_TCH,n);}
if(kind==RT_HW_PGM_PIN_DOT_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_DOT,n);}
if(kind==RT_HW_PGM_PIN_PWM_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_PWM,n);}
if(kind==RT_HW_PGM_PIN_DAC_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_DAC,n);}
if(kind==RT_HW_PGM_PIN_INT_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_INT,n);}
if(kind==RT_HW_PGM_PIN_N5V_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_N5V,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_UHS_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_UHS,n);}
if(kind==RT_HW_PGM_PIN_USS_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_USS,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_I2C_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_I2C,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_SPI_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_SPI,n);}
if(kind==RT_HW_PGM_PIN_SPF_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_SPF,n);}
if(kind==RT_HW_PGM_PIN_SDC_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_SDC,n);}
if(kind==RT_HW_PGM_PIN_SPN_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_SPN,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_ETH_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_ETH,n);}
if(kind==RT_HW_PGM_PIN_CAN_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_CAN,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_BRD_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_BRD,n);}
if(kind==RT_HW_PGM_PIN_CSX_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_CSX,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_LC4_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_LC4,n);}
if(kind==RT_HW_PGM_PIN_LC6_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_LC6,n);}
if(kind==RT_HW_PGM_PIN_TFT_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_TFT,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_TST_DIS_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_TST_DIS,n);}
if(kind==RT_HW_PGM_TST_ANL_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_TST_ANL,n);}
if(kind==RT_HW_PGM_TST_SRV_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_TST_SRV,n);}
if(kind==RT_HW_PGM_TST_DEV_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_TST_DEV,n);}
if(kind==RT_HW_PGM_TST_URT_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_TST_URT,n);}
//-------------------------------------------------------------------------------------------------
return 0;}	

//=================================================================================================
//			   			1.3.Получение значения из массива по типу и индексу с контролем размера массива. 
// Если =254, это окончание массива.
// Если элемент не найден, возвращаетcя 255.
//=================================================================================================	
uint8_t readArrPGM(uint8_t kind, uint8_t n){
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t  i, bf8;
#endif
//-------------------------------------------------------------------------------------------------
bf8=0;
for(i=0; i<254; i++){if(getFromArrPGM(kind,i)==RT_HW_PGM_END){break;} bf8++;} ;
if(n>=bf8) {return 255;} 
return getFromArrPGM(kind,n);};
//=================================================================================================
//						1.4.Проверяет наличие в массиве пина равным n
//=================================================================================================
bool checkPinPGM(uint8_t kind, uint8_t n){
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t  i, bf8;
#endif
//-------------------------------------------------------------------------------------------------
for(i=0; i<254; i++){bf8=getFromArrPGM(kind,i); if(bf8==RT_HW_PGM_END) {return  0;} if((bf8!=255)&&(bf8==n)){return 1;}} 
return 0;};
//=================================================================================================
//						1.5.Возвращает полный размер массива
//=================================================================================================
uint8_t getLenFullPGM (uint8_t kind){uint8_t cnt=0;
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t  i, bf8;
#endif
//-------------------------------------------------------------------------------------------------
for(i=0; i<254; i++){bf8=getFromArrPGM(kind,i); if(bf8==RT_HW_PGM_END){break;}                  cnt++;} return cnt;};
//=================================================================================================
//						1.6.Возвращает кол-во допустимых элементов (!=255) в массиве
//=================================================================================================
uint8_t getLenPosPGM  (uint8_t kind){uint8_t cnt=0;	
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t  i, bf8;
#endif
//-------------------------------------------------------------------------------------------------
for(i=0; i<254; i++){bf8=getFromArrPGM(kind,i); if(bf8==RT_HW_PGM_END){break;}     if(bf8!=255) {cnt++;}} return cnt;};	
//==================================================================================================

/*
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//				3.ФУНКЦИИ ПОЛУЧЕНИЯ ИМЕНОВАННЫХ ЗНАЧЕНИЙ ИЗ ОПИСАНИЯ ПЛАТ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint8_t  vPinControl()	{return readArrPGM(RT_HW_PGM_PIN_BRD_ID,0);};	
uint8_t  vPinLed() 	    {return readArrPGM(RT_HW_PGM_PIN_BRD_ID,1);};
uint8_t  vPinButton()	{return readArrPGM(RT_HW_PGM_PIN_BRD_ID,2);};
uint8_t  vPinADC()   	{return readArrPGM(RT_HW_PGM_PIN_BRD_ID,3);};	
uint8_t  vPinPWM()   	{return readArrPGM(RT_HW_PGM_PIN_BRD_ID,4);};
uint8_t  vPinDebug() 	{return readArrPGM(RT_HW_PGM_PIN_BRD_ID,5);};
uint8_t  vPinWS2812() 	{return readArrPGM(RT_HW_PGM_PIN_BRD_ID,6);};
//-------------------------------------------------------------------------------------------------
uint8_t  vSpiCS0()  	{return readArrPGM(RT_HW_PGM_PIN_CSX_ID,0);};	
uint8_t  vSpiCS1() 		{return readArrPGM(RT_HW_PGM_PIN_CSX_ID,1);};	
uint8_t  vSpiCS2()   	{return readArrPGM(RT_HW_PGM_PIN_CSX_ID,2);};	
uint8_t  vSpiCS3()   	{return readArrPGM(RT_HW_PGM_PIN_CSX_ID,3);};	
uint8_t  vSpiCS4()   	{return readArrPGM(RT_HW_PGM_PIN_CSX_ID,4);};	
uint8_t  vSpiCS5()   	{return readArrPGM(RT_HW_PGM_PIN_CSX_ID,5);};
uint8_t  vSpiCS6()   	{return readArrPGM(RT_HW_PGM_PIN_CSX_ID,6);};	
uint8_t  vSpiCS7()   	{return readArrPGM(RT_HW_PGM_PIN_CSX_ID,7);};
//-------------------------------------------------------------------------------------------------
uint8_t  vTftBus(uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_TFT_ID,(0+(num*4)));};	
uint8_t  vTftCS (uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_TFT_ID,(1+(num*4)));};	
uint8_t  vTftDC (uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_TFT_ID,(2+(num*4)));};	
uint8_t  vTftLED(uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_TFT_ID,(3+(num*4)));};	
//-------------------------------------------------------------------------------------------------
uint8_t  vEthBus(uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_ETH_ID,(0+(num*4)));};
uint8_t  vEthCS (uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_ETH_ID,(1+(num*4)));};	
uint8_t  vEthINT(uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_ETH_ID,(2+(num*4)));};	
uint8_t  vEthRST(uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_ETH_ID,(3+(num*4)));};	
//-------------------------------------------------------------------------------------------------
uint8_t  vCanBus(uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_CAN_ID,(0+(num*2)));};
uint8_t  vCanCS (uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_CAN_ID,(1+(num*2)));};	
//-------------------------------------------------------------------------------------------------
uint8_t  vPinADC1()    {return readArrPGM(RT_HW_PGM_TST_ANL_ID,0);};	
uint8_t  vPinPWM1()    {return readArrPGM(RT_HW_PGM_TST_ANL_ID,1);};
//-------------------------------------------------------------------------------------------------
uint8_t  vPinServo1()  {return readArrPGM(RT_HW_PGM_TST_SRV_ID,0);};
uint8_t  vPinServo2()  {return readArrPGM(RT_HW_PGM_TST_SRV_ID,1);};
//-------------------------------------------------------------------------------------------------
uint8_t  vPinOneWire() {return readArrPGM(RT_HW_PGM_TST_DEV_ID,0);};	
uint8_t  vPinDHT22()   {return readArrPGM(RT_HW_PGM_TST_DEV_ID,1);};	
uint8_t  vPinSR04()    {return readArrPGM(RT_HW_PGM_TST_DEV_ID,2);};
//-------------------------------------------------------------------------------------------------
uint8_t  vUartConsole(){return readArrPGM(RT_HW_PGM_TST_URT_ID,0);};
uint8_t  vUartModBus1(){return readArrPGM(RT_HW_PGM_TST_URT_ID,1);};
uint8_t  vUartModBus2(){return readArrPGM(RT_HW_PGM_TST_URT_ID,2);};
uint8_t  vUartNextion(){return readArrPGM(RT_HW_PGM_TST_URT_ID,3);};
uint8_t  vUartWiFi()   {return readArrPGM(RT_HW_PGM_TST_URT_ID,4);};
uint8_t  vUartNum5()   {return readArrPGM(RT_HW_PGM_TST_URT_ID,5);};
uint8_t  vUartNum6()   {return readArrPGM(RT_HW_PGM_TST_URT_ID,6);};
uint8_t  vUartNum7()   {return readArrPGM(RT_HW_PGM_TST_URT_ID,7);};
//==================================================================================================
*/