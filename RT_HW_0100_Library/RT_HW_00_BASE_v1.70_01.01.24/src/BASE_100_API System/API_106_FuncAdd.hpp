//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//										ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================
//					Проверка на изменения значения с сохранением в буферe
//-------------------------------------------------------------------------------------------------
bool checkChangeVar(int8_t   &ago, int8_t   val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(uint8_t  &ago, uint8_t  val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar( int16_t &ago, int16_t  val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(uint16_t &ago, uint16_t val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(int32_t  &ago, int32_t  val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(uint32_t &ago, uint32_t val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(String   &ago, String   val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(float    &ago, float    val) {if(ago!=val) {ago=val;  return 1;} return 0;}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================
//					Ограничение переменных установленными границами mode[L,A,N]
// mode: 
// 'A' - всегда;
// 'L' - Если верхняя граница !=0 для верхней границы и если нижняя граница !=0 для нижней границы;
//-------------------------------------------------------------------------------------------------
uint8_t limitationVar(uint8_t  cur, uint8_t highLimit, uint8_t lowLimit, char mode='L'){
if(mode=='L'){if((highLimit!=0) && (cur>highLimit)){cur=highLimit;} if((lowLimit !=0) && (cur<lowLimit)) {cur=lowLimit;}	return cur;}
if(mode=='A'){                   if(cur>highLimit) {cur=highLimit;}                    if(cur<lowLimit)  {cur=lowLimit;}	return cur;}
return cur;}
//--------------------------------------------------------------------------------------------------
int16_t limitationVar(int16_t  cur, int16_t highLimit, int16_t lowLimit, char mode='L'){
if(mode=='L'){if((highLimit!=0) && (cur>highLimit)){cur=highLimit;} if((lowLimit !=0) && (cur<lowLimit)) {cur=lowLimit;}	return cur;}
if(mode=='A'){                   if(cur>highLimit) {cur=highLimit;}                    if(cur<lowLimit)  {cur=lowLimit;}	return cur;}
return cur;}
//-------------------------------------------------------------------------------------------------
int32_t limitationVar(int32_t  cur, int32_t highLimit, int32_t lowLimit, char mode='L'){
if(mode=='L'){if((highLimit!=0) && (cur>highLimit)){cur=highLimit;} if((lowLimit !=0) && (cur<lowLimit)) {cur=lowLimit;}	return cur;}
if(mode=='A'){                   if(cur>highLimit) {cur=highLimit;}                    if(cur<lowLimit)  {cur=lowLimit;}	return cur;}
return cur;}
//-------------------------------------------------------------------------------------------------
float limitationVar(float  cur, float highLimit, float lowLimit, char mode='L'){
if(mode=='L'){if((highLimit!=0) && (cur>highLimit)){cur=highLimit;} if((lowLimit !=0) && (cur<lowLimit)) {cur=lowLimit;}	return cur;}
if(mode=='A'){                   if(cur>highLimit) {cur=highLimit;}                    if(cur<lowLimit)  {cur=lowLimit;}	return cur;}
return cur;}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================
//							//==Расчет CRC8 (Dallas Semiconductor 8 bit CRC);
//=================================================================================================
uint8_t crc8(const uint8_t* addr,  uint8_t len){											
uint8_t crc = 0;
while (len--) {crc = *addr++ ^ crc;  crc = pgm_read_byte(RT_HW_PGM_TABLE_CRC8_2X16 + (crc & 0x0f)) ^ pgm_read_byte(RT_HW_PGM_TABLE_CRC8_2X16 + 16 + ((crc >> 4) & 0x0f));}
return crc;}
//=================================================================================================
//							Расчет CRC16;
//=================================================================================================
uint16_t crc16(const uint8_t* input, uint16_t len, uint16_t crc){								
  static const uint8_t oddparity[16] ={ 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 };
  for (uint16_t i=0; i<len; i++) {uint16_t cdata = input[i]; cdata = (cdata ^ crc) & 0xff; crc >>= 8;
                                  if (oddparity[cdata & 0x0F] ^ oddparity[cdata >> 4]) {crc ^= 0xC001;}
								  cdata <<= 6; crc ^= cdata; cdata <<= 1; crc ^= cdata; }
return crc;}
//=================================================================================================
//								Проверка CRC16
//=================================================================================================
bool check_crc16(const uint8_t* input, uint16_t len, const uint8_t* inverted_crc, uint16_t crc){
 crc = ~crc16(input, len, crc); return (crc & 0xFF) == inverted_crc[0] && (crc >> 8) == inverted_crc[1];}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++