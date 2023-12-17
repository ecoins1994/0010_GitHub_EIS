//============================Objects and variables Lcd.2===============================
RT_HW_LCD44780_DEVICE_ID z2; uint8_t n2; 
RT_HW_LCD44780_PARAM_ID  z2Blink,   z2BTN,   z2Speed;
RT_HW_LCD44780_PARAM_ID  z2RegA,    z2RegB;
RT_HW_LCD44780_PARAM_ID  z2Cr1Ok,  z2Cr1Cnt;
//RT_HW_LCD44780_PARAM_ID  z2USBdir,  z2USBcnt;
//======================================================================================
void Lcd2(){
//--------------------------------------------------------------------------------------
if(z2.custom==0){z2.custom=RT_HW_Base.i2cSetParam(z2.dvI,i2cAdrLcd2,0,400000UL); z2.mi='I'; z2.cols=20; z2.rows=4;}  RT_HW_lcd44780.direct(z2); n2=z2.num;
//--------------------------------------------------------------------------------------
if(z2Blink.custom==0)  {RT_HW_lcd44780.initBlinkID(z2Blink,   n2,500, 1,1);}            RT_HW_lcd44780.LcdBlink(z2Blink,' ','*');                    //--Flickering symbol;
//if(z2Speed.custom==0)  {RT_HW_lcd44780.initWordID(z2Speed,    n2,'U','R','~', 18,1,3);} RT_HW_lcd44780.LcdVAR  (z2Speed,    vSpeedSmall);        //--Speed/1000  output;
//----------------------
if(z2RegA.custom==0)   {RT_HW_lcd44780.initWordID (z2RegA,    n2,'#','L',';',  5,1,16); z2RegA.periodLimit=0; z2RegA.periodTask=20; z2RegA.modeTask='C';} RT_HW_lcd44780.LcdVAR (z2RegA, (inDM13C>>16)&0xFFFF);           //--Output DM13C;
if(z2RegB.custom==0)   {RT_HW_lcd44780.initWordID (z2RegB,    n2,'#','L',';',  5,2,16); z2RegB.periodLimit=0; z2RegB.periodTask=20; z2RegB.modeTask='C';} RT_HW_lcd44780.LcdVAR (z2RegB, (inDM13C)    &0xFFFF);       //--Output DM13C;
//---------------------
//if(z2Cr1Ok.custom==0)  {RT_HW_lcd44780.initBitID(z2Cr1Ok,     n2,            11,4);}    RT_HW_lcd44780.LcdBit  (z2Cr1Ok,  vCr1Ok);     
//if(z2Cr1Cnt.custom==0) {RT_HW_lcd44780.initByteID(z2Cr1Cnt,  n2,'U','L','~',12,4,2);}   RT_HW_lcd44780.LcdVAR  (z2Cr1Cnt, vCr1Cnt);
//--------------------------------------------------------------------------------------
};
