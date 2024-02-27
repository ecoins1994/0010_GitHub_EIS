#ifdef RT_HW_TEST_PERMIT_LCD1_i2c
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//============================Objects and variables Lcd.1===============================
RT_HW_LCD44780_DEVICE_ID z1; uint8_t n1; 
RT_HW_LCD44780_PARAM_ID  z1Blink, z1BTN, z1AHTok,z1Speed1,z1Speed2, z1Core1, z1CrGn1;
RT_HW_LCD44780_PARAM_ID  z1ADC,   z1Press;  const char z1hADC[]   PROGMEM="a=";   const char z1hPress[] PROGMEM="P=";
RT_HW_LCD44780_PARAM_ID  z1Temp,  z1Hum;    const char z1hTemp[]  PROGMEM="T=";   const char z1hHum[]   PROGMEM="H=";
//======================================================================================
void Lcd1(){
//--------------------------------------------------------------------------------------
if(z1.custom==0){z1.custom=RT_HW_Base.i2cSetParam(z1.dvI,i2cAdrLcd1,0,400000UL); z1.mi='I'; z1.cols=16; z1.rows=2;}  RT_HW_lcd44780.direct(z1); n1=z1.num;
//--------------------------------------------------------------------------------------
if(z1Blink.custom==0){RT_HW_lcd44780.initBlinkID (z1Blink, n1,500, 1,1);}           RT_HW_lcd44780.LcdBlink(z1Blink,       ' ','*');      //--Мерцающий символ;
if(z1BTN.custom==0)  {RT_HW_lcd44780.initBitID   (z1BTN,   n1,6,1);}                RT_HW_lcd44780.LcdBit  (z1BTN,vChatBut,'-','+');      //--Флаг работы CORE1;
//--------------------------------------------------------------------------------------
if(z1ADC.custom==0)  {RT_HW_lcd44780.initWordID  (z1ADC,   n1,'U','L',';', 2,1,4); z1ADC.periodLimit=20;} RT_HW_lcd44780.LcdVAR(z1ADC,vADCF); //--ADC (АЦП);
if(z1Speed1.custom==0){RT_HW_lcd44780.initWordID (z1Speed1,n1,'U','R','~',11,1,0);} RT_HW_lcd44780.LcdVAR  (z1Speed1,vSpeedMCUF);         //--Speed  CORE0;
//--------------------------------------------------------------------------------------
if(z1AHTok.custom==0){RT_HW_lcd44780.initBitID   (z1AHTok, n1,1,2);}                RT_HW_lcd44780.LcdBit  (z1AHTok,vAHTxx_ok,'-','+');   //--Сенсор AHTxx ok;
if(z1Temp.custom==0) {RT_HW_lcd44780.initFloatID (z1Temp,  n1,'2','L',';', 2,2,8);} RT_HW_lcd44780.LcdFloat(z1Temp,z1hTemp,vAHTxx_Temp);  //--Температура AHTxx;
if(z1Hum.custom==0)  {RT_HW_lcd44780.initFloatID (z1Hum,   n1,'2','L',';',10,2,7);} RT_HW_lcd44780.LcdFloat(z1Hum, z1hHum, vAHTxx_Hum);   //--Влажность AHTxx;
//--------------------------------------------------------------------------------------
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void Lcd1(){;};
#endif
//======================================================================================
