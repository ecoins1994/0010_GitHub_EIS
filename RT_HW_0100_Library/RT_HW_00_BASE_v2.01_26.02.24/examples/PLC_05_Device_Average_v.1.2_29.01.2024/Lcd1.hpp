//=================================================================================================
//                                    1.Lcd1
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_LCD1
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//=================================================================================================
//                     1.1.Объекты и переменные Lcd1.z
//=================================================================================================
RT_HW_LCD44780_DEVICE_ID z1; uint8_t n1; 
RT_HW_LCD44780_PARAM_ID  z1Blink, z1BTN, z1Speed1,z1Speed2, z1Core1;
RT_HW_LCD44780_PARAM_ID  z1ADC;   
RT_HW_LCD44780_PARAM_ID  z1SNS_ok;
RT_HW_LCD44780_PARAM_ID  z1SNS_Temp;   const char z1SNS_hTemp[]  PROGMEM="T=";
RT_HW_LCD44780_PARAM_ID  z1SNS_Hum;    const char z1SNS_hHum[]   PROGMEM="H=";
RT_HW_LCD44780_PARAM_ID  z1DIN;
//=================================================================================================
//                     1.2.Управление Lcd1.z (выполняется по состоянию Button=0)
//=================================================================================================
void Lcd1(){
//--------------------------------------------------------------------------------------
if(z1.custom==0){z1.custom=RT_HW_Base.i2cSetParam(z1.dvI,i2cAdrLcd1,0,400000UL); z1.mi='I'; z1.cols=16; z1.rows=2;} //--Настройка параметров дисплея; 
RT_HW_lcd44780.direct(z1); n1=z1.num;                                                                               //--Управление дисплеем;
//--------------------------------------------------------------------------------------
if(z1Blink.custom==0)   {RT_HW_lcd44780.initBlinkID (z1Blink,   n1,500, 1,1);}            RT_HW_lcd44780.LcdBlink(z1Blink,' ','*');                           //--Мерцающий символ;
if(z1DIN.custom ==0)    {RT_HW_lcd44780.initWordID  (z1DIN,     n1,'H','R','~', 2,1,4);}  RT_HW_lcd44780.LcdVAR  (z1DIN ,                 pinDIN);            //--Дискретные входы;
if(z1Speed1.custom==0)  {RT_HW_lcd44780.initWordID  (z1Speed1,  n1,'U','R','~', 7,1,4);}  RT_HW_lcd44780.LcdVAR  (z1Speed1,               vspeedMCUF0);       //--Быстродействие CORE0;
if(z1Core1.custom==0)   {RT_HW_lcd44780.initBitID   (z1Core1,   n1,            12,1);}    RT_HW_lcd44780.LcdBit  (z1Core1,RT_HW_Base.shed.isLoop1,' ','+');   //--Флаг работы CORE1;
if(z1Speed2.custom==0)  {RT_HW_lcd44780.initWordID  (z1Speed2,  n1,'U','R','~',13,1,4);}  RT_HW_lcd44780.LcdVAR  (z1Speed2,               vspeedMCUF1);       //--Быстродействие CORE1;
if(z1SNS_ok.custom==0)  {RT_HW_lcd44780.initBitID   (z1SNS_ok,  n1,1,2);}                 RT_HW_lcd44780.LcdBit  (z1SNS_ok,               vAHTxx_ok,'-','+'); //--Сенсор AHTxx ok;
if(z1SNS_Temp.custom==0){RT_HW_lcd44780.initFloatID (z1SNS_Temp,n1,'2','L',';', 2,2,8);}  RT_HW_lcd44780.LcdFloat(z1SNS_Temp,z1SNS_hTemp, vAHTxx_Temp);       //--Температура AHTxx;
if(z1SNS_Hum.custom==0) {RT_HW_lcd44780.initFloatID (z1SNS_Hum, n1,'2','L',';',10,2,7);}  RT_HW_lcd44780.LcdFloat(z1SNS_Hum, z1SNS_hHum,  vAHTxx_Hum);        //--Влажность AHTxx;
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void Lcd1(){;};
#endif
//=================================================================================================
