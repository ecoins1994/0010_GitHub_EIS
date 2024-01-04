#ifdef RT_HW_TEST_PERMIT_LCD2_i2c
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//============================Objects and variables Lcd.2===============================
RT_HW_LCD44780_DEVICE_ID z2; uint8_t n2; 
RT_HW_LCD44780_PARAM_ID  z2Blink;
RT_HW_LCD44780_PARAM_ID  z2Hour,   z2Min,   z2Sec;                const char z2hTime[]     PROGMEM=":";
RT_HW_LCD44780_PARAM_ID  z2ShtName, z2ShtOk, z2ShtTemp, z2ShtHum; const char z2hShtName[]  PROGMEM="SHT"; const char z2hShtTemp[] PROGMEM="T="; const char z2hShtHum[] PROGMEM="H=";
RT_HW_LCD44780_PARAM_ID  z2MaxName, z2MaxOk, z2MaxTemp;           const char z2hMaxName[]  PROGMEM="M";  const char z2hMaxTemp[] PROGMEM="T=";
RT_HW_LCD44780_PARAM_ID  z2H165,    z2H165var;                    const char z2hH165Name[] PROGMEM="165=";
//======================================================================================
void Lcd2(){
//z2HsrLen.modeBlink=vChatBut;
//--------------------------------------------------------------------------------------
if(z2.custom==0){z2.custom=RT_HW_Base.i2cSetParam(z2.dvI,i2cAdrLcd2,0,400000UL); z2.mi='I'; z2.cols=20; z2.rows=4;}  RT_HW_lcd44780.direct(z2); n2=z2.num;
//if(z2.custom==0){RT_HW_lcd44780.setParamI(z2,i2cAdrLcd2,0,400000UL); z2.cols=20; z2.rows=4;}  RT_HW_lcd44780.direct(z2); n2=z2.num;
//--------------------------------------------------------------------------------------
if(z2Blink.custom==0)  {RT_HW_lcd44780.initBlinkID(z2Blink,   n2,500, 1,1);}           RT_HW_lcd44780.LcdBlink(z2Blink,' ','*');                   //--Flickering symbol;
//----------------------
if(z2Hour.custom==0)    {RT_HW_lcd44780.initByteID(z2Hour,    n2,'U','L','~',13,1,3);} RT_HW_lcd44780.LcdVAR  (z2Hour,        timeHour);
if(z2Min.custom==0)     {RT_HW_lcd44780.initByteID(z2Min,     n2,'U','L','~',15,1,3);} RT_HW_lcd44780.LcdVar  (z2Min, z2hTime,timeMin);
if(z2Sec.custom==0)     {RT_HW_lcd44780.initByteID(z2Sec,     n2,'U','L','~',18,1,3);} RT_HW_lcd44780.LcdVar  (z2Sec, z2hTime,timeSec);
//---------------------
if(z2H165.custom==0)  {RT_HW_lcd44780.initByteID(z2H165,      n2,'#','L','~', 13,3,0);} RT_HW_lcd44780.LcdVAR  (z2H165, (uint8_t)v74HC165);        //--74HC165;

//if(z2Cr1Ok.custom==0)  {RT_HW_lcd44780.initBitID(z2Cr1Ok,     n2,            11,4);}    RT_HW_lcd44780.LcdBit  (z2Cr1Ok,  vcoreOk);     
//if(z2Cr1Cnt.custom==0) {RT_HW_lcd44780.initByteID(z2Cr1Cnt,  n2,'U','L','~',12,4,2);}   RT_HW_lcd44780.LcdVAR  (z2Cr1Cnt, vcoreCnt);
//if(z2Speed.custom==0)  {RT_HW_lcd44780.initWordID(z2Speed,   n2,'U','R','~',18,4,3);}   RT_HW_lcd44780.LcdVAR  (z2Speed,  vspeedSmall);        //--Speed/1000  output;
//--------------------------------------------------------------------------------------
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void Lcd2(){;};
#endif
//======================================================================================
