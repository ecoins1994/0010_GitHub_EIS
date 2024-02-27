#ifdef RT_HW_TEST_PERMIT_LCD2_i2c
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//============================Objects and variables Lcd.2===============================
RT_HW_LCD44780_DEVICE_ID z2; uint8_t n2; 
RT_HW_LCD44780_PARAM_ID  z2Blink;
RT_HW_LCD44780_PARAM_ID  z2DsbName, z2DsbOk, z2DsbTemp;           const char z2hDsbName[] PROGMEM="DS";  const char z2hDsbTemp[] PROGMEM="T="; 
RT_HW_LCD44780_PARAM_ID  z2Hour,    z2Min,   z2Sec, z2Year2, z2Month, z2Day;               
RT_HW_LCD44780_PARAM_ID  z2ShtName, z2ShtOk, z2ShtTemp, z2ShtHum; const char z2hShtName[]  PROGMEM="SHT"; const char z2hShtTemp[] PROGMEM="T="; const char z2hShtHum[] PROGMEM="H=";
RT_HW_LCD44780_PARAM_ID  z2MaxName, z2MaxOk, z2MaxTemp;           const char z2hMaxName[]  PROGMEM="M";  const char z2hMaxTemp[] PROGMEM="T=";
RT_HW_LCD44780_PARAM_ID  z2H165,    z2H165var;                    const char z2hH165Name[] PROGMEM="165=";
RT_HW_LCD44780_PARAM_ID  z2Stamp, z2Base, z2Ntp, z2Delta, z2Week;
RT_HW_LCD44780_PARAM_ID  z2IP0,z2IP1,z2IP2,z2IP3,z2NTP,z2SERV;
//======================================================================================
void Lcd2(){
//--------------------------------------------------------------------------------------
if(z2.custom==0){z2.custom=RT_HW_Base.i2cSetParam(z2.dvI,i2cAdrLcd2,0,400000UL); z2.mi='I'; z2.cols=20; z2.rows=4;}  RT_HW_lcd44780.direct(z2); n2=z2.num;
//--------------------------------------------------------------------------------------
if(z2Blink.custom==0)  {RT_HW_lcd44780.initBlinkID(z2Blink,   n2,500, 1,1);}            RT_HW_lcd44780.LcdBlink(z2Blink,' ','*'); //--Мерцание символом;
if(z2Day.custom  ==0)  {RT_HW_lcd44780.initTimeID(z2Day,      n2,        '.', 2,1, 3);} RT_HW_lcd44780.LcdVAR  (z2Day,   RT_HW_Base.unixID.day);
if(z2Month.custom==0)  {RT_HW_lcd44780.initTimeID(z2Month,    n2,        '.', 5,1, 3);} RT_HW_lcd44780.LcdVAR  (z2Month, RT_HW_Base.unixID.month);
if(z2Year2.custom==0)  {RT_HW_lcd44780.initTimeID(z2Year2,    n2,        '~', 8,1, 2);} RT_HW_lcd44780.LcdVAR  (z2Year2, RT_HW_Base.unixID.year2);
if(z2Week.custom ==0)  {RT_HW_lcd44780.initByteID(z2Week,     n2,'U','R','~',19,1, 2);} RT_HW_lcd44780.LcdVAR  (z2Week,  RT_HW_Base.unixID.weekDay);   

if(z2Hour.custom ==0)  {RT_HW_lcd44780.initTimeID(z2Hour,     n2,        ':',11,1, 3);} RT_HW_lcd44780.LcdVAR  (z2Hour,  RT_HW_Base.unixID.hours);
if(z2Min.custom  ==0)  {RT_HW_lcd44780.initTimeID(z2Min,      n2,        ':',14,1, 3);} RT_HW_lcd44780.LcdVAR  (z2Min,   RT_HW_Base.unixID.minutes);
if(z2Sec.custom  ==0)  {RT_HW_lcd44780.initTimeID(z2Sec,      n2,        '~',17,1, 2);} RT_HW_lcd44780.LcdVAR  (z2Sec,   RT_HW_Base.unixID.seconds);

if(z2SERV.custom ==0)  {RT_HW_lcd44780.initByteID(z2SERV,     n2,'U','L','~', 1,2, 3);} RT_HW_lcd44780.LcdVAR  (z2SERV,  ethServerCnt);

if(z2IP0.custom ==0)   {RT_HW_lcd44780.initByteID(z2IP0,      n2,'U','R','.', 6,2, 4);} RT_HW_lcd44780.LcdVAR  (z2IP0,  ethIP[0]);   
if(z2IP1.custom ==0)   {RT_HW_lcd44780.initByteID(z2IP1,      n2,'U','R','.',10,2, 4);} RT_HW_lcd44780.LcdVAR  (z2IP1,  ethIP[1]);
if(z2IP2.custom ==0)   {RT_HW_lcd44780.initByteID(z2IP2,      n2,'U','R','.',14,2, 4);} RT_HW_lcd44780.LcdVAR  (z2IP2,  ethIP[2]);   
if(z2IP3.custom ==0)   {RT_HW_lcd44780.initByteID(z2IP3,      n2,'U','R','~',18,2, 3);} RT_HW_lcd44780.LcdVAR  (z2IP3,  ethIP[3]);

if(z2Base.custom ==0)  {RT_HW_lcd44780.initLongID(z2Base,     n2,'U','L','~', 1,3,10);} RT_HW_lcd44780.LcdVAR  (z2Base,  RT_HW_Base.unixID.timeUNIX);   
if(z2Delta.custom==0)  {RT_HW_lcd44780.initLongID(z2Delta,    n2,'I','R','~',11,3,11);} RT_HW_lcd44780.LcdVAR  (z2Delta,(RT_HW_Base.unixID.timeUNIX-getTimeUnixNTP())); 
if(z2Ntp.custom  ==0)  {RT_HW_lcd44780.initLongID(z2Ntp,      n2,'U','L','~', 1,4,10);} RT_HW_lcd44780.LcdVAR  (z2Ntp,   getTimeUnixNTP()); 

if(z2H165.custom ==0)  {RT_HW_lcd44780.initWordID(z2H165,     n2,'H','L','~',13,4, 0);} RT_HW_lcd44780.LcdVar  (z2H165,  z2hH165Name, v74HC165);
//--------------------------------------------------------------------------------------
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void Lcd2(){;};
#endif
//======================================================================================
