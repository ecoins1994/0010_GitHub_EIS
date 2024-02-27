//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//				1.ФУНКЦИИ ПОЛУЧЕНИЕ ЧИСЛОВЫХ ПАРАМЕТРОВ ПРОЦЕССОРА
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint8_t vArchCode(){				//--Код архитектуры MCU (в файлах Select_XXX);	
#if defined(RT_HW_ARCH_CODE) 					
    return  RT_HW_ARCH_CODE;  
#else
	return 255;
#endif
};
//-------------------------------------------------------------------------------------------------
uint8_t vBoardCode(){				//--Код платы (в файлах Select_XXX);	
#if defined(RT_HW_BOARD_CODE) 					
    return  RT_HW_BOARD_CODE;  
#else
	return 255;
#endif
};
//-------------------------------------------------------------------------------------------------
uint16_t vFCPU(){					//--Частота процессора (в файлах Select_XXX);	
#if defined(RT_HW_BOARD_FCPU) 					
    return  RT_HW_BOARD_FCPU;  
#else
	return 16;
#endif
};
//-------------------------------------------------------------------------------------------------
uint16_t vVcc(){					//--Напряжение процессора (в файлах Select_XXX);	
#if defined(RT_HW_BOARD_VCC) 					
    return  RT_HW_BOARD_VCC;  
#else
	return 255;
#endif
};
//-------------------------------------------------------------------------------------------------
uint8_t vDepthSYS(){				//--Системная разрядность переменных для обмена между устройствами;	
#if defined(RT_HW_BOARD_DEPTH_SYS) 					
    return  RT_HW_BOARD_DEPTH_SYS;  
#else
	return  12;
#endif
};
//-------------------------------------------------------------------------------------------------
uint8_t vDepthPWM(){				//--Разрядность PWM(default);	
#if defined(RT_HW_BOARD_DEPTH_PWM) 					
    return  RT_HW_BOARD_DEPTH_PWM;  
#else
	return  10;
#endif
};
//-------------------------------------------------------------------------------------------------
uint8_t vDepthADC(){				//--Разрядность ADC(default);	
#if defined(RT_HW_BOARD_DEPTH_ADC) 					
    return  RT_HW_BOARD_DEPTH_ADC;  
#else
	return  10;
#endif
};
//-------------------------------------------------------------------------------------------------
uint8_t vDriftADC(){				//--ADC дрейф показаний;	
#if defined(RT_HW_BOARD_DRIFT_ADC) 					
    return  RT_HW_BOARD_DRIFT_ADC;  
#else
	return  10;
#endif
};
//-------------------------------------------------------------------------------------------------
uint8_t vNullADC(){				//--ADC дрейф нуля;	
#if defined(RT_HW_BOARD_NULL_ADC) 					
    return  RT_HW_BOARD_NULL_ADC;  
#else
	return  10;
#endif
};
//-------------------------------------------------------------------------------------------------
uint8_t vDepthDAC(){				//--Разрядность DAC(default);	
#if defined(RT_HW_BOARD_DEPTH_DAC) 					
    return  RT_HW_BOARD_DEPTH_DAC;  
#else
	return  8;
#endif
};
//-------------------------------------------------------------------------------------------------
uint8_t vDepthTCH(){				//--Разрядность TOUCH(default);	
#if defined(RT_HW_BOARD_DEPTH_TCH) 					
    return  RT_HW_BOARD_DEPTH_TCH;  
#else
	return  10;
#endif
};
