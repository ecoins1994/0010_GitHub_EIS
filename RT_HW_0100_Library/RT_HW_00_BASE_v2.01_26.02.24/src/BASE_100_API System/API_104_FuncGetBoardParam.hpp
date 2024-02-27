//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//				1.ФУНКЦИИ ПОЛУЧЕНИЯ ИМЕНОВАННЫХ ЗНАЧЕНИЙ ИЗ ОПИСАНИЯ ПЛАТ
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
uint8_t  vCanBus(uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_CAN_ID,(0+(num*4)));};
uint8_t  vCanCS (uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_CAN_ID,(1+(num*4)));};	
uint8_t  vCanINT(uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_CAN_ID,(2+(num*4)));};	
uint8_t  vCanRST(uint8_t num=0){return readArrPGM(RT_HW_PGM_PIN_CAN_ID,(3+(num*4)));};	
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