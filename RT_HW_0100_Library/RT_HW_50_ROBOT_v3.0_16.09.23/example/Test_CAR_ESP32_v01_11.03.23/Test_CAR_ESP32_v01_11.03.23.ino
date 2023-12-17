

#include "RT_HW_BASE.h"
#include "RT_HW_CAR.h"
#include "RT_HW_LCD44780.h"

#include "RT_HW_SENSORS.h"
#include "flprogUtilites.h"
#include "RT_HW_BASE.h"

struct UB_155925232
{
bool ubo_165148602 = 0;
};
UB_155925232 UB_155925232_Instance8;
UB_155925232 UB_155925232_Instance3;
UB_155925232 UB_155925232_Instance4;
UB_155925232 UB_155925232_Instance1;
UB_155925232 UB_155925232_Instance2;
bool UB_155925232_ubi_145242304 = 0;
bool UB_155925232_ubi_226131302 = 0;
bool UB_155925232_ubi_66480724 = 0;
bool UB_155925232_ubi_236369655 = 0;
bool UB_155925232_ubi_22624954 = 0;
bool control_125667378_2;
bool meand500_125667378_2;
byte quick_125667378_2;
byte fast_125667378_2;
byte slow_125667378_2;
byte back_125667378_2;
byte frdm_125667378_2;
bool cnsHead_125667378_2;
int speed_125667378_2;
RT_HW_FILTER_RING_AVERAGE<uint32_t,6> filterSpeed_125667378_2;
byte pin_157794672_2;
bool v1_C_157794672_2;
uint8_t ago_157794672_2=255;
RT_HW_PIN_DIR_ID id_157794672_2;
byte LedBLT_242336732_2;
byte Trig_256712857_2;
bool ok_256712857_2;
int Lcm_256712857_2;
RT_HW_STRUCT_SR04_ID dvSR04_256712857_2;
RT_HW_STRUCT_SHED_TASK shSR04_256712857_2;
RT_HW_FILTER_MEDIAN_3<uint16_t> ftrSR04_256712857_2;
byte pin_172969935_1;
bool chatBut_172969935_1;
RT_HW_PIN_DIR_ID idPinButton_172969935_1; 
RT_HW_CHAT_V8_ID idChatButton_172969935_1;
uint8_t vButton_172969935_1;
byte pin_204703115_5;
bool v1_204703115_5;
RT_HW_PIN_DIR_ID id_204703115_5;
byte pin_204703115_1;
bool v1_204703115_1;
RT_HW_PIN_DIR_ID id_204703115_1;
byte pin_204703115_2;
bool v1_204703115_2;
RT_HW_PIN_DIR_ID id_204703115_2;
byte pin_204703115_3;
bool v1_204703115_3;
RT_HW_PIN_DIR_ID id_204703115_3;
byte pin_45778680_3;
int v16_45778680_3;
int pwm_45778680_3;
RT_HW_PIN_PWM_ID idPinPWM_45778680_3; 
byte pin_45778680_1;
int v16_45778680_1;
int pwm_45778680_1;
RT_HW_PIN_PWM_ID idPinPWM_45778680_1; 
int period_61639954_1;
bool mean_61639954_1;
RT_HW_GENERATOR_EVENT_ID id_61639954_1; //--generator;
byte pin_204703115_4;
bool v1_204703115_4;
RT_HW_PIN_DIR_ID id_204703115_4;
byte pin_204703115_6;
bool v1_204703115_6;
RT_HW_PIN_DIR_ID id_204703115_6;
byte pin_204703115_8;
bool v1_204703115_8;
RT_HW_PIN_DIR_ID id_204703115_8;
byte pin_204703115_7;
bool v1_204703115_7;
RT_HW_PIN_DIR_ID id_204703115_7;
byte pin_204703115_9;
bool v1_204703115_9;
RT_HW_PIN_DIR_ID id_204703115_9;
byte adr_26633920_2;
byte i2c_lcd_26633920_2;
RT_HW_LCD44780_DEVICE_ID z_26633920_2;  
byte lcd_blink_65252357_2;
RT_HW_LCD44780_PARAM_ID id_65252357_2; 
byte lcd_263569229_6;
int v16_263569229_6;
RT_HW_LCD44780_PARAM_ID id_263569229_6; 
const char Whead_263569229_6[] PROGMEM ="~";
byte lcd_263569229_1;
int v16_263569229_1;
RT_HW_LCD44780_PARAM_ID id_263569229_1; 
const char Whead_263569229_1[] PROGMEM ="~";
byte lcd_263569229_2;
int v16_263569229_2;
RT_HW_LCD44780_PARAM_ID id_263569229_2; 
const char Whead_263569229_2[] PROGMEM ="L=";
byte lcd_159752097_2;
bool v1_159752097_2;
RT_HW_LCD44780_PARAM_ID id_159752097_2; 
byte lcd_165773337_3;
char vChar_165773337_3;
RT_HW_LCD44780_PARAM_ID id_165773337_3; 
byte lcd_165773337_1;
char vChar_165773337_1;
RT_HW_LCD44780_PARAM_ID id_165773337_1; 
byte lcd_7931312_1;
byte v8_7931312_1;
RT_HW_LCD44780_PARAM_ID id_7931312_1; 
const char Bhead_7931312_1[] PROGMEM ="~";
byte lcd_7931312_2;
byte v8_7931312_2;
RT_HW_LCD44780_PARAM_ID id_7931312_2; 
const char Bhead_7931312_2[] PROGMEM ="~";
byte lcd_7931312_3;
byte v8_7931312_3;
RT_HW_LCD44780_PARAM_ID id_7931312_3; 
const char Bhead_7931312_3[] PROGMEM ="~";
byte lcd_7931312_4;
byte v8_7931312_4;
RT_HW_LCD44780_PARAM_ID id_7931312_4; 
const char Bhead_7931312_4[] PROGMEM ="~";
byte _gtv1;
bool _gtv2;
byte _gtv3;
byte _gtv4;
byte _gtv5;
bool Out_10039442_204089172;
bool Out_249516242_204089172;
bool Out_184389009_204089172;
bool Out_243199273_204089172;
bool Out_119077874_204089172;
bool Out_129932860_204089172;
bool Out_117079429_204089172;
bool Out_52175160_204089172;
byte Out_233024936_204089172;
int Out_83718342_160004970;
bool Out_21204663_160004970;
bool Out_131441182_160004970;
bool Out_169487922_160004970;
bool Out_101211898_160004970;
int Out_190513980_160004970;
int Out_244824752_112378484;
byte Out_233024936_112378484;
byte Out_246508497_112378484;
byte Out_257291689_112378484;
char Out_191028604_112378484;
char Out_216424747_112378484;
RT_HW_STRUCT_CAR_UART_RC  id_112378484;
uint8_t dir_112378484=0;
RT_HW_STRUCT_CAR_MOTOR z_160004970;


