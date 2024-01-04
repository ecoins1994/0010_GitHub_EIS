#ifdef RT_HW_TEST_PERMIT_LCD2_i2c
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
char L2Sign1=' ', L2Sign2='*';
//============================Objects and variables Lcd.2===============================
RT_HW_LCD44780_DEVICE_ID z2; uint8_t n2; 
RT_HW_LCD44780_DEVICE_ID x2; uint8_t m2; 
RT_HW_LCD44780_PARAM_ID  z2Blink;
RT_HW_LCD44780_PARAM_ID  z2Adc0; const char z2hAdc0[]     PROGMEM="A=";
RT_HW_LCD44780_PARAM_ID  z2Adc1; const char z2hAdc1[]     PROGMEM="A1=";
RT_HW_LCD44780_PARAM_ID  z2Adc2; const char z2hAdc2[]     PROGMEM="A2=";
RT_HW_LCD44780_PARAM_ID  z2Adc3; const char z2hAdc3[]     PROGMEM="A3=";
RT_HW_LCD44780_PARAM_ID  z2Adc4; const char z2hAdc4[]     PROGMEM="A4=";
RT_HW_LCD44780_PARAM_ID  z2Adc5; const char z2hAdc5[]     PROGMEM="A5=";
RT_HW_LCD44780_PARAM_ID  z2Adc6; const char z2hAdc6[]     PROGMEM="A6=";
RT_HW_LCD44780_PARAM_ID  z2Adc7; const char z2hAdc7[]     PROGMEM="A7=";
//======================================================================================
void Lcd2z(){
//--------------------------------------------------------------------------------------
if(z2.custom==0){z2.custom=RT_HW_Base.i2cSetParam(z2.dvI,i2cAdrLcd2,0,400000UL); z2.mi='I'; z2.cols=20; z2.rows=4;}  RT_HW_lcd44780.direct(z2); n2=z2.num;
//--------------------------------------------------------------------------------------
if(z2Blink.custom==0) {RT_HW_lcd44780.initBlinkID(z2Blink,   n2,500, 1,1);}                                     RT_HW_lcd44780.LcdBlink(z2Blink,L2Sign1,L2Sign2); //--Мерцающий символ;
//--------------------------------------------------------------------------------------
if(z2Adc0.custom==0)  {RT_HW_lcd44780.initFloatID (z2Adc0,    n2,'3','L',';',  2,1, 9); z2Adc0.periodLimit=20;} RT_HW_lcd44780.LcdFloat(z2Adc0,z2hAdc0,vADC0); //--Adc0 (АЦП);
if(z2Adc1.custom==0)  {RT_HW_lcd44780.initFloatID (z2Adc1,    n2,'3','R',';', 11,1, 0); z2Adc1.periodLimit=20;} RT_HW_lcd44780.LcdFloat(z2Adc1,z2hAdc1,vADC1); //--Adc1 (АЦП);
//--------------------------------------------------------------------------------------
if(z2Adc2.custom==0)  {RT_HW_lcd44780.initFloatID (z2Adc2,    n2,'3','L',';',  1,2,10); z2Adc2.periodLimit=20;} RT_HW_lcd44780.LcdFloat(z2Adc2,z2hAdc2,vADC2); //--Adc2 (АЦП);
if(z2Adc3.custom==0)  {RT_HW_lcd44780.initFloatID (z2Adc3,    n2,'3','R',';', 11,2, 0); z2Adc3.periodLimit=20;} RT_HW_lcd44780.LcdFloat(z2Adc3,z2hAdc3,vADC3); //--Adc3 (АЦП);
//--------------------------------------------------------------------------------------
if(z2Adc4.custom==0)  {RT_HW_lcd44780.initFloatID (z2Adc4,    n2,'3','L',';',  1,3,10); z2Adc4.periodLimit=20;} RT_HW_lcd44780.LcdFloat(z2Adc4,z2hAdc4,vADC4); //--Adc4 (АЦП);
if(z2Adc5.custom==0)  {RT_HW_lcd44780.initFloatID (z2Adc5,    n2,'3','R',';', 11,3, 0); z2Adc5.periodLimit=20;} RT_HW_lcd44780.LcdFloat(z2Adc5,z2hAdc5,vADC5); //--Adc5 (АЦП);
//--------------------------------------------------------------------------------------
if(z2Adc6.custom==0)  {RT_HW_lcd44780.initFloatID (z2Adc6,    n2,'3','L',';',  1,4,10); z2Adc6.periodLimit=20;} RT_HW_lcd44780.LcdFloat(z2Adc6,z2hAdc6,vADC6); //--Adc6 (АЦП);
if(z2Adc7.custom==0)  {RT_HW_lcd44780.initFloatID (z2Adc7,    n2,'3','R',';', 11,4, 0); z2Adc7.periodLimit=20;} RT_HW_lcd44780.LcdFloat(z2Adc7,z2hAdc7,vADC7); //--Adc7 (АЦП);
//--------------------------------------------------------------------------------------
};
//======================================================================================
RT_HW_LCD44780_PARAM_ID  x2Blink;
RT_HW_LCD44780_PARAM_ID  x2Adc01; const char x2hAdc01[]     PROGMEM="01=";
RT_HW_LCD44780_PARAM_ID  x2Adc23; const char x2hAdc23[]     PROGMEM="23=";
RT_HW_LCD44780_PARAM_ID  x2Adc45; const char x2hAdc45[]     PROGMEM="45=";
RT_HW_LCD44780_PARAM_ID  x2Adc67; const char x2hAdc67[]     PROGMEM="67=";
void Lcd2x(){
//--------------------------------------------------------------------------------------
if(x2.custom==0){x2.custom=RT_HW_Base.i2cSetParam(x2.dvI,i2cAdrLcd2,0,400000UL); x2.mi='I'; x2.cols=20; x2.rows=4;}  RT_HW_lcd44780.direct(x2); m2=x2.num;
//--------------------------------------------------------------------------------------
if(x2Blink.custom==0) {RT_HW_lcd44780.initBlinkID (x2Blink, m2,500, 1,1);}                                     RT_HW_lcd44780.LcdBlink(x2Blink,L2Sign1,L2Sign2); //--Мерцающий символ;
//--------------------------------------------------------------------------------------
if(x2Adc01.custom==0)  {RT_HW_lcd44780.initFloatID(x2Adc01, m2,'3','L',';',  1,3,10); x2Adc01.periodLimit=20;} RT_HW_lcd44780.LcdFloat(x2Adc01,x2hAdc01,vADC01); //--Adc01 (АЦП);
if(x2Adc23.custom==0)  {RT_HW_lcd44780.initFloatID(x2Adc23, m2,'3','R',';', 11,3, 0); x2Adc23.periodLimit=20;} RT_HW_lcd44780.LcdFloat(x2Adc23,x2hAdc23,vADC23); //--Adc23(АЦП);
//--------------------------------------------------------------------------------------
if(x2Adc45.custom==0)  {RT_HW_lcd44780.initFloatID(x2Adc45, m2,'3','L',';',  1,4,10); x2Adc45.periodLimit=20;} RT_HW_lcd44780.LcdFloat(x2Adc45,x2hAdc45,vADC45); //--Adc6 (АЦП);
if(x2Adc67.custom==0)  {RT_HW_lcd44780.initFloatID(x2Adc67, m2,'3','R',';', 11,4, 0); x2Adc67.periodLimit=20;} RT_HW_lcd44780.LcdFloat(x2Adc67,x2hAdc67,vADC67); //--Adc7 (АЦП);
//--------------------------------------------------------------------------------------
};
//======================================================================================
//
//======================================================================================
void Lcd2(){
if(vAdcOk){L2Sign2='*';} else {L2Sign2='#';}
z2.extEN=!vChatBut; Lcd2z(); 
x2.extEN= vChatBut; Lcd2x();
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void Lcd2(){;};
#endif
//======================================================================================
