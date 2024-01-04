//============================Objects and variables Lcd.3=================================
RT_HW_LCD44780_DEVICE_ID z3; uint8_t n3; 
RT_HW_LCD44780_PARAM_ID  z3Blink, z3Speed, z3Cr1Speed ; 
RT_HW_LCD44780_PARAM_ID  z3AdsOk,z3AdsA0,z3AdsA1,z3AdsA2,z3AdsA3;
RT_HW_LCD44780_PARAM_ID  z3PCF8575ok,z3PCF8575A,z3PCF8575B;
RT_HW_LCD44780_PARAM_ID  z3Cr1Ok, z3Cr1Cnt;
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
  if(z3Cr1Speed.custom==0){RT_HW_lcd44780.initWordID (z3Cr1Speed,n3,'U','R','~',15,2,0);}   RT_HW_lcd44780.LcdVAR  (z3Cr1Speed,vCr1SpeedMCUF);          //--Speed.filter output;
//--------------------------------------------------------------------------------------
  if(z3AdsA0.custom==0)   {RT_HW_lcd44780.initFloatID(z3AdsA0,   n3,'3','L',';', 2,1,6);}   RT_HW_lcd44780.LcdFLOAT(z3AdsA0, vADS1115_A0f);              //--Output ADS1115_A0f;
  if(z3AdsA1.custom==0)   {RT_HW_lcd44780.initFloatID(z3AdsA1,   n3,'3','L',';', 9,1,6);}   RT_HW_lcd44780.LcdFLOAT(z3AdsA1, vADS1115_A1f);              //--Output ADS1115_A1f;  
  if(z3AdsOk.custom==0)   {RT_HW_lcd44780.initBitID  (z3AdsOk,   n3,             1,2);}     RT_HW_lcd44780.LcdBit  (z3AdsOk, vADS1115_ok);               //--Output ADS1115_ok;
  if(z3AdsA2.custom==0)   {RT_HW_lcd44780.initFloatID(z3AdsA2,   n3,'3','L',';', 2,2,6);}   RT_HW_lcd44780.LcdFLOAT(z3AdsA2, vADS1115_A2f);              //--Output ADS1115_A2f;
  if(z3AdsA3.custom==0)   {RT_HW_lcd44780.initFloatID(z3AdsA3,   n3,'3','L',';', 9,2,6);}   RT_HW_lcd44780.LcdFLOAT(z3AdsA3, vADS1115_A3f);              //--Output ADS1115_A3f;     
//-------------------------------------------------------------------------------------
  if(z3PCF8575A.custom==0){RT_HW_lcd44780.initWordID (z3PCF8575A,n3,'*','L','~', 1,3,8);}   RT_HW_lcd44780.LcdVAR  (z3PCF8575A,dvPCF8575.inA);              //--Output dvPCF8575.inA; 
  if(z3PCF8575B.custom==0){RT_HW_lcd44780.initWordID (z3PCF8575B,n3,'*','L','~', 9,3,8);}   RT_HW_lcd44780.LcdVAR  (z3PCF8575B,dvPCF8575.inB);              //--Output dvPCF8575.inB; 
  if(z3Cr1Cnt.custom==0)  {RT_HW_lcd44780.initByteID (z3Cr1Cnt,  n3,'U','L','~',17,3,2);}   RT_HW_lcd44780.LcdVAR  (z3Cr1Cnt,  vCr1Cnt);                    //--Output vCr1Cnt;
  if(z3Cr1Ok.custom==0)   {RT_HW_lcd44780.initByteID (z3Cr1Ok,   n3,'U','L','~',20,3,1);}   RT_HW_lcd44780.LcdVAR  (z3Cr1Ok,   vCr1Ok);                     //--Output vCr1Cnt;  

