//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								СИСТЕМНЫЕ ФУНКЦИИ ОБЩИЕ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//=================================================================================================
//				Функции нормализации значений ADC,PWW,DAC до системного значения 
//=================================================================================================	
uint16_t maxBitDepthSys (){return ((1<<device.depth.sys)-1);};		 //-return	max var разрядности 1:16 для системной разрядности;
uint16_t maxBitDepth (uint8_t &depth){if(depth>=16) {return 0xFFFF;} if(depth==0){return 0;} return ((1<<depth)-1);}; //-return	max var разрядности 1:16;
uint16_t normADC(uint16_t v){return map(v,0,maxBitDepth(device.depth.adc),0,maxBitDepth(device.depth.sys));}; //--нормализация для ADC;
uint16_t normPWM(uint16_t v){return map(v,0,maxBitDepth(device.depth.sys),0,maxBitDepth(device.depth.pwm));}; //--нормализация для PWM;
uint16_t normDAC(uint16_t v){return map(v,0,maxBitDepth(device.depth.sys),0,maxBitDepth(device.depth.dac));}; //--нормализация для DAC;
uint16_t normDepth(uint16_t v,uint8_t depth){if(depth>16){depth=16;} 										  //--нормализация системного сигнала SYS ;
                             return map(v,0,maxBitDepth(device.depth.sys),0,maxBitDepth(depth));};			   			
uint16_t normDepthFull(uint16_t v,uint8_t inDepth, uint8_t outDepth){if(inDepth>16){inDepth=16;} if(outDepth>16){outDepth=16;}	//--универсальный норматизатор;  
		                     return map(v,0,maxBitDepth(inDepth),0,maxBitDepth(outDepth));};;
//=================================================================================================
//				Функции гистерезиса меняют значение var на cur при его отклонение на delta) 
//=================================================================================================	
uint16_t makeDelta(uint16_t &var, uint16_t cur, uint8_t delta){			
  if(cur>var){if((cur-var)>delta){var=cur;}} 
  if(cur<var){if((var-cur)>delta){var=cur;}} return var;} 
//=================================================================================================
//						Обмен битов uint8_t
//=================================================================================================
uint8_t changeBitByte(uint8_t val){
return((val&0x01)<<7)|((val&0x02)<<5)|((val&0x04)<<3)|((val&0x08)<<1)|((val&0x10)>>1)|((val&0x20)>>3)|((val&0x40)>>5)|((val&0x80)>>7);};	  
//=================================================================================================
//						Обмен битов uint16_t
//=================================================================================================
uint16_t changeBitWord(uint16_t val){
return((val&0x0001)<<15)|((val&0x0002)<<13)|((val&0x0004)<<11)|((val&0x0008)<<9)|((val&0x0010)<<7)|((val&0x0020)<<5)|((val&0x0040)<<3) | ((val&0x0080)<<1) |
      ((val&0x8000)>>15)|((val&0x4000)>>13)|((val&0x2000)>>11)|((val&0x1000)>>9)|((val&0x0800)>>7)|((val&0x0400)>>5)|((val&0x0200)>>3) | ((val&0x0100)>>1);}                                     
