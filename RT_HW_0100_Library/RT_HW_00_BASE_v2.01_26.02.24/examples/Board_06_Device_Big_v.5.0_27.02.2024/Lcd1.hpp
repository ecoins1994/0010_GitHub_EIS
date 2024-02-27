//=================================================================================================
//                                    1. Lcd1
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_LCD1
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//=================================================================================================
//                     1.1. Объекты и переменные Lcd1.z
//=================================================================================================
  RT_HW_LCD44780_DEVICE_ID z1; uint8_t n1; 
  RT_HW_LCD44780_PARAM_ID  z1Blink, z1BTN, z1Speed1,z1Speed2, z1Core1;
  RT_HW_LCD44780_PARAM_ID  z1ADC;   
  RT_HW_LCD44780_PARAM_ID  z1SNS_ok;
  RT_HW_LCD44780_PARAM_ID  z1SNS_Temp;   const char z1SNS_hTemp[]  PROGMEM="T=";
  RT_HW_LCD44780_PARAM_ID  z1SNS_Hum;    const char z1SNS_hHum[]   PROGMEM="H=";
  RT_HW_LCD44780_PARAM_ID  z1HC165;
//=================================================================================================
//                     1.2. Управление Lcd1.z (выполняется по состоянию Button=0)
//=================================================================================================
void Lcd1z(){
//-------------------------------------------------------------------------------------------------
  if(z1.custom==0){z1.custom=RT_HW_Base.i2cSetParam(z1.dvI,i2cAdrLcd1,0,400000UL); z1.mi='I'; z1.cols=16; z1.rows=2;} //--Настройка параметров дисплея; 
  RT_HW_lcd44780.direct(z1); n1=z1.num;                                                                               //--Управление дисплеем;
//-------------------------------------------------------------------------------------------------
  if(z1Blink.custom   ==0) {RT_HW_lcd44780.initBlinkID (z1Blink,   n1,500, 1,1);}            RT_HW_lcd44780.LcdBlink(z1Blink,' ','*');             //--Мерцающий символ;
  if(z1ADC.custom     ==0) {RT_HW_lcd44780.initWordID  (z1ADC,     n1,'U','L','~', 2,1,4); z1ADC.periodLimit=20;}                                  //--ADC, не чаще 50 вхождения в блок вывода;
                                                                                          RT_HW_lcd44780.LcdVAR(z1ADC,vADCF); //--ADC (АЦП);    //--ADC,
  if(z1HC165.custom   ==0) {RT_HW_lcd44780.initByteID  (z1HC165,   n1,'H','R','~', 6,1,2);}  RT_HW_lcd44780.LcdVAR  (z1HC165,  (uint8_t)(v74HC165_vr&0xFF));    //--74HC165_vr;
  if(z1Speed1.custom  ==0) {RT_HW_lcd44780.initWordID  (z1Speed1,  n1,'U','R','~', 8,1,4);}  RT_HW_lcd44780.LcdVAR  (z1Speed1,  vspeedMCUF0);                    //--Быстродействие CORE0;
  if(z1Core1.custom   ==0) {RT_HW_lcd44780.initBitID   (z1Core1,   n1,            12,1);}    RT_HW_lcd44780.LcdBit  (z1Core1,RT_HW_Base.shed.isLoop1,' ','+');   //--Флаг работы CORE1;
  if(z1Speed2.custom  ==0) {RT_HW_lcd44780.initWordID  (z1Speed2,  n1,'U','R','~',13,1,4);}  RT_HW_lcd44780.LcdVAR  (z1Speed2,  vspeedMCUF1);                    //--Быстродействие CORE1;
//-------------------------------------------------------------------------------------------------
  if(z1SNS_ok.custom  ==0) {RT_HW_lcd44780.initBitID   (z1SNS_ok,  n1,1,2);}                 RT_HW_lcd44780.LcdBit  (z1SNS_ok,               vAHTxx_ok,'-','+'); //--Сенсор AHTxx ok;
  if(z1SNS_Temp.custom==0) {RT_HW_lcd44780.initFloatID (z1SNS_Temp,n1,'2','L',';', 2,2,8);}  RT_HW_lcd44780.LcdFloat(z1SNS_Temp,z1SNS_hTemp, vAHTxx_Temp);       //--Температура AHTxx;
  if(z1SNS_Hum.custom ==0) {RT_HW_lcd44780.initFloatID (z1SNS_Hum, n1,'2','L',';',10,2,7);}  RT_HW_lcd44780.LcdFloat(z1SNS_Hum, z1SNS_hHum,  vAHTxx_Hum);        //--Влажность AHTxx;
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//                     1.3. Объекты и переменные Lcd1.x (управляется по состоянию Button=0)
//=================================================================================================
RT_HW_LCD44780_DEVICE_ID  x1; uint8_t m1; 
RT_HW_LCD44780_PARAM_ID   x1Blink, x1BTN; 
RT_HW_LCD44780_PARAM_ID   x1DS1820_ok;  
RT_HW_LCD44780_PARAM_ID   x1DS1820_vr;  const char x1DS1820_hTemp[] PROGMEM="T=";
RT_HW_LCD44780_PARAM_ID   x1SR04_ok;    
RT_HW_LCD44780_PARAM_ID   x1SR04_Len;   const char x1SR04_hLen[]    PROGMEM="L=";
RT_HW_LCD44780_PARAM_ID   x1SNS_ok;
RT_HW_LCD44780_PARAM_ID   x1SNS_Temp;   const char x1SNS_hTemp[]    PROGMEM="T=";
RT_HW_LCD44780_PARAM_ID   x1SNS_Hum;    const char x1SNS_hHum[]     PROGMEM="H=";

//=================================================================================================
//                     1.4. Управление Lcd1.x (выполняется по состоянию Button=1)
//=================================================================================================
void Lcd1x(){
//-------------------------------------------------------------------------------------------------
  if(x1.custom==0){x1.custom=RT_HW_Base.i2cSetParam(x1.dvI,i2cAdrLcd1,0,400000UL); x1.mi='I'; x1.cols=16; x1.rows=2;} //--Настройка параметров дисплея;   
  RT_HW_lcd44780.direct(x1); m1=x1.num;                                                                               //--Управление дисплеем;
//-------------------------------------------------------------------------------------------------
  if(x1Blink.custom    ==0) {RT_HW_lcd44780.initBlinkID (x1Blink, m1,500, 1,1);}              RT_HW_lcd44780.LcdBlink(x1Blink,' ','#');                                 //--Мерцающий символ '#';
  if(x1DS1820_ok.custom==0) {RT_HW_lcd44780.initBitID   (x1DS1820_ok,m1,             2,1);}   RT_HW_lcd44780.LcdBit  (x1DS1820_ok,                vDS1820_ok,'-','+');  //--DS1820.ok;
  if(x1DS1820_vr.custom==0) {RT_HW_lcd44780.initFloatID (x1DS1820_vr,m1,'2','L',';', 3,1,8);} RT_HW_lcd44780.LcdFloat(x1DS1820_vr,x1DS1820_hTemp, vDS1820_Temp);        //--DS1820.Temp;
  if(x1SR04_ok.custom  ==0) {RT_HW_lcd44780.initBitID   (x1SR04_ok,m1,11,1);}                 RT_HW_lcd44780.LcdBit  (x1SR04_ok,                  vSR04_ok, '-','+');   //--HC-SR04.ok;
  if(x1SR04_Len.custom ==0) {RT_HW_lcd44780.initWordID  (x1SR04_Len,  m1,'U','L',';',12,1,0);}RT_HW_lcd44780.LcdVar  (x1SR04_Len, x1SR04_hLen,    vSR04_Len);           //--HC-SR04.Len;
//-------------------------------------------------------------------------------------------------
  if(x1SNS_ok.custom  ==0)  {RT_HW_lcd44780.initBitID   (x1SNS_ok,   m1,             1,2);}   RT_HW_lcd44780.LcdBit  (x1SNS_ok,                   vSHT3x_ok,'-','+');   //--SHT3x.ok;
  if(x1SNS_Temp.custom==0)  {RT_HW_lcd44780.initFloatID (x1SNS_Temp, m1,'2','L',';', 2,2,8);} RT_HW_lcd44780.LcdFloat(x1SNS_Temp, x1SNS_hTemp,    vSHT3x_Temp);         //--SHT3x.Temp;
  if(x1SNS_Hum.custom ==0)  {RT_HW_lcd44780.initFloatID (x1SNS_Hum,  m1,'1','L',';',10,2,0);} RT_HW_lcd44780.LcdFloat(x1SNS_Hum,  x1SNS_hHum,     vSHT3x_Hum);          //--SHT3x.Hum;
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//                           1.5. Управление Lcd1  
//=================================================================================================
void Lcd1(){
  z1.extEN=!vButtonF; Lcd1z();    //--Разрешение выполнения по состоянию Button=0; 
  x1.extEN= vButtonF; Lcd1x();    //--Разрешение выполнения по состоянию Button=1; 
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void Lcd1(){;};
#endif
//=================================================================================================