//  if(z3USBdir.custom==0)   {RT_HW_lcd44780.initByteID(z3USBdir,  n3,'U','L','~',1,4,2);}   RT_HW_lcd44780.LcdVAR  (z3USBdir,   RT_HW_Base.uartUSB.dir);     
//  if(z3USBcnt.custom==0)   {RT_HW_lcd44780.initByteID(z3USBcnt,  n3,'U','L','~',5,4,2);}   RT_HW_lcd44780.LcdVAR  (z3USBcnt,   RT_HW_Base.uartUSB.cntTest);    
//--------------------------------------------------------------------------------------
//  if(z3HtuTemp.custom==0) {RT_HW_lcd44780.initFloatID(z3HtuTemp, n3,'2','L',';', 5,2,8);}   RT_HW_lcd44780.LcdFloat(z3HtuTemp, z3hHtuTemp, vHTU21_Temp);  //--Output HTU21.Temp;
//  if(z3DhtTxt.custom==0)  {RT_HW_lcd44780.initTextID (z3DhtTxt,  n3,'L',         2,1,2);}   RT_HW_lcd44780.LcdText (z3DhtTxt,  z3hDhtTxt);                //--Output  DHT22.name;
//  if(z3DhtOk.custom==0)   {RT_HW_lcd44780.initBitID  (z3DhtOk,   n3,             4,1);}     RT_HW_lcd44780.LcdBit  (z3DhtOk,               vDHT22ok);     //--Output DHT22.ok;  
//  if(z3DhtTemp.custom==0) {RT_HW_lcd44780.initFloatID(z3DhtTemp, n3,'2','L',';', 5,1,8);}   RT_HW_lcd44780.LcdFloat(z3DhtTemp, z3hDhtTemp, vDHT22Temp);   //--Output DHT22.Temp;
//  if(z3DhtHum.custom==0)  {RT_HW_lcd44780.initFloatID(z3DhtHum,  n3,'2','L',';',13,1,8);}   RT_HW_lcd44780.LcdFloat(z3DhtHum,  z3hDhtHum,  vDHT22Hum);    //--Output DHT22.Hum;
//--------------------------------------------------------------------------------------   
//  if(z3HtuTxt.custom==0)  {RT_HW_lcd44780.initTextID (z3HtuTxt,  n3,'L',         1,2,3);}   RT_HW_lcd44780.LcdText (z3HtuTxt,  z3hHtuTxt);                //--Output HTU21.name;
//  if(z3HtuOk.custom==0)   {RT_HW_lcd44780.initBitID  (z3HtuOk,   n3,             4,2);}     RT_HW_lcd44780.LcdBit  (z3HtuOk,               vHTU21_ok);    //--Output HTU21.ok;  
//  if(z3HtuTemp.custom==0) {RT_HW_lcd44780.initFloatID(z3HtuTemp, n3,'2','L',';', 5,2,8);}   RT_HW_lcd44780.LcdFloat(z3HtuTemp, z3hHtuTemp, vHTU21_Temp);  //--Output HTU21.Temp;
//  if(z3HtuHum.custom==0)  {RT_HW_lcd44780.initFloatID(z3HtuHum,  n3,'2','L',';',13,2,0);}   RT_HW_lcd44780.LcdFloat(z3HtuHum,  z3hHtuHum,  vHTU21_Hum);   //--Output HTU21.Hum;
//--------------------------------------------------------------------------------------  
//  if(z3ByteBit2.custom==0){RT_HW_lcd44780.initByteID (z3ByteBit2,n3,'#','L','~', 1,3,8);}   RT_HW_lcd44780.LcdVAR  (z3ByteBit2,(v74HC165>>8)&0XFF);      //--Output v74HC165.4;
//  if(z3ByteBit1.custom==0){RT_HW_lcd44780.initByteID (z3ByteBit1,n3,'#','L','~',13,3,8);}   RT_HW_lcd44780.LcdVAR  (z3ByteBit1,(v74HC165)   &0XFF);      //--Output v74HC165.3;
//  if(z3ByteBit2.custom==0){RT_HW_lcd44780.initByteID (z3ByteBit2,n3,'#','L','~', 1,4,8);}   RT_HW_lcd44780.LcdVAR  (z3ByteBit2,(v74HC165>>8) &0XFF);    //--Output v74HC165.2;
//--------------------------------------------------------------------------------------
//  if(z3NXBTN.custom==0)   {RT_HW_lcd44780.initByteID (z3NXBTN,n3,'#','L','~', 1,4,8);}      RT_HW_lcd44780.LcdVAR  (z3NXBTN,nxtVr1);                      //--Output next.BTN;
//  if(z3NXPage.custom==0)  {RT_HW_lcd44780.initByteID (z3NXPage,  n3,'U','L','~', 9,4,1);}   RT_HW_lcd44780.LcdVAR  (z3NXPage,nxtPage);                    //--Output next.Page0;
//  if(z3NXSL1.custom==0)   {RT_HW_lcd44780.initByteID (z3NXSL1,   n3,'H','L','~',11,4,2);}   RT_HW_lcd44780.LcdVAR  (z3NXSL1,nxtVr2);                      //--Output NEXT.Slider1;
//  if(z3NXSL2.custom==0)   {RT_HW_lcd44780.initByteID (z3NXSL2,   n3,'H','L','~',14,4,2);}   RT_HW_lcd44780.LcdVAR  (z3NXSL2,nxtVr3);                      //--Output NEXT.Slider2;  
//--------------------------------------------------------------------------------------
//  if(z3HC165N.custom==0)  {RT_HW_lcd44780.initWordID (z3HC165N,  n3,'H','L','~',17,3,4);}   RT_HW_lcd44780.LcdVAR  (z3HC165N,(v74HC165N&0xFFFF));         //--Output 74HC165Nx2; 
//  if(z3HC165S.custom==0)  {RT_HW_lcd44780.initWordID (z3HC165S,  n3,'H','L','~',17,4,4);}   RT_HW_lcd44780.LcdVAR  (z3HC165S,(v74HC165 &0xFFFF));         //--Output 74HC165 x2;  
//--------------------------------------------------------------------------------------
};
