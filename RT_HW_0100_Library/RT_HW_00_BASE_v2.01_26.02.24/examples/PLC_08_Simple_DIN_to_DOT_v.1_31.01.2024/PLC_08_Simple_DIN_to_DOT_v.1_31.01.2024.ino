



#include "flprogUtilites.h"
#include "RT_HW_BASE.h"
#include "RT_HW_EXPANDERS.h"
#include "RT_HW_LCD44780.h"
byte Out_49295676_179550003;
bool Out_77162603_234380927;
bool Out_77162603_220479992;
bool Out_77162603_14751153;
bool Out_77162603_159084393;
byte Out_176998533_247586584;
bool Out_29242867_125881529;
RT_HW_PIN_DIR_ID id_127934494; 
RT_HW_PIN_DIR_ID id_212958616; 
RT_HW_PIN_DIR_ID id_230706577; 
RT_HW_PIN_DIR_ID id_239775842; 
RT_HW_PIN_DIR_ID id_111425579; 
RT_HW_74HC595_DEV dv_110561315;  RT_HW_STRUCT_SHED_TASK sh_110561315; uint32_t var_110561315;
uint16_t period_110561315=100; uint8_t periodLimit_110561315=5; 

uint8_t spiBUS_110561315=0; uint8_t spiCS_110561315=255; 
RT_HW_PIN_DIR_ID id_159084393; uint8_t vButton_159084393; //--block DI;
RT_HW_PIN_DIR_ID id_14751153; uint8_t vButton_14751153; //--block DI;
RT_HW_PIN_DIR_ID id_234380927; uint8_t vButton_234380927; //--block DI;
RT_HW_PIN_DIR_ID id_220479992; uint8_t vButton_220479992; //--block DI;
RT_HW_74HC165_DEV dv_179550003;  RT_HW_STRUCT_SHED_TASK sh_179550003; uint32_t var_179550003;
uint8_t periodLimit_179550003=5; uint16_t period_179550003=100; uint8_t fresh_179550003=0;
uint8_t spiBUS_179550003=0; uint8_t spiCS_179550003=255; 
RT_HW_LCD44780_DEVICE_ID id_247586584; 
uint8_t cols_247586584; uint8_t rows_247586584; uint8_t periodReboot_247586584; 
uint8_t i2c8_bus_247586584=0; uint8_t i2c8_adr_247586584;
RT_HW_LCD44780_PARAM_ID id_87782060; 
uint16_t Gperiod_87782060; char Gsign0_87782060; char Gsign1_87782060;
RT_HW_LCD44780_PARAM_ID id_18509587; 
char Rsign0_18509587; char Rsign1_18509587;
RT_HW_LCD44780_PARAM_ID id_211932930; 
char Rsign0_211932930; char Rsign1_211932930;
RT_HW_LCD44780_PARAM_ID id_217385506; 
char Rsign0_217385506; char Rsign1_217385506;
RT_HW_LCD44780_PARAM_ID id_110307881; 
char Rsign0_110307881; char Rsign1_110307881;
RT_HW_LCD44780_PARAM_ID id_35729038; 
const char Bhead_35729038[] PROGMEM ="~";
RT_HW_GENERATOR_EVENT_ID id_125881529; //--generator;


