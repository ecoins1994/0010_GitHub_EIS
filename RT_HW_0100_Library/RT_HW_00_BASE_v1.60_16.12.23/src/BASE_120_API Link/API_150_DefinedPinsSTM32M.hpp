//=================================================================================================
/*
		Для совместимости пинов STM32MASTER c пинами STM32DUINO

=====STM32F103x====================================================================================
Макросы::RT_HW_BOARD_STM32MASTER_F103CX,RT_HW_BOARD_STM32MASTER_F103RX, RT_HW_BOARD_STM32MASTER_F103RX
 variant.generic_stm32f103c::
 enum {
    PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13,PA14,PA15,
	PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13,PB14,PB15,
	PC13,PC14,PC15 };
 
 variant.generic_stm32f103r::
enum {
PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
PD0,PD1,PD2
};// Note PB2 is skipped as this is Boot1 and is not going to be much use as its likely to be pulled permanently low 
 
 variant.generic_stm32f103v::
enum {
PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,
}; 
=====STM32F401x====================================================================================
Макросы::RT_HW_BOARD_STM32MASTER_F401
variant.blackpill_f401
enum {
PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB12=(PB10+2),PB13,PB14,PB15,
PC13=(32+13),PC14,PC15,
BOARD_NR_GPIO_PINS
};
=====STM32F411x====================================================================================
Макросы::RT_HW_BOARD_STM32MASTER_F411
variant.disco_f411
enum {
PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,
BOARD_NR_GPIO_PINS
};
=====STM32F407x====================================================================================
Макросы::RT_HW_BOARD_STM32MASTER_F407V
variant.generic_f407v
enum {
PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,
#ifdef PACKAGE_LQFP144
PF0,PF1,PF2,PF3,PF4,PF5,PF6,PF7,PF8,PF9,PF10,PF11,PF12,PF13,PF14,PF15,
PG0,PG1,PG2,PG3,PG4,PG5,PG6,PG7,PG8,PG9,PG10,PG11,PG12,PG13,PG14,PG15,
#endif
BOARD_NR_GPIO_PINS
};
*/
//===================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F103CX)  ||\
    defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F103RX)  ||\
	defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F103VX)  ||\
    defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F401XX)  ||\
	defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F411XX)  ||\
	defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F407VX) 
#define PA0   0
#define PA1   1
#define PA2   2
#define PA3   3
#define PA4   4
#define PA5   5
#define PA6   6
#define PA7   7
#define PA8   8
#define PA9   9
#define PA10 10
#define PA11 11
#define PA12 12
#define PA13 13
#define PA14 14
#define PA15 15
#endif

#if defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F103CX) 
#define PB0  16
#define PB1  17
#define PB2  18
#define PB3  19
#define PB4  20
#define PB5  21
#define PB6  22
#define PB7  23
#define PB8  24
#define PB9  25
#define PB10 26
#define PB11 27
#define PB12 28
#define PB13 29
#define PB14 30
#define PB15 31
#define PC13 32
#define PC14 33
#define PC15 34
#endif

#if defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F401XX)|| defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F411XX)
#define PB0  16
#define PB1  17
#define PB2  18
#define PB3  19
#define PB4  20
#define PB5  21
#define PB6  22
#define PB7  23
#define PB8  24
#define PB9  25
#define PB10 26
#define PB12 28
#define PB13 29
#define PB14 30
#define PB15 31
#define PC13 45
#define PC14 46
#define PC15 47
#endif

#if defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F103RX) || defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F103VX) || defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F407VX) 
#define PB0  16
#define PB1  17
#define PB2  18
#define PB3  19
#define PB4  20
#define PB5  21
#define PB6  22
#define PB7  23
#define PB8  24
#define PB9  25
#define PB10 26
#define PB11 27
#define PB12 28
#define PB13 29
#define PB14 30
#define PB15 31
#define PC0  32
#define PC1  33
#define PC2  34
#define PC3  35
#define PC4  36
#define PC5  37
#define PC6  38
#define PC7  39
#define PC8  40
#define PC9  41
#define PC10 42
#define PC11 43
#define PC12 44
#define PC13 45
#define PC14 46
#define PC15 47
#endif

#if defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F103RX)
#define PD0 48
#define PD1 49
#define PD2 50
#endif

#if defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F103VX) || defined(RT_HW_STM32_ENABLE_DEFINE_PIN_F407VX) 
#define PD0  48
#define PD1  49
#define PD2  50
#define PD3  51
#define PD4  52
#define PD5  53
#define PD6  54
#define PD7  55
#define PD8  56
#define PD9  57
#define PD10 58
#define PD11 59
#define PD12 60
#define PD13 61
#define PD14 62
#define PD15 63
#define PE0  64
#define PE1  65
#define PE2  66
#define PE3  67
#define PE4  68
#define PE5  69
#define PE6  70
#define PE7  71
#define PE8  72
#define PE9  73
#define PE10 74
#define PE11 75
#define PE12 76
#define PE13 77
#define PE14 78
#define PE15 79
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++