//=================================================================================================
//						Reverse bit v8
//=================================================================================================
inline uint8_t reverseV8(uint8_t b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;}
//=================================================================================================
//						Reverse bit v16
//=================================================================================================
//  uint16_t x = _dataOut;                              //  x = 0123456789ABCDEF
//  x = (((x & 0xAAAA) >> 1) | ((x & 0x5555) << 1));    //  x = 1032547698BADCFE
//  x = (((x & 0xCCCC) >> 2) | ((x & 0x3333) << 2));    //  x = 32107654BA98FEDC
//  x = (((x & 0xF0F0) >> 4) | ((x & 0x0F0F) << 4));    //  x = 76543210FEDCBA98
//  x = (x >> 8) | ( x << 8);                           //  x = FEDCBA9876543210
uint16_t reverseV16(uint16_t v) {//uint8_t v0=v & 0xFF; uint8_t v1=(v>>8) & 0xFF; 
return ((reverseV8(v & 0xFF)<< 8) | reverseV8((v>>8) & 0xFF));}
//=================================================================================================
//						Reverse bit v24
//=================================================================================================
uint32_t reverseV24(uint32_t v) {uint8_t v0=v & 0xFF; uint8_t v1=(v>>8) & 0xFF; uint8_t v2=(v>>16) & 0xFF; 
return (                                    (((uint32_t)reverseV8(v0))<<16) | (((uint32_t)reverseV8(v1))<< 8) | reverseV8(v2));}
//=================================================================================================
//						Reverse bit v32
//=================================================================================================
uint32_t reverseV32(uint32_t v) {uint8_t v0=v & 0xFF; uint8_t v1=(v>>8) & 0xFF; uint8_t v2=(v>>16) & 0xFF; uint8_t v3=(v>>24) & 0xFF; 
return ((((uint32_t)reverseV8(v0))<<24) | (((uint32_t)reverseV8(v1))<<16) | (((uint32_t)reverseV8(v2))<< 8) | reverseV8(v3));}
//=================================================================================================
//						Извлечение цифры из числа
//=================================================================================================
char 	 getCharVal(uint32_t val,uint8_t upper,char mode,uint8_t len,uint8_t n){//==Возвращает цифру(как символ) из val начиная со старшей позиции;
//---mode B,b,H,h,D,I,0,1,2,3,T; upper =0 верхний регистр, =1 нижний регистр;
uint32_t buff32=0;
if((mode=='B') || (mode=='b')) {buff32=(val>>(len-n))&1;}
if((mode=='H') || (mode=='h')) {buff32=(val>>(len-n)*4)&0xf;}
if((mode=='D') || (mode=='I') ||(mode=='U')|| (mode=='0') ||(mode=='1') ||(mode=='2') || (mode=='3') || (mode=='T')) 
                                        {n=len-n+1; while(n!=0) {buff32=val; val/=10; buff32=buff32-(val*10); n--;};}
if(buff32<=9) {buff32=buff32 +'0';} else {buff32=buff32-10+(upper ? 'A' : 'a') ;}
return (uint8_t)buff32;}; 
//=================================================================================================
//							Поиск номера первого свободного бита в регистре состояний						
// Возвращает номер первого свободного бита (0:15) или -1;	
//=================================================================================================
int8_t getFistFreeBit    (uint16_t &reg, uint8_t maxNum=15){
 if(maxNum>16) {return -1;} for(uint8_t i=0;i<maxNum;i++){if(!bitRead(reg,i)) return i;} return -1;};
//=================================================================================================
//		Функции поиска и захвата первый свободный бит в регистре состояний						
// Возвращает номер первого свободного бита (0:15) или -1;	
//=================================================================================================
int8_t setFirstFreeBit   (uint16_t &reg, uint8_t maxNum=15){
if(maxNum>16) {return -1;} for(uint8_t i=0;i<maxNum;i++){if(!bitRead(reg,i)) {bitSet(reg,i); return i;}} return -1;};	
//=================================================================================================
//							Проверяет занятость в reg номера бита num(0:15) 
// при ограничении его номера maxNum(if(num>max){return 0;}; 					
// Возвращает номер первого свободного бита (0:15) или -1;	
//=================================================================================================
bool checkBusyNumBit   (uint16_t &reg, uint8_t num, uint8_t maxNum=15){if(maxNum>16) {return 0;} return bitRead(reg,num);};		
//=================================================================================================
//							Занимает в reg номер первого свободного устройства(1:16) и возращает его номер или 0; 								
//=================================================================================================
uint8_t  setFistFreeDevice (uint16_t &reg, uint8_t maxNum=16){				//==Занимает в reg номер первого свободного устройства(1:16) и возращает его номер или 0; 	
 if((maxNum>16) || (maxNum==0)) {return 0;} 
 for(uint8_t i=1;i<=maxNum;i++){if(!bitRead(reg,(i-1))) {bitSet(reg,(i-1)); return i;}} return 0;};	
