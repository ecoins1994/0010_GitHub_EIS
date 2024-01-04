//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//					1.STRUCTURES FOR INPUT WITH PINS, HALL SENSOR
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================
//								1.1. DI(discrete input)
//  RT_HW_PIN_DIR_ID - defined in the kernel description;
//=================================================================================================
//=================================================================================================
//								1.2.ADC(analogue input)
//================================================================================================= 
struct RT_HW_PIN_ADC_ID{
uint8_t  dir=0;				//--Stage number in the executive function;  
uint8_t  pin=255;			//--Pin number;
uint16_t adcVar,adcMax;		//--Internal variables;
uint16_t vPin;				//--Pin value[analogRead(pin)];
uint16_t vFltr;	    		//--vPin with measurement drift filter(device.depth.drift) and zero drift(device.depth.vNull); 
uint16_t vNorm;				//--vFltr with normalization of the value to the system SYS with bit depth=device.depth.sys; 
};
//=================================================================================================
//								1.3.TCH(touch input)[ESP32]
//================================================================================================= 
struct RT_HW_PIN_TCH_ID{
uint8_t  dir=0;				//--Stage number in the executive function;  
uint8_t  pin=255;			//--Pin number;
uint16_t vPin;	    		//--Pin value[touchRead(pin)]; 
uint16_t vNorm;				//--vPin with normalization of the value to the system SYS with bit depth=device.depth.sys;
};
//=================================================================================================
//						1.4.HALL(датчика Холла)[ESP32]
// Depending on the direction of the magnetic field, it generates values with a different sign.
//================================================================================================= 
struct RT_HW_PIN_HALL_ID{
uint8_t  dir=0;				//--Stage number in the executive function;  
int16_t  vPin;	    		//--Sensor value [hallRead()];
uint16_t vNorm;				//--vPin with normalization of the value to the system SYS with bit depth=device.depth.sys;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							2.STRUCTURES FOR OUTPUT TO PINS
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//								2.1.DO(discrete output)
//  RT_HW_PIN_DIR_ID - defined in the kernel description;
//=================================================================================================

//=================================================================================================
//								2.2.PWM(pulse width output)
//================================================================================================= 
struct RT_HW_PIN_PWM_ID{
uint8_t  dir=0;				//--Stage number in the executive function; 
uint8_t  pin=255;			//--Pin number;
uint8_t  channel=255;		//--Channel number[ESP32]
uint8_t  depth=255;			//--Bit depth PWM[ESP32]. If=255 then depth=device.depth.pwm;
uint16_t freq=1000;			//--Frequency;
char     mode='N';			//--Output type (N-normal, O-open collector);
//----------------------------------------------------------
uint8_t  idx;				//--Working index;
uint32_t var;				//--External direct;
uint16_t duration;			//--The value of the PWM pulse normalized to depth;
uint16_t duty;				//--The value written to the pin (taking into account the PWM bit depth);
};
//================================================================================================= 
//										2.3.DAC
//=================================================================================================  
struct RT_HW_PIN_DAC_ID{
uint8_t  dir=0;				//--Stage number in the executive function; 
uint8_t  pin=255;			//--Pin number;
uint16_t var;				//--Set value;
uint16_t vPin;				//--The value written to the pin;
};
//================================================================================================= 
//										2.4.SERVO
//=================================================================================================  
struct RT_HW_PIN_SERVO_ID{
uint8_t  custom=0;			//--Флаг настройки параметров;
uint8_t  dir=0;				//--Номер этапа управления вывода; 
uint8_t  pin=255;			//--Номер пина;
uint8_t  channel=4;			//--Channel number[ESP32]
uint8_t  depth=16;			//--Bit depth[ESP32];
uint16_t freq=50;			//--Frequency;
uint16_t maxAngle=180;		//--The maximum angle of rotation (-360,+360);
uint16_t minWidth=800;		//--Minimum pulse width(mcs);   
uint16_t maxWidth=2300;		//--Maximum pulse width(mcs);  
uint16_t maxDepth=0xFFFF;   //--Maximum value for the selected bit depth;
uint16_t period=20000;		//--Period of control pulses(calculated variable=1000000/freq); 
//-------------------------------
uint8_t  idx;				//--Working index;
uint16_t var;				//--External pulse duration setting;
uint16_t duration;			//--Estimated pulse duration;
uint16_t duty;				//--The value written to the device (taking into account the PWM bit depth);
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//					3.ADDITIONAL STRUCTURES FOR WORKING WITH PINS
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//						           3.1.Chatter protection
//=================================================================================================
struct RT_HW_CHATTER_DIN{uint32_t timeBegin; uint8_t dir=0; uint8_t ago=0;};	
struct RT_HW_CHAT_V8_ID {
uint8_t  dir=0;				//--Stage number in the executive function;  
uint8_t  ago=0;				//--The previous value of the monitored value; 
uint16_t period; 			//--Anti-bounce period;
uint32_t timeBegin;			//--Working register for working with time;
};
//=================================================================================================