uint16_t direct_204089172=0;
uint8_t cmd_204089172;
uint8_t speed_204089172;
uint8_t control_204089172;


void setup()
{


RT_HW_Base.shed.quick.qnt= 5 ;
RT_HW_Base.shed.fast.qnt= 4 ; 
RT_HW_Base.shed.slow.qnt= 4 ; 
RT_HW_Base.shed.back.qnt= 5 ;  
RT_HW_Base.shed.frdm.qnt= 50 ; 

LedBLT_242336732_2 =RT_HW_Base.device.pin.led; 




























}
void loop()
{







//Плата:1
RT_HW_Base.sheduler(); 
RT_HW_Base.consoleBegin();
control_125667378_2=RT_HW_Base.shed.control; 
meand500_125667378_2=RT_HW_Base.shed.blink500;
quick_125667378_2=RT_HW_Base.shed.quick.num; 
fast_125667378_2=RT_HW_Base.shed.fast.num; 
slow_125667378_2=RT_HW_Base.shed.slow.num;
back_125667378_2=RT_HW_Base.shed.back.num; 
frdm_125667378_2=RT_HW_Base.shed.frdm.num;
cnsHead_125667378_2=RT_HW_Base.console.head; 
if(RT_HW_Base.shed.eventSec){filterSpeed_125667378_2.filtered(RT_HW_Base.shed.cycle); speed_125667378_2 =round(((float)filterSpeed_125667378_2.vr)/1000);}

_gtv2 = cnsHead_125667378_2;
_gtv1 = frdm_125667378_2;
_gtv3 = fast_125667378_2;
_gtv4 = quick_125667378_2;

pin_157794672_2 = LedBLT_242336732_2;
v1_C_157794672_2 = meand500_125667378_2;
if(ago_157794672_2!=v1_C_157794672_2){ago_157794672_2=v1_C_157794672_2; RT_HW_Base.pinDigitalWrite(id_157794672_2,pin_157794672_2 ,'N',ago_157794672_2);}

//Плата:2
//Наименование:Дальномер HC-SR04
if (_gtv1 == 5) {
Trig_256712857_2 = 13;
//=======================================*HC-SR04=====================================================
if(shSR04_256712857_2.custom==0){RT_HW_Base.setTaskID(shSR04_256712857_2, 75 ,25);}        //--Настройка периодического вызова с периодом 75ms;
if(dvSR04_256712857_2.custom==0){dvSR04_256712857_2.custom=1; dvSR04_256712857_2.extPinTrig=Trig_256712857_2 ; dvSR04_256712857_2.maxLen= 450 ;} //--Настройка параметров сенсора;
dvSR04_256712857_2.run=RT_HW_Base.directTask(shSR04_256712857_2);                       //--Чтение события запуска измерения от планировщика directTask();
RT_HW_sr04.direct(dvSR04_256712857_2);                                     //--Управление сенсором;
if(dvSR04_256712857_2.state==1) {dvSR04_256712857_2.state++;  attachInterrupt(dvSR04_256712857_2.numIRQ, RT_HW_IRQ_SR04_handler_dvSR04_256712857_2,CHANGE);}
if(dvSR04_256712857_2.fresh){dvSR04_256712857_2.fresh=0; dvSR04_256712857_2.LenMcs=ftrSR04_256712857_2.filtered(dvSR04_256712857_2.echoMcs); 
                 dvSR04_256712857_2.Len=round(dvSR04_256712857_2.LenMcs * dvSR04_256712857_2.speedSoundAir/10.0) ;  if(dvSR04_256712857_2.Len>dvSR04_256712857_2.maxLen){dvSR04_256712857_2.Len=dvSR04_256712857_2.maxLen;}
                  Lcm_256712857_2 =dvSR04_256712857_2.Len;  ok_256712857_2=dvSR04_256712857_2.ok;} //--Обновление измеренных данных;

}

//Плата:3
//Наименование:Управление через UART RemoteCar
if (_gtv1 == 5) {
pin_172969935_1 = 34;
if(idPinButton_172969935_1.dir==0) {idPinButton_172969935_1.pin=pin_172969935_1; idPinButton_172969935_1.mode='U'; idChatButton_172969935_1.period=50;} //--Настройка параметров;
vButton_172969935_1=!RT_HW_Base.pinDigitalRead(idPinButton_172969935_1);           //--Чтение кнопки с подтянутым пином к Vcc;
chatBut_172969935_1=RT_HW_Base.chatterV8(idChatButton_172969935_1,vButton_172969935_1);       //--Защита от дребезга значения с кнопки;
//-----------------------------Debug car.RC---------------------------------------------------------
id_112378484.extBlock=(( (( ((Lcm_256712857_2) < (30)) && ((_gtv5) == (1)) )) || (chatBut_172969935_1) ));
if(id_112378484.custom==0){id_112378484.timeOut=1500;
id_112378484.uart=10;
id_112378484.speed=115200;
RT_HW_Base.uartSetNameBTH("ESP32S BTH v.2.1");
id_112378484.custom=1;}
RT_HW_Car.getDirectFromUART_RC(id_112378484);
Out_244824752_112378484=id_112378484.direct;
Out_233024936_112378484=id_112378484.cmd;
Out_246508497_112378484=id_112378484.speed;
Out_257291689_112378484=id_112378484.control;
Out_191028604_112378484=id_112378484.sign;
Out_216424747_112378484=id_112378484.signS;
//-------------------------------------------------------------------------------------------------
_gtv5 = Out_233024936_112378484;
}

//Плата:4
//Наименование:Управление моторами
if (_gtv1 == 7) {
z_160004970.direct=(Out_244824752_112378484);
if(z_160004970.custom==0){
z_160004970.powerSystem=RT_HW_Base.maxBitDepth(RT_HW_Base.device.depth.sys);
z_160004970.period=50;
z_160004970.powerMax=4000;
z_160004970.powerMin=2000;
if(z_160004970.powerMax>z_160004970.powerMin){z_160004970.powerDelta=z_160004970.powerMax-z_160004970.powerMin;}
else                       {z_160004970.powerDelta=z_160004970.powerMin-z_160004970.powerMax;}
z_160004970.stepStop=((uint32_t)z_160004970.powerDelta) * 40 /100;
z_160004970.stepDrive=((uint32_t)z_160004970.powerDelta) * 5 /100;
z_160004970.portionTurn=75;
z_160004970.custom=1;}
if(RT_HW_Car.directPeriod(z_160004970)){ 	            //--Периодический вызов функций;
RT_HW_Car.directMotor(z_160004970); 	     //--Управление моторами;
RT_HW_Car.directMotorOutput(z_160004970);} //--Вывод параметров;
Out_83718342_160004970=z_160004970.EnA;
Out_21204663_160004970=z_160004970.in1;
Out_131441182_160004970=z_160004970.in2;
Out_169487922_160004970=z_160004970.in3;
Out_101211898_160004970=z_160004970.in4;
Out_190513980_160004970=z_160004970.EnB;
pin_45778680_1 = 32;
v16_45778680_1 = Out_190513980_160004970;
if(idPinPWM_45778680_1.dir==0){idPinPWM_45778680_1.pin=pin_45778680_1; idPinPWM_45778680_1.channel= 0 ; idPinPWM_45778680_1.freq= 1000 ; idPinPWM_45778680_1.depth= 16 ;} //--Настройка PWM;
RT_HW_Base.pinPWM(idPinPWM_45778680_1,v16_45778680_1); //--Запись PWM;
pwm_45778680_1=idPinPWM_45778680_1.duty; //--Вывод значения;
pin_204703115_3 = 25;
v1_204703115_3 = Out_101211898_160004970;
RT_HW_Base.pinDigitalWrite(id_204703115_3,pin_204703115_3 ,'N',v1_204703115_3);
pin_204703115_1 = 33;
v1_204703115_1 = Out_169487922_160004970;
RT_HW_Base.pinDigitalWrite(id_204703115_1,pin_204703115_1 ,'N',v1_204703115_1);
pin_204703115_2 = 5;
v1_204703115_2 = Out_131441182_160004970;
RT_HW_Base.pinDigitalWrite(id_204703115_2,pin_204703115_2 ,'N',v1_204703115_2);
pin_204703115_5 = 18;
v1_204703115_5 = Out_21204663_160004970;
RT_HW_Base.pinDigitalWrite(id_204703115_5,pin_204703115_5 ,'N',v1_204703115_5);
pin_45778680_3 = 19;
v16_45778680_3 = Out_83718342_160004970;
if(idPinPWM_45778680_3.dir==0){idPinPWM_45778680_3.pin=pin_45778680_3; idPinPWM_45778680_3.channel= 0 ; idPinPWM_45778680_3.freq= 1000 ; idPinPWM_45778680_3.depth= 16 ;} //--Настройка PWM;
RT_HW_Base.pinPWM(idPinPWM_45778680_3,v16_45778680_3); //--Запись PWM;
pwm_45778680_3=idPinPWM_45778680_3.duty; //--Вывод значения;
}

//Плата:5
//Наименование:Управление индикацией и звуком
//Комментарии:Индикация и звук
if (_gtv1 == 1) {
//-------------------------car.Vector--------------------------------------------------------------
if(direct_204089172!=(Out_244824752_112378484)){
direct_204089172=(Out_244824752_112378484);
control_204089172=(direct_204089172>>8) & 0xFF;
speed_204089172=(direct_204089172>>4) & 0x0F;
cmd_204089172=(direct_204089172) & 0x0F;
Out_233024936_204089172=cmd_204089172;
Out_10039442_204089172=bitRead(control_204089172,0);
Out_249516242_204089172=bitRead(control_204089172,1);
Out_184389009_204089172=bitRead(control_204089172,2);
Out_243199273_204089172=bitRead(control_204089172,3);
Out_119077874_204089172=bitRead(control_204089172,4);
Out_129932860_204089172=bitRead(control_204089172,5);
Out_117079429_204089172=bitRead(control_204089172,6);
Out_52175160_204089172=bitRead(control_204089172,7);
}
//-------------------------------------------------------------------------------------------------
period_61639954_1 = 500;
RT_HW_Base.generatorEvent(id_61639954_1,period_61639954_1); mean_61639954_1=id_61639954_1.meander; 
UB_155925232_ubi_145242304 = ( ((Out_233024936_204089172) == (2)) || ((Out_233024936_204089172) == (5)) || ((Out_233024936_204089172) == (7)) );
UB_155925232_ubi_226131302 = !(Out_52175160_204089172);
UB_155925232_ubi_66480724 = Out_243199273_204089172;
UB_155925232_ubi_236369655 = mean_61639954_1;
UB_155925232_ubi_22624954 = Out_184389009_204089172;
_func_UB_155925232(&UB_155925232_Instance2, UB_155925232_ubi_145242304, UB_155925232_ubi_226131302, UB_155925232_ubi_66480724, UB_155925232_ubi_236369655, UB_155925232_ubi_22624954);
pin_204703115_9 = 16;
v1_204703115_9 = UB_155925232_Instance2.ubo_165148602;
RT_HW_Base.pinDigitalWrite(id_204703115_9,pin_204703115_9 ,'N',v1_204703115_9);
UB_155925232_ubi_145242304 = ( ((Out_233024936_204089172) == (2)) || ((Out_233024936_204089172) == (5)) || ((Out_233024936_204089172) == (7)) );
UB_155925232_ubi_226131302 = Out_119077874_204089172;
UB_155925232_ubi_66480724 = Out_243199273_204089172;
UB_155925232_ubi_236369655 = mean_61639954_1;
UB_155925232_ubi_22624954 = Out_249516242_204089172;
_func_UB_155925232(&UB_155925232_Instance4, UB_155925232_ubi_145242304, UB_155925232_ubi_226131302, UB_155925232_ubi_66480724, UB_155925232_ubi_236369655, UB_155925232_ubi_22624954);
pin_204703115_8 = 27;
v1_204703115_8 = UB_155925232_Instance4.ubo_165148602;
RT_HW_Base.pinDigitalWrite(id_204703115_8,pin_204703115_8 ,'N',v1_204703115_8);
UB_155925232_ubi_145242304 = ( ((Out_233024936_204089172) == (4)) || ((Out_233024936_204089172) == (6)) || ((Out_233024936_204089172) == (8)) );
UB_155925232_ubi_226131302 = 0;
UB_155925232_ubi_66480724 = Out_243199273_204089172;
UB_155925232_ubi_236369655 = mean_61639954_1;
UB_155925232_ubi_22624954 = Out_184389009_204089172;
_func_UB_155925232(&UB_155925232_Instance1, UB_155925232_ubi_145242304, UB_155925232_ubi_226131302, UB_155925232_ubi_66480724, UB_155925232_ubi_236369655, UB_155925232_ubi_22624954);
pin_204703115_7 = 4;
v1_204703115_7 = UB_155925232_Instance1.ubo_165148602;
RT_HW_Base.pinDigitalWrite(id_204703115_7,pin_204703115_7 ,'N',v1_204703115_7);
UB_155925232_ubi_145242304 = ( ((Out_233024936_204089172) == (4)) || ((Out_233024936_204089172) == (6)) || ((Out_233024936_204089172) == (8)) );
UB_155925232_ubi_226131302 = Out_119077874_204089172;
UB_155925232_ubi_66480724 = Out_243199273_204089172;
UB_155925232_ubi_236369655 = mean_61639954_1;
UB_155925232_ubi_22624954 = Out_249516242_204089172;
_func_UB_155925232(&UB_155925232_Instance3, UB_155925232_ubi_145242304, UB_155925232_ubi_226131302, UB_155925232_ubi_66480724, UB_155925232_ubi_236369655, UB_155925232_ubi_22624954);
pin_204703115_6 = 14;
v1_204703115_6 = UB_155925232_Instance3.ubo_165148602;
RT_HW_Base.pinDigitalWrite(id_204703115_6,pin_204703115_6 ,'N',v1_204703115_6);
UB_155925232_ubi_145242304 = Out_10039442_204089172;
UB_155925232_ubi_226131302 = 0;
UB_155925232_ubi_66480724 = 0;
UB_155925232_ubi_236369655 = mean_61639954_1;
UB_155925232_ubi_22624954 = Out_10039442_204089172;
_func_UB_155925232(&UB_155925232_Instance8, UB_155925232_ubi_145242304, UB_155925232_ubi_226131302, UB_155925232_ubi_66480724, UB_155925232_ubi_236369655, UB_155925232_ubi_22624954);
pin_204703115_4 = 26;
v1_204703115_4 = UB_155925232_Instance8.ubo_165148602;
RT_HW_Base.pinDigitalWrite(id_204703115_4,pin_204703115_4 ,'N',v1_204703115_4);
}

//Плата:6
//Наименование:Lcd
if (_gtv1 == 10) {
adr_26633920_2 = 63;
//=================================Lcd HD44780.direct=============================================
if(z_26633920_2.custom==0){RT_HW_lcd44780.initDeviceI2CPCF8574(z_26633920_2, 16 , 2 , adr_26633920_2 , 0, 400000 );  z_26633920_2.periodReboot= 10; } 
RT_HW_lcd44780.directDevice(z_26633920_2);  i2c_lcd_26633920_2=z_26633920_2.num;
lcd_blink_65252357_2 = i2c_lcd_26633920_2;
if(id_65252357_2.custom==0){RT_HW_lcd44780.initBlinkID (id_65252357_2, lcd_blink_65252357_2 , 500 ,  1 , 1 );} RT_HW_lcd44780.LcdBlink(id_65252357_2, ' ' , '*' ); 

lcd_263569229_1 = i2c_lcd_26633920_2;
v16_263569229_1 = speed_125667378_2;
if(id_263569229_1.custom==0)  {RT_HW_lcd44780.initWordID  (id_263569229_1, lcd_263569229_1 , 'U'  ,  'R'  ,  '~'  , 14 , 1 , 0 );} RT_HW_lcd44780.LcdVar(id_263569229_1, Whead_263569229_1,v16_263569229_1);  

lcd_263569229_6 = i2c_lcd_26633920_2;
v16_263569229_6 = Out_244824752_112378484;
if(id_263569229_6.custom==0)  {RT_HW_lcd44780.initWordID  (id_263569229_6, lcd_263569229_6 , 'H'  ,  '~'  ,  '~'  , 10 , 1 , 4 );} RT_HW_lcd44780.LcdVar(id_263569229_6, Whead_263569229_6,v16_263569229_6);  

lcd_165773337_3 = i2c_lcd_26633920_2;
vChar_165773337_3 = Out_191028604_112378484;
if(id_165773337_3.custom==0)  {RT_HW_lcd44780.initCharID (id_165773337_3,lcd_165773337_3 , 2 , 1);} RT_HW_lcd44780.LcdChar(id_165773337_3, vChar_165773337_3); //--Вывод символа;
lcd_165773337_1 = i2c_lcd_26633920_2;
vChar_165773337_1 = Out_216424747_112378484;
if(id_165773337_1.custom==0)  {RT_HW_lcd44780.initCharID (id_165773337_1,lcd_165773337_1 , 3 , 1);} RT_HW_lcd44780.LcdChar(id_165773337_1, vChar_165773337_1); //--Вывод символа;
lcd_7931312_3 = i2c_lcd_26633920_2;
v8_7931312_3 = Out_257291689_112378484;
if(id_7931312_3.custom==0)  {RT_HW_lcd44780.initByteID (id_7931312_3,lcd_7931312_3 , 'H' , 'L' , '~' , 4 , 1 , 2 );} RT_HW_lcd44780.LcdVar(id_7931312_3, Bhead_7931312_3, v8_7931312_3 );

lcd_7931312_2 = i2c_lcd_26633920_2;
v8_7931312_2 = Out_246508497_112378484;
if(id_7931312_2.custom==0)  {RT_HW_lcd44780.initByteID (id_7931312_2,lcd_7931312_2 , 'H' , 'L' , '~' , 7 , 1 , 1 );} RT_HW_lcd44780.LcdVar(id_7931312_2, Bhead_7931312_2, v8_7931312_2 );

lcd_7931312_1 = i2c_lcd_26633920_2;
v8_7931312_1 = Out_233024936_112378484;
if(id_7931312_1.custom==0)  {RT_HW_lcd44780.initByteID (id_7931312_1,lcd_7931312_1 , 'H' , 'L' , '~' , 8 , 1 , 1 );} RT_HW_lcd44780.LcdVar(id_7931312_1, Bhead_7931312_1, v8_7931312_1 );

lcd_7931312_4 = i2c_lcd_26633920_2;
v8_7931312_4 = Out_257291689_112378484;
if(id_7931312_4.custom==0)  {RT_HW_lcd44780.initByteID (id_7931312_4,lcd_7931312_4 , '#' , 'L' , '~' , 9 , 2 , 0 );} RT_HW_lcd44780.LcdVar(id_7931312_4, Bhead_7931312_4, v8_7931312_4 );

lcd_263569229_2 = i2c_lcd_26633920_2;
v16_263569229_2 = Lcm_256712857_2;
if(id_263569229_2.custom==0)  {RT_HW_lcd44780.initWordID  (id_263569229_2, lcd_263569229_2 , 'U'  ,  'L'  ,  ';'  , 2 , 2 , 6 );} RT_HW_lcd44780.LcdVar(id_263569229_2, Whead_263569229_2,v16_263569229_2);  

lcd_159752097_2 = i2c_lcd_26633920_2;
v1_159752097_2 = ok_256712857_2;
if(id_159752097_2.custom==0)  {RT_HW_lcd44780.initBitID(id_159752097_2, lcd_159752097_2, 1 , 2 );} RT_HW_lcd44780.LcdBit (id_159752097_2, v1_159752097_2 , '-' , '+' );
}







}

RT_HW_IRAM_ATTR void RT_HW_IRQ_SR04_handler_dvSR04_256712857_2()
{
  if(dvSR04_256712857_2.state==2) {if( RT_HW_PIN_DIR_READ(dvSR04_256712857_2.ddPin)){dvSR04_256712857_2.timeBegin=micros(); dvSR04_256712857_2.state=3;}}
  if(dvSR04_256712857_2.state==3) {if(!RT_HW_PIN_DIR_READ(dvSR04_256712857_2.ddPin)){dvSR04_256712857_2.timeEnd  =micros(); dvSR04_256712857_2.state=4;}}

}


void _func_UB_155925232(struct UB_155925232 *_ubInstans, bool ubi_145242304, bool ubi_226131302, bool ubi_66480724, bool ubi_236369655, bool ubi_22624954)
{
bool ubo_165148602 = _ubInstans->ubo_165148602;
ubo_165148602 = ( (( (( (ubi_145242304) || (ubi_226131302) || (ubi_66480724) )) && (ubi_236369655) )) || (( (!(( (ubi_145242304) || (ubi_226131302) || (ubi_66480724) ))) && (ubi_22624954) )) );
_ubInstans->ubo_165148602 = ubo_165148602;

}
