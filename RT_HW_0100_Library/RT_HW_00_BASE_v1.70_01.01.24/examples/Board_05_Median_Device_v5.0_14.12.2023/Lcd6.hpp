#ifdef RT_HW_TEST_PERMIT_LCD6_i2c
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//============================Objects and variables Lcd.2===============================
RT_HW_LCD44780_DEVICE_ID z6; uint8_t n6; 
RT_HW_LCD44780_PARAM_ID  z6Hour,   z6Min,   z6Sec;                const char z6hTime[]     PROGMEM=":";
RT_HW_LCD44780_PARAM_ID  z6Blink,   z6BTN,   z6Speed;
RT_HW_LCD44780_PARAM_ID  z6ADS0,z6ADS1; const char z6hADS0[] PROGMEM="A0="; const char z6hADS1[] PROGMEM="A1=";
RT_HW_LCD44780_PARAM_ID  z6ADS2,z6ADS3; const char z6hADS2[] PROGMEM="A2="; const char z6hADS3[] PROGMEM="A3=";
//RT_HW_LCD44780_PARAM_ID  z2DsbName, z2DsbOk, z2DsbTemp;           const char z2hDsbName[] PROGMEM="DS";  const char z2hDsbTemp[] PROGMEM="T="; 
//RT_HW_LCD44780_PARAM_ID  z2HsrName, z2HsrOk, z2HsrLen;            const char z2hHsrName[] PROGMEM="SR";  const char z2hHsrTemp[] PROGMEM="L="; 
//RT_HW_LCD44780_PARAM_ID  z2DhtName, z2DhtOk, z2DhtTemp, z2DhtHum; const char z2hDhtName[] PROGMEM="DHT"; const char z2hDhtTemp[] PROGMEM="T="; const char z2hDhtHum[] PROGMEM="H=";

