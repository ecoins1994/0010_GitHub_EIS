 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.Константы в PROGMEM для отображения bool
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
//static const unsigned char  RT_HW_ARR_BOOL_SIGN_1[] PROGMEM= {'1', '+', '*', '#', '|', '>', '+', '*', '+', 255};  
//static const unsigned char  RT_HW_ARR_BOOL_SIGN_0[] PROGMEM= {'0', '-', ' ', ' ', '-', '<', '_', '_', ' ', ' '}; 
const char  RT_HW_ARR_BOOL_SIGN_1[] PROGMEM= {'1', '+', '*', '#', '|', '>', '+', '*', '+', (char)0xFF};  
const char  RT_HW_ARR_BOOL_SIGN_0[] PROGMEM= {'0', '-', ' ', ' ', '-', '<', '_', '_', ' ', ' '};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//    						2.Таблица для расчета контрольной суммы
// Dow-CRC using polynomial X^8 + X^5 + X^4 + X^0
// Tiny 2x16 entry CRC table created by Arjen Lentz
// See http://lentz.com.au/blog/calculating-crc-with-a-tiny-32-entry-lookup-table
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const uint8_t PROGMEM RT_HW_PGM_TABLE_CRC8_2X16[]= {
0x00, 0x5E, 0xBC, 0xE2, 0x61, 0x3F, 0xDD, 0x83,
0xC2, 0x9C, 0x7E, 0x20, 0xA3, 0xFD, 0x1F, 0x41,
0x00, 0x9D, 0x23, 0xBE, 0x46, 0xDB, 0x65, 0xF8,
0x8C, 0x11, 0xAF, 0x32, 0xCA, 0x57, 0xE9, 0x74
};

