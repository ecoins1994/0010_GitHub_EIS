
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 									1.GENERAL FUNCTIONS
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define RT_HW_PERMIT_QUICK_PIN		//--Permit working with quick pins;
//=================================================================================================
//									1.1.General Functions
//=================================================================================================
bool checkPinDIN(uint8_t pin){return checkPinPGM(RT_HW_PGM_PIN_DIN_ID,pin);};	//--Check pin for discret input;
bool checkPinADC(uint8_t pin){return checkPinPGM(RT_HW_PGM_PIN_ADC_ID,pin);};	//--Check pin for analog  input;
bool checkPinTCH(uint8_t pin){return checkPinPGM(RT_HW_PGM_PIN_TCH_ID,pin);};	//--Check pin for touch   input;
bool checkPinDOT(uint8_t pin){return checkPinPGM(RT_HW_PGM_PIN_DOT_ID,pin);};	//--Check pin for discret output;
bool checkPinPWM(uint8_t pin){return checkPinPGM(RT_HW_PGM_PIN_PWM_ID,pin);};	//--Check pin for PWM     output;
bool checkPinDAC(uint8_t pin){return checkPinPGM(RT_HW_PGM_PIN_DAC_ID,pin);};	//--Check pin for DAC     output;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 									2.QUICK FUNCTIONS INPUT/OUTPUT
//									  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									2.1.Discret input
// mode: U->discret input pullup +Vcc; D->input pulldown GND; I || F->input (floating entrance);
//=================================================================================================
bool pinDigitalRead(RT_HW_PIN_DIR_ID &id, uint8_t pin, char mode='I'){
//-------------------------------------------------------------------------------------------------
if(id.dir==0){if(!checkPinDIN(pin)){id.dir=50; return 0;} 	//--Check pin for digital input;  
RT_HW_PIN_DIR_SET_ID(id,pin); id.mode=mode;					//--Save pin,mode;
//---------------------------
#if defined(RT_HW_CORE_STM32) || defined(RT_HW_CORE_ESP32)
     if(id.mode=='U') {pinMode(id.pin, INPUT_PULLUP);}		//--Init as discret input pulldown GND;
else if(id.mode=='D') {pinMode(id.pin, INPUT_PULLDOWN);}	//--Init as discret input pulldown GND;
else 				  {pinMode(id.pin, INPUT);}				//--Init as discret input;
//---------------------------
#else
id.pin=pin; id.mode=mode;									//--Save pin,mode;
if(id.mode=='U')      {pinMode(id.pin, INPUT_PULLUP);}		//--Init as discret input pulldown GND;
else 			      {pinMode(id.pin, INPUT);}				//--Init as discret input;
#endif
//---------------------------
id.dir=1;}
//-------------------------------------------------------------------------------------------------
if(id.dir==1){
#if defined(RT_HW_PERMIT_QUICK_PIN)
return RT_HW_PIN_DIR_READ(id);								//--Quick   read discret pin; 
#else
return digitalRead(id.pin);									//--Arduino read discret pin;
#endif
}
//-------------------------------------------------------------------------------------------------
return 0;};
//=================================================================================================
//									2.2.Discret input chatter
//=================================================================================================
bool chatterDIN(RT_HW_CHATTER_DIN &id, uint8_t var, uint16_t period){
if(id.dir==0) {if(id.ago!=var){id.timeBegin=RT_HW_MILLIS; id.dir++;}               return id.ago;}
if(id.dir==1) {if((getPastMs  (id.timeBegin)< period) && (id.ago==var)) {id.dir=0; return id.ago;} 
			   if( getPastMs  (id.timeBegin)> period)    {id.ago=var;	 id.dir=0; return id.ago;}}
																				   return id.ago;};
