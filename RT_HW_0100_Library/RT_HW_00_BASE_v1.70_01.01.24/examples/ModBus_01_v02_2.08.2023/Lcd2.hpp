//============================Objects and variables Lcd.2===============================
RT_HW_LCD44780_DEVICE_ID z2; uint8_t n2; 
RT_HW_LCD44780_PARAM_ID  z2Blink,   z2speed, z2Speed;
RT_HW_LCD44780_PARAM_ID  z2coreOk,  z2coreCnt;
RT_HW_LCD44780_PARAM_ID  z2MBrg0,z2MBrg1,z2MBrg2,z2MBrg3;
RT_HW_LCD44780_PARAM_ID  z2MBrg4,z2MBrg5,z2MBrg6,z2MBrg7;
//======================================================================================
void Lcd2(){
//--------------------------------------------------------------------------------------
if(z2.custom==0){z2.custom=RT_HW_Base.i2cSetParam(z2.dvI,i2cAdrLcd2,0,400000UL); z2.mi='I'; z2.cols=20; z2.rows=4;}  RT_HW_lcd44780.direct(z2); n2=z2.num;
//--------------------------------------------------------------------------------------
if(z2Blink.custom==0)  {RT_HW_lcd44780.initBlinkID(z2Blink,    n2,500, 1,1);}           RT_HW_lcd44780.LcdBlink(z2Blink,' ','*');            //--Flickering symbol;
if(z2coreOk.custom==0) {RT_HW_lcd44780.initBitID  (z2coreOk,   n2,             2,1);}   RT_HW_lcd44780.LcdBit  (z2coreOk,  vcoreOk);         //--Флаг наличия CORE 1;     
if(z2coreCnt.custom==0){RT_HW_lcd44780.initByteID (z2coreCnt,  n2,'U','L','~', 3,1,4);} RT_HW_lcd44780.LcdVAR  (z2coreCnt, vcoreCnt);        //--Контрольный счетчик для CORE 1; 
if(z2Speed.custom==0)  {RT_HW_lcd44780.initWordID (z2Speed,    n2,'U','R','~',17,1,0);} RT_HW_lcd44780.LcdVAR  (z2Speed,vSpeedSmall);        //--speed/1000  CORE 1;
if(z2speed.custom==0)  {RT_HW_lcd44780.initWordID (z2speed,    n2,'U','R',';',13,1,4);} RT_HW_lcd44780.LcdVAR  (z2speed,vspeedSmall);        //--Speed/1000  CORE 2;
//--------------------------------------------------------------------------------------
if(z2MBrg0.custom==0)  {RT_HW_lcd44780.initWordID (z2MBrg0,    n2,'U','R','~', 1,2,5);} RT_HW_lcd44780.LcdVAR  (z2MBrg0,rg0);                 //--Modbus rg0;
if(z2MBrg1.custom==0)  {RT_HW_lcd44780.initWordID (z2MBrg1,    n2,'U','R','~', 6,2,5);} RT_HW_lcd44780.LcdVAR  (z2MBrg1,rg1);                 //--Modbus rg1;
if(z2MBrg2.custom==0)  {RT_HW_lcd44780.initWordID (z2MBrg2,    n2,'U','R','~',11,2,5);} RT_HW_lcd44780.LcdVAR  (z2MBrg2,rg2);                 //--Modbus rg2;
if(z2MBrg3.custom==0)  {RT_HW_lcd44780.initWordID (z2MBrg3,    n2,'U','R','~',16,2,5);} RT_HW_lcd44780.LcdVAR  (z2MBrg3,rg3);                 //--Modbus rg3;
//--------------------------------------------------------------------------------------
if(z2MBrg4.custom==0)  {RT_HW_lcd44780.initWordID (z2MBrg4,    n2,'U','R','~', 1,3,5);} RT_HW_lcd44780.LcdVAR  (z2MBrg4,rg4);                 //--Modbus rg4;
if(z2MBrg5.custom==0)  {RT_HW_lcd44780.initWordID (z2MBrg5,    n2,'U','R','~', 6,3,5);} RT_HW_lcd44780.LcdVAR  (z2MBrg5,rg5);                 //--Modbus rg5;
if(z2MBrg6.custom==0)  {RT_HW_lcd44780.initWordID (z2MBrg6,    n2,'U','R','~',11,3,5);} RT_HW_lcd44780.LcdVAR  (z2MBrg6,rg6);                 //--Modbus rg6;
if(z2MBrg7.custom==0)  {RT_HW_lcd44780.initWordID (z2MBrg7,    n2,'U','R','~',16,3,5);} RT_HW_lcd44780.LcdVAR  (z2MBrg7,rg7);                 //--Modbus rg7;
//--------------------------------------------------------------------------------------
};