//=================================================================================================
//							Занимает в reg номер первого свободного устройства(1:16) и возращает его номер или 0; 
//==Проверяет занятость номера устройства(1:16); 								
//=================================================================================================	
bool  checkBusyNumDevice(uint16_t &reg, uint8_t num, uint8_t maxNum=16) {if((maxNum>16) || (num==0)) {return 0;} return bitRead(reg,(num-1));};	
//=================================================================================================
//							Проверка кодов архитектуры, платы
//=================================================================================================
bool checkArch (uint8_t codeArch) {if(device.board.codeArch ==codeArch) {return 1;} else {return 0;}}; //--Проверка кода архитектуры;
bool checkBoard(uint8_t codeBoard){if(device.board.codeBoard==codeBoard){return 1;} else {return 0;}}; //--Проверка кода платы;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//				ФУНКЦИИ ДЛЯ РАБОТЫ МАССИВАМИ PGM БИБЛИОТЕКИ RT_HW_BASE.h(kind - тип массива)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//			   			Получение 3-x символьного имени массива
//=================================================================================================	
String getNameKindPin(uint8_t kind){
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_ALL_ID) {return String(F("ALL"));}	
if(kind==RT_HW_PGM_PIN_DIN_ID) {return String(F("DIN"));}
if(kind==RT_HW_PGM_PIN_ADC_ID) {return String(F("ADC"));}
if(kind==RT_HW_PGM_PIN_TCH_ID) {return String(F("TCH"));}	
if(kind==RT_HW_PGM_PIN_DOT_ID) {return String(F("DOT"));}
if(kind==RT_HW_PGM_PIN_PWM_ID) {return String(F("PWM"));}
if(kind==RT_HW_PGM_PIN_DAC_ID) {return String(F("DAC"));}
if(kind==RT_HW_PGM_PIN_INT_ID) {return String(F("INT"));} 
if(kind==RT_HW_PGM_PIN_N5V_ID) {return String(F("N5V"));}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_UHS_ID) {return String(F("UHS"));}	
if(kind==RT_HW_PGM_PIN_USS_ID) {return String(F("USS"));}	
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_I2C_ID) {return String(F("I2C"));}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_SPI_ID) {return String(F("SPI"));}
if(kind==RT_HW_PGM_PIN_SPF_ID) {return String(F("SPF"));}
if(kind==RT_HW_PGM_PIN_SDC_ID) {return String(F("SDC"));}
if(kind==RT_HW_PGM_PIN_SPN_ID) {return String(F("SPN"));}	
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_ETH_ID) {return String(F("ETH"));}
if(kind==RT_HW_PGM_PIN_CAN_ID) {return String(F("CAN"));}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_BRD_ID) {return String(F("BRD"));}	
if(kind==RT_HW_PGM_PIN_CSX_ID) {return String(F("CSX"));}
//-------------------------------------------------------------------------------------------------	
if(kind==RT_HW_PGM_PIN_LC4_ID) {return String(F("LC4"));}	
if(kind==RT_HW_PGM_PIN_LC6_ID) {return String(F("LC6"));}	
if(kind==RT_HW_PGM_PIN_TFT_ID) {return String(F("TFT"));}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_TST_DIS_ID) {return String(F("DIS"));}	
if(kind==RT_HW_PGM_TST_ANL_ID) {return String(F("ANL"));}	
if(kind==RT_HW_PGM_TST_SRV_ID) {return String(F("SRV"));}
if(kind==RT_HW_PGM_TST_DEV_ID) {return String(F("DEV"));}
if(kind==RT_HW_PGM_TST_URT_ID) {return String(F("URT"));}
//-------------------------------------------------------------------------------------------------
return String(F(" - "));  };
//=================================================================================================
//			   			Получение значения из массива по типу и индексу
//=================================================================================================	
uint8_t  getFromArrPGM (uint8_t kind, uint8_t n){
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_ALL_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_ALL,n);}
if(kind==RT_HW_PGM_PIN_DIN_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_DIN,n);}
if(kind==RT_HW_PGM_PIN_ADC_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_ADC,n);}
if(kind==RT_HW_PGM_PIN_TCH_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_TCH,n);}
if(kind==RT_HW_PGM_PIN_DOT_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_DOT,n);}
if(kind==RT_HW_PGM_PIN_PWM_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_PWM,n);}
if(kind==RT_HW_PGM_PIN_DAC_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_DAC,n);}
if(kind==RT_HW_PGM_PIN_INT_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_INT,n);}
if(kind==RT_HW_PGM_PIN_N5V_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_N5V,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_UHS_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_UHS,n);}
if(kind==RT_HW_PGM_PIN_USS_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_USS,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_I2C_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_I2C,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_SPI_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_SPI,n);}
if(kind==RT_HW_PGM_PIN_SPF_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_SPF,n);}
if(kind==RT_HW_PGM_PIN_SDC_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_SDC,n);}
if(kind==RT_HW_PGM_PIN_SPN_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_SPN,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_ETH_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_ETH,n);}
if(kind==RT_HW_PGM_PIN_CAN_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_CAN,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_BRD_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_BRD,n);}
if(kind==RT_HW_PGM_PIN_CSX_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_CSX,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_PIN_LC4_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_LC4,n);}
if(kind==RT_HW_PGM_PIN_LC6_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_LC6,n);}
if(kind==RT_HW_PGM_PIN_TFT_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_PIN_TFT,n);}
//-------------------------------------------------------------------------------------------------
if(kind==RT_HW_PGM_TST_DIS_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_TST_DIS,n);}
if(kind==RT_HW_PGM_TST_ANL_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_TST_ANL,n);}
if(kind==RT_HW_PGM_TST_SRV_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_TST_SRV,n);}
if(kind==RT_HW_PGM_TST_DEV_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_TST_DEV,n);}
if(kind==RT_HW_PGM_TST_URT_ID)	{return RT_HW_READ_BYTE_PGM(RT_HW_PGM_TST_URT,n);}
//-------------------------------------------------------------------------------------------------
return 0;}	
//=================================================================================================
//			   			Получение значения из массива по типу и индексу
//					    с контролем размера массива. Если элемент не найден, возвращаетя 255.
//=================================================================================================	
uint8_t readArrPGM(uint8_t kind, uint8_t n){
uint8_t len=0;
for(uint8_t i=0; i<254; i++){if(getFromArrPGM(kind,i)==RT_HW_PGM_END){break;} len++;} ;
if(n>=len) {return 255;} 
return getFromArrPGM(kind,n);};
//=================================================================================================
//						Проверяет наличие в массиве пина равным n
//=================================================================================================
bool checkPinPGM(uint8_t kind, uint8_t n){
for(uint8_t i=0; i<254; i++){uint8_t k=getFromArrPGM(kind,i); if(k==RT_HW_PGM_END) {return  0;} if((k!=255)&&(k==n)){return 1;}} return 0;};
//=================================================================================================
//							Возвращает полный размер массива
//=================================================================================================
uint8_t getLenFullPGM (uint8_t kind){uint8_t cnt=0;
for(uint8_t i=0; i<254; i++){uint8_t k=getFromArrPGM(kind,i); if(k==RT_HW_PGM_END){break;}                  cnt++;} return cnt;};
//=================================================================================================
//							Возвращает кол-во допустимых элементов (!=255) в массиве
//=================================================================================================
uint8_t getLenPosPGM  (uint8_t kind){uint8_t cnt=0;	
for(uint8_t i=0; i<254; i++){uint8_t k=getFromArrPGM(kind,i); if(k==RT_HW_PGM_END){break;}     if(k!=255) {cnt++;}} return cnt;};	
//==================================================================================================