//=================================================================================================
//									2.3.Discret output
// mode: N->normal output; O->open collector;
//=================================================================================================
void pinDigitalWrite(RT_HW_PIN_DIR_ID &id, uint8_t pin, uint8_t var, char mode='N'){
//-------------------------------------------------------------------------------------------------
if(id.dir==0){if(!checkPinDOT(pin)){id.dir=50; return;} 	//--Проверка допустимости номера пина;  
RT_HW_PIN_DIR_SET_ID(id,pin); id.mode=mode;					//--Save pin,mode;
RT_HW_PIN_DIR_WRITE(id,var);



//---------------------------
#if defined(RT_HW_CORE_STM32) || defined(RT_HW_CORE_ESP32)
     if(id.mode=='N') {pinMode(pin, OUTPUT);}				//--Init as discret output;
else 				  {pinMode(pin, OUTPUT_OPEN_DRAIN);}	//--Init as discret output open collector;
//---------------------------
#else
					   pinMode(pin, OUTPUT);				//--Init as discret output;
#endif
id.dir=1;}
//-------------------------------------------------------------------------------------------------
if(id.dir==1) {
#if defined(RT_HW_PERMIT_QUICK_PIN)
RT_HW_PIN_DIR_WRITE(id,var);								//--Quick   output discret pin; 
#else
return digitalWrite(id.pin,var);							//--Arduino output discret pin;
#endif
}
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 									3.FUNCTIONS INPUT
//									  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									3.1.Analog input
//struct RT_HW_PIN_ADC_ID{
//	uint8_t  dir=0;				//--Stage number in the executive function;  
//	uint8_t  pin=255;			//--Pin number;
//	uint16_t adcVar,adcMax;		//--Internal variables;
//	uint16_t vPin;				//--Pin value[analogRead(pin)];
//	uint16_t vFltr;	    		//--vPin with measurement drift filter(device.depth.drift) and zero drift(device.depth.vNull); 
//	uint16_t vNorm;				//--vFltr with normalization of the value to the system SYS with bit depth=device.depth.sys; 
//  };
//=================================================================================================
void pinAnalogRead(RT_HW_PIN_ADC_ID &id, uint8_t pin){
(void)pin; 
//-------------------------------------------------------------------------------------------------
if(id.dir==0){if(!checkPinADC(pin)){id.dir=50; return;} 	//--Check pin for analog input;  
id.pin=pin;													//--Save pin;
id.adcMax=maxBitDepth(device.depth.adc);					//--Get max value;
#if defined(RT_HW_CORE_STM32)
pinMode(pin, INPUT_ANALOG);									//--Init as analog input for STM32;
#else
pinMode(pin, INPUT);										//--Init as analog input for other MCU;
#endif
id.dir=1;}
//-------------------------------------------------------------------------------------------------
if(id.dir==1){
id.vPin=analogRead(id.pin);
#if defined(RT_HW_BOARD_ESP32C3_DEV)
if(id.pin==0){id.vPin=(uint32_t)id.vPin*3300/1000;}	//--This controller has a resistor divider on pin 0;
#endif	
if(id.vPin>id.adcVar){if((id.vPin-id.adcVar)>device.depth.adcDrift){id.adcVar=id.vPin;}}
if(id.vPin<id.adcVar){if((id.adcVar-id.vPin)>device.depth.adcDrift){id.adcVar=id.vPin;}}
if(id.adcVar>id.adcMax){id.adcVar=id.adcMax;}
if(id.adcVar<device.depth.adcNull){id.adcVar=0;}
id.vNorm=normADC(id.adcVar);}
};
//=================================================================================================
//									3.2.Touch input [ESP32]
//=================================================================================================
void pinTouchRead(RT_HW_PIN_TCH_ID &id, uint8_t pin){	
(void)pin;
if(id.dir==0){if(!checkPinTCH(id.pin)){id.dir=50; return;} 		//--Check pin for touch input; 
id.pin=pin;	 													//--Save  pin;
id.dir=1;}
//-------------------------------------------------------------------------------------------------
if(id.dir==1){
#if defined(RT_HW_CORE_ESP32) && defined(RT_HW_PERMIT_TOUCH)	
id.vPin=touchRead(id.pin); id.vNorm=id.vNorm; return; 
#endif	
id.vPin=id.vNorm=0;}
};
//=================================================================================================
//									3.3.Hall sensor reading[ESP32]
//=================================================================================================
void pinReadHALL(RT_HW_PIN_HALL_ID &id){	
#if  defined(RT_HW_CORE_ESP32) && defined(RT_HW_PERMIT_HALL)
id.vPin=hallRead();
id.vNorm=map(id.vPin,-128,127,0,maxBitDepth(device.depth.sys));	return;
#endif
id.vPin=id.vNorm=0;	
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 										4.FUNCTIONS OUTPUT
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//											4.1.PWM
//struct RT_HW_PIN_PWM_ID{
//	uint8_t  dir=0;				//--Stage number in the executive function; 
//	uint8_t  pin=255;			//--Pin number;
//	uint8_t  channel=255;		//--Channel number[ESP32]
//	uint8_t  depth=255;			//--Bit depth PWM[ESP32]. If=255 then depth=device.depth.pwm;
//	uint16_t freq=1000;			//--Frequency;
//	char     mode='N';			//--Output type (N-normal, O-open collector);
//	uint8_t  idx;				//--Working index;
//	uint32_t var;				//--External direct;
//	uint16_t duration;			//--The value of the PWM pulse normalized to depth;
//	uint16_t duty;				//--The value written to the pin (taking into account the PWM bit depth);
// }
//=================================================================================================
//-------------------------------------------------------------------------------------------------
void pinPWM(RT_HW_PIN_PWM_ID &id, uint8_t pin, uint16_t var){
(void)pin; (void)var; 
//-------------------------------------------------------------------------------------------------
if(id.dir==0){if(!checkPinPWM(pin)){id.dir=50; return;} 		//--Check pin for discret output; 
id.pin=pin;	 													//--Save  pin;
//-----------------------------------------------
#if defined(RT_HW_CORE_STM32)
if(id.mode=='O'){pinMode(id.pin,OUTPUT_OPEN_DRAIN);}			//--Init as output with open collector for STM32;
else            {pinMode(id.pin,OUTPUT);}						//--Init as output for STM32;
#endif
//-----------------------------------------------
#if defined(RT_HW_CORE_ESP32) 
pinMode(id.pin,OUTPUT); 										//--Init as discret output for ESP32;
if(id.depth==255){id.depth=device.depth.pwm;} 					//--Init bit depth as default;
if(id.depth>16)  {id.depth=16;}				  					//--Bit depth limitation;
#if defined(RT_HW_CORE_ESP32C3)
if(id.depth>14)  {id.depth=14;}				  					//--Bit depth limitation for ESP32C3;
#endif	
if(id.channel==255){for(id.idx=0; id.idx<RT_HW_MAX_NUM_CHANNEL; id.idx++){	//--Free channel selection;
                    if(!bitRead(device.pwm.channel,id.idx)){bitSet(device.pwm.channel,id.idx); 
					id.channel=id.idx; break;}}}
ledcSetup(id.channel,id.freq,id.depth);							//--Init channel: freq, bit depth;
ledcAttachPin(id.pin,id.channel);								//--Binding a pin to a channel number;	
#endif
//-----------------------------------------------
#if !defined(RT_HW_CORE_STM32) && !defined(RT_HW_CORE_ESP32) 
if(id.depth==255){id.depth=device.depth.pwm;} 					//--Init bit depth as default;
pinMode(id.pin,OUTPUT);											//--Init as output for other MCU;											
#endif
//-----------------------------------------------
id.dir=1;} 
//-------------------------------------------------------------------------------------------------
if(id.dir==1){
#if defined(RT_HW_CORE_STM32) 
id.var=normPWM(var); analogWrite(id.pin,id.var); return;		//--PWM output STM32;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP32) 
//ledcChangeFrequency(id.channel,id.freq,id.depth); 
id.var=var;
id.duration=id.var;												//--Save duration variable; 
id.duty=normDepth(id.duration,id.depth); 						//--Save duty mcs; 
ledcWrite(id.channel,id.duty); 									//--Output PWM ESP32;		
return;
#endif
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HW_CORE_STM32) && !defined(RT_HW_CORE_ESP32) 
id.var=normPWM(var); analogWrite(id.pin,id.var); return;
#endif
}
//-------------------------------------------------------------------------------------------------
id.var=var; //--For blocking warnings from C++;
};

//=================================================================================================
//											4.2.FREQ ESP32
//struct RT_HW_PIN_PWM_ID{
//	uint8_t  dir=0;				//--Stage number in the executive function; 
//	uint8_t  pin=255;			//--Pin number;
//	uint8_t  channel=255;		//--Channel number[ESP32]
//	uint8_t  depth=255;			//--Bit depth PWM[ESP32]. If=255 then depth=device.depth.pwm;
//	uint16_t freq=1000;			//--Frequency;
//	char     mode='N';			//--Output type (N-normal, O-open collector);
//	uint8_t  idx;				//--Working index;
//	uint32_t var;				//--External direct;
//	uint16_t duration;			//--The value of the PWM pulse normalized to depth;
//	uint16_t duty;				//--The value written to the pin (taking into account the PWM bit depth);
// }
//=================================================================================================
void pinFreq(RT_HW_PIN_PWM_ID &id, uint8_t pin, uint16_t freq, uint8_t var){
(void)pin; (void)var; (void)freq;
//-------------------------------------------------------------------------------------------------
if(id.dir==0){
if(!checkPinPWM(pin)){id.dir=50; return;} 		           		//--Check pin for discret output; 
id.pin=pin; pinMode(id.pin,OUTPUT); 							//--Init pin via pinMode();
//---------------------------------------------------------
#if defined(RT_HW_CORE_ESP32) 
//---------------------------------------------------------
if(id.depth==255){id.depth=device.depth.pwm;} 					//--Init bit depth as default;
if(id.depth>16)  {id.depth=16;}				  					//--Bit depth limitation;
#if defined(RT_HW_CORE_ESP32C3)
if(id.depth>14)  {id.depth=14;}				  					//--Bit depth limitation for ESP32C3;
#endif	
if(id.channel==255){for(id.idx=0; id.idx<RT_HW_MAX_NUM_CHANNEL; id.idx++){	//--Free channel selection;
                    if(!bitRead(device.pwm.channel,id.idx)){bitSet(device.pwm.channel,id.idx); 
					id.channel=id.idx; break;}}}
ledcSetup(id.channel,id.freq,id.depth);							//--Init channel: freq, bit depth;
ledcAttachPin(id.pin,id.channel);								//--Binding a pin to a channel number;	
//---------------------------------------------------------
#endif
id.dir=2;}  
//-------------------------------------------------------------------------------------------------
if(id.dir==1){
if((id.freq!=freq) || (id.var!=var)){id.dir=2;}
id.dir=2;
}
//-------------------------------------------------------------------------------------------------
if(id.dir==2){
#if defined(RT_HW_CORE_ESP32) 
//---------------------------------------------------------
if(id.freq!=freq){id.freq=freq;
//ledcChangeFrequency(id.channel,id.freq,id.depth); 
}
id.var=var;
id.duration=id.var;												//--Save duration variable; 
id.duty=normDepth(id.duration,id.depth); 						//--Save duty mcs; 
ledcWrite(id.channel,id.duty); 									//--Output PWM ESP32;		
id.dir=1; return;
#else
id.freq=freq; id.var=var;	
#endif
}
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//											4.4.DAC
//=================================================================================================
void pinDAC(RT_HW_PIN_DAC_ID &id, uint8_t pin, uint16_t var){
(void)pin; (void)var; 
//------------------------------------------------------------------------
if(id.dir==0){if(!checkPinDAC(pin)){id.dir=50; return;} 		//--Check pin for DAC;  
id.pin=pin;	 													//--Save pin,mode;
id.dir=1;} 				   
//-----------------------------------------------
if(id.dir==1) {
#if defined(RT_HW_PERMIT_DAC) && defined(RT_HW_CORE_ESP32) 	
	id.vPin=normDAC(var); dacWrite(id.pin,id.vPin);	return;
#endif
//-----------------------------------------------
#if defined(RT_HW_PERMIT_DAC) && defined(RT_HW_CORE_STM32)	 
 	id.vPin=normDAC(var); analogWrite(id.pin,id.vPin); return;
#endif
//-----------------------------------------------
if(var) {return;} //--For blocking warnings from C++;
}  //--END if (id.dir==1)
//=============================================================================
};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 										5.SERVO CONTROL
//-------------------------------------------------------------------------------------------------
//struct RT_HW_PIN_SERVO_ID{
//	uint8_t  dir=0;				//--Stage number in the executive function; 
//	uint8_t  pin=255;			//--Pin number;
//	uint8_t  channel=4;			//--Channel number[ESP32]
//	uint8_t  depth=16;			//--Bit depthESP32];
//	uint16_t freq=50;			//--Frequency;
//	uint16_t maxAngle=180;		//--The maximum angle of rotation (-360,+360);
//	uint16_t minWidth=800;		//--Minimum pulse width(mcs);   
//	uint16_t maxWidth=2300;		//--Maximum pulse width(mcs);  
//	uint16_t maxDepth=0xFFFF;   //--Maximum value for the selected bit depth;
//	uint16_t period=20000;		//--Period of control pulses(calculated variable=1000000/freq); 
//-------------------------------
//	uint8_t  idx;				//--Working index;
//	uint16_t var;				//--External pulse duration setting;
//	uint16_t duration;			//--Estimated pulse duration;
//	uint16_t duty;				//--The value written to the device (taking into account the PWM bit depth);
//};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									5.1.SET DEFAULT FOR SERVO
//=================================================================================================
//void pinServoSet_MG90S(RT_HW_PIN_SERVO_ID &id){id.freq=50; id.minWidth=650; id.maxWidth=2300;}
void pinServoSet_MG90S (RT_HW_PIN_SERVO_ID &id){id.freq=50; id.minWidth=650; id.maxWidth=2200; id.maxAngle=180;}
void pinServoSet_MG996R(RT_HW_PIN_SERVO_ID &id){id.freq=50; id.minWidth=650; id.maxWidth=2200; id.maxAngle=180;}
//=================================================================================================
//									5.2.Нормализация значения ширины управляющего импульса(mcs)
//=================================================================================================
uint16_t pinServoNormSYS  (RT_HW_PIN_SERVO_ID &id, uint16_t var){return map(var,0,((1<<device.depth.sys)-1),id.minWidth,id.maxWidth);}
//=================================================================================================
//									5.3.Нормализация угла поворота
//=================================================================================================
int16_t  pinServoNormAngle(RT_HW_PIN_SERVO_ID &id, uint16_t var){return map(var,0,id.maxAngle,id.minWidth,id.maxWidth);}
//=================================================================================================
//									5.3.УПРАВЛЕНИЕ СЕРВО
//=================================================================================================
void pinServo(RT_HW_PIN_SERVO_ID &id, uint8_t pin, uint16_t var){
(void)id; (void)pin; (void)var; 	//--Для устранения предупреждений от C++;
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP32)
//-------------------------------------------------------------------------------------------------
//									5.3.0.1Проверка допустимости и настройка пина ESP32
//-------------------------------------------------------------------------------------------------
if(id.dir==0){
if(!checkPinPWM(pin)){id.dir=50; return;} 					//--Проверка допустимости номера пина; 	
id.pin=pin;	 												//--Сохранение номера пина;
pinMode(id.pin,RT_HW_PIN_MODE_OUTPUT);						//--Настройка пина на вывод;   
//-------------------------------------------------------------------------------------------------
//									5.3.0.1.Настройка рарядности пина ESP32
//-------------------------------------------------------------------------------------------------
if(id.depth==255){id.depth=device.depth.pwm;} 				//--Установка используемой разрядности шины (ESP32);
if(id.depth>16)  {id.depth=16;}				  				//--Ограничение разрядности;
#if defined(RT_HW_CORE_ESP32C3)
	if(id.depth>14)  {id.depth=14;}				  			//--Ограничение разрядности для ESP32C3;
#endif
//-------------------------------------------------------------------------------------------------
//									5.3.0.2.Выбор номера канала PWM (ESP32)
//-------------------------------------------------------------------------------------------------
if(id.channel==255){for(id.idx=0; id.idx<RT_HW_MAX_NUM_CHANNEL; id.idx++){	//--Выбор свободного канала;
                    if(!bitRead(device.pwm.channel,id.idx)){bitSet(device.pwm.channel,id.idx); id.channel=id.idx; break;}}}
if(id.channel==255){id.dir=51; return;} 					//--Выход по ошибке "Нет свободного канала;
//-------------------------------------------------------------------------------------------------
//									5.3.0.3.Настройка канала PWM (ESP32)
//-------------------------------------------------------------------------------------------------
if(id.freq<40){id.freq=40;} if(id.freq>100){id.freq=100;} 	//--Нормализация частоты;
id.period=1000000UL/id.freq;								//--Расчет периода вывода импульсов;
id.maxDepth=((1 << id.depth) - 1);							//--Расчет максимального значения для выбранной разрядности;
ledcSetup(id.channel,id.freq,id.depth);						//--Настройка канала id.channel: частота и разрешение;
ledcAttachPin(id.pin,id.channel);							//--Привязка пина к номеру канала;
id.dir=1;}
//-------------------------------------------------------------------------------------------------
//									5.3.1.1.Вывод на серво(ESP32)
//-------------------------------------------------------------------------------------------------
if(id.dir==1){ 
id.duration=id.var; 
if(id.duration<id.minWidth){id.duration=id.minWidth;} 		//--Ограничение импульса снизу;
if(id.duration>id.maxWidth){id.duration=id.maxWidth;}		//--Ограничение импульса сверху;
id.duty=map(id.duration,0,id.period,0,id.maxDepth);			//--Расчет длительности с учетом разрядности depth;
ledcWrite(id.channel,id.duty);
return;}	
//-------------------------------------------------------------------------------------------------
#endif	//--END if defined(RT_HW_CORE_ESP32)
//-------------------------------------------------------------------------------------------------
};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							ФУНКЦИИ ЗАПИСИ-ЧТЕНИЯ ПИНОВ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//bool changeProtectPinDI(RT_HW_CHANGE_PINDI_ID &id, uint8_t timeChange, uint8_t val){//==Защита от дребезга значения на пине DI;
//if(id.dir==0) {if(id.ago!=val) {id.time=RT_HW_MILLIS; id.dir++;}                       return id.ago;}
//if(id.dir==1) {if((getPastMs(id.time)< (timeChange)) && (id.ago==val))  	{id.dir=0; return id.ago;} 
//				if( getPastMs(id.time)>= timeChange)     {id.ago=val;		 id.dir=0; return id.ago;}}
//																					   return id.ago;};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
