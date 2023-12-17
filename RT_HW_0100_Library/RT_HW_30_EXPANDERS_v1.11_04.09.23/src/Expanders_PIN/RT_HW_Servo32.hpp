/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010, LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

 /*
 * Arduino srl - www.arduino.org
 * Base on lib for stm32f4 (d2a4a47): https://github.com/arduino-libraries/Servo/blob/master/src/stm32f4/ServoTimers.h
 * 2017 Jul 5: Edited by Jaroslav Páral (jarekparal) - paral@robotikabrno.cz
 */
/*
struct RT_HW_STRUCT_SERVO{
RT_HW_PIN_DIR_ID dvPin;
//RT_HW_PIN_PWM_ID dvPWM;
uint8_t  dir=0;
uint8_t  pin=255;				//--Номер пина;
uint8_t  channel=0;				//--Номер канала;
uint16_t freq=50;				//--Частота;
uint8_t  depth=16;				//--Разрядность PWM (ESP32);
//---------------------------------------------------------
uint8_t  state=0;				//--Состояние:0-не инициал., 1-подключен к пину; 9-подюключение заблокировано;
uint8_t  codeErr=0;				//--Код ошибки(=1 пин не инициализирован);
//---------------------------------------------------------
int16_t  minAngle=0;			//--Минимальный  угол поворота(град.);
int16_t  maxAngle=180; 			//--Максимальный угол поворота(град.);
uint16_t minWidthPulse=544; 	//--Минимальная  ширина импульса(mcs);    
uint16_t maxWidthPulse=2500; 	//--Максимальная ширина импульса(mcs);   
uint16_t maxCompare=0xFFFF; 	//-- 
//---------------------------------------------------------
uint8_t  bu8;					//
uint8_t  outServo;				//--Выходной сигнал;
};
    static const int MIN_ANGLE = 0;
    static const int MAX_ANGLE = 180;
    
    static const int MIN_PULSE_WIDTH = 544;     // the shortest pulse sent to a servo
    static const int MAX_PULSE_WIDTH = 2400;     // the longest pulse sent to a servo
    static const int MAX_COMPARE = ((1 << 16) - 1); // 65535
    
    static const int TAU_MSEC = 20;
    static const int TAU_USEC = (TAU_MSEC * 1000);

    static const int CHANNEL_MAX_NUM = 16;

*/

#pragma once
#include "RT_HW_BASE.h"
//============
class Servo32 {
//
//int usToDuty(RT_HW_STRUCT_SERVO &id, int us)   {return map(us, 0, TAU_USEC, 0, MAX_COMPARE); }
//int dutyToUs(RT_HW_STRUCT_SERVO &id, int duty) {return map(duty, 0, MAX_COMPARE, 0, TAU_USEC); }
//int usToAngle(int us)   { return map(us, _minPulseWidth, _maxPulseWidth, _minAngle, _maxAngle); }
//int angleToUs(RT_HW_STRUCT_SERVO &id, int angle){ return map(angle, _minAngle, _maxAngle, _minPulseWidth, _maxPulseWidth); }


//-------------------------------------------------------------------------------------------------
uint8_t attach(RT_HW_STRUCT_SERVO &id, uint8_t pin, uint8_t channel) {
if(id.state!=0){return 0;}
id.pin=pin; id.channel=channel;
if(!checkPinPGM(RT_HW_PGM_PIN_PWM_ID,id.pin))   {id.codeErr=50; return 0;}	//--Проверка на допустимость PWM;     
id.state=1;
id.periodServo=1000000UL/id.freq;			//--Расчет длительности импульса;
ledcSetup(id.channel,id.freq,id.depth); 	//--Установк параметров;
ledcAttachPin(_pin, _channel);
return 1;};
//------------------------------------------------------------------------------------------------
uint8_t detach(RT_HW_STRUCT_SERVO &id) {if(id.state==1){ledcDetachPin(id.pin); id.state=0; return 1;} return 0;}
//------------------------------------------------------------------------------------------------
void    write(RT_HW_STRUCT_SERVO &id, int angle) {
	id.angle = constrain(angle, id.minAngle, id.maxAngle); 
	id.duration=map(angle, id.minAngle, id.maxAngle, id.minPulseWidth, id.maxPulseWidth);
	ledcWrite(id.channel,id.durations);
};

void writeMicroseconds(int pulseUs) {if (!attached()) {return;}
     id.duration=constrain(pulseUs, id.minPulseWidth, id.maxPulseWidth);
     ledcWrite(id.channel,id.durations);
};

};