//RT_HW_LCD44780_PARAM_ID  z2MaxName, z2MaxOk, z2MaxTemp;           const char z2hMaxName[] PROGMEM="M";  const char z2hMaxTemp[] PROGMEM="T=";
//RT_HW_LCD44780_PARAM_ID  z2maxName, z2maxOk, z2maxTemp;           const char z2hmaxName[] PROGMEM="m";  const char z2hmaxTemp[] PROGMEM="T=";
//RT_HW_LCD44780_PARAM_ID  z2ShtName, z2ShtOk, z2ShtTemp, z2ShtHum; const char z2hShtName[] PROGMEM="SHT"; const char z2hShtTemp[] PROGMEM="T="; const char z2hShtHum[] PROGMEM="H=";
//RT_HW_LCD44780_PARAM_ID  z2Cr1Ok,  z2Cr1Cnt;
//RT_HW_LCD44780_PARAM_ID  z2USBdir,  z2USBcnt;
//======================================================================================
void Lcd6(){
//--------------------------------------------------------------------------------------
if(z6.custom==0){z6.custom=RT_HW_Base.i2cSetParam(z6.dvI,i2cAdrLcd6,0,400000UL); z6.mi='I'; z6.cols=20; z6.rows=4;}  RT_HW_lcd44780.direct(z6); n6=z6.num;
//--------------------------------------------------------------------------------------
if(z6Blink.custom==0)  {RT_HW_lcd44780.initBlinkID(z6Blink,   n6,500, 1,1);}           RT_HW_lcd44780.LcdBlink(z6Blink,' ','*');                   //--Flickering symbol;
//----------------------
if(z6ADS0.custom==0){RT_HW_lcd44780.initFloatID(z6ADS0, n6,'3','L',';',  1,2,10);} RT_HW_lcd44780.LcdFloat(z6ADS0, z6hADS0, vADS1115_A0f); //--Output ADS1115_A0f.Temp;  
if(z6ADS1.custom==0){RT_HW_lcd44780.initFloatID(z6ADS1, n6,'3','L',';', 11,2,10);} RT_HW_lcd44780.LcdFloat(z6ADS1, z6hADS1, vADS1115_A1f); //--Output ADS1115_A1f.Temp;
if(z6ADS2.custom==0){RT_HW_lcd44780.initFloatID(z6ADS2, n6,'3','L',';',  1,3,10);} RT_HW_lcd44780.LcdFloat(z6ADS2, z6hADS2, vADS1115_A2f); //--Output ADS1115_A2f.Temp;  
if(z6ADS3.custom==0){RT_HW_lcd44780.initFloatID(z6ADS3, n6,'3','L',';', 11,3,10);} RT_HW_lcd44780.LcdFloat(z6ADS3, z6hADS3, vADS1115_A3f); //--Output ADS1115_A3f.Temp;
//----------------------
//if(z2DhtName.custom==0){RT_HW_lcd44780.initTextID (z2DhtName, n2,'L',          1,2,3);} RT_HW_lcd44780.LcdText (z2DhtName, z2hDhtName);             //--Output head DHT22;         
//if(z2DhtOk.custom==0)  {RT_HW_lcd44780.initBitID  (z2DhtOk,   n2,              4,2);}   RT_HW_lcd44780.LcdBit  (z2DhtOk,               vDHT22ok);   //--Output HC-SR04.ok;
//if(z2DhtTemp.custom==0){RT_HW_lcd44780.initFloatID(z2DhtTemp, n2,'2','L',';',  5,2,8);} RT_HW_lcd44780.LcdFloat(z2DhtTemp, z2hDhtTemp, vDHT22Temp); //--Output DHT22.Temp;        
//if(z2DhtHum.custom==0) {RT_HW_lcd44780.initFloatID(z2DhtHum,  n2,'2','L',';', 13,2,8);} RT_HW_lcd44780.LcdFloat(z2DhtHum,  z2hDhtHum,  vDHT22Hum);  //--Output DHT22.Hum;
//----------------------
//if(z2ShtName.custom==0){RT_HW_lcd44780.initTextID (z2ShtName, n2,'L',          1,3,3);} RT_HW_lcd44780.LcdText (z2ShtName, z2hShtName);             //--Output head DHT22;         
//if(z2ShtOk.custom==0)  {RT_HW_lcd44780.initBitID  (z2ShtOk,   n2,              4,3);}   RT_HW_lcd44780.LcdBit  (z2ShtOk,               vSHT3x_ok);   //--Output HC-SR04.ok;
//if(z2ShtTemp.custom==0){RT_HW_lcd44780.initFloatID(z2ShtTemp, n2,'2','L',';',  5,3,8);} RT_HW_lcd44780.LcdFloat(z2ShtTemp, z2hShtTemp, vSHT3x_Temp); //--Output DHT22.Temp;        
//if(z2ShtHum.custom==0) {RT_HW_lcd44780.initFloatID(z2ShtHum,  n2,'2','L',';', 13,3,8);} RT_HW_lcd44780.LcdFloat(z2ShtHum,  z2hShtHum,  vSHT3x_Hum);  //--Output DHT22.Hum;
//----------------------
//if(z2MaxName.custom==0){RT_HW_lcd44780.initTextID (z2MaxName, n2,'L',          1,4,1);} RT_HW_lcd44780.LcdText (z2MaxName, z2hMaxName);                 //--Output head MAX6675;         
//if(z2MaxOk.custom==0)  {RT_HW_lcd44780.initBitID  (z2MaxOk,   n2,              2,4);}   RT_HW_lcd44780.LcdBit  (z2MaxOk,               vMAX6675ok);     //--Output MAX6675.ok;
//if(z2MaxTemp.custom==0){RT_HW_lcd44780.initFloatID(z2MaxTemp, n2,'2','L',';',  3,4,8);} RT_HW_lcd44780.LcdFloat(z2MaxTemp, z2hMaxTemp, vMAX6675Temp);   //--Output MAX6675.Temp;  
//if(z2maxName.custom==0){RT_HW_lcd44780.initTextID (z2maxName, n2,'L',         11,4,1);} RT_HW_lcd44780.LcdText (z2maxName, z2hmaxName);                 //--Output head MAX6675;         
//if(z2maxOk.custom==0)  {RT_HW_lcd44780.initBitID  (z2maxOk,   n2,             12,4);}   RT_HW_lcd44780.LcdBit  (z2maxOk,               vMAX6675Nok);  //--Output MAX6675.ok;
//if(z2maxTemp.custom==0){RT_HW_lcd44780.initFloatID(z2maxTemp, n2,'2','L',';', 13,4,8);} RT_HW_lcd44780.LcdFloat(z2maxTemp, z2hmaxTemp, vMAX6675NTemp);//--Output MAX6675.Temp;

//if(z2Cr1Ok.custom==0)  {RT_HW_lcd44780.initBitID(z2Cr1Ok,     n2,            11,4);}    RT_HW_lcd44780.LcdBit  (z2Cr1Ok,  vcoreOk);     
//if(z2Cr1Cnt.custom==0) {RT_HW_lcd44780.initByteID(z2Cr1Cnt,  n2,'U','L','~',12,4,2);}   RT_HW_lcd44780.LcdVAR  (z2Cr1Cnt, vcoreCnt);
//if(z2Speed.custom==0)  {RT_HW_lcd44780.initWordID(z2Speed,   n2,'U','R','~',18,4,3);}   RT_HW_lcd44780.LcdVAR  (z2Speed,  vspeedSmall);        //--Speed/1000  output;
//--------------------------------------------------------------------------------------
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void Lcd6(){;};
#endif
