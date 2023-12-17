//============================Objects and variables Lcd.4=================================
RT_HW_LCD44780_DEVICE_ID z4; uint8_t n4; 
RT_HW_LCD44780_PARAM_ID  z4Blink; // z4BTN,    z4Speed; 
RT_HW_LCD44780_PARAM_ID  z4DhtTxt, z4DhtOk,  z4DhtTemp,z4DhtHum;   const char z4hDhtTxt[] PROGMEM="DHT="; const char z4hDhtTemp[] PROGMEM="T="; const char z4hDhtHum[]   PROGMEM="H=";
RT_HW_LCD44780_PARAM_ID  z4HtuTxt, z4HtuOk,  z4HtuTemp,z4HtuHum;   const char z4hHtuTxt[] PROGMEM="HTU="; const char z4hHtuTemp[] PROGMEM="T="; const char z4hHtuHum[]   PROGMEM="H=";
RT_HW_LCD44780_PARAM_ID  z4WordBit1;
RT_HW_LCD44780_PARAM_ID  z4NXSL1,  z4NXSL2,  z4NXBTN, z4NXPage;    const char z4hNXSL1[]  PROGMEM="s1=";  const char z4hNXSL2[]   PROGMEM="s2=";
//RT_HW_LCD44780_PARAM_ID  z3DhtTxt, z3DhtOk, z3DhtTemp,z3DhtHum;   const char z3hDhtTxt[] PROGMEM="DHT="; const char z3hDhtTemp[] PROGMEM="T="; const char z3hDhtHum[]   PROGMEM="H=";
//RT_HW_LCD44780_PARAM_ID  z3HtuTxt, z3HtuOk, z3HtuTemp,z3HtuHum;   const char z3hHtuTxt[] PROGMEM="HTU="; const char z3hHtuTemp[] PROGMEM="T="; const char z3hHtuHum[]   PROGMEM="H=";
//RT_HW_LCD44780_PARAM_ID  z3ShtTxt, z3ShtOk, z3ShtTemp,z3ShtHum;   const char z3hShtTxt[] PROGMEM="SHT="; const char z3hShtTemp[] PROGMEM="T="; const char z3hShtHum[]   PROGMEM="H=";
//RT_HW_LCD44780_PARAM_ID  z3BmpTxt, z3BmpOk, z3BmpTemp,z3BmpPress; const char z3hBmpTxt[] PROGMEM="BMP="; const char z3hBmpTemp[] PROGMEM="T="; const char z3hBmpPress[] PROGMEM="P=";
//RT_HW_LCD44780_PARAM_ID  z3NXSL1, z3NXSL2,  z3NXBTN, z3NXPage;    const char z3hNXSL1[]  PROGMEM="s1=";  const char z3hNXSL2[]   PROGMEM="s2=";
//RT_HW_LCD44780_PARAM_ID  z3MBSL1, z3MBSL2,  z3MBBTN;              const char z3hMBSL1[]  PROGMEM="S1=";  const char z3hMBSL2[]   PROGMEM="S2=";
//RT_HW_LCD44780_PARAM_ID  z3ByteBit1, z3ByteBit2, z3HC165S, z3HC165N; 
//======================================================================================
void Lcd4_SPN(){
//--------------------------------------------------------------------------------------
if(z4.custom==0){z4.custom=RT_HW_Base.spnSetParam(z4.dvN,sckLcdSPN, 255, mosiLcdSPN, csLcdSPN,0); z4.mi='N'; z4.cols=20; z4.rows=4;}  RT_HW_lcd44780.direct(z4); n4=z4.num;
//--------------------------------------------------------------------------------------
  if(z4Blink.custom==0)   {RT_HW_lcd44780.initBlinkID(z4Blink,   n4,500, 1,1);}             RT_HW_lcd44780.LcdBlink(z4Blink,' ','*');
//--------------------------------------------------------------------------------------
  if(z4DhtTxt.custom==0)  {RT_HW_lcd44780.initTextID (z4DhtTxt,  n4,'L',         2,1,2);}   RT_HW_lcd44780.LcdText (z4DhtTxt,  z4hDhtTxt);                //--Output DHT22.name;
  if(z4DhtOk.custom==0)   {RT_HW_lcd44780.initBitID  (z4DhtOk,   n4,             4,1);}     RT_HW_lcd44780.LcdBit  (z4DhtOk,               vDHT22ok);     //--Output DHT22.ok;  
  if(z4DhtTemp.custom==0) {RT_HW_lcd44780.initFloatID(z4DhtTemp, n4,'2','L',';', 5,1,8);}   RT_HW_lcd44780.LcdFloat(z4DhtTemp, z4hDhtTemp, vDHT22Temp);   //--Output DHT22.Temp;
  if(z4DhtHum.custom==0)  {RT_HW_lcd44780.initFloatID(z4DhtHum,  n4,'2','L',';',13,1,8);}   RT_HW_lcd44780.LcdFloat(z4DhtHum,  z4hDhtHum,  vDHT22Hum);    //--Output DHT22.Hum;  
//--------------------------------------------------------------------------------------
  if(z4HtuTxt.custom==0)  {RT_HW_lcd44780.initTextID (z4HtuTxt,  n4,'L',         1,2,3);}   RT_HW_lcd44780.LcdText (z4HtuTxt,  z4hHtuTxt);                //--Output HTU21.name;
  if(z4HtuOk.custom==0)   {RT_HW_lcd44780.initBitID  (z4HtuOk,   n4,             4,2);}     RT_HW_lcd44780.LcdBit  (z4HtuOk,               vHTU21_ok);    //--Output HTU21.ok;  
  if(z4HtuTemp.custom==0) {RT_HW_lcd44780.initFloatID(z4HtuTemp, n4,'2','L',';', 5,2,8);}   RT_HW_lcd44780.LcdFloat(z4HtuTemp, z4hHtuTemp, vHTU21_Temp);  //--Output HTU21.Temp;
  if(z4HtuHum.custom==0)  {RT_HW_lcd44780.initFloatID(z4HtuHum,  n4,'2','L',';',13,2,0);}   RT_HW_lcd44780.LcdFloat(z4HtuHum,  z4hHtuHum,  vHTU21_Hum);   //--Output HTU21.Hum;  
//--------------------------------------------------------------------------------------  
  if(z4WordBit1.custom==0){RT_HW_lcd44780.initWordID (z4WordBit1,n4,'#','L','~', 1,3,16);}   RT_HW_lcd44780.LcdVAR (z4WordBit1,v74HC165);      //--Output v74HC165.2;
//--------------------------------------------------------------------------------------
  if(z4NXBTN.custom==0)   {RT_HW_lcd44780.initByteID (z4NXBTN,   n4,'#','L','~', 1,4,8);}      RT_HW_lcd44780.LcdVAR  (z4NXBTN,nxtVr1);                      //--Output next.BTN; 
  if(z4NXPage.custom==0)  {RT_HW_lcd44780.initByteID (z4NXPage,  n4,'U','L','~', 9,4,1);}   RT_HW_lcd44780.LcdVAR  (z4NXPage,nxtPage);                    //--Output next.Page0;
  if(z4NXSL1.custom==0)   {RT_HW_lcd44780.initByteID (z4NXSL1,   n4,'H','L','~',11,4,2);}   RT_HW_lcd44780.LcdVAR  (z4NXSL1,nxtVr2);                      //--Output NEXT.Slider1;
  if(z4NXSL2.custom==0)   {RT_HW_lcd44780.initByteID (z4NXSL2,   n4,'H','L','~',14,4,2);}   RT_HW_lcd44780.LcdVAR  (z4NXSL2,nxtVr3);                      //--Output NEXT.Slider2; 
//  if(z3DhtTxt.custom==0)  {RT_HW_lcd44780.initTextID (z3DhtTxt,  n3,'L',         2,1,2);}   RT_HW_lcd44780.LcdText (z3DhtTxt,  z3hDhtTxt);                //--Output  DHT22.name;
//  if(z3DhtOk.custom==0)   {RT_HW_lcd44780.initBitID  (z3DhtOk,   n3,             4,1);}     RT_HW_lcd44780.LcdBit  (z3DhtOk,               vDHT22ok);     //--Output DHT22.ok;  
//  if(z3DhtTemp.custom==0) {RT_HW_lcd44780.initFloatID(z3DhtTemp, n3,'2','L',';', 5,1,8);}   RT_HW_lcd44780.LcdFloat(z3DhtTemp, z3hDhtTemp, vDHT22Temp);   //--Output DHT22.Temp;
//  if(z3DhtHum.custom==0)  {RT_HW_lcd44780.initFloatID(z3DhtHum,  n3,'2','L',';',13,1,8);}   RT_HW_lcd44780.LcdFloat(z3DhtHum,  z3hDhtHum,  vDHT22Hum);    //--Output DHT22.Hum;
   
//  if(z3HtuTxt.custom==0)  {RT_HW_lcd44780.initTextID (z3HtuTxt,  n3,'L',         1,2,3);}   RT_HW_lcd44780.LcdText (z3HtuTxt,  z3hHtuTxt);                //--Output HTU21.name;
//  if(z3HtuOk.custom==0)   {RT_HW_lcd44780.initBitID  (z3HtuOk,   n3,             4,2);}     RT_HW_lcd44780.LcdBit  (z3HtuOk,               vHTU21_ok);    //--Output HTU21.ok;  
//  if(z3HtuTemp.custom==0) {RT_HW_lcd44780.initFloatID(z3HtuTemp, n3,'2','L',';', 5,2,8);}   RT_HW_lcd44780.LcdFloat(z3HtuTemp, z3hHtuTemp, vHTU21_Temp);  //--Output HTU21.Temp;
//  if(z3HtuHum.custom==0)  {RT_HW_lcd44780.initFloatID(z3HtuHum,  n3,'2','L',';',13,2,0);}   RT_HW_lcd44780.LcdFloat(z3HtuHum,  z3hHtuHum,  vHTU21_Hum);   //--Output HTU21.Hum;
  
//  if(z3ByteBit2.custom==0){RT_HW_lcd44780.initByteID (z3ByteBit2,n3,'#','L','~', 1,3,8);}   RT_HW_lcd44780.LcdVAR  (z3ByteBit2,(v74HC165>>8)&0XFF);      //--Output v74HC165.4;
//  if(z3ByteBit1.custom==0){RT_HW_lcd44780.initByteID (z3ByteBit1,n3,'#','L','~',13,3,8);}   RT_HW_lcd44780.LcdVAR  (z3ByteBit1,(v74HC165)   &0XFF);      //--Output v74HC165.3;
//  if(z3ByteBit2.custom==0)  {RT_HW_lcd44780.initByteID (z3ByteBit2,n3,'#','L','~', 1,4,8);} RT_HW_lcd44780.LcdVAR  (z3ByteBit2,(v74HC165>>8) &0XFF);    //--Output v74HC165.2;
//  if(z3NXBTN.custom==0)   {RT_HW_lcd44780.initByteID (z3NXBTN,n3,'#','L','~', 1,4,8);}      RT_HW_lcd44780.LcdVAR  (z3NXBTN,nxtVr1);                      //--Output next.BTN;
//  if(z3NXPage.custom==0)  {RT_HW_lcd44780.initByteID (z3NXPage,  n3,'U','L','~', 9,4,1);}   RT_HW_lcd44780.LcdVAR  (z3NXPage,nxtPage);                    //--Output next.Page0;
//  if(z3NXSL1.custom==0)   {RT_HW_lcd44780.initByteID (z3NXSL1,   n3,'H','L','~',11,4,2);}   RT_HW_lcd44780.LcdVAR  (z3NXSL1,nxtVr2);                      //--Output NEXT.Slider1;
//  if(z3NXSL2.custom==0)   {RT_HW_lcd44780.initByteID (z3NXSL2,   n3,'H','L','~',14,4,2);}   RT_HW_lcd44780.LcdVAR  (z3NXSL2,nxtVr3);                      //--Output NEXT.Slider2;  
//  if(z3HC165N.custom==0)  {RT_HW_lcd44780.initWordID (z3HC165N,  n3,'H','L','~',17,3,4);}   RT_HW_lcd44780.LcdVAR  (z3HC165N,(v74HC165N&0xFFFF));         //--Output 74HC165Nx2; 
//  if(z3HC165S.custom==0)  {RT_HW_lcd44780.initWordID (z3HC165S,  n3,'H','L','~',17,4,4);}   RT_HW_lcd44780.LcdVAR  (z3HC165S,(v74HC165 &0xFFFF));         //--Output 74HC165 x2;  
//--------------------------------------------------------------------------------------
};
