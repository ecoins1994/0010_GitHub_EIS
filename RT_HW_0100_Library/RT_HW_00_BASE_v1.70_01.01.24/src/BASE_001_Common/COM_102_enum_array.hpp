//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.Индексы массивов хранящихся в PGM
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
enum{RT_HW_PGM_PIN_ALL_ID,	RT_HW_PGM_PIN_DIN_ID, 	RT_HW_PGM_PIN_ADC_ID,  	RT_HW_PGM_PIN_TCH_ID, 
     RT_HW_PGM_PIN_DOT_ID,	RT_HW_PGM_PIN_PWM_ID,	RT_HW_PGM_PIN_DAC_ID,	
	 RT_HW_PGM_PIN_INT_ID,  RT_HW_PGM_PIN_N5V_ID,
//-------------------------------------------------------------------------------------------------
	 RT_HW_PGM_PIN_UHS_ID,	RT_HW_PGM_PIN_USS_ID,   RT_HW_PGM_PIN_I2C_ID, 	
	 RT_HW_PGM_PIN_SPI_ID,  RT_HW_PGM_PIN_SPF_ID,   RT_HW_PGM_PIN_SDC_ID, RT_HW_PGM_PIN_SPN_ID,
	 RT_HW_PGM_PIN_ETH_ID,  RT_HW_PGM_PIN_CAN_ID,
//-------------------------------------------------------------------------------------------------
	 RT_HW_PGM_PIN_BRD_ID,	RT_HW_PGM_PIN_CSX_ID, 	
	 RT_HW_PGM_PIN_LC4_ID, 	RT_HW_PGM_PIN_LC6_ID,   RT_HW_PGM_PIN_TFT_ID,	
//-------------------------------------------------------------------------------------------------
	 RT_HW_PGM_TST_DIS_ID,	RT_HW_PGM_TST_ANL_ID,   RT_HW_PGM_TST_SRV_ID,   
	 RT_HW_PGM_TST_DEV_ID, 	RT_HW_PGM_TST_URT_ID,
//-------------------------------------------------------------------------------------------------	 
	 RT_HW_PGM_QNT_ID,		RT_HW_PGM_END=254};  //--RT_HW_PGM_END=254 - Должно быть последним; 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						Константы в PROGMEM для отображения bool
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
static const unsigned char  RT_HW_ARR_BOOL_SIGN_1[] PROGMEM= {'1', '+', '*', '#', '|', '>', '+', '*', '+', 255};  
static const unsigned char  RT_HW_ARR_BOOL_SIGN_0[] PROGMEM= {'0', '-', ' ', ' ', '-', '<', '_', '_', ' ', ' '}; 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//    Таблица для расчета контрольной суммы
// Dow-CRC using polynomial X^8 + X^5 + X^4 + X^0
// Tiny 2x16 entry CRC table created by Arjen Lentz
// See http://lentz.com.au/blog/calculating-crc-with-a-tiny-32-entry-lookup-table
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static const uint8_t PROGMEM RT_HW_PGM_TABLE_CRC8_2X16[]= {
0x00, 0x5E, 0xBC, 0xE2, 0x61, 0x3F, 0xDD, 0x83,
0xC2, 0x9C, 0x7E, 0x20, 0xA3, 0xFD, 0x1F, 0x41,
0x00, 0x9D, 0x23, 0xBE, 0x46, 0xDB, 0x65, 0xF8,
0x8C, 0x11, 0xAF, 0x32, 0xCA, 0x57, 0xE9, 0x74
};