void setup()
{




}
void loop()
{







//Плата:1
RT_HW_Base.generatorEvent(id_125881529,(500));
Out_29242867_125881529=id_125881529.meander;
RT_HW_Base.pinDigitalWrite(id_111425579, (25), (Out_29242867_125881529),'N');
vButton_159084393=RT_HW_Base.pinDigitalRead (id_159084393,(10),'U'); 
Out_77162603_159084393=vButton_159084393;
RT_HW_Base.pinDigitalWrite(id_127934494, (2), (!(Out_77162603_159084393)),'N');
//==================================Lcd HD44780====================================================
if(id_247586584.custom==0){
cols_247586584=162/10; rows_247586584=162-(cols_247586584*10);
i2c8_bus_247586584=0;
i2c8_adr_247586584=(0x27);
id_247586584.custom=RT_HW_Base.i2cSetParam(id_247586584.dvI,i2c8_adr_247586584,0,0); 
id_247586584.mi='I'; id_247586584.cols=cols_247586584; id_247586584.rows=rows_247586584;
id_247586584.periodReboot=periodReboot_247586584;
}
RT_HW_lcd44780.direct(id_247586584);
Out_176998533_247586584=id_247586584.num;
//================================ 74H165 ===================================================
if(dv_179550003.custom==0){
period_179550003=(uint16_t)100;  //-getting table period;
spiBUS_179550003=0; //-- getting SPI bus.table;
spiCS_179550003=(20); //-getting SPI cs.ext;
dv_179550003.bitOrder=1;
dv_179550003.qnt=1;
if(1==1){dv_179550003.qnt=1;}
if(1==2){dv_179550003.qnt=2;}
if(1==3){dv_179550003.qnt=3;}
if(1==4){dv_179550003.qnt=4;}
if(1==5){dv_179550003.qnt=2;}
if(1==6){dv_179550003.qnt=3;}
if(1==7){dv_179550003.qnt=4;}
if(1==8){dv_179550003.qnt=1;}
if(1==9){dv_179550003.qnt=2;}
dv_179550003.custom=RT_HW_Base.spiSetParam(dv_179550003.dvS,spiCS_179550003,spiBUS_179550003,0); dv_179550003.mi='S';
RT_HW_Base.setTaskID(sh_179550003,'P',period_179550003);
}
RT_HW_Base.directTask(sh_179550003); 
RT_HW_74hc165.direct(dv_179550003,sh_179550003.run); 
if(dv_179550003.fresh){dv_179550003.fresh=0;
Out_49295676_179550003=dv_179550003.var & 0xFF;
}
//==================================================================================================
//================================ 74HC595 ===================================================
if(dv_110561315.custom==0){
spiBUS_110561315=0; //-- getting SPI bus.table;
spiCS_110561315=(17); //-getting SPI cs.ext;
dv_110561315.bitOrder=1; dv_110561315.qnt=1;
if(1==1){dv_110561315.qnt=1;} if(1==2){dv_110561315.qnt=2;} if(1==3){dv_110561315.qnt=3;}
if(1==4){dv_110561315.qnt=4;} if(1==5){dv_110561315.qnt=2;} if(1==6){dv_110561315.qnt=3;}
if(1==7){dv_110561315.qnt=4;} if(1==8){dv_110561315.qnt=1;} if(1==9){dv_110561315.qnt=2;}
dv_110561315.custom=RT_HW_Base.spiSetParam(dv_110561315.dvS,spiCS_110561315,spiBUS_110561315,0);
dv_110561315.mi='S';
RT_HW_Base.setTaskID(sh_110561315,'Q',period_110561315);
}
RT_HW_Base.directTask(sh_110561315); 
if(sh_110561315.run){
var_110561315=(Out_49295676_179550003);
}
RT_HW_74hc595.direct(dv_110561315,var_110561315,sh_110561315.run);
//==================================================================================================
//===================================Lcd HD44780 output============================================
if(id_35729038.custom==0)  {RT_HW_lcd44780.initByteID(id_35729038,(Out_176998533_247586584),'*','L','~',8,2,8);}
RT_HW_lcd44780.LcdVar(id_35729038,Bhead_35729038,(Out_49295676_179550003));
vButton_220479992=RT_HW_Base.pinDigitalRead (id_220479992,(29),'U'); 
Out_77162603_220479992=vButton_220479992;
RT_HW_Base.pinDigitalWrite(id_230706577, (28), (!(Out_77162603_220479992)),'N');
//===================================Lcd HD44780 output============================================
if(id_110307881.custom==0){ 
Rsign0_110307881=RT_HW_lcd44780.getSignBitCode(1,0); Rsign1_110307881=RT_HW_lcd44780.getSignBitCode(1,1); 
RT_HW_lcd44780.initBitID(id_110307881,(Out_176998533_247586584),4,2);
} 
RT_HW_lcd44780.LcdBit (id_110307881,(!(Out_77162603_220479992)),Rsign0_110307881,Rsign1_110307881); 
vButton_234380927=RT_HW_Base.pinDigitalRead (id_234380927,(23),'U'); 
Out_77162603_234380927=vButton_234380927;
RT_HW_Base.pinDigitalWrite(id_239775842, (22), (!(Out_77162603_234380927)),'N');
//===================================Lcd HD44780 output============================================
if(id_217385506.custom==0){ 
Rsign0_217385506=RT_HW_lcd44780.getSignBitCode(1,0); Rsign1_217385506=RT_HW_lcd44780.getSignBitCode(1,1); 
RT_HW_lcd44780.initBitID(id_217385506,(Out_176998533_247586584),3,2);
} 
RT_HW_lcd44780.LcdBit (id_217385506,(!(Out_77162603_234380927)),Rsign0_217385506,Rsign1_217385506); 
vButton_14751153=RT_HW_Base.pinDigitalRead (id_14751153,(11),'U'); 
Out_77162603_14751153=vButton_14751153;
RT_HW_Base.pinDigitalWrite(id_212958616, (3), (!(Out_77162603_14751153)),'N');
//===================================Lcd HD44780 output============================================
if(id_211932930.custom==0){ 
Rsign0_211932930=RT_HW_lcd44780.getSignBitCode(1,0); Rsign1_211932930=RT_HW_lcd44780.getSignBitCode(1,1); 
RT_HW_lcd44780.initBitID(id_211932930,(Out_176998533_247586584),2,2);
} 
RT_HW_lcd44780.LcdBit (id_211932930,(!(Out_77162603_14751153)),Rsign0_211932930,Rsign1_211932930); 
//===================================Lcd HD44780 output============================================
if(id_87782060.custom==0){ 
Gsign0_87782060=RT_HW_lcd44780.getSignBitCode(2,0); Gsign1_87782060=RT_HW_lcd44780.getSignBitCode(2,1); 
Gperiod_87782060=500; 
RT_HW_lcd44780.initBlinkID (id_87782060,(Out_176998533_247586584),Gperiod_87782060, 1,1);
} 
RT_HW_lcd44780.LcdBlink(id_87782060,Gsign0_87782060,Gsign1_87782060);
//===================================Lcd HD44780 output============================================
if(id_18509587.custom==0){ 
Rsign0_18509587=RT_HW_lcd44780.getSignBitCode(1,0); Rsign1_18509587=RT_HW_lcd44780.getSignBitCode(1,1); 
RT_HW_lcd44780.initBitID(id_18509587,(Out_176998533_247586584),1,2);
} 
RT_HW_lcd44780.LcdBit (id_18509587,(!(Out_77162603_159084393)),Rsign0_18509587,Rsign1_18509587); 







}
