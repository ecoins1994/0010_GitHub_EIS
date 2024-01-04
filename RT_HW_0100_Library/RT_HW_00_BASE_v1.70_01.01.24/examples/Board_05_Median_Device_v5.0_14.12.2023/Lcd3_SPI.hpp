#ifdef RT_HW_TEST_PERMIT_LCD3_SPI
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//============================Objects and variables Lcd.3=================================
RT_HW_LCD44780_DEVICE_ID z3; uint8_t n3; 
RT_HW_LCD44780_PARAM_ID  z3Blink, z3Speed, z3Cr1Speed ; 
RT_HW_LCD44780_PARAM_ID  z3AdsOk,z3AdsA0,z3AdsA1,z3AdsA2,z3AdsA3;
RT_HW_LCD44780_PARAM_ID  z3PCF8575ok,z3PCF8575A,z3PCF8575B;
RT_HW_LCD44780_PARAM_ID  z3coreOk, z3coreCnt;
//RT_HW_LCD44780_PARAM_ID  z3USBdir, z3USBcnt;
//RT_HW_LCD44780_PARAM_ID  z3DhtTxt, z3DhtOk, z3DhtTemp,z3DhtHum;   const char z3hDhtTxt[] PROGMEM="DHT="; const char z3hDhtTemp[] PROGMEM="T="; const char z3hDhtHum[]   PROGMEM="H=";
//RT_HW_LCD44780_PARAM_ID  z3HtuTxt, z3HtuOk, z3HtuTemp,z3HtuHum;   const char z3hHtuTxt[] PROGMEM="HTU="; const char z3hHtuTemp[] PROGMEM="T="; const char z3hHtuHum[]   PROGMEM="H=";
//RT_HW_LCD44780_PARAM_ID  z3ShtTxt, z3ShtOk, z3ShtTemp,z3ShtHum;   const char z3hShtTxt[] PROGMEM="SHT="; const char z3hShtTemp[] PROGMEM="T="; const char z3hShtHum[]   PROGMEM="H=";


RT_HW_LCD44780_PARAM_ID  z3NXSL1, z3NXSL2,  z3NXBTN, z3NXPage;    const char z3hNXSL1[]  PROGMEM="s1=";  const char z3hNXSL2[]   PROGMEM="s2=";
RT_HW_LCD44780_PARAM_ID  z3MBSL1, z3MBSL2,  z3MBBTN;              const char z3hMBSL1[]  PROGMEM="S1=";  const char z3hMBSL2[]   PROGMEM="S2=";
RT_HW_LCD44780_PARAM_ID  z3ByteBit1, z3ByteBit2, z3HC165S, z3HC165N; 
//======================================================================================
void Lcd3_SPI(){
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
if(z3.custom==0){z3.custom=RT_HW_Base.spiSetParam(z3.dvS,csLcdSPI,0,0); z3.mi='S'; z3.cols=20; z3.rows=4;}  RT_HW_lcd44780.direct(z3); n3=z3.num;
//--------------------------------------------------------------------------------------
  if(z3Blink.custom==0)   {RT_HW_lcd44780.initBlinkID(z3Blink,   n3,500, 1,1);}             RT_HW_lcd44780.LcdBlink(z3Blink,' ','*');                   //--Output blink char;
  if(z3Speed.custom==0)   {RT_HW_lcd44780.initWordID (z3Speed,   n3,'U','R','~',15,1,0);}   RT_HW_lcd44780.LcdVAR  (z3Speed,   vSpeedMCUF);             //--Speed.filter output;
  if(z3Cr1Speed.custom==0){RT_HW_lcd44780.initWordID (z3Cr1Speed,n3,'U','R','~',15,2,0);}   RT_HW_lcd44780.LcdVAR  (z3Cr1Speed,vspeedMCUF);          //--Speed.filter output;
//--------------------------------------------------------------------------------------
  if(z3AdsA0.custom==0)   {RT_HW_lcd44780.initFloatID(z3AdsA0,   n3,'3','L',';', 2,1,6);}   RT_HW_lcd44780.LcdFLOAT(z3AdsA0, vADS1115_A0f);              //--Output ADS1115_A0f;
  if(z3AdsA1.custom==0)   {RT_HW_lcd44780.initFloatID(z3AdsA1,   n3,'3','L',';', 9,1,6);}   RT_HW_lcd44780.LcdFLOAT(z3AdsA1, vADS1115_A1f);              //--Output ADS1115_A1f;  
  if(z3AdsOk.custom==0)   {RT_HW_lcd44780.initBitID  (z3AdsOk,   n3,             1,2);}     RT_HW_lcd44780.LcdBit  (z3AdsOk, vADS1115_ok);               //--Output ADS1115_ok;
  if(z3AdsA2.custom==0)   {RT_HW_lcd44780.initFloatID(z3AdsA2,   n3,'3','L',';', 2,2,6);}   RT_HW_lcd44780.LcdFLOAT(z3AdsA2, vADS1115_A2f);              //--Output ADS1115_A2f;
  if(z3AdsA3.custom==0)   {RT_HW_lcd44780.initFloatID(z3AdsA3,   n3,'3','L',';', 9,2,6);}   RT_HW_lcd44780.LcdFLOAT(z3AdsA3, vADS1115_A3f);              //--Output ADS1115_A3f;     
//-------------------------------------------------------------------------------------
  if(z3PCF8575A.custom==0){RT_HW_lcd44780.initWordID (z3PCF8575A,n3,'*','L','~', 1,3,8);}   RT_HW_lcd44780.LcdVAR  (z3PCF8575A,vPCF8575inA);              //--Output dvPCF8575.inA; 
  if(z3PCF8575B.custom==0){RT_HW_lcd44780.initWordID (z3PCF8575B,n3,'*','L','~',10,3,8);}   RT_HW_lcd44780.LcdVAR  (z3PCF8575B,vPCF8575inB);              //--Output dvPCF8575.inB;   
//--------------------------------------------------------------------------------------
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void Lcd3_SPI(){;};
#endif
