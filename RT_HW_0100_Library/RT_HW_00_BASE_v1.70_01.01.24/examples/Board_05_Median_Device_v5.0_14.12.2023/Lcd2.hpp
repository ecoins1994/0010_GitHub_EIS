#ifdef RT_HW_TEST_PERMIT_LCD2_i2c
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//============================Objects and variables Lcd.2===============================
RT_HW_LCD44780_DEVICE_ID z2; uint8_t n2; 
RT_HW_LCD44780_PARAM_ID  z2Blink;
RT_HW_LCD44780_PARAM_ID  z2DsbName, z2DsbOk, z2DsbTemp;           const char z2hDsbName[] PROGMEM="DS";  const char z2hDsbTemp[] PROGMEM="T="; 
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
if(z2DsbName.custom==0){RT_HW_lcd44780.initTextID (z2DsbName, n2,'L',         2,1,2);} RT_HW_lcd44780.LcdText (z2DsbName, z2hDsbName);             //--Output head DS1820;
if(z2DsbOk.custom==0)  {RT_HW_lcd44780.initBitID  (z2DsbOk,   n2,             4,1);}   RT_HW_lcd44780.LcdBit  (z2DsbOk,               vDS1820ok);  //--Output vDS1820ok;
if(z2DsbTemp.custom==0){RT_HW_lcd44780.initFloatID(z2DsbTemp, n2,'2','L',';', 5,1,8);} RT_HW_lcd44780.LcdFloat(z2DsbTemp, z2hDsbTemp, vDS1820Temp);//--Output vDS1820Temp;
//----------------------
if(z2Hour.custom==0)    {RT_HW_lcd44780.initByteID(z2Hour,    n2,'U','L','~',13,1,3);} RT_HW_lcd44780.LcdVAR  (z2Hour,        timeHour);
if(z2Min.custom==0)     {RT_HW_lcd44780.initByteID(z2Min,     n2,'U','L','~',15,1,3);} RT_HW_lcd44780.LcdVar  (z2Min, z2hTime,timeMin);
if(z2Sec.custom==0)     {RT_HW_lcd44780.initByteID(z2Sec,     n2,'U','L','~',18,1,3);} RT_HW_lcd44780.LcdVar  (z2Sec, z2hTime,timeSec);
//----------------------
if(z2ShtName.custom==0){RT_HW_lcd44780.initTextID (z2ShtName, n2,'L',          1,2,3);} RT_HW_lcd44780.LcdText (z2ShtName, z2hShtName);             //--Output head DHT22;         
if(z2ShtOk.custom==0)  {RT_HW_lcd44780.initBitID  (z2ShtOk,   n2,              4,2);}   RT_HW_lcd44780.LcdBit  (z2ShtOk,               vSHT3x_ok);   //--Output HC-SR04.ok;
if(z2ShtTemp.custom==0){RT_HW_lcd44780.initFloatID(z2ShtTemp, n2,'2','L',';',  5,2,8);} RT_HW_lcd44780.LcdFloat(z2ShtTemp, z2hShtTemp, vSHT3x_Temp); //--Output DHT22.Temp;        
if(z2ShtHum.custom==0) {RT_HW_lcd44780.initFloatID(z2ShtHum,  n2,'2','L',';', 13,2,8);} RT_HW_lcd44780.LcdFloat(z2ShtHum,  z2hShtHum,  vSHT3x_Hum);  //--Output DHT22.Hum;
//----------------------
if(z2MaxName.custom==0){RT_HW_lcd44780.initTextID (z2MaxName, n2,'L',          1,3,1);} RT_HW_lcd44780.LcdText (z2MaxName, z2hMaxName);                 //--Output head MAX6675;         
if(z2MaxOk.custom==0)  {RT_HW_lcd44780.initBitID  (z2MaxOk,   n2,              2,3);}   RT_HW_lcd44780.LcdBit  (z2MaxOk,               vMAX6675ok);     //--Output MAX6675.ok;
if(z2MaxTemp.custom==0){RT_HW_lcd44780.initFloatID(z2MaxTemp, n2,'2','L',';',  3,3,8);} RT_HW_lcd44780.LcdFloat(z2MaxTemp, z2hMaxTemp, vMAX6675Temp);   //--Output MAX6675.Temp;  
//---------------------
if(z2H165.custom==0)  {RT_HW_lcd44780.initWordID(z2H165,      n2,'H','L','~', 13,3,0);} RT_HW_lcd44780.LcdVar  (z2H165,    z2hH165Name, v74HC165);        //--Speed/1000  output;

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

//
//RT_HW_LCD44780_PARAM_ID  z2Blink,   z2BTN,   z2Speed;
//RT_HW_LCD44780_PARAM_ID  z2maxName, z2maxOk, z2maxTemp;           const char z2hmaxName[] PROGMEM="m";  const char z2hmaxTemp[] PROGMEM="T=";

//RT_HW_LCD44780_PARAM_ID  z2HsrName, z2HsrOk, z2HsrLen;            const char z2hHsrName[] PROGMEM="SR";  const char z2hHsrTemp[] PROGMEM="L="; 
//RT_HW_LCD44780_PARAM_ID  z2DhtName, z2DhtOk, z2DhtTemp, z2DhtHum; const char z2hDhtName[] PROGMEM="DHT"; const char z2hDhtTemp[] PROGMEM="T="; const char z2hDhtHum[] PROGMEM="H=";
//RT_HW_LCD44780_PARAM_ID  z2Cr1Ok,  z2Cr1Cnt;
//RT_HW_LCD44780_PARAM_ID  z2USBdir,  z2USBcnt;
//----------------------
//if(z2HsrName.custom==0){RT_HW_lcd44780.initTextID (z2HsrName, n2,'L',         13,1,2);} RT_HW_lcd44780.LcdText (z2HsrName, z2hHsrName);             //--Output head HC-SR04;         
//if(z2HsrOk.custom==0)  {RT_HW_lcd44780.initBitID  (z2HsrOk,   n2,             15,1);}   RT_HW_lcd44780.LcdBit  (z2HsrOk,               vSR04ok);    //--Output HC-SR04.ok;
//if(z2HsrLen.custom==0) {RT_HW_lcd44780.initWordID (z2HsrLen,  n2,'U','L',';', 16,1,5);} RT_HW_lcd44780.LcdVar  (z2HsrLen,  z2hHsrTemp, vSR04Len);   //--Output HC-SR04.Len;

//----------------------
//if(z2DhtName.custom==0){RT_HW_lcd44780.initTextID (z2DhtName, n2,'L',          1,2,3);} RT_HW_lcd44780.LcdText (z2DhtName, z2hDhtName);             //--Output head DHT22;         
//if(z2DhtOk.custom==0)  {RT_HW_lcd44780.initBitID  (z2DhtOk,   n2,              4,2);}   RT_HW_lcd44780.LcdBit  (z2DhtOk,               vDHT22ok);   //--Output HC-SR04.ok;
//if(z2DhtTemp.custom==0){RT_HW_lcd44780.initFloatID(z2DhtTemp, n2,'2','L',';',  5,2,8);} RT_HW_lcd44780.LcdFloat(z2DhtTemp, z2hDhtTemp, vDHT22Temp); //--Output DHT22.Temp;        
//if(z2DhtHum.custom==0) {RT_HW_lcd44780.initFloatID(z2DhtHum,  n2,'2','L',';', 13,2,8);} RT_HW_lcd44780.LcdFloat(z2DhtHum,  z2hDhtHum,  vDHT22Hum);  //--Output DHT22.Hum;
