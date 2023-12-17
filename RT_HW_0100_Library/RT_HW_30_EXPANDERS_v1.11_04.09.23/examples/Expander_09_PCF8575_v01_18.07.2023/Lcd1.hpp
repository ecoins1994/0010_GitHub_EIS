//============================Objects and variables Lcd.1===============================
RT_HW_LCD44780_DEVICE_ID z1; uint8_t n1; 
RT_HW_LCD44780_PARAM_ID  z1Blink, z1BTN, z1AHTok, z1BMPok, z1Speed, z1Char, z1PWM;
RT_HW_LCD44780_PARAM_ID  z1ADC,   z1Press;  const char z1hADC[]   PROGMEM="a=";   const char z1hPress[] PROGMEM="P=";
RT_HW_LCD44780_PARAM_ID  z1Temp,  z1Hum;    const char z1hTemp[]  PROGMEM="T=";   const char z1hHum[]   PROGMEM="H=";
RT_HW_LCD44780_PARAM_ID  z1INA,   z1INB;
//======================================================================================
void Lcd1z(){
//--------------------------------------------------------------------------------------
if(z1.custom==0){z1.custom=RT_HW_Base.i2cSetParam(z1.dvI,i2cAdrLcd1,0,400000UL); z1.mi='I'; z1.cols=16; z1.rows=2;}  RT_HW_lcd44780.direct(z1); n1=z1.num;
//--------------------------------------------------------------------------------------
if(z1Blink.custom==0){RT_HW_lcd44780.initBlinkID (z1Blink,n1,500, 1,1);}           RT_HW_lcd44780.LcdBlink(z1Blink,' ','*');            //--Flickering symbol;
if(z1ADC.custom==0)  {RT_HW_lcd44780.initWordID  (z1ADC,  n1,'U','L',';', 2,1,5); z1ADC.periodLimit=20;} RT_HW_lcd44780.LcdVAR(z1ADC,vADCF); //--ADC output(no header);
if(z1INA.custom==0)  {RT_HW_lcd44780.initByteID  (z1INA,  n1,'H','L',';', 8,1,2); z1INA.periodLimit=20;} RT_HW_lcd44780.LcdVAR(z1INA,PCF8575inA); //--PCF8575inA;
if(z1INB.custom==0)  {RT_HW_lcd44780.initByteID  (z1INB,  n1,'H','L',';',11,1,2); z1INB.periodLimit=20;} RT_HW_lcd44780.LcdVAR(z1INB,PCF8575inB); //--PCF8575inB;
//if(z1BMPok.custom==0){RT_HW_lcd44780.initBitID   (z1BMPok,n1,6,1);}                RT_HW_lcd44780.LcdBit  (z1BMPok,vBMP_ok,'-','+');    //--Sensor ok   output;
//if(z1Press.custom==0){RT_HW_lcd44780.initFloatID (z1Press,n1,'1','L',';', 7,1,7);} RT_HW_lcd44780.LcdFLOAT(z1Press,vBMP_Press);         //--Pressure    output;
if(z1Speed.custom==0){RT_HW_lcd44780.initWordID  (z1Speed,n1,'U','R','~',14,1,3);} RT_HW_lcd44780.LcdVAR  (z1Speed,vSpeedSmall);        //--Speed/1000  output;
//--------------------------------------------------------------------------------------
if(z1AHTok.custom==0){RT_HW_lcd44780.initBitID   (z1AHTok,n1,1,2);}                RT_HW_lcd44780.LcdBit  (z1AHTok,vAHTxx_ok,'-','+');   //--Sensor ok   output;
if(z1Temp.custom==0) {RT_HW_lcd44780.initFloatID (z1Temp, n1,'2','L',';', 2,2,8);} RT_HW_lcd44780.LcdFloat(z1Temp,z1hTemp,vAHTxx_Temp);  //--Temperature output;
if(z1Hum.custom==0)  {RT_HW_lcd44780.initFloatID (z1Hum,  n1,'1','L',';',10,2,7);} RT_HW_lcd44780.LcdFloat(z1Hum, z1hHum, vAHTxx_Hum);   //--Humidity    output
//--------------------------------------------------------------------------------------
};
//============================Objects and variables Lcd.1===============================
RT_HW_LCD44780_DEVICE_ID x1; uint8_t m1; 
RT_HW_LCD44780_PARAM_ID  x1Blink, x1BTN, x1DS18Ok, x1SR04Ok, x1DHTOk;
RT_HW_LCD44780_PARAM_ID  x1DS1820, x1SR04;  const char x1hDS18[]    PROGMEM="T=";   const char x1hSR04[] PROGMEM="L=";
RT_HW_LCD44780_PARAM_ID  x1Temp,  x1Hum;    const char x1hTemp[]  PROGMEM="T=";   const char x1hHum[]   PROGMEM="H=";
//======================================================================================
void Lcd1x(){
//--------------------------------------------------------------------------------------
if(x1.custom==0){x1.custom=RT_HW_Base.i2cSetParam(x1.dvI,i2cAdrLcd1,0,400000UL); x1.mi='I'; x1.cols=16; x1.rows=2;}  RT_HW_lcd44780.direct(x1); m1=x1.num;
//if(x1.custom==0){RT_HW_lcd44780.setParamI(x1,i2cAdrLcd1,0,400000UL); x1.cols=16; x1.rows=2;}  RT_HW_lcd44780.direct(x1); m1=x1.num;
//--------------------------------------------------------------------------------------
if(x1Blink.custom==0){RT_HW_lcd44780.initBlinkID (x1Blink, m1,500, 1,1);}          RT_HW_lcd44780.LcdBlink(x1Blink,' ','#');              //--Flickering symbol;
if(x1DS18Ok.custom==0){RT_HW_lcd44780.initBitID  (x1DS18Ok,m1,2,1);}               RT_HW_lcd44780.LcdBit  (x1DS18Ok,vDS1820ok,'-','+');   //--DS1820 ok   output;
if(x1DS1820.custom==0){RT_HW_lcd44780.initFloatID(x1DS1820,m1,'2','L',';', 3,1,8);}RT_HW_lcd44780.LcdFloat(x1DS1820,x1hDS18,vDS1820Temp); //--DS1820 output Temp;
if(x1SR04Ok.custom==0){RT_HW_lcd44780.initBitID  (x1SR04Ok,m1,11,1);}              RT_HW_lcd44780.LcdBit  (x1SR04Ok,vSR04ok,'-','+');     //--HC-SR04 ok   output;
if(x1SR04.custom==0){RT_HW_lcd44780.initWordID   (x1SR04,  m1,'U','R',';',12,1,0);}RT_HW_lcd44780.LcdVar  (x1SR04,x1hSR04,vSR04Len);      //--HC-SR04 Len  output;
//--------------------------------------------------------------------------------------
if(x1DHTOk.custom==0){RT_HW_lcd44780.initBitID   (x1DHTOk,m1,1,2);}                RT_HW_lcd44780.LcdBit (x1DHTOk,vDHT22ok,'-','+');      //--Sensor ok   output;
if(x1Temp.custom==0) {RT_HW_lcd44780.initFloatID (x1Temp, m1,'2','L',';', 2,2,8);} RT_HW_lcd44780.LcdFloat(x1Temp,x1hTemp,vDHT22Temp);    //--Temperature output;
if(x1Hum.custom==0)  {RT_HW_lcd44780.initFloatID (x1Hum,  m1,'1','L',';',10,2,0);} RT_HW_lcd44780.LcdFloat(x1Hum, x1hHum, vDHT22Hum);     //--Humidity    output
//--------------------------------------------------------------------------------------
};

//======================================================================================
//
//======================================================================================
void Lcd1(){
z1.extEN=!vChatBut; Lcd1z(); 
x1.extEN= vChatBut; Lcd1x();
};
